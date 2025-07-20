IF((CMAKE_BUILD_TYPE STREQUAL "x86_Clang") OR (CMAKE_BUILD_TYPE STREQUAL
                                               "x86_GCC"))

  INCLUDE(FetchContent)
  FETCHCONTENT_DECLARE(
    imgui_external
    URL https://github.com/ocornut/imgui/archive/refs/tags/v1.91.9.tar.gz
        EXCLUDE_FROM_ALL)
  FETCHCONTENT_MAKEAVAILABLE(imgui_external)

  ADD_COMPILE_DEFINITIONS(
    IMGUI_USER_CONFIG=\"${CMAKE_CURRENT_SOURCE_DIR}/imconfig_allegro5.h\")

  ADD_LIBRARY(
    imgui
    ${imgui_external_SOURCE_DIR}/imgui.cpp
    ${imgui_external_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_external_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_external_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_external_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_external_SOURCE_DIR}/backends/imgui_impl_allegro5.cpp)
  TARGET_INCLUDE_DIRECTORIES(imgui PUBLIC ${imgui_external_SOURCE_DIR})

  ADD_EXECUTABLE(WoodenClockSimulator main.cpp)
  TARGET_LINK_LIBRARIES(WoodenClockSimulator PUBLIC APP BSP OsAbstraction)

ENDIF()

ADD_SUBDIRECTORY(BSP)
ADD_SUBDIRECTORY(OS)
