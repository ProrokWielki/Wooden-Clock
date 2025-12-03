IF((CMAKE_BUILD_TYPE STREQUAL "ARM_Debug"))
  ADD_EXECUTABLE(SpiTest spi_test.cpp)

  TARGET_LINK_LIBRARIES(
    SpiTest
    PRIVATE CMSIS
            SPI
            Clock
            SysConfig
            HalTypes
            GPIO
            MCU
            TestingFramework
            FakeHandlers)

  TARGET_LINK_OPTIONS(
    SpiTest PRIVATE
    "LINKER:--script=${CMAKE_SOURCE_DIR}/src/stm32/MCU/STM32L452RETx_FLASH.ld")

  ADD_TEST(
    NAME SpiTest
    COMMAND pytest ${CMAKE_CURRENT_SOURCE_DIR}/test_spi.py
            --name=${CMAKE_CURRENT_BINARY_DIR}/SpiTest -s -v
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

ENDIF()
