ADD_LIBRARY(
  ScreenMario
  include/Screens/StateMario.hpp Mario.cpp)

TARGET_INCLUDE_DIRECTORIES(ScreenMario INTERFACE include)

TARGET_LINK_LIBRARIES(
  ScreenMario
  PRIVATE BSP EmbedGUI)
