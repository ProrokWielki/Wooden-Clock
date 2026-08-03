set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../Messages/tools/nanopb/extra)
find_package(Nanopb REQUIRED)

add_subdirectory(esp)
