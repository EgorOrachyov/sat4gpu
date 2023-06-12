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

#include "cpu_naive_comb_backend.hpp"

#include <cassert>

namespace sat4gpu {

    void CpuNaiveCombBackend::configure(const std::vector<Var> &vars, const std::vector<Clause> &clauses) {
        m_vars = vars;
        m_clauses = clauses;
    }
    Solution CpuNaiveCombBackend::solve(int timeout) {
        m_try_assignment.clear();
        m_try_assignment.resize(m_vars.size(), false);

        const bool is_solved = try_solve_recursive(0);

        Solution solution;
        solution.conclusion = is_solved ? Conclusion::Satisfiable : Conclusion::Unsatisfiable;
        solution.model = is_solved ? std::optional(m_try_assignment) : std::nullopt;

        return solution;
    }
    bool CpuNaiveCombBackend::try_solve_recursive(int var_idx) {
        assert(var_idx <= m_vars.size());

        if (var_idx == m_vars.size()) {
            auto iter = m_clauses.begin();
            const auto iter_end = m_clauses.end();

            while (iter != iter_end) {
                const Clause &clause = *iter;

                if (!clause.eval(m_try_assignment)) {
                    return false;
                }

                ++iter;
            }

            return true;
        }

        m_try_assignment[var_idx] = true;
        if (try_solve_recursive(var_idx + 1)) {
            return true;
        }

        m_try_assignment[var_idx] = false;
        if (try_solve_recursive(var_idx + 1)) {
            return true;
        }

        return false;
    }
    BackendType CpuNaiveCombBackend::backend_type() const {
        return BackendType::CpuNaiveComb;
    }
    std::shared_ptr<Backend> CpuNaiveCombBackend::instantiate() const {
        return std::make_shared<CpuNaiveCombBackend>();
    }


}// namespace sat4gpu