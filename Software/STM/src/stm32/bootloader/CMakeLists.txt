IF(NOT ((CMAKE_BUILD_TYPE STREQUAL "x86_Clang") OR (CMAKE_BUILD_TYPE STREQUAL
                                                    "x86_GCC")))
  ADD_LIBRARY(STM_BootLoader STATIC EXCLUDE_FROM_ALL bootloader.cpp
                                                     bootloader.hpp)

  TARGET_LINK_LIBRARIES(STM_BootLoader PRIVATE CMSIS FreeRTOS)

  TARGET_INCLUDE_DIRECTORIES(STM_BootLoader PUBLIC .)
ENDIF()
