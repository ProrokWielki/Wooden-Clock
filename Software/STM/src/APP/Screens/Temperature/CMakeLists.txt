ADD_LIBRARY(
  ScreenTemperature
  include/Screens/Temperature.hpp Temperature.cpp)

TARGET_INCLUDE_DIRECTORIES(ScreenTemperature INTERFACE include)

TARGET_LINK_LIBRARIES(
  ScreenTemperature
  PRIVATE BSP EmbedGUI Texts)
