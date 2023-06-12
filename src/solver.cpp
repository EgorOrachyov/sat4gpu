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

#include "solver.hpp"

namespace sat4gpu {

    Var Solver::add_var() {
        Var v{int(m_vars.size())};
        m_vars.push_back(v);

        return v;
    }

    Clause Solver::add_clause(const std::vector<Lit> &lits) {
        int offset = int(m_lit_buffer.size());
        m_lit_buffer.resize(m_lit_buffer.size() + lits.size());

        Clause clause(lits, offset, &m_lit_buffer);
        m_clauses.push_back(clause);

        return clause;
    }

    Solution Solver::solve(int timeout) {
        return Solution();
    }

    bool Solver::eval(const std::vector<bool> &assignment) const {
        bool satisfied = true;

        auto iter = m_clauses.begin();
        const auto iter_end = m_clauses.end();

        while (iter != iter_end && satisfied) {
            const Clause &clause = *iter;

            satisfied = clause.eval(assignment);

            ++iter;
        }

        return satisfied;
    }

    int Solver::num_vars() const {
        return int(m_vars.size());
    }
    int Solver::num_clauses() const {
        return int(m_clauses.size());
    }
    int Solver::num_lits() const {
        return int(m_lit_buffer.size());
    }

}// namespace sat4gpu