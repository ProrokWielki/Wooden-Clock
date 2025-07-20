ADD_LIBRARY(
  PcButton STATIC EXCLUDE_FROM_ALL
  Button.cpp include/BSP/Button.hpp)

TARGET_INCLUDE_DIRECTORIES(PcButton PUBLIC include)
