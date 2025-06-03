IF((CMAKE_BUILD_TYPE STREQUAL "x86_Clang") OR (CMAKE_BUILD_TYPE STREQUAL
                                               "x86_GCC"))
  INCLUDE(FetchContent)
  FETCHCONTENT_DECLARE(
    googletest
    EXCLUDE_FROM_ALL
    URL https://github.com/google/googletest/releases/download/v1.16.0/googletest-1.16.0.tar.gz
  )
  FETCHCONTENT_MAKEAVAILABLE(googletest)
ENDIF()

ADD_SUBDIRECTORY(hal)
ADD_SUBDIRECTORY(mocks)
