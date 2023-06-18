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

#ifndef SAT4GPU_MATH_HPP
#define SAT4GPU_MATH_HPP

#include <cinttypes>
#include <cmath>

namespace sat4gpu {

    static constexpr int BITS_CAPACITY = 32;
    static constexpr int BITS_DIV_BIT = BITS_CAPACITY / 1;

    inline int align(int size, int alignment) {
        return ((size + alignment - 1) / alignment) * alignment;
    }

    inline int get_bitset_num_entries(int size) {
        return size / BITS_DIV_BIT + (size % BITS_DIV_BIT ? 1 : 0);
    }

    inline int get_bitset_bit(const int *buffer, int idx) {
        const unsigned int entry_idx = idx / BITS_DIV_BIT;
        const unsigned int bit_shift = idx % BITS_DIV_BIT;

        return (buffer[entry_idx] >> bit_shift) & 0x1;
    }

    inline void set_bitset_bit(int *buffer, int idx, int val) {
        const unsigned int entry_idx = idx / BITS_DIV_BIT;
        const unsigned int bit_shift = idx % BITS_DIV_BIT;

        const int mask = ~(0x1 << bit_shift);

        buffer[entry_idx] = (mask & buffer[entry_idx]) | ((val & 0x1) << bit_shift);
    }

}// namespace sat4gpu

#endif//SAT4GPU_MATH_HPP
