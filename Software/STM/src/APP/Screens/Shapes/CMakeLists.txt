ADD_LIBRARY(
  ScreenShapes
  include/Screens/Shapes.hpp Shapes.cpp)

TARGET_INCLUDE_DIRECTORIES(ScreenShapes PUBLIC include)

TARGET_LINK_LIBRARIES(
  ScreenShapes
  PRIVATE BSP EmbedGUI)
