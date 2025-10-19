ADD_LIBRARY(
  PcCommunication STATIC EXCLUDE_FROM_ALL
  Communication.cpp include/BSP/Communication.hpp)

TARGET_INCLUDE_DIRECTORIES(PcCommunication PUBLIC include)
