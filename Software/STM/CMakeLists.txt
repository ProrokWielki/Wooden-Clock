CMAKE_MINIMUM_REQUIRED(VERSION 3.30)

IF(NOT DEFINED CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE " ")
ENDIF()

IF((CMAKE_BUILD_TYPE STREQUAL "ARM_Debug")
   OR (CMAKE_BUILD_TYPE STREQUAL "ARM_Release")
   OR (CMAKE_BUILD_TYPE STREQUAL "ARM_Size")
   OR (CMAKE_BUILD_TYPE STREQUAL "ARM_Speed"))
  SET(CMAKE_TOOLCHAIN_FILE
      ${CMAKE_SOURCE_DIR}/config/cmake/toolchain_files/stm32l452xx.cmake)
ELSEIF(CMAKE_BUILD_TYPE STREQUAL "x86_Clang")
  SET(CMAKE_TOOLCHAIN_FILE
      ${CMAKE_SOURCE_DIR}/config/cmake/toolchain_files/x86_clang.cmake)
ELSEIF(CMAKE_BUILD_TYPE STREQUAL "x86_GCC")
  SET(CMAKE_TOOLCHAIN_FILE
      ${CMAKE_SOURCE_DIR}/config/cmake/toolchain_files/x86_gcc.cmake)
ELSE()
  MESSAGE(
    FATAL_ERROR
      "\
CMAKE_BUILD_TYPE not set. Please provide -DCMAKE_BUILD_TYPE=<BUILD_TYPE>
Supported BUILD_TYEPE:
  ARM_Release      Release build - no debug symbols and 02\n\
  ARM_Debug        Debug build - debug symbols and 00\n\
  ARM_Size         Size optimized build - no debug symbols\n\
  ARM_Speed        Speed optimized build - no debug symbols\n\
  x86_Clang    Builds libs and unit tests for host machine using clang\n\
  x86_GCC      Builds libs and unit tests for host machine using gcc\n\
  ")
ENDIF()

PROJECT(WoodenClock)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_custom_target(
    copy-compile-commands ALL
    ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_CURRENT_LIST_DIR}
    )

SET(CMAKE_CXX_STANDARD 23)
ENABLE_LANGUAGE(C ASM CXX)

IF(CMAKE_EXPORT_COMPILE_COMMANDS)
  SET(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES
      ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
ENDIF()

ADD_COMPILE_DEFINITIONS(STM32L452xx)

ADD_CUSTOM_TARGET(
  doc COMMAND doxygen ${CMAKE_CURRENT_SOURCE_DIR}/config/doxygen/Doxyfile)

ADD_CUSTOM_TARGET(tidy COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/ci/run_clang_tidy.sh
                               ${CMAKE_BINARY_DIR})

ADD_CUSTOM_TARGET(iwyu COMMAND iwyu-tool -p ${CMAKE_BINARY_DIR})

ADD_CUSTOM_TARGET(
  flash
  COMMAND
    openocd -f /usr/share/openocd/scripts/interface/jlink.cfg -c
    "transport select swd" -f /usr/share/openocd/scripts/target/stm32l4x.cfg -c
    "program ${CMAKE_BINARY_DIR}/src/WoodenClock verify reset exit")

ADD_CUSTOM_TARGET(
  coverage
  COMMAND
    mkdir -p coverage && lcov --ignore-errors inconsistent --ignore-errors
    mismatch -c -d . -o coverage/coverage.in && genhtml coverage/coverage.in -o
    coverage/)

ENABLE_TESTING()

ADD_SUBDIRECTORY(lib)
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(tests)
