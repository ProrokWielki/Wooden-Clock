IF((CMAKE_BUILD_TYPE STREQUAL "ARM_Debug"))
  ADD_EXECUTABLE(RtcTest rtc_test.cpp)

  TARGET_LINK_LIBRARIES(
    RtcTest
    PRIVATE CMSIS
            RTC
            Clock
            HalTypes
            Power
            GPIO
            MCU
            TestingFramework
            FakeHandlers)

  TARGET_LINK_OPTIONS(
    RtcTest PRIVATE
    "LINKER:--script=${CMAKE_SOURCE_DIR}/src/stm32/MCU/STM32L452RETx_FLASH.ld")

  ADD_TEST(
    NAME RtcTest
    COMMAND pytest ${CMAKE_CURRENT_SOURCE_DIR}/test_rtc.py
            --name=${CMAKE_CURRENT_BINARY_DIR}/RtcTest -s -v
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

ENDIF()
