set(FreeRTOS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/FreeRTOS/FreeRTOS/FreeRTOS-Kernel)

file(
  GLOB
  SRCS
  ${FreeRTOS_SRC_DIR}/*.c
  ${FreeRTOS_SRC_DIR}/portable/MemMang/heap_3.c
  ${FreeRTOS_SRC_DIR}/portable/GCC/ARM_CM4F/*
  ${FreeRTOS_SRC_DIR}/include/*
  ${CMAKE_CURRENT_SOURCE_DIR}/FreeRTOSConfig.h)

add_library(FreeRTOS STATIC ${SRCS})

target_include_directories(
  FreeRTOS PUBLIC  ${FreeRTOS_SRC_DIR}/include .
                   ${FreeRTOS_SRC_DIR}/portable/GCC/ARM_CM4F)

set_target_properties(FreeRTOS PROPERTIES LINKER_LANGUAGE C)
