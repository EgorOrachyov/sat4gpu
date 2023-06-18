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

#ifndef SAT4GPU_CPU_STRUCTS_HPP
#define SAT4GPU_CPU_STRUCTS_HPP

#include "math.hpp"

#include <vector>

namespace sat4gpu {

    struct CpuMat {
        int n_rows = 0;
        int n_cols = 0;
        int n_vals = 0;
        std::vector<int> row_ptr;
        std::vector<int> cols;

        void resize(int n_rows, int n_cols, int n_vals) {
            this->n_rows = n_rows;
            this->n_cols = n_cols;
            this->n_vals = n_vals;
            this->row_ptr.resize(n_rows + 1, 0);
            this->cols.resize(n_vals, 0);
        }
    };

    struct CpuMatBit {
        int n_rows = 0;
        int n_cols = 0;
        int n_vals = 0;
        std::vector<int> row_ptr;
        std::vector<int> cols;
        std::vector<int> val_bit;

        void resize(int n_rows, int n_cols, int n_vals) {
            this->n_rows = n_rows;
            this->n_cols = n_cols;
            this->n_vals = n_vals;
            this->row_ptr.resize(n_rows + 1, 0);
            this->cols.resize(n_vals, 0);
            this->val_bit.resize(get_bitset_num_entries(n_vals), 0);
        }

        void set(int idx, int value) {
            set_bitset_bit(val_bit.data(), idx, value);
        }

        [[nodiscard]] int get(int idx) const {
            return get_bitset_bit(val_bit.data(), idx);
        }
    };

    struct CpuVec {
        int n_rows = 0;
        std::vector<float> val;

        void resize(int n_rows) {
            this->n_rows = n_rows;
            this->val.resize(n_rows, 0);
        }
    };

    struct CpuVecBit {
        int n_rows = 0;
        std::vector<int> val_bit;

        void resize(int n_rows) {
            this->n_rows = n_rows;
            this->val_bit.resize(get_bitset_num_entries(n_rows), 0);
        }

        void set(int idx, int value) {
            set_bitset_bit(val_bit.data(), idx, value);
        }

        [[nodiscard]] int get(int idx) const {
            return get_bitset_bit(val_bit.data(), idx);
        }

        [[nodiscard]] std::vector<bool> to_bool() const {
            std::vector<bool> v(n_rows);

            for (int i = 0; i < n_rows; i++) {
                v[i] = get(i);
            }

            return v;
        }
    };

}// namespace sat4gpu

#endif//SAT4GPU_CPU_STRUCTS_HPP
