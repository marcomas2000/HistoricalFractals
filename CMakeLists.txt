# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("HistoricalFractals")

# Include sub-projects.
add_subdirectory ("JuliaSets")
add_subdirectory ("MandelbrotSets")
add_subdirectory ("LyapunovSpace")
add_subdirectory ("SectSets")

