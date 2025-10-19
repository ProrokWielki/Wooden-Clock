IF(NOT ((CMAKE_BUILD_TYPE STREQUAL "x86_Clang") OR (CMAKE_BUILD_TYPE STREQUAL
                                                    "x86_GCC")))

  ADD_LIBRARY(ISR EXCLUDE_FROM_ALL InterruptServiceRoutine.cpp)

  TARGET_LINK_LIBRARIES(ISR PRIVATE CMSIS FreeRTOS BSP)

ENDIF()
