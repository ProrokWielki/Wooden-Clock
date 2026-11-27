ADD_LIBRARY(
  ScreenCounter
  Counter.cpp include/Screens/Counter.hpp)

TARGET_INCLUDE_DIRECTORIES(ScreenCounter PUBLIC include)

TARGET_LINK_LIBRARIES(
  ScreenCounter
  PRIVATE BSP EmbedGUI)
