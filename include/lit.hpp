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

#ifndef SAT4GPU_LIT_HPP
#define SAT4GPU_LIT_HPP

#include "var.hpp"

#include <cassert>

namespace sat4gpu {

    enum class Sign {
        Positive = 0,
        Negative = 1
    };

    struct Lit {
        int x = -1;

        Lit() = default;
        Lit(Var var, Sign sign = Sign::Positive);

        bool operator==(const Lit &) const;
        bool operator!=(const Lit &) const;
        bool operator<(const Lit &) const;

        [[nodiscard]] bool eval(bool var_assignment) const;

        [[nodiscard]] Var var() const;
        [[nodiscard]] Sign sign() const;
        [[nodiscard]] Lit to_neg() const;
        [[nodiscard]] bool is_valid() const;
        [[nodiscard]] bool is_invalid() const;
    };

    inline Lit operator-(const Var &var) {
        return Lit(var).to_neg();
    }

    inline Lit operator-(const Lit &lit) {
        return lit.to_neg();
    }

}// namespace sat4gpu

#endif//SAT4GPU_LIT_HPP
