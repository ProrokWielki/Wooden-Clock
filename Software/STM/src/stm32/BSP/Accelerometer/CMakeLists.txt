ADD_LIBRARY(
  StmAccelerometer STATIC EXCLUDE_FROM_ALL
  Accelerometer.cpp include/BSP/Accelerometer.hpp)

TARGET_LINK_LIBRARIES(StmAccelerometer PRIVATE LSM9DS1 HAL)

TARGET_INCLUDE_DIRECTORIES(StmAccelerometer PUBLIC include)
