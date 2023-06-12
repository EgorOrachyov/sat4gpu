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

#include "clause.hpp"

namespace sat4gpu {

    Clause::Clause(const std::vector<Lit> &lits, int offset, std::vector<Lit> *lit_buffer) {
        assert(lit_buffer);
        assert(!lits.empty());

        m_offset = offset;
        m_count = int(lits.size());
        m_lit_buffer = lit_buffer;

        for (int i = 0; i < m_count; i++) {
            (*lit_buffer)[m_offset + i] = lits[i];
        }
    }

    bool Clause::eval(const std::vector<bool> &assignments) const {
        bool satisfied = false;

        auto iter = begin();
        const auto iter_end = end();

        while (iter != iter_end && !satisfied) {
            const Lit &lit = *iter;
            const Var lit_var = lit.var();
            const bool var_assignment = assignments[lit_var.id];

            satisfied = lit.eval(var_assignment);

            ++iter;
        }

        return satisfied;
    }

    Lit *Clause::begin() {
        return m_lit_buffer->data() + m_offset;
    }
    Lit *Clause::end() {
        return m_lit_buffer->data() + m_offset + m_count;
    }
    const Lit *Clause::begin() const {
        return m_lit_buffer->data() + m_offset;
    }
    const Lit *Clause::end() const {
        return m_lit_buffer->data() + m_offset + m_count;
    }

}// namespace sat4gpu