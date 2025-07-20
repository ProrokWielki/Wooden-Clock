IF((CMAKE_BUILD_TYPE STREQUAL "ARM_Debug"))
  ADD_EXECUTABLE(RegisterTest register_test.cpp)

  TARGET_LINK_LIBRARIES(RegisterTest PRIVATE CMSIS Register MCU
                                             TestingFramework FakeHandlers)

  TARGET_LINK_OPTIONS(
    RegisterTest PRIVATE
    "LINKER:--script=${CMAKE_SOURCE_DIR}/src/stm32/MCU/STM32L452RETx_FLASH.ld")

  ADD_TEST(
    NAME RegisterTest
    COMMAND pytest ${CMAKE_CURRENT_SOURCE_DIR}/test_register.py
            --name=${CMAKE_CURRENT_BINARY_DIR}/RegisterTest
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

ENDIF()
