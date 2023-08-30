//#include "pch.h"
#include <iostream>
#include "gtest/gtest.h"
#include "C:\Users\bernh\Documents\25_Sommer2022\PrecompiledHeadersEdges.h"
//#include "C:\Users\bernh\Documents\25_Sommer2022\CMBuild\Debug\TrafficSimulatorApp.pch"

#include "C:\Users\bernh\Documents\25_Sommer2022\simpleWindowUserInterface.h"
#include "C:\Users\bernh\Documents\25_Sommer2022\edge.h"
#include "C:\Users\bernh\Documents\25_Sommer2022\vertex.h"
#include "C:\Users\bernh\Documents\25_Sommer2022\vertexEnd.h"
#include "C:\Users\bernh\Documents\25_Sommer2022\vertexFlex.h"
#include "C:\Users\bernh\Documents\25_Sommer2022\vertexStart.h"
#include "C:\Users\bernh\Documents\25_Sommer2022\vehicle.cpp" 
#include "C:\Users\bernh\Documents\25_Sommer2022\vehicle.h" 
#include "C:\Users\bernh\Documents\25_Sommer2022\velocityToLength.h" 
#include "C:\Users\bernh\Documents\25_Sommer2022\callBackLinks.h" 
#include <memory>

#include "C:\Users\bernh\Documents\25_Sommer2022\userFunctionsOfTheSimpleWindowInterface.h"
#include "C:\Users\bernh\Documents\25_Sommer2022\networkDataStructure.h"


int main(int argc, char** argv) {
	int a = 0;
	//InitGoogleTest();
	RUN_ALL_TESTS();
	std::cin >> a;
	return 0;
}
TEST(NetworkBuildingTest, NCT1) {
	//networkDataStructure testingClass;
	userFunctionsOfTheSimpleWindowInterface networkCreationClass;
	networkCreationClass.networkLaneVector.clear();
	networkCreationClass.establishLane(1000, 1000, 1, 100, 0, true);
	networkCreationClass.establishLane(1000, 1000, 1, 100, 580, false);
	networkCreationClass.establishLane(1000, 1000, 1, 0, 100, true);
	networkCreationClass.establishLane(1000, 1000, 1, 700, 100, false);
	
	//testingClass.establishLane(1, 100, 0, true);
	//testingClass.establishLane(1, 100, 580, false);
	//testingClass.establishLane(1, 0, 100, true);
	//testingClass.establishLane(1, 700, 100, false);
	/*for (auto& i : networkCreationClass.networkLaneVector) {
		networkCreationClass.fillNetworkLaneVector(std::get<0>(i), std::get<1>(i), std::get<2>(i), std::get<3>(i));
	}*/
	
	networkCreationClass.m_CBLptr = new callBackLinks;
	networkCreationClass.m_cObSptr = new concreteObserverSubjekt;
	//networkCreationClass.establishVertexOfGraphA();
	networkCreationClass.graphGenerationFromClickPairs(1000, 1000, 2);
	delete networkCreationClass.m_CBLptr;
	delete networkCreationClass.m_cObSptr;
	EXPECT_EQ(networkCreationClass.appliedGraph.size(), 1);
}



