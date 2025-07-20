ADD_LIBRARY(
  PcAccelerometer STATIC EXCLUDE_FROM_ALL
  Accelerometer.cpp include/BSP/Accelerometer.hpp)

TARGET_INCLUDE_DIRECTORIES(PcAccelerometer PUBLIC include)
