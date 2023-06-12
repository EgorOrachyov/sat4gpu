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

#ifndef SAT4GPU_SOLVER_HPP
#define SAT4GPU_SOLVER_HPP

#include "backend.hpp"
#include "clause.hpp"
#include "lit.hpp"
#include "solution.hpp"
#include "var.hpp"

#include <string>
#include <unordered_map>
#include <vector>

namespace sat4gpu {

    class Solver {
    public:
        static constexpr int DEFAULT_TIMEOUT_SEC = 20000;

        Var add_var();
        void add_vars(int num_of_vars);
        Clause add_clause(Lit a);
        Clause add_clause(Lit a, Lit b);
        Clause add_clause(Lit a, Lit b, Lit c);
        Clause add_clause(const std::vector<Lit> &lits);

        Solution solve(int timeout, BackendType backend_type = BackendType::CpuNaiveComb);
        Solution solve(int timeout, const std::shared_ptr<Backend> &backend);

        [[nodiscard]] bool eval(const std::vector<bool> &assignment) const;

        [[nodiscard]] int num_vars() const;
        [[nodiscard]] int num_clauses() const;
        [[nodiscard]] int num_lits() const;
        [[nodiscard]] const std::vector<Var> &vars() const;
        [[nodiscard]] const std::vector<Clause> &clauses() const;
        [[nodiscard]] const std::vector<Lit> &lit_buffer() const;

    private:
        std::vector<Var> m_vars;
        std::vector<Clause> m_clauses;
        std::vector<Lit> m_lit_buffer;
    };

}// namespace sat4gpu

#endif//SAT4GPU_SOLVER_HPP
