set(LINK_D3D11_OUTPUT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/d3d11_ms.lib)
set(LINK_ARCH "x64")

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_LIST_DIR}/include/*.h
        ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

add_library(d3d11 SHARED "")
add_custom_command(
        TARGET d3d11 PRE_BUILD
        COMMAND lib /def:${CMAKE_CURRENT_LIST_DIR}/d3d11_ms.def /out:${LINK_D3D11_OUTPUT} /machine:${LINK_ARCH}
        DEPENDS ${CMAKE_CURRENT_LIST_DIR}/d3d11_ms.def)
target_sources(
        d3d11 PRIVATE
        ${SRC_FILES}
        ${CMAKE_CURRENT_LIST_DIR}/d3d11_wrap.def)
target_include_directories(d3d11 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
# target_compile_definitions(d3d11 PRIVATE ENABLE_D3D12_WRAPPER)
set_target_properties(d3d11 PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS ON)