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

        Lit(Var var, Sign sign);

        [[nodiscard]] Var var() const;
        [[nodiscard]] Sign sign() const;
        [[nodiscard]] Lit to_neg() const;
        [[nodiscard]] bool is_valid() const;
        [[nodiscard]] bool is_invalid() const;
    };

    Lit::Lit(Var var, Sign sign) {
        assert(var.is_valid());

        x = var.id * 2 + int(sign);
    }

    Var Lit::var() const {
        assert(is_valid());

        return {x / 2};
    }
    Sign Lit::sign() const {
        assert(is_valid());

        return static_cast<Sign>(x % 2);
    }
    Lit Lit::to_neg() const {
        assert(is_valid());

        return {var(), static_cast<Sign>(((x % 2) + 1) % 2)};
    }

    bool Lit::is_valid() const {
        return x >= 0;
    }
    bool Lit::is_invalid() const {
        return x == -1;
    }


}// namespace sat4gpu

#endif//SAT4GPU_LIT_HPP
