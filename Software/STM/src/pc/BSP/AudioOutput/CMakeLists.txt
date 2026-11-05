ADD_LIBRARY(
  PcAudioOutput STATIC EXCLUDE_FROM_ALL
  AudioOutput.cpp include/BSP/AudioOutput.hpp)

TARGET_INCLUDE_DIRECTORIES(PcAudioOutput PUBLIC include)
