ADD_LIBRARY(
  Communication STATIC EXCLUDE_FROM_ALL
  Communication.cpp include/BSP/Communication.hpp)

TARGET_LINK_LIBRARIES(
  Communication
  PRIVATE HAL)

TARGET_INCLUDE_DIRECTORIES(Communication PUBLIC include)
