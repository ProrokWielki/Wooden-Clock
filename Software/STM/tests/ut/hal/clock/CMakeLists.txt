IF((CMAKE_BUILD_TYPE STREQUAL "x86_Clang") OR (CMAKE_BUILD_TYPE STREQUAL
                                               "x86_GCC"))

  GET_TARGET_PROPERTY(CLOCK_SOURCES Clock SOURCES)

  SET(UPDATED_SOURCES "")

  FOREACH(FILE ${CLOCK_SOURCES})
    LIST(APPEND UPDATED_SOURCES "${CMAKE_SOURCE_DIR}/src/stm32/HAL/Clock/${FILE}")
  ENDFOREACH()

  ADD_EXECUTABLE(UtClockTest ${UPDATED_SOURCES} clock_test.cpp)
  TARGET_LINK_LIBRARIES(UtClockTest GTest::gtest_main GTest::gmock RegisterMock
                        CmsisBridgeMock HalTypes Clock)

  TARGET_INCLUDE_DIRECTORIES(UtClockTest
                             PUBLIC ${CMAKE_SOURCE_DIR}/src/HAL/Clock/include)

  INCLUDE(GoogleTest)
  GTEST_DISCOVER_TESTS(UtClockTest)

ENDIF()
