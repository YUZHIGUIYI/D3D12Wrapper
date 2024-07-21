cmake_minimum_required(VERSION 3.18)

project(D3D12Wrapper LANGUAGES CXX C)

#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_EXTENSIONS ON)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

#set(LINK_D3D12_OUTPUT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/d3d12_ms.lib)
#set(LINK_ARCH "x64")
#file(GLOB_RECURSE SRCFILES CONFIGURE_DEPENDS 
#    ${CMAKE_CURRENT_LIST_DIR}/src/*.h
#    ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

# spdlog
add_subdirectory(external/spdlog)

# d3d12
add_subdirectory(d3d12)
#add_library(d3d12 SHARED "")
#add_custom_command(
#        TARGET d3d12 PRE_BUILD
#        COMMAND lib /def:${CMAKE_CURRENT_LIST_DIR}/src/d3d12_ms.def /out:${LINK_D3D12_OUTPUT} /machine:${LINK_ARCH}
#        DEPENDS ${CMAKE_CURRENT_LIST_DIR}/src/d3d12_ms.def)
#target_sources(d3d12 PRIVATE
#        ${SRCFILES}
#        ${CMAKE_CURRENT_LIST_DIR}/src/d3d12_wrap.def)
#target_include_directories(d3d12 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)
#target_link_libraries(d3d12 PUBLIC ${LINK_D3D12_OUTPUT})
