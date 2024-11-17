set(LINK_DXGI_OUTPUT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dxgi_ms.lib)
set(LINK_ARCH "x64")

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_LIST_DIR}/include/*.h
        ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

add_library(dxgi SHARED "")
add_custom_command(
        TARGET dxgi PRE_BUILD
        COMMAND lib /def:${CMAKE_CURRENT_LIST_DIR}/dxgi_ms.def /out:${LINK_DXGI_OUTPUT} /machine:${LINK_ARCH}
        DEPENDS ${CMAKE_CURRENT_LIST_DIR}/dxgi_ms.def)
target_sources(
        dxgi PRIVATE
        ${SRC_FILES}
        ${CMAKE_CURRENT_LIST_DIR}/dxgi_wrap.def)
target_include_directories(dxgi PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(dxgi PUBLIC ${LINK_DXGI_OUTPUT})
target_link_libraries(dxgi PRIVATE GFXShimHeader)
set_target_properties(dxgi PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS ON)