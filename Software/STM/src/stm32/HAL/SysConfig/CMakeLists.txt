ADD_LIBRARY(
  SysConfig STATIC EXCLUDE_FROM_ALL
  include/HAL/SysConfig.hpp SysConfig.cpp)

TARGET_LINK_LIBRARIES(
  SysConfig
  PRIVATE CmsisBridge
  PUBLIC Register HalTypes GPIO)

TARGET_INCLUDE_DIRECTORIES(SysConfig PUBLIC include)
