ADD_LIBRARY(
  ScreenButtons
  Buttons.cpp include/Screens/StateButtons.hpp)

TARGET_INCLUDE_DIRECTORIES(ScreenButtons PUBLIC include)

TARGET_LINK_LIBRARIES(
  ScreenButtons
  PRIVATE BSP EmbedGUI)
