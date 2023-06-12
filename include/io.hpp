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

#ifndef SAT4GPU_IO_HPP
#define SAT4GPU_IO_HPP

#include "lit.hpp"
#include "solver.hpp"
#include "var.hpp"

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace sat4gpu {

    class DimacsLoader {
    public:
        DimacsLoader(Solver &solver, std::filesystem::path filepath);

        bool load();

        [[nodiscard]] const std::filesystem::path &path() const { return m_path; }
        [[nodiscard]] Solver &solver() const { return m_solver; }
        [[nodiscard]] int n_vars() const { return m_n_vars; }
        [[nodiscard]] int n_clauses() const { return m_n_clauses; }

    private:
        std::filesystem::path m_path;
        Solver &m_solver;
        int m_n_vars = 0;
        int m_n_clauses = 0;
    };

}// namespace sat4gpu

#endif//SAT4GPU_IO_HPP
