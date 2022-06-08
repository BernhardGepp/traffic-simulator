cmake_minimum_required(VERSION 3.16.2 FATAL_ERROR)


project(Projekt1 LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
#set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)
enable_testing()

set(Sources main.cpp callBackLinks.cpp PrecompiledHeadersEdges.cpp 
	random_speed_neu.cpp 
	vehicle.cpp)
add_subdirectory(googletest)



add_library(Projekt1 STATIC ${Sources}) 



add_subdirectory(unitTest)
