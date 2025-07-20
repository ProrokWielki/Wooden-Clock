ADD_LIBRARY(
  Magnetometer STATIC EXCLUDE_FROM_ALL
  include/BSP/Magnetometer.hpp Magnetometer.cpp)
  
TARGET_LINK_LIBRARIES(
  Magnetometer
  PRIVATE LSM9DS1 HAL)

TARGET_INCLUDE_DIRECTORIES(Magnetometer PUBLIC include)
