SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR arm)

SET(CMAKE_C_COMPILER "arm-none-eabi-gcc")
SET(CMAKE_CXX_COMPILER "arm-none-eabi-g++")
SET(CMAKE_SIZE "arm-none-eabi-size")

SET(O_FLAG "O0")
SET(DEBUG_FLAG "-g")

IF(CMAKE_BUILD_TYPE STREQUAL "ARM_Debug")
  SET(DEBUG_FLAG "-g")
  SET(O_FLAG "-O0")
ELSEIF(CMAKE_BUILD_TYPE STREQUAL "ARM_Release")
  SET(DEBUG_FLAG "")
  SET(O_FLAG "-O2")
ELSEIF(CMAKE_BUILD_TYPE STREQUAL "ARM_Speed")
  SET(DEBUG_FLAG "")
  SET(O_FLAG "-Ofast")
ELSEIF(CMAKE_BUILD_TYPE STREQUAL "ARM_Size")
  SET(DEBUG_FLAG "")
  SET(O_FLAG "-Os")
ENDIF()

SET(EXTRA_FLAGS
    "${DEBUG_FLAG} ${O_FLAG} -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Wall -Wextra -Wpedantic -Werror"
)

SET(CMAKE_EXE_LINKER_FLAGS
    "-specs=nosys.specs -mcpu=cortex-m4 -Wl,--print-memory-usage"
    CACHE INTERNAL "")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_FLAGS}")
SET(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_FLAGS}")
