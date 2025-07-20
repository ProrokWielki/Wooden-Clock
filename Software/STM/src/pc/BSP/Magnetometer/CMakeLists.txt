ADD_LIBRARY(
  PcMagnetometer STATIC EXCLUDE_FROM_ALL
  Magnetometer.cpp include/BSP/Magnetometer.hpp)

TARGET_INCLUDE_DIRECTORIES(PcMagnetometer PUBLIC include)
