IF(NOT ((CMAKE_BUILD_TYPE STREQUAL "x86_Clang") OR (CMAKE_BUILD_TYPE STREQUAL
                                                    "x86_GCC")))
  ADD_LIBRARY(StmOsAbstraction STATIC EXCLUDE_FROM_ALL os_abstraction.cpp
                                                       os_abstraction.hpp)

  TARGET_LINK_LIBRARIES(StmOsAbstraction PRIVATE FreeRTOS)

  TARGET_INCLUDE_DIRECTORIES(StmOsAbstraction PUBLIC .)
ENDIF()
