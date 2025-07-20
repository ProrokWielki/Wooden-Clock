ADD_LIBRARY(
  TestingFramework STATIC EXCLUDE_FROM_ALL
  testing_framework.cpp testing_framework.hpp)

TARGET_INCLUDE_DIRECTORIES(TestingFramework PUBLIC .)
