IF((CMAKE_BUILD_TYPE STREQUAL "ARM_Debug"))
  ADD_EXECUTABLE(I2cTest i2c_test.cpp)

  TARGET_LINK_LIBRARIES(
    I2cTest
    PRIVATE CMSIS
            I2C
            Clock
            HalTypes
            GPIO
            MCU
            TestingFramework
            FakeHandlers)

  TARGET_LINK_OPTIONS(
    I2cTest PRIVATE
    "LINKER:--script=${CMAKE_SOURCE_DIR}/src/stm32/MCU/STM32L452RETx_FLASH.ld")

  ADD_TEST(
    NAME I2cTest
    COMMAND pytest ${CMAKE_CURRENT_SOURCE_DIR}/test_i2c.py
            --name=${CMAKE_CURRENT_BINARY_DIR}/I2cTest
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

ENDIF()
