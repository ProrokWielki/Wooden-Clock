ADD_LIBRARY(
  DAC STATIC EXCLUDE_FROM_ALL
  DAC.cpp include/HAL/DAC.hpp)

TARGET_LINK_LIBRARIES(
  DAC
  PRIVATE HalTypes
          APP
          CmsisBridge
          GPIO
          Clock
          Register
          DMA)

TARGET_INCLUDE_DIRECTORIES(DAC PUBLIC include)
