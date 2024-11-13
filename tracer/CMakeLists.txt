file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_LIST_DIR}/include/*.h
        ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

add_library(d3d12_tracer SHARED "")
target_sources(
        d3d12_tracer PRIVATE
        ${SRC_FILES}
        ${CMAKE_CURRENT_LIST_DIR}/d3d12_tracer.def)
target_include_directories(d3d12_tracer PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
set_target_properties(d3d12_tracer PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS ON)