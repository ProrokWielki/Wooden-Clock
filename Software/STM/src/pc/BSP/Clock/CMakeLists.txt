ADD_LIBRARY(
  PcClock STATIC EXCLUDE_FROM_ALL
  Clock.cpp include/BSP/Clock.hpp)

TARGET_INCLUDE_DIRECTORIES(PcClock PUBLIC include)
