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

#ifndef SAT4GPU_CPU_MATSAT_BACKEND_HPP
#define SAT4GPU_CPU_MATSAT_BACKEND_HPP

#include "backend.hpp"
#include "cpu_structs.hpp"
#include "math.hpp"
#include "solver.hpp"

#include <cinttypes>
#include <random>
#include <vector>

namespace sat4gpu {

    class CpuMatsatBackend : public Backend {
    public:
        ~CpuMatsatBackend() override = default;

        void configure(const class Solver &solver) override;
        Solution solve(int timeout) override;

        [[nodiscard]] BackendType backend_type() const override;
        [[nodiscard]] std::shared_ptr<Backend> instantiate() const override;

        [[nodiscard]] int &uniform_seed() { return m_uniform_seed; }
        [[nodiscard]] int &max_try() { return m_max_try; }
        [[nodiscard]] int &max_itr() { return m_max_itr; }
        [[nodiscard]] float &theta_slice() { return m_theta_slice; }
        [[nodiscard]] float &beta() { return m_beta; }

    private:
        int m_uniform_seed = 137483;// uniform distribution randomization
        int m_max_try = 200;        // outer loop max iterations
        int m_max_itr = 5;          // inner loop max iterations
        float m_theta_slice = 200;  // num steps to threshold to binary vector level
        float m_beta = 0.5f;        // randomization mix
        float m_l = 0.01;           // l norm weigh

        CpuMat m_Q;          // cnf matrix in binary form
        CpuMatBit m_Q2_Q1_T; // packed dif with 2-bits per entry
        CpuVecBit m_u;       // result bit vec u
        CpuVec m_Q_u_tilda_d;// cached mem for Qu~d product
        CpuVec m_u_tilda;    // current floating u solution
        CpuVec m_u_tilda_new;// new floating u solution
        CpuVec m_J_sat_acb;  // every iter evaluated grad
        float m_J_sat;       // every iter evaluated error
        int m_error = 0;     // num of unsat clauses
    };

}// namespace sat4gpu

#endif//SAT4GPU_CPU_MATSAT_BACKEND_HPP
