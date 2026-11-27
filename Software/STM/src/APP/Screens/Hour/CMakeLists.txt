ADD_LIBRARY(
  ScreenHour
  Hour.cpp include/Screens/Hour.hpp)

TARGET_INCLUDE_DIRECTORIES(ScreenHour PUBLIC include)

TARGET_LINK_LIBRARIES(
  ScreenHour
  PRIVATE BSP EmbedGUI)
