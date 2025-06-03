ADD_LIBRARY(
  Magnetometer STATIC EXCLUDE_FROM_ALL
  include/BSP/Magnetometer.hpp Magnetometer.cpp)

TARGET_INCLUDE_DIRECTORIES(Magnetometer PUBLIC include)
