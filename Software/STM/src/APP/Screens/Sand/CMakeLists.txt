ADD_LIBRARY(
  ScreenSand
  include/Screens/StateSand.hpp Sand.cpp)

TARGET_INCLUDE_DIRECTORIES(ScreenSand INTERFACE include)

TARGET_LINK_LIBRARIES(
  ScreenSand
  PRIVATE BSP EmbedGUI)
