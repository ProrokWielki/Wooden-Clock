IF(NOT ((CMAKE_BUILD_TYPE STREQUAL "x86_Clang") OR (CMAKE_BUILD_TYPE STREQUAL
                                                    "x86_GCC")))

  ADD_LIBRARY(HAL STATIC EXCLUDE_FROM_ALL HAL.cpp include/HAL/HAL.hpp)

  TARGET_LINK_LIBRARIES(
    HAL
    PUBLIC I2C
           SPI
           Register
           DMA
           Timer
           GPIO
           74HC595
           LSM9DS1
           BME280
           S25FL129P
           Flash
           TLC59208F
           SysConfig
           ISR
           QSPI
           RTC
           USART
           Clock
           Power)

  TARGET_INCLUDE_DIRECTORIES(HAL PUBLIC include)
ENDIF()

ADD_SUBDIRECTORY(Register)
ADD_SUBDIRECTORY(DMA)
ADD_SUBDIRECTORY(GPIO)
ADD_SUBDIRECTORY(I2C)
ADD_SUBDIRECTORY(SPI)
ADD_SUBDIRECTORY(Timer)
ADD_SUBDIRECTORY(ISR)
ADD_SUBDIRECTORY(Clock)
ADD_SUBDIRECTORY(RTC)
ADD_SUBDIRECTORY(USART)
ADD_SUBDIRECTORY(Flash)
ADD_SUBDIRECTORY(SysConfig)
ADD_SUBDIRECTORY(Power)
ADD_SUBDIRECTORY(QSPI)
ADD_SUBDIRECTORY(hal_types)

IF(NOT ((CMAKE_BUILD_TYPE STREQUAL "x86_Clang") OR (CMAKE_BUILD_TYPE STREQUAL
                                                    "x86_GCC")))
  ADD_SUBDIRECTORY(cmsis_bridge)
ENDIF()
