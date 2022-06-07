cmake_minimum_required(VERSION 3.16.2 FATAL_ERROR)

set(This ExampleTests)
set(Sources 
	test.cpp
)

add_executable(${This} ${Sources} )
#set(WIN32 True)
set(Boost_USE_STATIC_LIBS ON)
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "D:/vs_Community/boost/boost_1_64_0/boost_1_64_0")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "D:/vs_Community/boost/boost_1_64_0/boost_1_64_0/stage/lib")
find_package(Boost 1.64.0 REQUIRED)
if(Boost_FOUND)

	target_include_directories(${This} PUBLIC ${Boost_INCLUDE_DIRS})
	#target_link_libraries(${This} ${Boost_LIBARIES})
    
endif()

find_package(Microsoft.GSL EXACT REQUIRED PATHS "C:/GSL/build-x86")
message(STATUS ${Microsoft.GSL_FOUND})
message(STATUS ${Microsoft.GSL_INCLUDE_DIRS})

#target_link_libraries(${This} Microsoft.GSL::GSL)
target_include_directories(${This} PUBLIC Microsoft.GSL::GSL)
target_link_libraries(${This} PUBLIC
	gtest_main
	WIN32 Projekt1
	Microsoft.GSL::GSL
	${Boost_LIBARIES}
)

add_test(NAME ${This} COMMAND ${This})