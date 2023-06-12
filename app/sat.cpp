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

#include <cxxopts.hpp>

int main(const int argc, const char *const *argv) {
    cxxopts::Options options("sat4gpu", "Minimalistic sat-solver with GPU acceleration");
    options.add_option("", cxxopts::Option("h,help", "display help info about application", cxxopts::value<bool>()->default_value("false")));
    options.add_option("", cxxopts::Option("backend", "backend name for execution (cpu/gpu)", cxxopts::value<std::string>()->default_value("cpu")));
    options.add_option("", cxxopts::Option("input", "path to input formula to proces", cxxopts::value<std::string>()->default_value("<none>")));
    options.add_option("", cxxopts::Option("output", "path to output file to save result", cxxopts::value<std::string>()->default_value("out.txt")));
    options.add_option("", cxxopts::Option("niters", "times to execute", cxxopts::value<int>()->default_value("4")));

    cxxopts::ParseResult args;

    // parse arguments
    try {
        args = options.parse(argc, argv);
    } catch (const std::exception &e) {
        std::cerr << "failed to parse input arguments " << e.what();
        return 1;
    }

    // show help and exit, ok
    if (args["help"].as<bool>()) {
        std::cout << options.help();
        return 0;
    }

    // handle no-args case
    if (args["input"].as<std::string>() == "<none>") {
        std::cerr << "no input formula to process";
        return 0;
    }

    return 0;
}