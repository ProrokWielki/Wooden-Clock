ADD_LIBRARY(
  ButtonHandler STATIC
  ButtonHandler.cpp ButtonStateMachine.cpp
  include/ButtonHandler/ButtonHandler.hpp
  include/ButtonHandler/detail/ButtonStateMachine.hpp)

TARGET_INCLUDE_DIRECTORIES(ButtonHandler INTERFACE includes/ButtonHandler)

TARGET_LINK_LIBRARIES(
  ButtonHandler
  PRIVATE BSP)
