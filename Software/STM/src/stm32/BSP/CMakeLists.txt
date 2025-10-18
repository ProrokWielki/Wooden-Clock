ADD_LIBRARY(
  StmBSP STATIC EXCLUDE_FROM_ALL
  BSP.cpp include/BSP/BSP.hpp)

TARGET_LINK_LIBRARIES(
  StmBSP
  Button
  StmDisplay
  APP
  HAL
  Magnetometer
  Communication
  StmClock
  StmAccelerometer
  StmThermometer)

TARGET_INCLUDE_DIRECTORIES(StmBSP PUBLIC include)

ADD_SUBDIRECTORY(Display)
ADD_SUBDIRECTORY(Magnetometer)
ADD_SUBDIRECTORY(Accelerometer)
ADD_SUBDIRECTORY(Thermometer)
ADD_SUBDIRECTORY(Button)
ADD_SUBDIRECTORY(Clock)
ADD_SUBDIRECTORY(Communication)
