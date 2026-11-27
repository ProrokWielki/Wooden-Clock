ADD_LIBRARY(
  ScreenButtonHandler
  ButtonHandler.cpp include/Screens/StateButtonHandler.hpp)

TARGET_INCLUDE_DIRECTORIES(ScreenButtonHandler PUBLIC include)

TARGET_LINK_LIBRARIES(
  ScreenButtonHandler
  PRIVATE BSP EmbedGUI)
