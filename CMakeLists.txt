cmake_minimum_required(VERSION 3.18)

project(D3D12Wrapper LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_language(ASM_MASM)

set(CMAKE_ASM_COMPILER "ml64")
#set(CMAKE_ASM_FLAGS "/c /Fo ${CMAKE_CURRENT_BINARY_DIR}/dll_aux_fwd_asm.obj")
#set(ASM_FILE "${CMAKE_CURRENT_LIST_DIR}/src/dll_aux_fwd_asm.asm")
#
#add_custom_command(
#    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/dll_aux_fwd_asm.obj
#    COMMAND ${CMAKE_ASM_COMPILER} ${CMAKE_ASM_FLAGS} ${ASM_FILE}
#    DEPENDS ${ASM_FILE}
#)

file(GLOB_RECURSE SRCFILES CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_LIST_DIR}/src/*.h"
    "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/*.asm"
    "${CMAKE_CURRENT_LIST_DIR}/src/*.def")

add_library(d3d12 SHARED ${SRCFILES}) # ${CMAKE_CURRENT_BINARY_DIR}/dll_aux_fwd_asm.obj
target_include_directories(d3d12 PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src")
set_target_properties(d3d12 PROPERTIES LINKER_LANGUAGE CXX)
