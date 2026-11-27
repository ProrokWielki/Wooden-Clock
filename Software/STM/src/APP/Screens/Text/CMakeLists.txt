ADD_LIBRARY(
  ScreenText STATIC
  include/Screens/Text.hpp Text.cpp)

TARGET_INCLUDE_DIRECTORIES(ScreenText INTERFACE include)

TARGET_LINK_LIBRARIES(
  ScreenText
  PRIVATE BSP EmbedGUI Texts)
