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

#ifndef SAT4GPU_CPU_MATSAT_FUNCS_HPP
#define SAT4GPU_CPU_MATSAT_FUNCS_HPP

#include "backend.hpp"
#include "clause.hpp"
#include "cpu_structs.hpp"
#include "math.hpp"

#include <random>
#include <vector>

namespace sat4gpu {

    class MatSat {
    public:
        static void build_matrix_Q(const std::vector<Clause> &clauses, int num_vars, int num_lits, CpuMat &Q);

        static void build_matrix_Q2_Q1_T(const std::vector<Clause> &clauses, int num_vars, int num_lits, CpuMatBit &Q2_Q1_T);

        static void eval_vec_norm_F_2(const CpuVec &v, float &v_norm_F_2);

        static void eval_matvec_Q_u_tilda_d(const CpuMat &Q, const CpuVec &u_tilde, CpuVec &Q_u_tilda_d);

        static void eval_J_sat(const CpuVec &u_tilda, const CpuMat &Q, const CpuVec &Q_u_tilda_d, float l, float &J_sat);

        static void eval_J_sat_acb(const CpuMatBit &Q2_Q1_T, const CpuVec &u_tilda, const CpuVec &Q_u_tilda_d, float l, CpuVec &J_sat_acb);

        static void eval_u_tilda_new(const CpuVec &u_tilda, const CpuVec &J_sat_acb, float J_sat, CpuVec &u_tilda_new);

        static void eval_u_by_u_tilda(const CpuVec &u_tilda, float theta, CpuVecBit &u);

        static void eval_matvec_Q_u_d_error(const CpuMat &Q, const CpuVecBit &u, int &error);

        static void eval_matvec_Q_u_d_min_error(const CpuMat &Q, const CpuVec &u_tilda, float theta_slice, CpuVecBit &u, int &error);

        static void randomize_vec_uniform(float beta, std::default_random_engine &engine, CpuVec &v);
    };

}// namespace sat4gpu

#endif//SAT4GPU_CPU_MATSAT_FUNCS_HPP
