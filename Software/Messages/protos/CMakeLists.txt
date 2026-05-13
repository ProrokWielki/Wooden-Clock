set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../Messages/tools/nanopb/extra)
find_package(Nanopb REQUIRED)

nanopb_generate_cpp(TARGET message_time time.proto)
