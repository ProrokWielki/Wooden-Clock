ADD_LIBRARY(
  ScreenAcceleration
  Acceleration.cpp include/Screens/StateAccel.hpp)

TARGET_INCLUDE_DIRECTORIES(ScreenAcceleration PUBLIC include)

TARGET_LINK_LIBRARIES(
  ScreenAcceleration
  PRIVATE BSP EmbedGUI)
