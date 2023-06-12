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

#ifndef SAT4GPU_CPU_NAIVE_COMB_BACKEND_HPP
#define SAT4GPU_CPU_NAIVE_COMB_BACKEND_HPP

#include "backend.hpp"
#include "solver.hpp"

namespace sat4gpu {

    class CpuNaiveCombBackend final : public Backend {
    public:
        ~CpuNaiveCombBackend() override = default;

        void configure(const std::vector<Var> &vars, const std::vector<Clause> &clauses) override;
        Solution solve(int timeout) override;

        [[nodiscard]] BackendType backend_type() const override;
        [[nodiscard]] std::shared_ptr<Backend> instantiate() const override;

    private:
        bool try_solve_recursive(int var_idx);

    private:
        std::vector<Var> m_vars;
        std::vector<Clause> m_clauses;
        std::vector<bool> m_try_assignment;
    };

}// namespace sat4gpu

#endif//SAT4GPU_CPU_NAIVE_COMB_BACKEND_HPP
