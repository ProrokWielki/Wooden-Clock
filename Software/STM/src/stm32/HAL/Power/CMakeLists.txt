ADD_LIBRARY(
  Power STATIC EXCLUDE_FROM_ALL
  include/HAL/Power.hpp Power.cpp)

TARGET_LINK_LIBRARIES(
  Power
  PRIVATE CmsisBridge
  PUBLIC Register HalTypes)

TARGET_INCLUDE_DIRECTORIES(Power PUBLIC include)
