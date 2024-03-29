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

#ifndef SAT4GPU_BACKEND_HPP
#define SAT4GPU_BACKEND_HPP

#include "clause.hpp"
#include "lit.hpp"
#include "solution.hpp"
#include "var.hpp"

#include <memory>
#include <vector>

namespace sat4gpu {

    enum class BackendType {
        CpuComb = 0,
        CpuMatsat,
        CudaMatsat
    };

    class Backend {
    public:
        virtual ~Backend() = default;

        virtual void configure(const class Solver &solver) = 0;
        virtual Solution solve(int timeout) = 0;

        [[nodiscard]] virtual BackendType backend_type() const = 0;
        [[nodiscard]] virtual std::shared_ptr<Backend> instantiate() const = 0;
    };

}// namespace sat4gpu

#endif//SAT4GPU_BACKEND_HPP
