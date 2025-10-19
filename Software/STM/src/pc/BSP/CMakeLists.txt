ADD_LIBRARY(
  PcBSP STATIC EXCLUDE_FROM_ALL
  BSP.cpp include/BSP/BSP.hpp)

TARGET_LINK_LIBRARIES(
  PcBSP
  PUBLIC PcDisplay
         PcClock
         PcAccelerometer
         PcMagnetometer
         PcButton
         PcCommunication
         PcThermometer)

TARGET_INCLUDE_DIRECTORIES(PcBSP PUBLIC include)

ADD_SUBDIRECTORY(Display)
ADD_SUBDIRECTORY(Accelerometer)
ADD_SUBDIRECTORY(Magnetometer)
ADD_SUBDIRECTORY(Clock)
ADD_SUBDIRECTORY(Button)
ADD_SUBDIRECTORY(Thermometer)
ADD_SUBDIRECTORY(Communication)
