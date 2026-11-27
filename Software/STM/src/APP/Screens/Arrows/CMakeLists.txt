ADD_LIBRARY(
  ScreenArrows
  Arrows.cpp include/Screens/StateArrows.hpp)

TARGET_INCLUDE_DIRECTORIES(ScreenArrows PUBLIC include)

TARGET_LINK_LIBRARIES(
  ScreenArrows
  PRIVATE BSP EmbedGUI)
