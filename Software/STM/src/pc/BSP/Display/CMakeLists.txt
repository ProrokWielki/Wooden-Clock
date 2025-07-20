ADD_LIBRARY(
  PcDisplay STATIC EXCLUDE_FROM_ALL
  Display.cpp include/BSP/Display.hpp)

TARGET_LINK_LIBRARIES(
  PcDisplay
  PRIVATE imgui allegro allegro_main allegro_primitives BSP)

TARGET_INCLUDE_DIRECTORIES(PcDisplay PUBLIC include)
