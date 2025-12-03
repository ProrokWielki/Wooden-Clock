IF((CMAKE_BUILD_TYPE STREQUAL "ARM_Debug"))
  ADD_EXECUTABLE(GpioTest gpio_test.cpp)

  TARGET_LINK_LIBRARIES(
    GpioTest
    PRIVATE CMSIS
            MCU
            Clock
            GPIO
            HalTypes
            SysConfig
            TestingFramework
            FakeHandlers)

  TARGET_LINK_OPTIONS(
    GpioTest PRIVATE
    "LINKER:--script=${CMAKE_SOURCE_DIR}/src/stm32/MCU/STM32L452RETx_FLASH.ld")

  ADD_TEST(
    NAME GpioTest
    COMMAND pytest ${CMAKE_CURRENT_SOURCE_DIR}/test_gpio.py
            --name=${CMAKE_CURRENT_BINARY_DIR}/GpioTest
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

ENDIF()
