////////////////////////////////////////////////////////////////////////////////////
// MIT License                                                                    //
//                                                                                //
// Copyright (c) 2023 Egor Orachyov                                               //
//                                                                                //
// Permission is hereby granted, free of charge, to any person obtaining a copy   //
// of this software and associated documentation files (the "Software"), to deal  //
// in the Software without restriction, including without limitation the rights   //
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      //
// copies of the Software, and to permit persons to whom the Software is          //
// furnished to do so, subject to the following conditions:                       //
//                                                                                //
// The above copyright notice and this permission notice shall be included in all //
// copies or substantial portions of the Software.                                //
//                                                                                //
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     //
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       //
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    //
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         //
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  //
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  //
// SOFTWARE.                                                                      //
////////////////////////////////////////////////////////////////////////////////////

#include "cpu_matsat_funcs.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>

namespace sat4gpu {

    void MatSat::build_matrix_Q(const std::vector<Clause> &clauses, int num_vars, int num_lits, CpuMat &Q) {
        const int n = num_vars;
        const int m = int(clauses.size());

        Q.resize(m, 2 * n, num_lits);

        int write_index = 0;

        for (int i = 0; i < m; i++) {
            const Clause &clause = clauses[i];
            Q.row_ptr[i] = write_index;

            for (const Lit &lit: clause) {
                Q.cols[write_index] = lit.var().id + (lit.sign() == Sign::Negative ? n : 0);
                write_index += 1;
            }
        }

        assert(write_index == num_lits);

        Q.row_ptr[m] = write_index;
    }

    void MatSat::build_matrix_Q2_Q1_T(const std::vector<Clause> &clauses, int num_vars, int num_lits, CpuMatBit &Q2_Q1_T) {
        const int m = int(clauses.size());
        const int n = num_vars;

        std::vector<int> row_sizes(n + 1, 0);

        for (int i = 0; i < m; i++) {
            const Clause &clause = clauses[i];

            for (const Lit &lit: clause) {
                row_sizes[lit.var().id] += 1;
            }
        }

        Q2_Q1_T.resize(n, m, num_lits);

        std::exclusive_scan(row_sizes.begin(), row_sizes.end(), Q2_Q1_T.row_ptr.begin(), 0);

        std::vector<int> row_offsets = Q2_Q1_T.row_ptr;

        for (int i = 0; i < m; i++) {
            const Clause &clause = clauses[i];

            for (const Lit &lit: clause) {
                const int var_id = lit.var().id;
                const int var_sign = lit.sign() == Sign::Positive ? 0 : 1;

                Q2_Q1_T.cols[row_offsets[var_id]] = i;
                Q2_Q1_T.set(row_offsets[var_id], var_sign);

                row_offsets[var_id] += 1;
            }
        }

        assert(Q2_Q1_T.row_ptr[n] == num_lits);
    }

    void MatSat::eval_vec_norm_F_2(const CpuVec &v, float &v_norm_F_2) {
        const int n = v.n_rows;

        v_norm_F_2 = 0.0f;

        for (int i = 0; i < n; i++) {
            const float u_i = v.val[i];
            const float u_i_2 = u_i * u_i;

            v_norm_F_2 += u_i_2;
        }
    }

    void MatSat::eval_matvec_Q_u_tilda_d(const CpuMat &Q, const CpuVec &u_tilda, CpuVec &Q_u_tilda_d) {
        const int n = u_tilda.n_rows;
        const int m = Q.n_rows;

        assert(Q_u_tilda_d.n_rows == m);

        for (int i = 0; i < m; i++) {
            float accum = 0.0f;

            for (int k = Q.row_ptr[i]; k < Q.row_ptr[i + 1]; k++) {
                const int col_id = Q.cols[k];
                const float u_val = col_id < n ? u_tilda.val[col_id] : 1.0f - u_tilda.val[col_id % n];

                accum += u_val;
            }

            Q_u_tilda_d.val[i] = accum;
        }
    }

    void MatSat::eval_J_sat(const CpuVec &u_tilda, const CpuMat &Q, const CpuVec &Q_u_tilda_d, float l, float &J_sat) {
        const int n = u_tilda.n_rows;
        const int m = Q.n_rows;

        assert(Q_u_tilda_d.n_rows == m);

        float u_norm_2 = 0;

        for (int i = 0; i < n; i++) {
            const float hadamar_u_i = u_tilda.val[i] * (1.0f - u_tilda.val[i]);
            const float hadamar_u_i_2 = hadamar_u_i * hadamar_u_i;

            u_norm_2 += hadamar_u_i_2;
        }

        float all_sat = 0.0f;

        for (int i = 0; i < m; i++) {
            all_sat += 1.0f - std::min(Q_u_tilda_d.val[i], 1.0f);
        }

        J_sat = all_sat + (l / 2.0f) * u_norm_2;
    }

