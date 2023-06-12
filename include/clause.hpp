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
        Clause(const std::vector<Lit> &lits, int offset, std::vector<Lit> *lit_buffer);

        [[nodiscard]] bool eval(const std::vector<bool> &assignments) const;

        [[nodiscard]] Lit *begin();
        [[nodiscard]] Lit *end();
        [[nodiscard]] const Lit *begin() const;
        [[nodiscard]] const Lit *end() const;

        [[nodiscard]] int offset() const { return m_offset; }
        [[nodiscard]] int count() const { return m_count; }
        [[nodiscard]] Lit *lits() const { return m_lit_buffer->data() + m_offset; }
        [[nodiscard]] Lit *lit_buffer() const { return m_lit_buffer->data(); }

    private:
        int m_offset = -1;
        int m_count = 0;
        std::vector<Lit> *m_lit_buffer = nullptr;
    };

}// namespace sat4gpu

#endif//SAT4GPU_CLAUSE_HPP
