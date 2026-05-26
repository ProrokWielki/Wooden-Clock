ADD_LIBRARY(
  X86_BootLoader STATIC EXCLUDE_FROM_ALL
  bootloader.cpp bootloader.hpp)

TARGET_INCLUDE_DIRECTORIES(X86_BootLoader PUBLIC .)
