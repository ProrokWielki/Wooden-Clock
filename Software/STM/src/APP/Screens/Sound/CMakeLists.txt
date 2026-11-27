ADD_LIBRARY(
  ScreenSound
  include/Screens/Sound.hpp Sound.cpp)

TARGET_INCLUDE_DIRECTORIES(ScreenSound PUBLIC include)

TARGET_LINK_LIBRARIES(
  ScreenSound
  PRIVATE BSP EmbedGUI)
