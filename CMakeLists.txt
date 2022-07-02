cmake_minimum_required(VERSION 3.16.2 FATAL_ERROR)


project(TrafficSimulator LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
#set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)
enable_testing()

set(Sources 
	main.cpp 
	edge.cpp
	callBackLinks.cpp 
	PrecompiledHeadersEdges.cpp 
	random_speed_neu.cpp 
	vehicle.cpp
	flowSimulation1NegStraight.cpp
	flowSimulation1PosStraight.cpp
	flowSimulation2NegStraight.cpp
	flowSimulation2PosStraight.cpp
	graph.cpp
	graphTrafficGenerationOnAllRoutes.cpp
	graphTrafficGenerationOnFastRoutes.cpp
	graphTrafficGenerationTrafficOnRoutesSelectedByDijkstraAlg.cpp
	networkCreationOfVHLinks.cpp
	networkCreationVHLinks.cpp
	observer.cpp
	observer_subjekt.cpp
	PrintInGDIplusWin1LN.cpp
	PrintInGDIplusWin1LP.cpp
	PrintInGDIplusWin2LN.cpp
	PrintInGDIplusWin2LP.cpp
	PrintInGDIplusWin1LN.cpp
	PrintInGDIplusWindow.cpp
	PrintInGDIplusWin1LN.cpp
	PrintInGDIplusWinEmpty.cpp
	route.cpp
	sectionVehicleSet.cpp
	selectionFlowSimulation.cpp
	velocityToLength.cpp
	vertex.cpp
	vertexEnd.cpp
	vertexFlex.cpp
	vertexStart.cpp
	)

add_subdirectory(googletest)

add_library(TrafficSimulatorApp STATIC ${Sources}) 

add_subdirectory(unitTest)
