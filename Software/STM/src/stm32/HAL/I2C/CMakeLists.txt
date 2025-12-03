ADD_LIBRARY(
  I2C STATIC EXCLUDE_FROM_ALL
  I2C.cpp include/HAL/I2C.hpp)

TARGET_LINK_LIBRARIES(
  I2C
  PUBLIC Register
  PRIVATE CMSIS
          Clock
          CmsisBridge
          HalTypes
          GPIO
          DMA
          SysConfig)

TARGET_INCLUDE_DIRECTORIES(I2C PUBLIC include)
