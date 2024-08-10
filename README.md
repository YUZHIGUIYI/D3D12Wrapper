# D3D12Wrapper
## Introduction
Safely hook `d3d12.dll`, do per-execution-dump or per-draw-dump, and save resource to dds or bin file.

## Getting started
Firstly, clone this project:
```bash
# Step 1
git clone https://github.com/YUZHIGUIYI/D3D12Wrapper.git
# Step 2
cd D3D12Wrapper
# Step 3
git submodule init
# Step 4
git submodule update
```
Secondly, build this project:
```bash
cmake -B build
cmake --build build --config=Release
```
Thirdly, copy the compiled `d3d12.dll` dynamic library to any program startup path, then launch the application that uses d3d12 api, d3d12 api invokes will be hooked safely.

## Dependencies
The following third-party libraries are used:
- [spdlog](https://github.com/gabime/spdlog): Fast C++ logging library.
- [DirectXTex](https://github.com/microsoft/DirectXTex): DirectXTex texture processing library