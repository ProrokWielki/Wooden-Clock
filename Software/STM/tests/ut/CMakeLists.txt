IF((CMAKE_BUILD_TYPE STREQUAL "x86_Clang") OR (CMAKE_BUILD_TYPE STREQUAL
                                               "x86_GCC"))
  INCLUDE(FetchContent)
  FETCHCONTENT_DECLARE(
    googletest
    EXCLUDE_FROM_ALL
    URL https://github.com/google/googletest/releases/download/v1.16.0/googletest-1.18.0.tar.gz
  )
  FETCHCONTENT_MAKEAVAILABLE(googletest)

  IF(TARGET gtest)
    TARGET_COMPILE_OPTIONS(gtest PRIVATE "-Wno-error")
    TARGET_COMPILE_OPTIONS(gtest_main PRIVATE "-Wno-error")

  ENDIF()
ENDIF()

ADD_SUBDIRECTORY(hal)
ADD_SUBDIRECTORY(bsp)
ADD_SUBDIRECTORY(mocks)
