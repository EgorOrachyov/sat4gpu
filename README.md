# sat4gpu

[![Build](https://github.com/EgorOrachyov/sat4gpu/actions/workflows/build.yml/badge.svg)](https://github.com/EgorOrachyov/sat4gpu/actions/workflows/build.yml)
[![Clang Format](https://github.com/EgorOrachyov/sat4gpu/actions/workflows/clang-format.yml/badge.svg)](https://github.com/EgorOrachyov/sat4gpu/actions/workflows/clang-format.yml)

Minimalistic high-performance SAT solver with GPU acceleration.

## Building from sources

### Prerequisites

- **Common**:
    - Git (to get source code)
    - CMake (the latest version)
    - Ninja (as build files generator)
    - Python 3.7+
    - Nvidia Cuda SDK v10 or greater
- **Windows 10**:
    - Microsoft Visual C++ Compiler (MSVC) with C++17 support
    - x64 Native Tools Command Prompt for VS
- **Ubuntu 20.04**:
    - GNU C++ Compiler with C++17 support
- **MaсOS Catalina 10.15**:
    - Clang Compiler with C++17 support

### Get source code

The following code snippet downloads project source code repository, and enters project root folder. Must be executed
from the folder where you want to locate project.

```shell
$ git clone https://github.com/EgorOrachyov/sat4gpu.git
$ cd sat4gpu
```

### Configure and run build

> **Attention!** On Windows platform building commands must be executed in `x64 Native Tools Command Prompt for VS`.

The following code snippet runs `build.py` script, which allows configuring cmake and running of actual build with
selected options. You can specify build directory, build type, number of system threads for build.
Must be executed from project root folder.

```shell
$ python ./build.py --build-dir=build --build-type=Release --nt=4
```

On macOS, you can optionally specify target binaries architecture to build. Pass option `--arch`
with `x86_64` or `arm64` respectively. By default, build falls back to `CMAKE_SYSTEM_PROCESSOR` specified architecture.
See example bellow, replace `<arch>` with desired architecture for your build. Must be executed from project root
folder.

```shell
$ python ./build.py --build-dir=build --build-type=Release --nt=4 --arch=<arch>
```

### Run executable

The following code snippet allows to run executable application of the project to sat formulas.
Must be executed from the directory used for a build in the previous step.

Print help message to get all possible options.

```shell
$ ./sat4gpu -h
```

## Contributors

- Egor Orachyov (Github: [@EgorOrachyov](https://github.com/EgorOrachyov))

## Citation

```ignorelang
@online{sat4gpu,
  author = {Orachyov, Egor},
  title = {Sat4Gpu: Minimalistic high-performance SAT solver with GPU acceleration},
  year = 2023,
  url = {https://github.com/EgorOrachyov/sat4gpu},
  note = {Version 1.0.0}
}
```

## Project structure

| Entry               | Description                                               |
|:--------------------|:----------------------------------------------------------|
| `📁 .github`        | CI/CD scripts and GitHub related files                    |
| `📁 app`            | Compiled example application                              |
| `📁 deps`           | Third-party project dependencies, stored as submodules    |
| `📁 resource`       | Example formulas for tests                                |
| `📁 include`        | Public compiled library header files directory            |
| `📁 src`            | Private compiled source directory                         |
| `📁 test`           | Unit tests folder                                         |
| `📄 CMakeLists.txt` | CMake configuration, add as sub directory to your project |
| `📄 build.py`       | Script to build project sources to executable             |

## License

This project licensed under MIT License. License text can be found in the
[license file](https://github.com/EgorOrachyov/sat4gpu/blob/master/LICENSE.md).
