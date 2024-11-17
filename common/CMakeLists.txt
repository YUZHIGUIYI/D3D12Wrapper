# ---------------------------------------------------------------------------------------
# Header only
# ---------------------------------------------------------------------------------------
add_library(GFXShimHeader INTERFACE)
add_library(GFXShim::GFXShimHeader ALIAS GFXShimHeader)

target_include_directories(GFXShimHeader INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
                            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_link_libraries(GFXShimHeader INTERFACE DirectX-Headers)
set_target_properties(GFXShimHeader PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS ON)