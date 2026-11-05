ADD_LIBRARY(
  StmAudioOutput STATIC EXCLUDE_FROM_ALL
  AudioOutput.cpp include/BSP/AudioOutput.hpp)

TARGET_LINK_LIBRARIES(
  StmAudioOutput
  PRIVATE HAL)

TARGET_INCLUDE_DIRECTORIES(StmAudioOutput PUBLIC include)
