ADD_LIBRARY(
  CmsisBridge STATIC EXCLUDE_FROM_ALL
  cmsis_bridge.cpp include/cmsis_bridge/cmsis_bridge.hpp)

TARGET_LINK_LIBRARIES(
  CmsisBridge
  PRIVATE CMSIS
  PUBLIC HalTypes)

TARGET_INCLUDE_DIRECTORIES(CmsisBridge PUBLIC include)
