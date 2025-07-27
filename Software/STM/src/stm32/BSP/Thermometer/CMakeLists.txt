ADD_LIBRARY(
  StmThermometer STATIC EXCLUDE_FROM_ALL
  Thermometer.cpp include/BSP/Thermometer.hpp)

TARGET_LINK_LIBRARIES(StmThermometer PRIVATE BME280 HAL)

TARGET_INCLUDE_DIRECTORIES(StmThermometer PUBLIC include)
