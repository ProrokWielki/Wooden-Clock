ADD_LIBRARY(
  Animations STATIC
  Animations.cpp Animations.hpp)

TARGET_LINK_LIBRARIES(
  Animations
  PRIVATE Hourglass Arrows)

TARGET_INCLUDE_DIRECTORIES(Animations PUBLIC .)

ADD_SUBDIRECTORY(Hourglass)
ADD_SUBDIRECTORY(Arrows)
