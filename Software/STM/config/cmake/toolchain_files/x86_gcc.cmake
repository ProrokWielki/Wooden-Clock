SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR x86)

SET(CMAKE_C_COMPILER "gcc")
SET(CMAKE_CXX_COMPILER "g++")

SET(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror --coverage -ftest-coverage" # -fprofile-arcs
    # -ftest-coverage --coverage -fsanitize=undefined"
)
SET(CMAKE_C_FLAGS
    "${CMAKE_CXX_FLAGS}  -Wall -Wextra -Wpedantic -Werror --coverage -ftest-coverage" # -fprofile-arcs
    # -ftest-coverage --coverage -fsanitize=undefined"
)
SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage --coverage")
