IF((CMAKE_BUILD_TYPE STREQUAL "x86_Clang") OR (CMAKE_BUILD_TYPE STREQUAL
                                               "x86_GCC"))

  GET_TARGET_PROPERTY(ACCELEROMETER_SOURCES StmAccelerometer SOURCES)

  SET(UPDATED_SOURCES "")

  FOREACH(FILE ${ACCELEROMETER_SOURCES})
    LIST(APPEND UPDATED_SOURCES
         "${CMAKE_SOURCE_DIR}/src/stm32/BSP/Accelerometer/${FILE}")
  ENDFOREACH()

  ADD_EXECUTABLE(UtAccelerometerTest ${UPDATED_SOURCES} accelerometer_test.cpp)
  TARGET_LINK_LIBRARIES(
    UtGpioTest
    GTest::gtest_main
    GTest::gmock
    RegisterMock
    ClockMock
    CmsisBridge
    HalTypes)

  INCLUDE(GoogleTest)
  GTEST_DISCOVER_TESTS(UtAccelerometerTest)

ENDIF()
