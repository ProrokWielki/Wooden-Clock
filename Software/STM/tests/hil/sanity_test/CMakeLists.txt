IF((CMAKE_BUILD_TYPE STREQUAL "ARM_Debug"))
  ADD_EXECUTABLE(SanityTest sanity_test.cpp)

  TARGET_LINK_LIBRARIES(SanityTest PUBLIC CMSIS Register MCU TestingFramework FakeHandlers)

  TARGET_LINK_OPTIONS(
    SanityTest PRIVATE
    "LINKER:--script=${CMAKE_SOURCE_DIR}/src/stm32/MCU/STM32L452RETx_FLASH.ld")

  ADD_TEST(
    NAME SanityTest
    COMMAND pytest ${CMAKE_CURRENT_SOURCE_DIR}/test_sanity.py
            --name=${CMAKE_CURRENT_BINARY_DIR}/SanityTest -s -vvv
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

ENDIF()
