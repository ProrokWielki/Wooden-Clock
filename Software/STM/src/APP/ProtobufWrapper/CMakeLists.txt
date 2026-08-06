ADD_LIBRARY(
  protobuf_wrapper STATIC
  ProtobufWrapper.cpp ProtobufWrapper.hpp)

TARGET_LINK_LIBRARIES(
  protobuf_wrapper
  PRIVATE esp_msg)
