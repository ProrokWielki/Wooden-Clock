ADD_LIBRARY(
  StmOsAbstraction STATIC EXCLUDE_FROM_ALL
  os_abstraction.cpp os_abstraction.hpp)

TARGET_LINK_LIBRARIES(
  StmOsAbstraction
  # PUBLIC ISR
  PRIVATE FreeRTOS)

TARGET_INCLUDE_DIRECTORIES(StmOsAbstraction PUBLIC .)
