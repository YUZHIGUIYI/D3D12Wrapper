# D3D12Wrapper
## Introduction
Safely hook `d3d12.dll`.

## Getting started
Firstly, build this project:
```bash
cmake -B build
cmake --build build --config=Release
```
Secondly, copy the compiled `d3d12.dll` dynamic library to any program startup path, then launch the application that uses d3d12 api, d3d12 api invokes will be hooked safely.

## Dependencies
- [spdlog](https://github.com/gabime/spdlog): Fast C++ logging library.