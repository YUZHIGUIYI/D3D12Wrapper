set(SCREEN_GRAB_FILES
        ${CMAKE_CURRENT_LIST_DIR}/d3dx12.h
        ${CMAKE_CURRENT_LIST_DIR}/ScreenGrab12.h
        ${CMAKE_CURRENT_LIST_DIR}/ScreenGrab12.cpp)

add_library(ScreenGrab12 STATIC ${SCREEN_GRAB_FILES})
target_include_directories(ScreenGrab12 PUBLIC ${CMAKE_CURRENT_LIST_DIR})
set_target_properties(ScreenGrab12 PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS ON)