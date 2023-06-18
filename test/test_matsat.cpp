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

TEST(solve, matsat_sat) {
    using namespace sat4gpu;

    Solver solver;

    Var x = solver.add_var();
    Var y = solver.add_var();
    Var z = solver.add_var();
    Var w = solver.add_var();

    solver.add_clause(-x);
    solver.add_clause(-y);
    solver.add_clause(z, -w);

    Solution solution = solver.solve(Solver::DEFAULT_TIMEOUT_SEC, BackendType::CpuMatsat);

    EXPECT_EQ(solution.conclusion, Conclusion::Satisfiable);
    EXPECT_TRUE(solution.model.has_value() && solver.eval(solution.model.value()));
}

TEST(solve, matsat_unsat) {
    using namespace sat4gpu;

    Solver solver;

    Var x = solver.add_var();
    Var y = solver.add_var();

    solver.add_clause(x);
    solver.add_clause(-x);
    solver.add_clause(y);
    solver.add_clause(-y);

    Solution solution = solver.solve(Solver::DEFAULT_TIMEOUT_SEC, BackendType::CpuMatsat);

    EXPECT_EQ(solution.conclusion, Conclusion::DontKnow);
}

TEST(solve, matsat_test_1) {
    using namespace sat4gpu;

    Solver solver;
    DimacsLoader loader(solver, "../../resource/test_1.cnf");

    EXPECT_TRUE(loader.load());

    Solution solution = solver.solve(Solver::DEFAULT_TIMEOUT_SEC, BackendType::CpuMatsat);

    EXPECT_EQ(solution.conclusion, Conclusion::Satisfiable);
    EXPECT_TRUE(solution.model.has_value() && solver.eval(solution.model.value()));
}

TEST(solve, matsat_test_2) {
    using namespace sat4gpu;

    Solver solver;
    DimacsLoader loader(solver, "../../resource/test_2.cnf");

    EXPECT_TRUE(loader.load());

    Solution solution = solver.solve(Solver::DEFAULT_TIMEOUT_SEC, BackendType::CpuMatsat);

    EXPECT_EQ(solution.conclusion, Conclusion::Satisfiable);
    EXPECT_TRUE(solution.model.has_value() && solver.eval(solution.model.value()));
}

TEST(solve, matsat_test_3) {
    using namespace sat4gpu;

    Solver solver;
    DimacsLoader loader(solver, "../../resource/test_3.cnf");

    EXPECT_TRUE(loader.load());

    Solution solution = solver.solve(Solver::DEFAULT_TIMEOUT_SEC, BackendType::CpuMatsat);

    EXPECT_EQ(solution.conclusion, Conclusion::Satisfiable);
    EXPECT_TRUE(solution.model.has_value() && solver.eval(solution.model.value()));
}

TEST(solve, matsat_test_4) {
    using namespace sat4gpu;

    Solver solver;
    DimacsLoader loader(solver, "../../resource/test_4.cnf");

    EXPECT_TRUE(loader.load());

    Solution solution = solver.solve(Solver::DEFAULT_TIMEOUT_SEC, BackendType::CpuMatsat);

    EXPECT_EQ(solution.conclusion, Conclusion::Satisfiable);
    EXPECT_TRUE(solution.model.has_value() && solver.eval(solution.model.value()));
}

TEST(solve, matsat_test_5) {
    using namespace sat4gpu;

    Solver solver;
    DimacsLoader loader(solver, "../../resource/test_5.cnf");

    EXPECT_TRUE(loader.load());

    Solution solution = solver.solve(Solver::DEFAULT_TIMEOUT_SEC, BackendType::CpuMatsat);

    EXPECT_EQ(solution.conclusion, Conclusion::Satisfiable);
    EXPECT_TRUE(solution.model.has_value() && solver.eval(solution.model.value()));
}

TEST(solve, matsat_test_6) {
    using namespace sat4gpu;

    Solver solver;
    DimacsLoader loader(solver, "../../resource/test_6.cnf");

    EXPECT_TRUE(loader.load());

    Solution solution = solver.solve(Solver::DEFAULT_TIMEOUT_SEC, BackendType::CpuMatsat);

    EXPECT_EQ(solution.conclusion, Conclusion::DontKnow);
}

TEST(solve, matsat_test_7) {
    using namespace sat4gpu;

    Solver solver;
    DimacsLoader loader(solver, "../../resource/test_7.cnf");

    EXPECT_TRUE(loader.load());

    Solution solution = solver.solve(Solver::DEFAULT_TIMEOUT_SEC, BackendType::CpuMatsat);

    EXPECT_EQ(solution.conclusion, Conclusion::Satisfiable);
    EXPECT_TRUE(solution.model.has_value() && solver.eval(solution.model.value()));
}

TEST(solve, matsat_test_8) {
    using namespace sat4gpu;

    Solver solver;
    DimacsLoader loader(solver, "../../resource/test_8.cnf");

    EXPECT_TRUE(loader.load());

    Solution solution = solver.solve(Solver::DEFAULT_TIMEOUT_SEC, BackendType::CpuMatsat);

    EXPECT_EQ(solution.conclusion, Conclusion::Satisfiable);
    EXPECT_TRUE(solution.model.has_value() && solver.eval(solution.model.value()));
}

TEST(solve, matsat_test_9) {
    using namespace sat4gpu;

    Solver solver;
    DimacsLoader loader(solver, "../../resource/test_9.cnf");

    EXPECT_TRUE(loader.load());

    Solution solution = solver.solve(Solver::DEFAULT_TIMEOUT_SEC, BackendType::CpuMatsat);

    EXPECT_EQ(solution.conclusion, Conclusion::Satisfiable);
    EXPECT_TRUE(solution.model.has_value() && solver.eval(solution.model.value()));
}

TEST(solve, matsat_test_10) {
    using namespace sat4gpu;

    Solver solver;
    DimacsLoader loader(solver, "../../resource/test_10.cnf");

    EXPECT_TRUE(loader.load());

    Solution solution = solver.solve(Solver::DEFAULT_TIMEOUT_SEC, BackendType::CpuMatsat);

    EXPECT_EQ(solution.conclusion, Conclusion::Satisfiable);
    EXPECT_TRUE(solution.model.has_value() && solver.eval(solution.model.value()));
}

SAT4GPU_GTEST_MAIN