﻿# CMakeList.txt : CMake project for AoC24, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("AoC24")

# Add source to this project's executable.
add_executable (AoC24 "AoC24.cpp" "AoC24.h" "P01/DistanceBetweenLists.cpp" "FileHelper.cpp" "FileHelper.h" "P01/DistanceBetweenLists.h" "day2/solution.h" "day2/solution.cpp" "day3/solution.h" "day3/solution.cpp" "day4/solution.h" "day4/solution.cpp" "day6/solution.h" "day6/solution.cpp" "day7/solution.h" "day7/solution.cpp"  "day8/solution.h" "day8/solution.cpp" "Helpers/pos.h" "Helpers/pos.cpp"  "day9/solution.h" "day9/solution.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AoC24 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
