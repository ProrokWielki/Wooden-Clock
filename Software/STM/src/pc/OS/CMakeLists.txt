ADD_LIBRARY(
  PcOsAbstraction STATIC EXCLUDE_FROM_ALL
  os_abstraction.cpp os_abstraction.hpp)

TARGET_INCLUDE_DIRECTORIES(PcOsAbstraction PUBLIC .)
