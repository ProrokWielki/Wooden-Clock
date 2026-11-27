ADD_LIBRARY(
  ScreenHourglass
  Hourglass.cpp include/Screens/StateHourglass.hpp)

TARGET_INCLUDE_DIRECTORIES(ScreenHourglass INTERFACE include)

TARGET_LINK_LIBRARIES(
  ScreenHourglass
  PRIVATE BSP EmbedGUI)