    void MatSat::eval_J_sat_acb(const CpuMatBit &Q2_Q1_T, const CpuVec &u_tilda, const CpuVec &Q_u_tilda_d, float l, CpuVec &J_sat_acb) {
        const int n = Q2_Q1_T.n_rows;
        const int m = Q2_Q1_T.n_cols;

        assert(u_tilda.n_rows == n);
        assert(Q_u_tilda_d.n_rows == m);
        assert(J_sat_acb.n_rows == n);

        for (int i = 0; i < n; i++) {
            float accum = 0.0f;

            for (int k = Q2_Q1_T.row_ptr[i]; k < Q2_Q1_T.row_ptr[i + 1]; k++) {
                const int col_id = Q2_Q1_T.cols[k];
                const Sign lit_sign = Q2_Q1_T.get(k) == 0 ? Sign::Positive : Sign::Negative;
                const float left = lit_sign == Sign::Positive ? -1.0f : 1.0f;
                const float right = Q_u_tilda_d.val[col_id] < 1.0f ? 1.0f : 0.0f;

                accum += left * right;
            }

            J_sat_acb.val[i] = accum;
        }

        for (int i = 0; i < n; i++) {
            const float u_i = u_tilda.val[i];
            const float one_minus_u_i = 1.0f - u_i;
            const float one_minus_2_u_i = 1.0f - 2 * u_i;

            J_sat_acb.val[i] += l * u_i * one_minus_u_i * one_minus_2_u_i;
        }
    }

    void MatSat::eval_u_tilda_new(const CpuVec &u_tilda, const CpuVec &J_sat_acb, const float J_sat, CpuVec &u_tilda_new) {
        const int n = u_tilda.n_rows;

        assert(u_tilda_new.n_rows == n);
        assert(J_sat_acb.n_rows == n);

        float J_sat_acb_F_2 = 0.0f;

        eval_vec_norm_F_2(J_sat_acb, J_sat_acb_F_2);

        const float J_sat_div_J_sat_acb_F_2 = J_sat / J_sat_acb_F_2;

        for (int i = 0; i < n; i++) {
            const float u_i = u_tilda.val[i];
            const float J_sat_acb_i = J_sat_acb.val[i];

            u_tilda_new.val[i] = u_i - J_sat_div_J_sat_acb_F_2 * J_sat_acb_i;
        }
    }

    void MatSat::eval_u_by_u_tilda(const CpuVec &u_tilda, float theta, CpuVecBit &u) {
        const int n = u_tilda.n_rows;

        assert(u.n_rows == n);

        for (int i = 0; i < n; i++) {
            const int bit = u_tilda.val[i] < theta ? 0 : 1;
            u.set(i, bit);
        }
    }

    void MatSat::eval_matvec_Q_u_d_error(const CpuMat &Q, const CpuVecBit &u, int &error) {
        const int n = u.n_rows;
        const int m = Q.n_rows;

        error = 0;

        for (int i = 0; i < m; i++) {
            int clause_i_sat = 0;

            for (int k = Q.row_ptr[i]; k < Q.row_ptr[i + 1] && clause_i_sat == 0; k++) {
                const int col_id = Q.cols[k];
                const int u_val = u.get(col_id % n);

                const bool is_clause_i_sat = (col_id < n) && (u_val == 1) || (col_id >= n) && (u_val == 0);

                clause_i_sat = is_clause_i_sat ? 1 : 0;
            }

            error += 1 - clause_i_sat;
        }
    }

    void MatSat::eval_matvec_Q_u_d_min_error(const CpuMat &Q, const CpuVec &u_tilda, float theta_slice, CpuVecBit &u, int &error) {
        const int n = u_tilda.n_rows;
        const int m = Q.n_rows;

        float u_tilda_min = u_tilda.val[0];
        float u_tilda_max = u_tilda.val[0];

        for (int i = 1; i < n; i++) {
            u_tilda_min = std::min(u_tilda_min, u_tilda.val[i]);
            u_tilda_max = std::max(u_tilda_max, u_tilda.val[i]);
        }

        const float delta = u_tilda_max - u_tilda_min;
        const float step = delta / theta_slice;

        float theta = u_tilda_min;

        int min_error = m + 1;
        float min_theta = theta;

        while (theta < u_tilda_max && min_error > 0) {
            eval_u_by_u_tilda(u_tilda, theta, u);
            eval_matvec_Q_u_d_error(Q, u, error);

            if (error < min_error) {
                min_error = error;
                min_theta = theta;
            }

            theta += step;
        }

        eval_u_by_u_tilda(u_tilda, min_theta, u);
    }

    void MatSat::randomize_vec_uniform(float beta, std::default_random_engine &engine, CpuVec &v) {
        const int n = v.n_rows;
        const std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

        for (int i = 0; i < n; i++) {
            v.val[i] = (1.0f - beta) * v.val[i] + beta * distribution(engine);
        }
    }

}// namespace sat4gpu