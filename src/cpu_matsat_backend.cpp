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

#include "cpu_matsat_backend.hpp"

#include "cpu_matsat_funcs.hpp"

#include <random>
#include <vector>

namespace sat4gpu {

    void CpuMatsatBackend::configure(const class Solver &solver) {
        const int n = solver.num_vars();
        const int m = solver.num_clauses();

        MatSat::build_matrix_Q(solver.clauses(), n, solver.num_lits(), m_Q);
        MatSat::build_matrix_Q2_Q1_T(solver.clauses(), n, solver.num_lits(), m_Q2_Q1_T);

        m_u.resize(n);
        m_u_tilda.resize(n);
        m_u_tilda_new.resize(n);
        m_J_sat_acb.resize(n);
        m_Q_u_tilda_d.resize(m);
    }

    Solution CpuMatsatBackend::solve(int timeout) {
        std::default_random_engine engine(m_uniform_seed);

        MatSat::randomize_vec_uniform(1.0f, engine, m_u_tilda);

        for (int p = 0; p < m_max_try; p++) {
            for (int q = 0; q < m_max_itr; q++) {
                MatSat::eval_matvec_Q_u_tilda_d(m_Q, m_u_tilda, m_Q_u_tilda_d);
                MatSat::eval_J_sat(m_u_tilda, m_Q, m_Q_u_tilda_d, m_l, m_J_sat);              // J_sat by (1)
                MatSat::eval_J_sat_acb(m_Q2_Q1_T, m_u_tilda, m_Q_u_tilda_d, m_l, m_J_sat_acb);// J_sat_acb by (2)
                MatSat::eval_u_tilda_new(m_u_tilda, m_J_sat_acb, m_J_sat, m_u_tilda_new);     // update u~ by (3)

                std::swap(m_u_tilda, m_u_tilda_new);

                MatSat::eval_matvec_Q_u_d_min_error(m_Q, m_u_tilda, m_theta_slice, m_u, m_error);// threshold u~ to binary vector u, compute error

                if (m_error == 0) {
                    Solution solution;
                    solution.conclusion = Conclusion::Satisfiable;
                    solution.model = m_u.to_bool();
                    return solution;
                }
            }

            MatSat::randomize_vec_uniform(m_beta, engine, m_u_tilda);// % 0 <= beta <= 1, rnd ~ U(0,1)
        }

        return Solution{};
    }

    BackendType CpuMatsatBackend::backend_type() const {
        return BackendType::CpuMatsat;
    }
    std::shared_ptr<Backend> CpuMatsatBackend::instantiate() const {
        return std::make_shared<CpuMatsatBackend>();
    }

}// namespace sat4gpu