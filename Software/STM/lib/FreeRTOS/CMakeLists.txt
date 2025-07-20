IF(NOT ((CMAKE_BUILD_TYPE STREQUAL "x86_Clang") OR (CMAKE_BUILD_TYPE STREQUAL
                                                    "x86_GCC")))

  SET(FreeRTOS_SRC_DIR
      ${CMAKE_CURRENT_SOURCE_DIR}/FreeRTOS/FreeRTOS/FreeRTOS-Kernel)

  FILE(
    GLOB
    SRCS
    ${FreeRTOS_SRC_DIR}/*.c
    ${FreeRTOS_SRC_DIR}/portable/MemMang/heap_3.c
    ${FreeRTOS_SRC_DIR}/portable/GCC/ARM_CM4F/*
    ${FreeRTOS_SRC_DIR}/include/*
    ${CMAKE_CURRENT_SOURCE_DIR}/FreeRTOSConfig.h)

  ADD_LIBRARY(FreeRTOS STATIC EXCLUDE_FROM_ALL ${SRCS})

  TARGET_INCLUDE_DIRECTORIES(
    FreeRTOS PUBLIC ${FreeRTOS_SRC_DIR}/include .
                    ${FreeRTOS_SRC_DIR}/portable/GCC/ARM_CM4F)

  SET_TARGET_PROPERTIES(FreeRTOS PROPERTIES LINKER_LANGUAGE C)

ENDIF()
