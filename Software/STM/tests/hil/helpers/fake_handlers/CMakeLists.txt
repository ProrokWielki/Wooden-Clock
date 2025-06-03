IF((CMAKE_BUILD_TYPE STREQUAL "ARM_Debug"))
  ADD_LIBRARY(FakeHandlers fake_handlers.c)
ENDIF()
