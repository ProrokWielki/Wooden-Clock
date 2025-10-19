IF((CMAKE_BUILD_TYPE STREQUAL "x86_Clang") OR (CMAKE_BUILD_TYPE STREQUAL
                                               "x86_GCC"))

  GET_TARGET_PROPERTY(GPIO_SOURCES GPIO SOURCES)

  SET(UPDATED_SOURCES "")

  FOREACH(FILE ${GPIO_SOURCES})
    LIST(APPEND UPDATED_SOURCES
         "${CMAKE_SOURCE_DIR}/src/stm32/HAL/GPIO/${FILE}")
  ENDFOREACH()

  ADD_EXECUTABLE(UtGpioTest ${UPDATED_SOURCES} gpio_test.cpp)
  TARGET_LINK_LIBRARIES(
    UtGpioTest
    GTest::gtest_main
    GTest::gmock
    RegisterMock
    ClockMock
    CmsisBridge
    HalTypes)

  INCLUDE(GoogleTest)
  GTEST_DISCOVER_TESTS(UtGpioTest)

ENDIF()
