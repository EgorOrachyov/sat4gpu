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

#ifndef SAT4GPU_CLAUSE_HPP
#define SAT4GPU_CLAUSE_HPP

#include "lit.hpp"
#include "var.hpp"

#include <cassert>
#include <vector>

namespace sat4gpu {

    class Clause {
    public:
        Clause(const std::vector<Lit> &lits, int offset, Lit *lit_buffer);

        [[nodiscard]] int offset() const { return m_offset; }
        [[nodiscard]] int count() const { return m_count; }
        [[nodiscard]] Lit *lit_buffer() const { return m_lit_buffer; }

    private:
        int m_offset = -1;
        int m_count = 0;
        Lit *m_lit_buffer = nullptr;
    };

    Clause::Clause(const std::vector<Lit> &lits, int offset, Lit *lit_buffer) {
        assert(lit_buffer);
        assert(!lits.empty());

        m_offset = offset;
        m_count = int(lits.size());
        m_lit_buffer = lit_buffer;

        for (int i = 0; i < m_count; i++) {
            lit_buffer[i] = lits[i];
        }
    }

}// namespace sat4gpu

#endif//SAT4GPU_CLAUSE_HPP
