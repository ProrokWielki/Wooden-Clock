ADD_LIBRARY(
  Arrows
  Arrows.cpp Arrows.hpp frames/1.hpp frames/2.hpp)

TARGET_LINK_LIBRARIES(
  Arrows
  PUBLIC EmbedGUI)
