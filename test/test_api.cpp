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

TEST(api, formula) {
    using namespace sat4gpu;

    Solver solver;

    Var x = solver.add_var();
    Var y = solver.add_var();
    Var z = solver.add_var();

    solver.add_clause({Lit(x, Sign::Positive), Lit(y, Sign::Negative), Lit(z, Sign::Negative)});
}

TEST(api, eval) {
    using namespace sat4gpu;

    Solver solver;

    Var x = solver.add_var();
    Var y = solver.add_var();
    Var z = solver.add_var();
    Var w = solver.add_var();

    solver.add_clause({Lit(x, Sign::Positive), Lit(y, Sign::Negative)});
    solver.add_clause({Lit(z, Sign::Positive), Lit(w, Sign::Negative)});

    EXPECT_TRUE(solver.eval({true, false, true, false}));

    EXPECT_TRUE(solver.eval({true, false, false, false}));

    EXPECT_FALSE(solver.eval({false, true, false, true}));
}

SAT4GPU_GTEST_MAIN