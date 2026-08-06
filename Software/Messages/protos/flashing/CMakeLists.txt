nanopb_generate_cpp(
  TARGET flashing_msg
  RELPATH detail
  flashing_msg.proto
  detail/flashing_state.proto
  detail/flashing_start.proto
  detail/page_data.proto)

