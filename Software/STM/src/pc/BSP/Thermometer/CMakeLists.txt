ADD_LIBRARY(
  PcThermometer STATIC EXCLUDE_FROM_ALL
  Thermometer.cpp include/BSP/Thermometer.hpp)

TARGET_INCLUDE_DIRECTORIES(PcThermometer PUBLIC include)
