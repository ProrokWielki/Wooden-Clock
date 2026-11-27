ADD_LIBRARY(
  ScreenNorth
  include/Screens/StateNorth.hpp North.cpp)

TARGET_INCLUDE_DIRECTORIES(ScreenNorth INTERFACE include)

TARGET_LINK_LIBRARIES(
  ScreenNorth
  PRIVATE BSP EmbedGUI)
