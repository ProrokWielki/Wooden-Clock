ADD_LIBRARY(
  HalTypes STATIC EXCLUDE_FROM_ALL
  include/HAL/types.hpp types.cpp)

TARGET_INCLUDE_DIRECTORIES(HalTypes PUBLIC include)
