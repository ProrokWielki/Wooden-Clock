nanopb_generate_cpp(
  TARGET esp_msg
  RELPATH detail
  esp_msg.proto
  detail/time.proto
  detail/weather_forecast.proto)
