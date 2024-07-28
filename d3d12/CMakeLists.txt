set(LINK_D3D12_OUTPUT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/d3d12_ms.lib)
set(LINK_ARCH "x64")

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_LIST_DIR}/include/*.h
    ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

add_library(d3d12 SHARED "")
add_custom_command(
        TARGET d3d12 PRE_BUILD
        COMMAND lib /def:${CMAKE_CURRENT_LIST_DIR}/d3d12_ms.def /out:${LINK_D3D12_OUTPUT} /machine:${LINK_ARCH}
        DEPENDS ${CMAKE_CURRENT_LIST_DIR}/d3d12_ms.def)
target_sources(
        d3d12 PRIVATE
        ${SRC_FILES}
        ${CMAKE_CURRENT_LIST_DIR}/d3d12_wrap.def)
target_include_directories(d3d12 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(d3d12 PUBLIC ${LINK_D3D12_OUTPUT})
target_link_libraries(d3d12 PRIVATE spdlog_header_only)
target_link_libraries(d3d12 PRIVATE ScreenGrab12)
set_target_properties(d3d12 PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS ON)