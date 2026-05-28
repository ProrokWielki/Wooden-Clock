ADD_LIBRARY(
  debug_messages_handler STATIC
  DebugMessagesHandler.cpp DebugMessagesHandler.hpp)

TARGET_LINK_LIBRARIES(
  debug_messages_handler
  PRIVATE BSP bootloader)
