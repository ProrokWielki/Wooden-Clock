ADD_LIBRARY(
  Timer STATIC EXCLUDE_FROM_ALL
  include/HAL/Timer.hpp Timer.cpp)

TARGET_INCLUDE_DIRECTORIES(Timer PUBLIC include)

TARGET_LINK_LIBRARIES(
  Timer
  PRIVATE CmsisBridge HalTypes
  PUBLIC Register)
