IF((CMAKE_BUILD_TYPE STREQUAL "x86_Clang") OR (CMAKE_BUILD_TYPE STREQUAL
                                               "x86_GCC"))

  ADD_EXECUTABLE(UtRegisterTest register_test.cpp)
  TARGET_LINK_LIBRARIES(UtRegisterTest GTest::gtest_main Register)

  INCLUDE(GoogleTest)
  GTEST_DISCOVER_TESTS(UtRegisterTest)

ENDIF()
