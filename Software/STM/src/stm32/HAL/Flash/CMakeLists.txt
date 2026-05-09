ADD_LIBRARY(
  Flash STATIC EXCLUDE_FROM_ALL
  Flash.cpp include/HAL/Flash.hpp)

TARGET_LINK_LIBRARIES(
  Flash
  PRIVATE CmsisBridge Register HalTypes)

TARGET_INCLUDE_DIRECTORIES(Flash PUBLIC include)
