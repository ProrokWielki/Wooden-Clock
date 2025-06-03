SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR x86)

SET(CMAKE_C_COMPILER "clang")
SET(CMAKE_CXX_COMPILER "clang++")

SET(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Wpedantic -Werror" # -fprofile-arcs
                                                          # -ftest-coverage
                                                          # -fsanitize=undefined"
)
SET(CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS} -g -Wall -Wextra -Wpedantic -Werror" # -fprofile-arcs
                                                        # -ftest-coverage
                                                        # -fsanitize=undefined"
)
# SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
