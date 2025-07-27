ADD_LIBRARY(
  Animations STATIC
  Animations.cpp Animations.hpp)

TARGET_LINK_LIBRARIES(
  Animations
  PRIVATE Hourglass Arrows)

ADD_SUBDIRECTORY(Hourglass)
ADD_SUBDIRECTORY(Arrows)
