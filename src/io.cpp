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

#include "io.hpp"

#include <iostream>
#include <sstream>
#include <utility>

namespace sat4gpu {

    DimacsLoader::DimacsLoader(Solver &solver, std::filesystem::path filepath)
        : m_path(std::move(filepath)), m_solver(solver) {
    }

    bool DimacsLoader::load() {
        std::fstream file(m_path, std::ios::in);

        if (!file.is_open()) {
            std::cerr << "failed to open file " << m_path;
            return false;
        }

        std::string line;

        while (std::getline(file, line)) {
            if (!line.empty() && line[0] != 'c') break;
        }

        if (line.empty() || line[0] != 'p') {
            std::cerr << "failed parse header of " << m_path;
            return false;
        }

        std::stringstream header(line);
        std::string symbol;
        std::string format;

        header >> symbol >> format >> m_n_vars >> m_n_clauses;

        if (format != "cnf") {
            std::cerr << "not supported format " << m_path;
            return false;
        }

        m_solver.add_vars(m_n_vars);

        std::vector<Lit> m_temp_literals;

        for (int i = 0; i < m_n_clauses; i++) {
            m_temp_literals.clear();

            int encoded_var = -1;

            while (encoded_var != 0) {
                file >> encoded_var;

                if (encoded_var != 0) {
                    int var_id = (encoded_var > 0 ? encoded_var : -encoded_var) - 1;
                    Sign var_sign = encoded_var > 0 ? Sign::Positive : Sign::Negative;
                    m_temp_literals.emplace_back(Var{var_id}, var_sign);
                }
            }

            m_solver.add_clause(m_temp_literals);
        }

        return true;
    }

}// namespace sat4gpu