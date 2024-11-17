cmake_minimum_required(VERSION 3.18)

project(D3D12Wrapper LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

# spdlog
add_subdirectory(external/spdlog)

# DirectXTex
add_subdirectory(external/DirectXTex)

# DirectX-Headers
add_subdirectory(external/DirectX-Headers)

# Common header
add_subdirectory(common)

# d3d12 tracer
add_subdirectory(d3d12_tracer)

# DXGI
add_subdirectory(dxgi)

# D3D12
add_subdirectory(d3d12)

# D3D11
add_subdirectory(d3d11)