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

#include "common.hpp"

TEST(io, dimacs) {
    using namespace sat4gpu;

    Solver solver;
    DimacsLoader loader(solver, "../../resource/test_5.cnf");

    EXPECT_TRUE(loader.load());

    EXPECT_EQ(loader.n_vars(), 5);
    EXPECT_EQ(loader.n_clauses(), 2);

    EXPECT_EQ(solver.clauses()[0].count(), 5);
    EXPECT_EQ(solver.clauses()[1].count(), 5);

    EXPECT_EQ(solver.clauses()[0].lits()[0], Var{0});
    EXPECT_EQ(solver.clauses()[0].lits()[1], Var{1});
    EXPECT_EQ(solver.clauses()[0].lits()[2], Var{2});
    EXPECT_EQ(solver.clauses()[0].lits()[3], Var{3});
    EXPECT_EQ(solver.clauses()[0].lits()[4], Var{4});

    EXPECT_EQ(solver.clauses()[1].lits()[0], -Var{0});
    EXPECT_EQ(solver.clauses()[1].lits()[1], -Var{1});
    EXPECT_EQ(solver.clauses()[1].lits()[2], -Var{2});
    EXPECT_EQ(solver.clauses()[1].lits()[3], -Var{3});
    EXPECT_EQ(solver.clauses()[1].lits()[4], Var{4});
}

SAT4GPU_GTEST_MAIN