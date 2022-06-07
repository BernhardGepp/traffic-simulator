//#include "pch.h"
#include <iostream>
#include "gtest/gtest.h"
//#include "C:\Users\bernh\Documents\23_Sommer2021\Projekt1\PrecompiledHeadersEdges.h"
#include "C:\Users\bernh\Documents\23_Sommer2021\Projekt1\network.h"
#include "C:\Users\bernh\Documents\23_Sommer2021\Projekt1\edge.h"
#include "C:\Users\bernh\Documents\23_Sommer2021\Projekt1\vertex.h"
#include "C:\Users\bernh\Documents\23_Sommer2021\Projekt1\vertexEnd.h"
#include "C:\Users\bernh\Documents\23_Sommer2021\Projekt1\vertexFlex.h"
#include "C:\Users\bernh\Documents\23_Sommer2021\Projekt1\vertexStart.h"
#include "C:\Users\bernh\Documents\23_Sommer2021\Projekt1\vehicle.cpp" 
#include "C:\Users\bernh\Documents\23_Sommer2021\Projekt1\vehicle.h" 
#include "C:\Users\bernh\Documents\23_Sommer2021\Projekt1\velocityToLength.h" 
#include "C:\Users\bernh\Documents\23_Sommer2021\Projekt1\callBackLinks.h"
#include  <fstream> 
#include <memory>
#include "C:\Users\bernh\Documents\23_Sommer2021\Projekt1\networkCreationVHLinks.h"
#include "C:\Users\bernh\Documents\23_Sommer2021\Projekt1\networkCreationOfVHLinks.h"

int main(int argc, char** argv) {
	int a = 0;
	//InitGoogleTest();
	RUN_ALL_TESTS();
	std::cin >> a;
	return 0;
}
TEST(NetworkBuildingTest, NCT1) {
	networkCreationVHLinks testingClass;
	networkCreationOfVHLinks networkCreationClass;
	testingClass.networkLaneVector.clear();
	testingClass.establishLane(1, 100, 0, true);
	testingClass.establishLane(1, 100, 580, false);
	testingClass.establishLane(1, 0, 100, true);
	testingClass.establishLane(1, 700, 100, false);
	for (auto& i : testingClass.networkLaneVector) {
		networkCreationClass.fillNetworkLaneVector(std::get<0>(i), std::get<1>(i), std::get<2>(i), std::get<3>(i));
	}
	
	networkCreationClass.m_CBLptr = new callBackLinks;
	networkCreationClass.m_cObSptr = new concreteObserverSubjekt;
	networkCreationClass.establishVertexOfGraphA();
	delete networkCreationClass.m_CBLptr;
	delete networkCreationClass.m_cObSptr;
	EXPECT_EQ(networkCreationClass.appliedGraph.size(), 1);
}
TEST(NetworkBuildingTest, NCT2) {
	networkCreationVHLinks testingClass;
	networkCreationOfVHLinks networkCreationClass;
	testingClass.networkLaneVector.clear();
	testingClass.establishLane(1, 100, 0, true);
	testingClass.establishLane(1, 100, 400, false);
	testingClass.establishLane(1, 100, 410, true);
	testingClass.establishLane(1, 100, 700, false);
	testingClass.establishLane(1, 0, 300, true);
	testingClass.establishLane(1, 300, 300, false);
	testingClass.establishLane(1, 0, 600, true);
	testingClass.establishLane(1, 300, 600, false);
	for (auto& i : testingClass.networkLaneVector) {
		networkCreationClass.fillNetworkLaneVector(std::get<0>(i), std::get<1>(i), std::get<2>(i), std::get<3>(i));
	}

	networkCreationClass.m_CBLptr = new callBackLinks;
	networkCreationClass.m_cObSptr = new concreteObserverSubjekt;
	networkCreationClass.establishVertexOfGraphA();
	delete networkCreationClass.m_CBLptr;
	delete networkCreationClass.m_cObSptr;
	EXPECT_EQ(networkCreationClass.appliedGraph.size(), 2);
}
TEST(NetworkBuildingTest, NCT3) {
	networkCreationVHLinks testingClass;
	networkCreationOfVHLinks networkCreationClass;
	testingClass.networkLaneVector.clear();
	//Building a Cross
	//1st Link horizontal left link
	testingClass.establishLane(1, 0, 100, true);
	testingClass.establishLane(1, 100, 100, false);
	//2nd Link vertical upper link
	testingClass.establishLane(1, 100, 0, true);
	testingClass.establishLane(1, 100, 100, false);
	//3rd Link vertical lower link
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 200, false);
	//4th Link horizontal right Link
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 200, 100, false);
	for (auto& i : testingClass.networkLaneVector) {
		networkCreationClass.fillNetworkLaneVector(std::get<0>(i), std::get<1>(i), std::get<2>(i), std::get<3>(i));
	}

	networkCreationClass.m_CBLptr = new callBackLinks;
	networkCreationClass.m_cObSptr = new concreteObserverSubjekt;
	networkCreationClass.establishVertexOfGraphA();
	delete networkCreationClass.m_CBLptr;
	delete networkCreationClass.m_cObSptr;
	EXPECT_EQ(networkCreationClass.appliedGraph.size(), 1);
}
TEST(NetworkBuildingTest, NCT4) {
	networkCreationVHLinks testingClass;
	networkCreationOfVHLinks networkCreationClass;
	testingClass.networkLaneVector.clear();
	//1st Link
	testingClass.establishLane(1, 0, 0, true);
	testingClass.establishLane(1, 0, 200, false);
	//2nd Link 
	testingClass.establishLane(1, 0, 200, true);
	testingClass.establishLane(1, 400, 200, false);
	//3rd Link 
	testingClass.establishLane(1, 400, 200, true);
	testingClass.establishLane(1, 400, 0, false);
	//4th Link 
	testingClass.establishLane(1, 400, 0, true);
	testingClass.establishLane(1, 0, 0, false);
	//5th Link
	testingClass.establishLane(1, 50, 50, true);
	testingClass.establishLane(1, 50, 150, false);
	//6th Link 
	testingClass.establishLane(1, 50, 150, true);
	testingClass.establishLane(1, 350, 150, false);
	//7th Link 
	testingClass.establishLane(1, 350, 150, true);
	testingClass.establishLane(1, 350, 50, false);
	//8th Link 
	testingClass.establishLane(1, 350, 50, true);
	testingClass.establishLane(1, 50, 50, false);
	for (auto& i : testingClass.networkLaneVector) {
		networkCreationClass.fillNetworkLaneVector(std::get<0>(i), std::get<1>(i), std::get<2>(i), std::get<3>(i));
	}

	networkCreationClass.m_CBLptr = new callBackLinks;
	networkCreationClass.m_cObSptr = new concreteObserverSubjekt;
	networkCreationClass.establishVertexOfGraphA();
	delete networkCreationClass.m_CBLptr;
	delete networkCreationClass.m_cObSptr;
	EXPECT_EQ(networkCreationClass.appliedGraph.size(), 2);
}

TEST(NetworkBuildingTest, EdgeCases1) {
	networkCreationVHLinks testingClass;
	//TestCase: Overlay of 2 horizontal connections with one and two lanes, which should not work at the field boundary!
	testingClass.networkLaneVector.clear(); 
	testingClass.establishLane(1, 0, 580, true);
	testingClass.establishLane(1, 1090, 580, false);
	testingClass.establishLane(2, 0, 590, true);
	testingClass.establishLane(2, 1090, 590, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 1);
	testingClass.networkLaneVector.clear();
	//TestCase: Overlay of 2 horizontal connections with one and two lanes, which should not work at the field boundary! Made outside valid range.
	testingClass.establishLane(1, 0, 600, true);
	testingClass.establishLane(1, 1090, 600, false);
	testingClass.establishLane(2, 0, 600, true);
	testingClass.establishLane(2, 1090, 600, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 1);
	//TestCase: Overlay of 2 vertical connections with one and two lanes, which should not work at the field boundary!
	testingClass.networkLaneVector.clear();
	testingClass.establishLane(1, 1080, 0, true);
	testingClass.establishLane(1, 1080, 590, false);
	testingClass.establishLane(2, 1090, 0, true);
	testingClass.establishLane(2, 1090, 590, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 1);
	//TestCase: Overlay of 2 vertical connections with one and two lanes, which should not work at the field boundary! Made outside valid range.
	testingClass.networkLaneVector.clear();
	testingClass.establishLane(1, 1200, 0, true);
	testingClass.establishLane(1, 1200, 590, false);
	testingClass.establishLane(2, 1200, 0, true);
	testingClass.establishLane(2, 1200, 590, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 1);
}
TEST(NetworkBuildingTest, EdgeCases2) {
	networkCreationVHLinks testingClass;
	testingClass.networkLaneVector.clear();
	//Links with ONE lane
	//links generated immediately one after the other
	//vertical Top->Down
	//1st
	testingClass.establishLane(1, 900, 10, true);
	testingClass.establishLane(1, 900, 100, false);
	//2nd
	testingClass.establishLane(1, 900, 100, true);
	testingClass.establishLane(1, 900, 200, false);

	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	testingClass.networkLaneVector.clear();
	//links generated immediately one after the other
	//vertical Bottom->up
	//1st
	testingClass.establishLane(1, 900, 200, true);
	testingClass.establishLane(1, 900, 100, false);
	//2nd
	testingClass.establishLane(1, 900, 100, true);
	testingClass.establishLane(1, 900, 10, false);

	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	testingClass.networkLaneVector.clear();

	//vertical opposite directions, approaching each other(1)
	//1st
	testingClass.establishLane(1, 900, 10, true);
	testingClass.establishLane(1, 900, 100, false);
	//2nd
	testingClass.establishLane(1, 900, 200, true);
	testingClass.establishLane(1, 900, 100, false);

	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	testingClass.networkLaneVector.clear();

	//vertical opposite directions, approaching each other(2)
	//1st
	testingClass.establishLane(1, 900, 200, true);
	testingClass.establishLane(1, 900, 100, false);
	//2nd
	testingClass.establishLane(1, 900, 10, true);
	testingClass.establishLane(1, 900, 100, false);

	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	testingClass.networkLaneVector.clear();
	//vertical opposite directions, move apart from each other(1)
	//1st
	testingClass.establishLane(1, 900, 100, true);
	testingClass.establishLane(1, 900, 10, false);
	//2nd
	testingClass.establishLane(1, 900, 100, true);
	testingClass.establishLane(1, 900, 200, false);

	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	testingClass.networkLaneVector.clear();
	//vertical opposite directions, move apart from each other(2)
	//1st
	testingClass.establishLane(1, 900, 100, true);
	testingClass.establishLane(1, 900, 200, false);
	//2nd
	testingClass.establishLane(1, 900, 100, true);
	testingClass.establishLane(1, 900, 10, false);

	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	testingClass.networkLaneVector.clear();
}
TEST(NetworkBuildingTest, EdgeCases3) {
	networkCreationVHLinks testingClass;
	testingClass.networkLaneVector.clear();
	//Links with ONE lane
	//links generated immediately one after the other
	//horizontal Left->Right
	//1st
	testingClass.establishLane(1, 10, 500, true);
	testingClass.establishLane(1, 100, 500, false);
	//2nd
	testingClass.establishLane(1, 100, 500, true);
	testingClass.establishLane(1, 200, 500, false);

	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	testingClass.networkLaneVector.clear();
	//links generated immediately one after the other
	//horizontal Left->Right
	//1st
	testingClass.establishLane(1, 200, 500, true);
	testingClass.establishLane(1, 100, 500, false);
	//2nd
	testingClass.establishLane(1, 100, 500, true);
	testingClass.establishLane(1, 10, 500, false);

	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	testingClass.networkLaneVector.clear();

	//horizontal opposite directions, approaching each other(1)
	//1st
	testingClass.establishLane(1, 10, 500, true);
	testingClass.establishLane(1, 100, 500, false);
	//2nd
	testingClass.establishLane(1, 200, 500, true);
	testingClass.establishLane(1, 100, 500, false);

	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	testingClass.networkLaneVector.clear();

	//horizontal opposite directions, approaching each other(2)
	//1st
	testingClass.establishLane(1, 200, 500, true);
	testingClass.establishLane(1, 100, 500, false);
	//2nd
	testingClass.establishLane(1, 10, 500, true);
	testingClass.establishLane(1, 100, 500, false);

	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	testingClass.networkLaneVector.clear();
	//horizontal opposite directions, move apart from each other(1)
	//1st
	testingClass.establishLane(1, 100, 500, true);
	testingClass.establishLane(1, 10, 500, false);
	//2nd
	testingClass.establishLane(1, 100, 500, true);
	testingClass.establishLane(1, 200, 500, false);

	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	testingClass.networkLaneVector.clear();
	//vertical opposite directions, move apart from each other(2)
	//1st
	testingClass.establishLane(1, 100, 500, true);
	testingClass.establishLane(1, 200, 500, false);
	//2nd
	testingClass.establishLane(1, 100, 500, true);
	testingClass.establishLane(1, 10, 500, false);

	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	testingClass.networkLaneVector.clear();
}

TEST(NetworkBuildingTest, NBT1) {
	networkCreationVHLinks testingClass;
	testingClass.networkLaneVector.clear();
	//Testing against 2 Links with one Lane in horizontal positive shape:
	//with Links with one Lane:
	EXPECT_EQ(testingClass.networkLaneVector.size(), 0);
	//Construction 1st Link:
	testingClass.establishLane(1, 10, 40, true);
	testingClass.establishLane(1, 600, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 1);
	//Construction 2nd Link:
	testingClass.establishLane(1, 700, 40, true);
	testingClass.establishLane(1, 1000, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//***************************************************************
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(1, 10, 40, true);
	testingClass.establishLane(1, 500, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(1, 500, 40, true);
	testingClass.establishLane(1, 10, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(1, 400, 40, true);
	testingClass.establishLane(1, 800, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(1, 800, 40, true);
	testingClass.establishLane(1, 400, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 40, true);
	testingClass.establishLane(1, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 650, 40, true);
	testingClass.establishLane(1, 900, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(1, 900, 40, true);
	testingClass.establishLane(1, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(1, 650, 40, true);
	testingClass.establishLane(1, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(1, 650, 40, true);
	testingClass.establishLane(1, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(1, 1100, 40, true);
	testingClass.establishLane(1, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(1, 0, 40, true);
	testingClass.establishLane(1, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(1, 1100, 40, true);
	testingClass.establishLane(1, 0, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//with Links with two Lanes(with shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 10, 30, true);
	testingClass.establishLane(2, 500, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 500, 30, true);
	testingClass.establishLane(2, 10, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 400, 30, true);
	testingClass.establishLane(2, 800, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 800, 30, true);
	testingClass.establishLane(2, 400, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 30, true);
	testingClass.establishLane(2, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 650, 30, true);
	testingClass.establishLane(2, 900, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 900, 30, true);
	testingClass.establishLane(2, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 650, 30, true);
	testingClass.establishLane(2, 100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 650, 30, true);
	testingClass.establishLane(2, 1100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 1100, 30, true);
	testingClass.establishLane(2, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 0, 30, true);
	testingClass.establishLane(2, 1100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 1100, 30, true);
	testingClass.establishLane(2, 0, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//with Links with two Lanes(without shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 10, 40, true);
	testingClass.establishLane(2, 500, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 500, 40, true);
	testingClass.establishLane(2, 10, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 400, 40, true);
	testingClass.establishLane(2, 800, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 800, 40, true);
	testingClass.establishLane(2, 400, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 40, true);
	testingClass.establishLane(2, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 650, 40, true);
	testingClass.establishLane(2, 900, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 900, 40, true);
	testingClass.establishLane(2, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 650, 40, true);
	testingClass.establishLane(2, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 650, 40, true);
	testingClass.establishLane(2, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 1100, 40, true);
	testingClass.establishLane(2, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 0, 40, true);
	testingClass.establishLane(2, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 1100, 40, true);
	testingClass.establishLane(2, 0, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//Construction 3rd Link:
	testingClass.establishLane(1, 10, 30, true);
	testingClass.establishLane(1, 600, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 3);
	//Construction 4th Link:
	testingClass.establishLane(1, 10, 50, true);
	testingClass.establishLane(1, 600,50, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 4);
	//Construction 5th Link:
	testingClass.establishLane(2, 10, 60, true);
	testingClass.establishLane(2, 600, 60, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 5);
	testingClass.networkLaneVector.clear();
}
TEST(NetworkBuildingTest, NBT2) {
	networkCreationVHLinks testingClass;
	testingClass.networkLaneVector.clear();
	//Testing against 2 Links with one Lane in horizontal negative shape:
	//with Links with one Lane:
	EXPECT_EQ(testingClass.networkLaneVector.size(), 0);
	//Construction 1st Link:
	testingClass.establishLane(1, 1000, 40, true);
	testingClass.establishLane(1, 700, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 1);
	//Construction 2nd Link:
	testingClass.establishLane(1, 600, 40, true);
	testingClass.establishLane(1, 10, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(1, 10, 40, true);
	testingClass.establishLane(1, 500, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(1, 500, 40, true);
	testingClass.establishLane(1, 10, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(1, 400, 40, true);
	testingClass.establishLane(1, 800, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(1, 800, 40, true);
	testingClass.establishLane(1, 400, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 40, true);
	testingClass.establishLane(1, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 650, 40, true);
	testingClass.establishLane(1, 900, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(1, 900, 40, true);
	testingClass.establishLane(1, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(1, 650, 40, true);
	testingClass.establishLane(1, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(1, 650, 40, true);
	testingClass.establishLane(1, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(1, 1100, 40, true);
	testingClass.establishLane(1, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(1, 0, 40, true);
	testingClass.establishLane(1, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(1, 1100, 40, true);
	testingClass.establishLane(1, 0, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//with Links with two Lanes(with shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 10, 30, true);
	testingClass.establishLane(2, 500, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 500, 30, true);
	testingClass.establishLane(2, 10, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 400, 30, true);
	testingClass.establishLane(2, 800, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 800, 30, true);
	testingClass.establishLane(2, 400, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 30, true);
	testingClass.establishLane(2, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 650, 30, true);
	testingClass.establishLane(2, 900, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 900, 30, true);
	testingClass.establishLane(2, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 650, 30, true);
	testingClass.establishLane(2, 100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 650, 30, true);
	testingClass.establishLane(2, 1100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 1100, 30, true);
	testingClass.establishLane(2, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 0, 30, true);
	testingClass.establishLane(2, 1100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 1100, 30, true);
	testingClass.establishLane(2, 0, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//with Links with two Lanes(without shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 10, 40, true);
	testingClass.establishLane(2, 500, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 500, 40, true);
	testingClass.establishLane(2, 10, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 400, 40, true);
	testingClass.establishLane(2, 800, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 800, 40, true);
	testingClass.establishLane(2, 400, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 40, true);
	testingClass.establishLane(2, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 650, 40, true);
	testingClass.establishLane(2, 900, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 900, 40, true);
	testingClass.establishLane(2, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 650, 40, true);
	testingClass.establishLane(2, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 650, 40, true);
	testingClass.establishLane(2, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 1100, 40, true);
	testingClass.establishLane(2, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 0, 40, true);
	testingClass.establishLane(2, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 1100, 40, true);
	testingClass.establishLane(2, 0, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//Construction 3rd Link:
	testingClass.establishLane(1, 600, 30, true);
	testingClass.establishLane(1, 10, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 3);
	//Construction 4rd Link:
	testingClass.establishLane(1, 600, 50, true);
	testingClass.establishLane(1, 10, 50, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 4);
	//Construction 5th Link:
	testingClass.establishLane(2, 10, 60, true);
	testingClass.establishLane(2, 600, 60, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 5);
	testingClass.networkLaneVector.clear();
}
TEST(NetworkBuildingTest, NBT3) {
	networkCreationVHLinks testingClass;
	testingClass.networkLaneVector.clear();
	//Testing against 2 Links with one Lane in horizontal shape, first in negative direction and seccond in positive direction:
	//with Links with one Lane:
	EXPECT_EQ(testingClass.networkLaneVector.size(), 0);
	//Construction 1st Link:
	testingClass.establishLane(1, 1000, 40, true);
	testingClass.establishLane(1, 700, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 1);
	//Construction 2nd Link:
	testingClass.establishLane(1, 10, 40, true);
	testingClass.establishLane(1, 600, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(1, 10, 40, true);
	testingClass.establishLane(1, 500, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(1, 500, 40, true);
	testingClass.establishLane(1, 10, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(1, 400, 40, true);
	testingClass.establishLane(1, 800, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(1, 800, 40, true);
	testingClass.establishLane(1, 400, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 40, true);
	testingClass.establishLane(1, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 650, 40, true);
	testingClass.establishLane(1, 900, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(1, 900, 40, true);
	testingClass.establishLane(1, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(1, 650, 40, true);
	testingClass.establishLane(1, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(1, 650, 40, true);
	testingClass.establishLane(1, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(1, 1100, 40, true);
	testingClass.establishLane(1, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(1, 0, 40, true);
	testingClass.establishLane(1, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(1, 1100, 40, true);
	testingClass.establishLane(1, 0, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//with Links with two Lanes(with shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 10, 30, true);
	testingClass.establishLane(2, 500, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 500, 30, true);
	testingClass.establishLane(2, 10, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 400, 30, true);
	testingClass.establishLane(2, 800, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 800, 30, true);
	testingClass.establishLane(2, 400, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 30, true);
	testingClass.establishLane(2, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 650, 30, true);
	testingClass.establishLane(2, 900, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 900, 30, true);
	testingClass.establishLane(2, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 650, 30, true);
	testingClass.establishLane(2, 100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 650, 30, true);
	testingClass.establishLane(2, 1100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 1100, 30, true);
	testingClass.establishLane(2, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 0, 30, true);
	testingClass.establishLane(2, 1100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 1100, 30, true);
	testingClass.establishLane(2, 0, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//with Links with two Lanes(without shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 10, 40, true);
	testingClass.establishLane(2, 500, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 500, 40, true);
	testingClass.establishLane(2, 10, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 400, 40, true);
	testingClass.establishLane(2, 800, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 800, 40, true);
	testingClass.establishLane(2, 400, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 40, true);
	testingClass.establishLane(2, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 650, 40, true);
	testingClass.establishLane(2, 900, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 900, 40, true);
	testingClass.establishLane(2, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 650, 40, true);
	testingClass.establishLane(2, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 650, 40, true);
	testingClass.establishLane(2, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 1100, 40, true);
	testingClass.establishLane(2, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 0, 40, true);
	testingClass.establishLane(2, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 1100, 40, true);
	testingClass.establishLane(2, 0, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//Construction 3rd Link:(opposite diretion concering 1st Link)
	testingClass.establishLane(1, 600, 30, true);
	testingClass.establishLane(1, 10, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 3);
	//Construction 4rd Link:(opposite diretion concering 1st Link)
	testingClass.establishLane(1, 600, 50, true);
	testingClass.establishLane(1, 10, 50, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 4);
	//Construction 5th Link:
	testingClass.establishLane(2, 10, 60, true);
	testingClass.establishLane(2, 600, 60, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 5);
	testingClass.networkLaneVector.clear();
}
TEST(NetworkBuildingTest, NBT4) {
	networkCreationVHLinks testingClass;
	testingClass.networkLaneVector.clear();
	//Testing against 2 Links with one Lane in horizontal shape, first in positve direction and seccond in negative direction:
	//with Links with one Lane:
	EXPECT_EQ(testingClass.networkLaneVector.size(), 0);
	//Construction 1st Link:
	testingClass.establishLane(1, 700, 40, true);
	testingClass.establishLane(1, 1000, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 1);
	//Construction 2nd Link:
	testingClass.establishLane(1, 600, 40, true);
	testingClass.establishLane(1, 10, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(1, 10, 40, true);
	testingClass.establishLane(1, 500, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(1, 500, 40, true);
	testingClass.establishLane(1, 10, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(1, 400, 40, true);
	testingClass.establishLane(1, 800, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(1, 800, 40, true);
	testingClass.establishLane(1, 400, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 40, true);
	testingClass.establishLane(1, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 650, 40, true);
	testingClass.establishLane(1, 900, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(1, 900, 40, true);
	testingClass.establishLane(1, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(1, 650, 40, true);
	testingClass.establishLane(1, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(1, 650, 40, true);
	testingClass.establishLane(1, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(1, 1100, 40, true);
	testingClass.establishLane(1, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(1, 0, 40, true);
	testingClass.establishLane(1, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(1, 1100, 40, true);
	testingClass.establishLane(1, 0, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//with Links with two Lanes(with shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 10, 30, true);
	testingClass.establishLane(2, 500, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 500, 30, true);
	testingClass.establishLane(2, 10, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 400, 30, true);
	testingClass.establishLane(2, 800, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 800, 30, true);
	testingClass.establishLane(2, 400, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 30, true);
	testingClass.establishLane(2, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 650, 30, true);
	testingClass.establishLane(2, 900, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 900, 30, true);
	testingClass.establishLane(2, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 650, 30, true);
	testingClass.establishLane(2, 100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 650, 30, true);
	testingClass.establishLane(2, 1100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 1100, 30, true);
	testingClass.establishLane(2, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 0, 30, true);
	testingClass.establishLane(2, 1100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 1100, 30, true);
	testingClass.establishLane(2, 0, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//with Links with two Lanes(without shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 10, 40, true);
	testingClass.establishLane(2, 500, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 500, 40, true);
	testingClass.establishLane(2, 10, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 400, 40, true);
	testingClass.establishLane(2, 800, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 800, 40, true);
	testingClass.establishLane(2, 400, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 40, true);
	testingClass.establishLane(2, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 650, 40, true);
	testingClass.establishLane(2, 900, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 900, 40, true);
	testingClass.establishLane(2, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 650, 40, true);
	testingClass.establishLane(2, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 650, 40, true);
	testingClass.establishLane(2, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 1100, 40, true);
	testingClass.establishLane(2, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 0, 40, true);
	testingClass.establishLane(2, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 1100, 40, true);
	testingClass.establishLane(2, 0, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//Construction 3rd Link:(opposite diretion concering 1st Link)
	testingClass.establishLane(1, 10, 30, true);
	testingClass.establishLane(1, 600, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 3);
	//Construction 4rd Link:(opposite diretion concering 1st Link)
	testingClass.establishLane(1, 10, 50, true);
	testingClass.establishLane(1, 600, 50, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 4);
	//Construction 5th Link:
	testingClass.establishLane(2, 10, 60, true);
	testingClass.establishLane(2, 600, 60, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 5);
	testingClass.networkLaneVector.clear();
	
}

TEST(NetworkBuildingTest, NBT5) {
	networkCreationVHLinks testingClass;
	testingClass.networkLaneVector.clear();
	//Testing against 2 Links with one Lane in vertical positive shape:
	//with Links with one Lane:
	EXPECT_EQ(testingClass.networkLaneVector.size(), 0);
	//Construction 1st Link:
	testingClass.establishLane(1, 100, 80, true);
	testingClass.establishLane(1, 100, 250, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 1);
	//Construction 2nd Link:
	testingClass.establishLane(1, 100, 300, true);
	testingClass.establishLane(1, 100, 600, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//*************************************************************************
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(1, 100, 200, true);
	testingClass.establishLane(1, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(1, 100, 350, true);
	testingClass.establishLane(1, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 380, true);
	testingClass.establishLane(1, 100, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(1, 100, 400, true);
	testingClass.establishLane(1, 100, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(1, 100, 280, true);
	testingClass.establishLane(1, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(1, 100, 40, true);
	testingClass.establishLane(1, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(1, 100, 280, true);
	testingClass.establishLane(1, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(1, 100, 0, true);
	testingClass.establishLane(1, 100, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(1, 100, 650, true);
	testingClass.establishLane(1, 100, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	//with Links with two Lane (with shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 90, 100, true);
	testingClass.establishLane(2, 90, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 90, 200, true);
	testingClass.establishLane(2, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 90, 100, true);
	testingClass.establishLane(2, 90, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 90, 350, true);
	testingClass.establishLane(2, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 90, 100, true);
	testingClass.establishLane(2, 90, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 90, 380, true);
	testingClass.establishLane(2, 90, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 90, 400, true);
	testingClass.establishLane(2,90, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 90, 280, true);
	testingClass.establishLane(2, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 90, 40, true);
	testingClass.establishLane(2, 90, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 90, 280, true);
	testingClass.establishLane(2, 90, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 90, 0, true);
	testingClass.establishLane(2, 90, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 90, 650, true);
	testingClass.establishLane(2, 90, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	//with Links with two Lane(without shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 100, 100, true);
	testingClass.establishLane(2, 100, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 100, 200, true);
	testingClass.establishLane(2, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 100, 100, true);
	testingClass.establishLane(2, 100, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 100, 350, true);
	testingClass.establishLane(2, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 100, true);
	testingClass.establishLane(2, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 380, true);
	testingClass.establishLane(2, 100, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 100, 400, true);
	testingClass.establishLane(2, 100, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 100, 280, true);
	testingClass.establishLane(2, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 100, 40, true);
	testingClass.establishLane(2, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 100, 280, true);
	testingClass.establishLane(2, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 100, 0, true);
	testingClass.establishLane(2, 100, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 100, 650, true);
	testingClass.establishLane(2, 100, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//*************************************************************
	//Construction 3rd Link:
	testingClass.establishLane(1, 110, 80, true);
	testingClass.establishLane(1, 110, 250, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 3);
	//Construction 4th Link:
	testingClass.establishLane(2, 120, 80, true);
	testingClass.establishLane(2, 120, 250, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 4);
	testingClass.networkLaneVector.clear();
}
TEST(NetworkBuildingTest, NBT6) {
	networkCreationVHLinks testingClass;
	testingClass.networkLaneVector.clear();
	//Testing against 2 Links with one Lane in vertical negative shape:
	//with Links with one Lane:
	EXPECT_EQ(testingClass.networkLaneVector.size(), 0);
	//Construction 1st Link:
	testingClass.establishLane(1, 100, 600, true);
	testingClass.establishLane(1, 100, 300, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 1);
	//Construction 2nd Link:
	testingClass.establishLane(1, 100, 250, true);
	testingClass.establishLane(1, 100, 80, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(1, 100, 200, true);
	testingClass.establishLane(1, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(1, 100, 350, true);
	testingClass.establishLane(1, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 380, true);
	testingClass.establishLane(1, 100, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(1, 100, 400, true);
	testingClass.establishLane(1, 100, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(1, 100, 280, true);
	testingClass.establishLane(1, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(1, 100, 40, true);
	testingClass.establishLane(1, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(1, 100, 280, true);
	testingClass.establishLane(1, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(1, 100, 0, true);
	testingClass.establishLane(1, 100, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(1, 100, 650, true);
	testingClass.establishLane(1, 100, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	//with Links with two Lane (with shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 90, 100, true);
	testingClass.establishLane(2, 90, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 90, 200, true);
	testingClass.establishLane(2, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 90, 100, true);
	testingClass.establishLane(2, 90, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 90, 350, true);
	testingClass.establishLane(2, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 90, 100, true);
	testingClass.establishLane(2, 90, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 90, 380, true);
	testingClass.establishLane(2, 90, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 90, 400, true);
	testingClass.establishLane(2, 90, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 90, 280, true);
	testingClass.establishLane(2, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 90, 40, true);
	testingClass.establishLane(2, 90, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 90, 280, true);
	testingClass.establishLane(2, 90, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 90, 0, true);
	testingClass.establishLane(2, 90, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 90, 650, true);
	testingClass.establishLane(2, 90, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	//with Links with two Lane(without shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 100, 100, true);
	testingClass.establishLane(2, 100, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 100, 200, true);
	testingClass.establishLane(2, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 100, 100, true);
	testingClass.establishLane(2, 100, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 100, 350, true);
	testingClass.establishLane(2, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 100, true);
	testingClass.establishLane(2, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 380, true);
	testingClass.establishLane(2, 100, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 100, 400, true);
	testingClass.establishLane(2, 100, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 100, 280, true);
	testingClass.establishLane(2, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 100, 40, true);
	testingClass.establishLane(2, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 100, 280, true);
	testingClass.establishLane(2, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 100, 0, true);
	testingClass.establishLane(2, 100, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 100, 650, true);
	testingClass.establishLane(2, 100, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//*************************************************************
	//Construction 3rd Link:
	testingClass.establishLane(1, 110, 80, true);
	testingClass.establishLane(1, 110, 250, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 3);
	//Construction 4th Link:
	testingClass.establishLane(2, 120, 80, true);
	testingClass.establishLane(2, 120, 250, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 4);
	testingClass.networkLaneVector.clear();
}
TEST(NetworkBuildingTest, NBT7) {
	networkCreationVHLinks testingClass;
	testingClass.networkLaneVector.clear();
	//Testing against 2 Links with one Lane in vertical shape, first in negative direction and seccond in positive direction:
	//with Links with one Lane:
	EXPECT_EQ(testingClass.networkLaneVector.size(), 0);
	//Construction 1st Link:
	testingClass.establishLane(1, 100, 250, true);
	testingClass.establishLane(1, 100, 80, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 1);
	//Construction 2nd Link:
	testingClass.establishLane(1, 100, 300, true);
	testingClass.establishLane(1, 100, 600, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(1, 100, 200, true);
	testingClass.establishLane(1, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(1, 100, 350, true);
	testingClass.establishLane(1, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 380, true);
	testingClass.establishLane(1, 100, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(1, 100, 400, true);
	testingClass.establishLane(1, 100, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(1, 100, 280, true);
	testingClass.establishLane(1, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(1, 100, 40, true);
	testingClass.establishLane(1, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(1, 100, 280, true);
	testingClass.establishLane(1, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(1, 100, 0, true);
	testingClass.establishLane(1, 100, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(1, 100, 650, true);
	testingClass.establishLane(1, 100, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	//with Links with two Lane (with shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 90, 100, true);
	testingClass.establishLane(2, 90, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 90, 200, true);
	testingClass.establishLane(2, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 90, 100, true);
	testingClass.establishLane(2, 90, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 90, 350, true);
	testingClass.establishLane(2, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 90, 100, true);
	testingClass.establishLane(2, 90, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 90, 380, true);
	testingClass.establishLane(2, 90, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 90, 400, true);
	testingClass.establishLane(2, 90, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 90, 280, true);
	testingClass.establishLane(2, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 90, 40, true);
	testingClass.establishLane(2, 90, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 90, 280, true);
	testingClass.establishLane(2, 90, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 90, 0, true);
	testingClass.establishLane(2, 90, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 90, 650, true);
	testingClass.establishLane(2, 90, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	//with Links with two Lane(without shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 100, 100, true);
	testingClass.establishLane(2, 100, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 100, 200, true);
	testingClass.establishLane(2, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 100, 100, true);
	testingClass.establishLane(2, 100, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 100, 350, true);
	testingClass.establishLane(2, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 100, true);
	testingClass.establishLane(2, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 380, true);
	testingClass.establishLane(2, 100, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 100, 400, true);
	testingClass.establishLane(2, 100, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 100, 280, true);
	testingClass.establishLane(2, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 100, 40, true);
	testingClass.establishLane(2, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 100, 280, true);
	testingClass.establishLane(2, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 100, 0, true);
	testingClass.establishLane(2, 100, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 100, 650, true);
	testingClass.establishLane(2, 100, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//*************************************************************
	//Construction 3rd Link:
	testingClass.establishLane(1, 110, 80, true);
	testingClass.establishLane(1, 110, 250, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 3);
	//Construction 4th Link:
	testingClass.establishLane(2, 120, 80, true);
	testingClass.establishLane(2, 120, 250, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 4);
	testingClass.networkLaneVector.clear();
}
TEST(NetworkBuildingTest, NBT8) {
	networkCreationVHLinks testingClass;
	testingClass.networkLaneVector.clear();
	//Testing against 2 Links with one Lane in vertical shape, first in positive direction and seccond in negative direction:
	//with Links with one Lane:
	EXPECT_EQ(testingClass.networkLaneVector.size(), 0);
	//Construction 1st Link:
	testingClass.establishLane(1, 100, 80, true);
	testingClass.establishLane(1, 100, 250, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 1);
	//Construction 2nd Link:
	testingClass.establishLane(1, 100, 600, true);
	testingClass.establishLane(1, 100, 300, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(1, 100, 200, true);
	testingClass.establishLane(1, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(1, 100, 350, true);
	testingClass.establishLane(1, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 380, true);
	testingClass.establishLane(1, 100, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(1, 100, 400, true);
	testingClass.establishLane(1, 100, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(1, 100, 280, true);
	testingClass.establishLane(1, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(1, 100, 40, true);
	testingClass.establishLane(1, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(1, 100, 280, true);
	testingClass.establishLane(1, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(1, 100, 0, true);
	testingClass.establishLane(1, 100, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(1, 100, 650, true);
	testingClass.establishLane(1, 100, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	//with Links with two Lane (with shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 90, 100, true);
	testingClass.establishLane(2, 90, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 90, 200, true);
	testingClass.establishLane(2, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 90, 100, true);
	testingClass.establishLane(2, 90, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 90, 350, true);
	testingClass.establishLane(2, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 90, 100, true);
	testingClass.establishLane(2, 90, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 90, 380, true);
	testingClass.establishLane(2, 90, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 90, 400, true);
	testingClass.establishLane(2, 90, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 90, 280, true);
	testingClass.establishLane(2, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 90, 40, true);
	testingClass.establishLane(2, 90, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 90, 280, true);
	testingClass.establishLane(2, 90, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 90, 0, true);
	testingClass.establishLane(2, 90, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 90, 650, true);
	testingClass.establishLane(2, 90, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	//with Links with two Lane(without shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 100, 100, true);
	testingClass.establishLane(2, 100, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 100, 200, true);
	testingClass.establishLane(2, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 100, 100, true);
	testingClass.establishLane(2, 100, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 100, 350, true);
	testingClass.establishLane(2, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 100, true);
	testingClass.establishLane(2, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 380, true);
	testingClass.establishLane(2, 100, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 100, 400, true);
	testingClass.establishLane(2, 100, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 100, 280, true);
	testingClass.establishLane(2, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 100, 40, true);
	testingClass.establishLane(2, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 100, 280, true);
	testingClass.establishLane(2, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 100, 0, true);
	testingClass.establishLane(2, 100, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 100, 650, true);
	testingClass.establishLane(2, 100, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//*************************************************************
	//Construction 3rd Link:
	testingClass.establishLane(1, 110, 80, true);
	testingClass.establishLane(1, 110, 250, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 3);
	//Construction 4th Link:
	testingClass.establishLane(2, 120, 80, true);
	testingClass.establishLane(2, 120, 250, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 4);
	testingClass.networkLaneVector.clear();
}

TEST(NetworkBuildingTest, NBT9) {
	networkCreationVHLinks testingClass;
	testingClass.networkLaneVector.clear();
	//Testing against 2 Links with two Lane in horizontal positive shape:
	EXPECT_EQ(testingClass.networkLaneVector.size(), 0);
	//Construction 1st Link:
	testingClass.establishLane(2, 10, 30, true);
	testingClass.establishLane(2, 600, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 1);
	//Construction 2nd Link:
	testingClass.establishLane(2, 700, 30, true);
	testingClass.establishLane(2, 1000, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	//Construction 1st Link(with shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(1, 10, 30, true);
	testingClass.establishLane(1, 500, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(1, 500, 30, true);
	testingClass.establishLane(1, 10, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(1, 400, 30, true);
	testingClass.establishLane(1, 800, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(1, 800, 30, true);
	testingClass.establishLane(1, 400, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 30, true);
	testingClass.establishLane(1, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 650, 30, true);
	testingClass.establishLane(1, 900, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(1, 900, 30, true);
	testingClass.establishLane(1, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(1, 650, 30, true);
	testingClass.establishLane(1, 100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(1, 650, 30, true);
	testingClass.establishLane(1, 1100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(1, 1100, 30, true);
	testingClass.establishLane(1, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(1, 0, 30, true);
	testingClass.establishLane(1, 1100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(1, 1100, 30, true);
	testingClass.establishLane(1, 0, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	//Construction 1st Link(without shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(1, 10, 40, true);
	testingClass.establishLane(1, 500, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(1, 500, 40, true);
	testingClass.establishLane(1, 10, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(1, 400, 40, true);
	testingClass.establishLane(1, 800, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(1, 800, 40, true);
	testingClass.establishLane(1, 400, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 40, true);
	testingClass.establishLane(1, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 650, 40, true);
	testingClass.establishLane(1, 900, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(1, 900, 40, true);
	testingClass.establishLane(1, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(1, 650, 40, true);
	testingClass.establishLane(1, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(1, 650, 40, true);
	testingClass.establishLane(1, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(1, 1100, 40, true);
	testingClass.establishLane(1, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(1, 0, 40, true);
	testingClass.establishLane(1, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(1, 1100, 40, true);
	testingClass.establishLane(1, 0, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//with Links with two Lanes(with extra shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 10, 20, true);
	testingClass.establishLane(2, 500, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 500, 20, true);
	testingClass.establishLane(2, 10, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 400, 20, true);
	testingClass.establishLane(2, 800, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 800, 20, true);
	testingClass.establishLane(2, 400, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 20, true);
	testingClass.establishLane(2, 650, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 650, 20, true);
	testingClass.establishLane(2, 900, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 900, 20, true);
	testingClass.establishLane(2, 650, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 650, 20, true);
	testingClass.establishLane(2, 100, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 650, 20, true);
	testingClass.establishLane(2, 1100, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 1100, 20, true);
	testingClass.establishLane(2, 650, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 0, 20, true);
	testingClass.establishLane(2, 1100, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 1100, 20, true);
	testingClass.establishLane(2, 0, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//with Links with two Lanes(with shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 10, 30, true);
	testingClass.establishLane(2, 500, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 500, 30, true);
	testingClass.establishLane(2, 10, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 400, 30, true);
	testingClass.establishLane(2, 800, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 800, 30, true);
	testingClass.establishLane(2, 400, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 30, true);
	testingClass.establishLane(2, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 650, 30, true);
	testingClass.establishLane(2, 900, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 900, 30, true);
	testingClass.establishLane(2, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 650, 30, true);
	testingClass.establishLane(2, 100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 650, 30, true);
	testingClass.establishLane(2, 1100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 1100, 30, true);
	testingClass.establishLane(2, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 0, 30, true);
	testingClass.establishLane(2, 1100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 1100, 30, true);
	testingClass.establishLane(2, 0, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//with Links with two Lanes(without shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 10, 40, true);
	testingClass.establishLane(2, 500, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 500, 40, true);
	testingClass.establishLane(2, 10, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 400, 40, true);
	testingClass.establishLane(2, 800, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 800, 40, true);
	testingClass.establishLane(2, 400, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 40, true);
	testingClass.establishLane(2, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 650, 40, true);
	testingClass.establishLane(2, 900, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 900, 40, true);
	testingClass.establishLane(2, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 650, 40, true);
	testingClass.establishLane(2, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 650, 40, true);
	testingClass.establishLane(2, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 1100, 40, true);
	testingClass.establishLane(2, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 0, 40, true);
	testingClass.establishLane(2, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 1100, 40, true);
	testingClass.establishLane(2, 0, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//*****************************************************************
	//Construction 3rd Link:
	testingClass.establishLane(1, 10, 50, true);
	testingClass.establishLane(1, 600, 50, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 3);
	//Construction 2nd Link:
	testingClass.establishLane(2, 10, 60, true);
	testingClass.establishLane(2, 600, 60, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 4);
	testingClass.networkLaneVector.clear();
}
TEST(NetworkBuildingTest, NBT10) {
	networkCreationVHLinks testingClass;
	testingClass.networkLaneVector.clear();
	//Testing against 2 Links with one Lane in horizontal negative shape:
	EXPECT_EQ(testingClass.networkLaneVector.size(), 0);
	//Construction 1st Link:
	testingClass.establishLane(2, 1000, 30, true);
	testingClass.establishLane(2, 700, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 1);
	//Construction 2nd Link:
	testingClass.establishLane(2, 600, 30, true);
	testingClass.establishLane(2, 10, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	//Construction 1st Link(with shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(1, 10, 30, true);
	testingClass.establishLane(1, 500, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(1, 500, 30, true);
	testingClass.establishLane(1, 10, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(1, 400, 30, true);
	testingClass.establishLane(1, 800, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(1, 800, 30, true);
	testingClass.establishLane(1, 400, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 30, true);
	testingClass.establishLane(1, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 650, 30, true);
	testingClass.establishLane(1, 900, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(1, 900, 30, true);
	testingClass.establishLane(1, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(1, 650, 30, true);
	testingClass.establishLane(1, 100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(1, 650, 30, true);
	testingClass.establishLane(1, 1100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(1, 1100, 30, true);
	testingClass.establishLane(1, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(1, 0, 30, true);
	testingClass.establishLane(1, 1100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(1, 1100, 30, true);
	testingClass.establishLane(1, 0, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	//Construction 1st Link(without shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(1, 10, 40, true);
	testingClass.establishLane(1, 500, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(1, 500, 40, true);
	testingClass.establishLane(1, 10, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(1, 400, 40, true);
	testingClass.establishLane(1, 800, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(1, 800, 40, true);
	testingClass.establishLane(1, 400, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 40, true);
	testingClass.establishLane(1, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 650, 40, true);
	testingClass.establishLane(1, 900, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(1, 900, 40, true);
	testingClass.establishLane(1, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(1, 650, 40, true);
	testingClass.establishLane(1, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(1, 650, 40, true);
	testingClass.establishLane(1, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(1, 1100, 40, true);
	testingClass.establishLane(1, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(1, 0, 40, true);
	testingClass.establishLane(1, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(1, 1100, 40, true);
	testingClass.establishLane(1, 0, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//with Links with two Lanes(with extra shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 10, 20, true);
	testingClass.establishLane(2, 500, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 500, 20, true);
	testingClass.establishLane(2, 10, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 400, 20, true);
	testingClass.establishLane(2, 800, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 800, 20, true);
	testingClass.establishLane(2, 400, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 20, true);
	testingClass.establishLane(2, 650, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 650, 20, true);
	testingClass.establishLane(2, 900, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 900, 20, true);
	testingClass.establishLane(2, 650, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 650, 20, true);
	testingClass.establishLane(2, 100, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 650, 20, true);
	testingClass.establishLane(2, 1100, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 1100, 20, true);
	testingClass.establishLane(2, 650, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 0, 20, true);
	testingClass.establishLane(2, 1100, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 1100, 20, true);
	testingClass.establishLane(2, 0, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//with Links with two Lanes(with shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 10, 30, true);
	testingClass.establishLane(2, 500, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 500, 30, true);
	testingClass.establishLane(2, 10, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 400, 30, true);
	testingClass.establishLane(2, 800, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 800, 30, true);
	testingClass.establishLane(2, 400, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 30, true);
	testingClass.establishLane(2, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 650, 30, true);
	testingClass.establishLane(2, 900, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 900, 30, true);
	testingClass.establishLane(2, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 650, 30, true);
	testingClass.establishLane(2, 100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 650, 30, true);
	testingClass.establishLane(2, 1100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 1100, 30, true);
	testingClass.establishLane(2, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 0, 30, true);
	testingClass.establishLane(2, 1100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 1100, 30, true);
	testingClass.establishLane(2, 0, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//with Links with two Lanes(without shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 10, 40, true);
	testingClass.establishLane(2, 500, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 500, 40, true);
	testingClass.establishLane(2, 10, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 400, 40, true);
	testingClass.establishLane(2, 800, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 800, 40, true);
	testingClass.establishLane(2, 400, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 40, true);
	testingClass.establishLane(2, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 650, 40, true);
	testingClass.establishLane(2, 900, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 900, 40, true);
	testingClass.establishLane(2, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 650, 40, true);
	testingClass.establishLane(2, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 650, 40, true);
	testingClass.establishLane(2, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 1100, 40, true);
	testingClass.establishLane(2, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 0, 40, true);
	testingClass.establishLane(2, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 1100, 40, true);
	testingClass.establishLane(2, 0, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//*****************************************************************
	//Construction 3rd Link:
	testingClass.establishLane(1, 10, 50, true);
	testingClass.establishLane(1, 600, 50, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 3);
	//Construction 2nd Link:
	testingClass.establishLane(2, 10, 60, true);
	testingClass.establishLane(2, 600, 60, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 4);
	testingClass.networkLaneVector.clear();
}
TEST(NetworkBuildingTest, NBT11) {
	networkCreationVHLinks testingClass;
	testingClass.networkLaneVector.clear();
	//Testing against 2 Links with two Lane in horizontal shape, first in negative direction and seccond in positive direction:
	EXPECT_EQ(testingClass.networkLaneVector.size(), 0);
	//Construction 1st Link:
	testingClass.establishLane(2, 1000, 30, true);
	testingClass.establishLane(2, 700, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 1);
	//Construction 2nd Link:
	testingClass.establishLane(2, 10, 30, true);
	testingClass.establishLane(2, 600, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
//Construction 1st Link(with shift):
//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(1, 10, 30, true);
	testingClass.establishLane(1, 500, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(1, 500, 30, true);
	testingClass.establishLane(1, 10, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(1, 400, 30, true);
	testingClass.establishLane(1, 800, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(1, 800, 30, true);
	testingClass.establishLane(1, 400, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 30, true);
	testingClass.establishLane(1, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 650, 30, true);
	testingClass.establishLane(1, 900, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(1, 900, 30, true);
	testingClass.establishLane(1, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(1, 650, 30, true);
	testingClass.establishLane(1, 100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(1, 650, 30, true);
	testingClass.establishLane(1, 1100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(1, 1100, 30, true);
	testingClass.establishLane(1, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(1, 0, 30, true);
	testingClass.establishLane(1, 1100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(1, 1100, 30, true);
	testingClass.establishLane(1, 0, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	//Construction 1st Link(without shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(1, 10, 40, true);
	testingClass.establishLane(1, 500, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(1, 500, 40, true);
	testingClass.establishLane(1, 10, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(1, 400, 40, true);
	testingClass.establishLane(1, 800, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(1, 800, 40, true);
	testingClass.establishLane(1, 400, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 40, true);
	testingClass.establishLane(1, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 650, 40, true);
	testingClass.establishLane(1, 900, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(1, 900, 40, true);
	testingClass.establishLane(1, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(1, 650, 40, true);
	testingClass.establishLane(1, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(1, 650, 40, true);
	testingClass.establishLane(1, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(1, 1100, 40, true);
	testingClass.establishLane(1, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(1, 0, 40, true);
	testingClass.establishLane(1, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(1, 1100, 40, true);
	testingClass.establishLane(1, 0, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//with Links with two Lanes(with extra shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 10, 20, true);
	testingClass.establishLane(2, 500, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 500, 20, true);
	testingClass.establishLane(2, 10, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 400, 20, true);
	testingClass.establishLane(2, 800, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 800, 20, true);
	testingClass.establishLane(2, 400, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 20, true);
	testingClass.establishLane(2, 650, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 650, 20, true);
	testingClass.establishLane(2, 900, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 900, 20, true);
	testingClass.establishLane(2, 650, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 650, 20, true);
	testingClass.establishLane(2, 100, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 650, 20, true);
	testingClass.establishLane(2, 1100, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 1100, 20, true);
	testingClass.establishLane(2, 650, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 0, 20, true);
	testingClass.establishLane(2, 1100, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 1100, 20, true);
	testingClass.establishLane(2, 0, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//with Links with two Lanes(with shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 10, 30, true);
	testingClass.establishLane(2, 500, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 500, 30, true);
	testingClass.establishLane(2, 10, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 400, 30, true);
	testingClass.establishLane(2, 800, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 800, 30, true);
	testingClass.establishLane(2, 400, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 30, true);
	testingClass.establishLane(2, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 650, 30, true);
	testingClass.establishLane(2, 900, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 900, 30, true);
	testingClass.establishLane(2, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 650, 30, true);
	testingClass.establishLane(2, 100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 650, 30, true);
	testingClass.establishLane(2, 1100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 1100, 30, true);
	testingClass.establishLane(2, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 0, 30, true);
	testingClass.establishLane(2, 1100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 1100, 30, true);
	testingClass.establishLane(2, 0, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//with Links with two Lanes(without shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 10, 40, true);
	testingClass.establishLane(2, 500, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 500, 40, true);
	testingClass.establishLane(2, 10, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 400, 40, true);
	testingClass.establishLane(2, 800, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 800, 40, true);
	testingClass.establishLane(2, 400, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 40, true);
	testingClass.establishLane(2, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 650, 40, true);
	testingClass.establishLane(2, 900, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 900, 40, true);
	testingClass.establishLane(2, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 650, 40, true);
	testingClass.establishLane(2, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 650, 40, true);
	testingClass.establishLane(2, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 1100, 40, true);
	testingClass.establishLane(2, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 0, 40, true);
	testingClass.establishLane(2, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 1100, 40, true);
	testingClass.establishLane(2, 0, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//*****************************************************************
	//Construction 3rd Link:
	testingClass.establishLane(1, 10, 50, true);
	testingClass.establishLane(1, 600, 50, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 3);
	//Construction 2nd Link:
	testingClass.establishLane(2, 10, 60, true);
	testingClass.establishLane(2, 600, 60, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 4);
	testingClass.networkLaneVector.clear();
}
TEST(NetworkBuildingTest, NBT12) {
	networkCreationVHLinks testingClass;
	testingClass.networkLaneVector.clear();
	//Testing against 2 Links with two Lane in horizontal shape, first in positve direction and seccond in negative direction:
	EXPECT_EQ(testingClass.networkLaneVector.size(), 0);
	//Construction 1st Link:
	testingClass.establishLane(2, 700, 30, true);
	testingClass.establishLane(2, 1000, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 1);
	//Construction 2nd Link:
	testingClass.establishLane(2, 600, 30, true);
	testingClass.establishLane(2, 10, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	//Construction 1st Link(with extra shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(1, 10, 30, true);
	testingClass.establishLane(1, 500, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(1, 500, 30, true);
	testingClass.establishLane(1, 10, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(1, 400, 30, true);
	testingClass.establishLane(1, 800, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(1, 800, 30, true);
	testingClass.establishLane(1, 400, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 30, true);
	testingClass.establishLane(1, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 650, 30, true);
	testingClass.establishLane(1, 900, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(1, 900, 30, true);
	testingClass.establishLane(1, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(1, 650, 30, true);
	testingClass.establishLane(1, 100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(1, 650, 30, true);
	testingClass.establishLane(1, 1100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(1, 1100, 30, true);
	testingClass.establishLane(1, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(1, 0, 30, true);
	testingClass.establishLane(1, 1100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(1, 1100, 30, true);
	testingClass.establishLane(1, 0, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	//Construction 1st Link(without shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(1, 10, 40, true);
	testingClass.establishLane(1, 500, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(1, 500, 40, true);
	testingClass.establishLane(1, 10, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(1, 400, 40, true);
	testingClass.establishLane(1, 800, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(1, 800, 40, true);
	testingClass.establishLane(1, 400, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 40, true);
	testingClass.establishLane(1, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 650, 40, true);
	testingClass.establishLane(1, 900, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(1, 900, 40, true);
	testingClass.establishLane(1, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(1, 650, 40, true);
	testingClass.establishLane(1, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(1, 650, 40, true);
	testingClass.establishLane(1, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(1, 1100, 40, true);
	testingClass.establishLane(1, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(1, 0, 40, true);
	testingClass.establishLane(1, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(1, 1100, 40, true);
	testingClass.establishLane(1, 0, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//with Links with two Lanes(with extra shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 10, 20, true);
	testingClass.establishLane(2, 500, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 500, 20, true);
	testingClass.establishLane(2, 10, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 400, 20, true);
	testingClass.establishLane(2, 800, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 800, 20, true);
	testingClass.establishLane(2, 400, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 20, true);
	testingClass.establishLane(2, 650, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 650, 20, true);
	testingClass.establishLane(2, 900, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 900, 20, true);
	testingClass.establishLane(2, 650, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 650, 20, true);
	testingClass.establishLane(2, 100, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 650, 20, true);
	testingClass.establishLane(2, 1100, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 1100, 20, true);
	testingClass.establishLane(2, 650, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 0, 20, true);
	testingClass.establishLane(2, 1100, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 1100, 20, true);
	testingClass.establishLane(2, 0, 20, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//with Links with two Lanes(with shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 10, 30, true);
	testingClass.establishLane(2, 500, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 500, 30, true);
	testingClass.establishLane(2, 10, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 400, 30, true);
	testingClass.establishLane(2, 800, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 800, 30, true);
	testingClass.establishLane(2, 400, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 30, true);
	testingClass.establishLane(2, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 650, 30, true);
	testingClass.establishLane(2, 900, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 900, 30, true);
	testingClass.establishLane(2, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 650, 30, true);
	testingClass.establishLane(2, 100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 650, 30, true);
	testingClass.establishLane(2, 1100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 1100, 30, true);
	testingClass.establishLane(2, 650, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 0, 30, true);
	testingClass.establishLane(2, 1100, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 1100, 30, true);
	testingClass.establishLane(2, 0, 30, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//with Links with two Lanes(without shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 10, 40, true);
	testingClass.establishLane(2, 500, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 500, 40, true);
	testingClass.establishLane(2, 10, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 400, 40, true);
	testingClass.establishLane(2, 800, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 800, 40, true);
	testingClass.establishLane(2, 400, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 40, true);
	testingClass.establishLane(2, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 650, 40, true);
	testingClass.establishLane(2, 900, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 900, 40, true);
	testingClass.establishLane(2, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 650, 40, true);
	testingClass.establishLane(2, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 650, 40, true);
	testingClass.establishLane(2, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 1100, 40, true);
	testingClass.establishLane(2, 650, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 0, 40, true);
	testingClass.establishLane(2, 1100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 1100, 40, true);
	testingClass.establishLane(2, 0, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//*****************************************************************
	//Construction 3rd Link:
	testingClass.establishLane(1, 10, 50, true);
	testingClass.establishLane(1, 600, 50, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 3);
	//Construction 2nd Link:
	testingClass.establishLane(2, 10, 60, true);
	testingClass.establishLane(2, 600, 60, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 4);
	testingClass.networkLaneVector.clear();
}

TEST(NetworkBuildingTest, NBT13) {
	networkCreationVHLinks testingClass;
	testingClass.networkLaneVector.clear();
	//Testing against 2 Links with two Lanes in vertical positive shape:
	EXPECT_EQ(testingClass.networkLaneVector.size(), 0);
	//Construction 1st Link:
	testingClass.establishLane(2, 90, 80, true);
	testingClass.establishLane(2, 90, 250, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 1);
	//Construction 2nd Link:
	testingClass.establishLane(2, 90, 300, true);
	testingClass.establishLane(2, 90, 590, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//Construction 1st Link(with shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(1, 90, 100, true);
	testingClass.establishLane(1, 90, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(1, 90, 200, true);
	testingClass.establishLane(1, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(1, 90, 100, true);
	testingClass.establishLane(1, 90, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(1, 90, 350, true);
	testingClass.establishLane(1, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 90, 100, true);
	testingClass.establishLane(1, 90, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 90, 380, true);
	testingClass.establishLane(1, 90, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(1, 90, 400, true);
	testingClass.establishLane(1, 90, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(1, 90, 280, true);
	testingClass.establishLane(1, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(1, 90, 40, true);
	testingClass.establishLane(1, 90, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(1, 90, 280, true);
	testingClass.establishLane(1, 90, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(1, 90, 0, true);
	testingClass.establishLane(1, 90, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(1, 90, 650, true);
	testingClass.establishLane(1, 90, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	//Construction 1st Link(without shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(1, 100, 200, true);
	testingClass.establishLane(1, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(1, 100, 350, true);
	testingClass.establishLane(1, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 380, true);
	testingClass.establishLane(1, 100, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(1, 100, 400, true);
	testingClass.establishLane(1, 100, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(1, 100, 280, true);
	testingClass.establishLane(1, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(1, 100, 40, true);
	testingClass.establishLane(1, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(1, 100, 280, true);
	testingClass.establishLane(1, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(1, 100, 0, true);
	testingClass.establishLane(1, 100, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(1, 100, 650, true);
	testingClass.establishLane(1, 100, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	////with Links with two Lanes(with extra shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 80, 100, true);
	testingClass.establishLane(2, 80, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 80, 200, true);
	testingClass.establishLane(2, 80, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 80, 100, true);
	testingClass.establishLane(2, 80, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 80, 350, true);
	testingClass.establishLane(2, 80, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 80, 100, true);
	testingClass.establishLane(2, 80, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 80, 380, true);
	testingClass.establishLane(2, 80, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 80, 400, true);
	testingClass.establishLane(2, 80, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 80, 280, true);
	testingClass.establishLane(2, 80, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 80, 40, true);
	testingClass.establishLane(2, 80, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 80, 280, true);
	testingClass.establishLane(2, 80, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 80, 0, true);
	testingClass.establishLane(2, 80, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 80, 650, true);
	testingClass.establishLane(2, 80, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	////with Links with two Lanes(with shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 90, 100, true);
	testingClass.establishLane(2, 90, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 90, 200, true);
	testingClass.establishLane(2, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 90, 100, true);
	testingClass.establishLane(2, 90, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 90, 350, true);
	testingClass.establishLane(2, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 90, 100, true);
	testingClass.establishLane(2, 90, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 90, 380, true);
	testingClass.establishLane(2, 90, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 90, 400, true);
	testingClass.establishLane(2, 90, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 90, 280, true);
	testingClass.establishLane(2, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 90, 40, true);
	testingClass.establishLane(2, 90, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 90, 280, true);
	testingClass.establishLane(2, 90, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 90, 0, true);
	testingClass.establishLane(2, 90, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 90, 650, true);
	testingClass.establishLane(2, 90, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//************************************************************************
	// //with Links with two Lanes(without shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 100, 100, true);
	testingClass.establishLane(2, 100, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 100, 200, true);
	testingClass.establishLane(2, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 100, 100, true);
	testingClass.establishLane(2, 100, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 100, 350, true);
	testingClass.establishLane(2, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 100, true);
	testingClass.establishLane(2, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 380, true);
	testingClass.establishLane(2, 100, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 100, 400, true);
	testingClass.establishLane(2, 100, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 100, 280, true);
	testingClass.establishLane(2, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 100, 40, true);
	testingClass.establishLane(2, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 100, 280, true);
	testingClass.establishLane(2, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 100, 0, true);
	testingClass.establishLane(2, 100, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 100, 650, true);
	testingClass.establishLane(2, 100, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//****************************************************************
	//Construction 3rd Link:
	testingClass.establishLane(1, 110, 80, true);
	testingClass.establishLane(1, 110, 250, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 3);
	//Construction 4th Link:
	testingClass.establishLane(2, 120, 80, true);
	testingClass.establishLane(2, 120, 250, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 4);
	testingClass.networkLaneVector.clear();
}
TEST(NetworkBuildingTest, NBT14) {
	networkCreationVHLinks testingClass;
	testingClass.networkLaneVector.clear();
	//Testing against 2 Links with two Lanes in vertical negative shape:
	EXPECT_EQ(testingClass.networkLaneVector.size(), 0);
	//Construction 1st Link:
	testingClass.establishLane(2, 90, 590, true);
	testingClass.establishLane(2, 90, 300, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 1);
	//Construction 2nd Link:
	testingClass.establishLane(2, 90, 250, true);
	testingClass.establishLane(2, 90, 80, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//Construction 1st Link(with shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(1, 90, 100, true);
	testingClass.establishLane(1, 90, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(1, 90, 200, true);
	testingClass.establishLane(1, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(1, 90, 100, true);
	testingClass.establishLane(1, 90, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(1, 90, 350, true);
	testingClass.establishLane(1, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 90, 100, true);
	testingClass.establishLane(1, 90, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 90, 380, true);
	testingClass.establishLane(1, 90, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(1, 90, 400, true);
	testingClass.establishLane(1, 90, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(1, 90, 280, true);
	testingClass.establishLane(1, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(1, 90, 40, true);
	testingClass.establishLane(1, 90, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(1, 90, 280, true);
	testingClass.establishLane(1, 90, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(1, 90, 0, true);
	testingClass.establishLane(1, 90, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(1, 90, 650, true);
	testingClass.establishLane(1, 90, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	//Construction 1st Link(without shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(1, 100, 200, true);
	testingClass.establishLane(1, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(1, 100, 350, true);
	testingClass.establishLane(1, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 380, true);
	testingClass.establishLane(1, 100, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(1, 100, 400, true);
	testingClass.establishLane(1, 100, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(1, 100, 280, true);
	testingClass.establishLane(1, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(1, 100, 40, true);
	testingClass.establishLane(1, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(1, 100, 280, true);
	testingClass.establishLane(1, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(1, 100, 0, true);
	testingClass.establishLane(1, 100, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(1, 100, 650, true);
	testingClass.establishLane(1, 100, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	////with Links with two Lanes(with extra shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 80, 100, true);
	testingClass.establishLane(2, 80, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 80, 200, true);
	testingClass.establishLane(2, 80, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 80, 100, true);
	testingClass.establishLane(2, 80, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 80, 350, true);
	testingClass.establishLane(2, 80, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 80, 100, true);
	testingClass.establishLane(2, 80, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 80, 380, true);
	testingClass.establishLane(2, 80, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 80, 400, true);
	testingClass.establishLane(2, 80, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 80, 280, true);
	testingClass.establishLane(2, 80, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 80, 40, true);
	testingClass.establishLane(2, 80, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 80, 280, true);
	testingClass.establishLane(2, 80, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 80, 0, true);
	testingClass.establishLane(2, 80, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 80, 650, true);
	testingClass.establishLane(2, 80, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	////with Links with two Lanes(with shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 90, 100, true);
	testingClass.establishLane(2, 90, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 90, 200, true);
	testingClass.establishLane(2, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 90, 100, true);
	testingClass.establishLane(2, 90, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 90, 350, true);
	testingClass.establishLane(2, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 90, 100, true);
	testingClass.establishLane(2, 90, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 90, 380, true);
	testingClass.establishLane(2, 90, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 90, 400, true);
	testingClass.establishLane(2, 90, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 90, 280, true);
	testingClass.establishLane(2, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 90, 40, true);
	testingClass.establishLane(2, 90, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 90, 280, true);
	testingClass.establishLane(2, 90, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 90, 0, true);
	testingClass.establishLane(2, 90, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 90, 650, true);
	testingClass.establishLane(2, 90, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//************************************************************************
	// //with Links with two Lanes(without shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 100, 100, true);
	testingClass.establishLane(2, 100, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 100, 200, true);
	testingClass.establishLane(2, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 100, 100, true);
	testingClass.establishLane(2, 100, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 100, 350, true);
	testingClass.establishLane(2, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 100, true);
	testingClass.establishLane(2, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 380, true);
	testingClass.establishLane(2, 100, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 100, 400, true);
	testingClass.establishLane(2, 100, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 100, 280, true);
	testingClass.establishLane(2, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 100, 40, true);
	testingClass.establishLane(2, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 100, 280, true);
	testingClass.establishLane(2, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 100, 0, true);
	testingClass.establishLane(2, 100, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 100, 650, true);
	testingClass.establishLane(2, 100, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//****************************************************************
	//Construction 3rd Link:
	testingClass.establishLane(1, 110, 80, true);
	testingClass.establishLane(1, 110, 250, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 3);
	//Construction 4th Link:
	testingClass.establishLane(2, 120, 80, true);
	testingClass.establishLane(2, 120, 250, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 4);
	testingClass.networkLaneVector.clear();
}
TEST(NetworkBuildingTest, NBT15) {
	networkCreationVHLinks testingClass;
	testingClass.networkLaneVector.clear();
	//Testing against 2 Links with two Lanes in vertical shape, first in negative direction and seccond in positive direction:
	EXPECT_EQ(testingClass.networkLaneVector.size(), 0);
	//Construction 1st Link:
	testingClass.establishLane(2, 90, 250, true);
	testingClass.establishLane(2, 90, 80, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 1);
	//Construction 2nd Link:
	testingClass.establishLane(2, 90, 300, true);
	testingClass.establishLane(2, 90, 590, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//Construction 1st Link(with shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(1, 90, 100, true);
	testingClass.establishLane(1, 90, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(1, 90, 200, true);
	testingClass.establishLane(1, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(1, 90, 100, true);
	testingClass.establishLane(1, 90, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(1, 90, 350, true);
	testingClass.establishLane(1, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 90, 100, true);
	testingClass.establishLane(1, 90, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 90, 380, true);
	testingClass.establishLane(1, 90, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(1, 90, 400, true);
	testingClass.establishLane(1, 90, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(1, 90, 280, true);
	testingClass.establishLane(1, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(1, 90, 40, true);
	testingClass.establishLane(1, 90, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(1, 90, 280, true);
	testingClass.establishLane(1, 90, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(1, 90, 0, true);
	testingClass.establishLane(1, 90, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(1, 90, 650, true);
	testingClass.establishLane(1, 90, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	//Construction 1st Link(without shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(1, 100, 200, true);
	testingClass.establishLane(1, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(1, 100, 350, true);
	testingClass.establishLane(1, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 380, true);
	testingClass.establishLane(1, 100, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(1, 100, 400, true);
	testingClass.establishLane(1, 100, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(1, 100, 280, true);
	testingClass.establishLane(1, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(1, 100, 40, true);
	testingClass.establishLane(1, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(1, 100, 280, true);
	testingClass.establishLane(1, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(1, 100, 0, true);
	testingClass.establishLane(1, 100, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(1, 100, 650, true);
	testingClass.establishLane(1, 100, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	////with Links with two Lanes(with extra shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 80, 100, true);
	testingClass.establishLane(2, 80, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 80, 200, true);
	testingClass.establishLane(2, 80, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 80, 100, true);
	testingClass.establishLane(2, 80, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 80, 350, true);
	testingClass.establishLane(2, 80, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 80, 100, true);
	testingClass.establishLane(2, 80, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 80, 380, true);
	testingClass.establishLane(2, 80, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 80, 400, true);
	testingClass.establishLane(2, 80, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 80, 280, true);
	testingClass.establishLane(2, 80, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 80, 40, true);
	testingClass.establishLane(2, 80, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 80, 280, true);
	testingClass.establishLane(2, 80, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 80, 0, true);
	testingClass.establishLane(2, 80, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 80, 650, true);
	testingClass.establishLane(2, 80, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	////with Links with two Lanes(with shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 90, 100, true);
	testingClass.establishLane(2, 90, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 90, 200, true);
	testingClass.establishLane(2, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 90, 100, true);
	testingClass.establishLane(2, 90, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 90, 350, true);
	testingClass.establishLane(2, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 90, 100, true);
	testingClass.establishLane(2, 90, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 90, 380, true);
	testingClass.establishLane(2, 90, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 90, 400, true);
	testingClass.establishLane(2, 90, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 90, 280, true);
	testingClass.establishLane(2, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 90, 40, true);
	testingClass.establishLane(2, 90, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 90, 280, true);
	testingClass.establishLane(2, 90, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 90, 0, true);
	testingClass.establishLane(2, 90, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 90, 650, true);
	testingClass.establishLane(2, 90, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//************************************************************************
	// //with Links with two Lanes(without shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 100, 100, true);
	testingClass.establishLane(2, 100, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 100, 200, true);
	testingClass.establishLane(2, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 100, 100, true);
	testingClass.establishLane(2, 100, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 100, 350, true);
	testingClass.establishLane(2, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 100, true);
	testingClass.establishLane(2, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 380, true);
	testingClass.establishLane(2, 100, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 100, 400, true);
	testingClass.establishLane(2, 100, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 100, 280, true);
	testingClass.establishLane(2, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 100, 40, true);
	testingClass.establishLane(2, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 100, 280, true);
	testingClass.establishLane(2, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 100, 0, true);
	testingClass.establishLane(2, 100, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 100, 650, true);
	testingClass.establishLane(2, 100, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//****************************************************************
	//Construction 3rd Link:
	testingClass.establishLane(1, 110, 80, true);
	testingClass.establishLane(1, 110, 250, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 3);
	//Construction 4th Link:
	testingClass.establishLane(2, 120, 80, true);
	testingClass.establishLane(2, 120, 250, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 4);
	testingClass.networkLaneVector.clear();
}
TEST(NetworkBuildingTest, NBT16) {
	networkCreationVHLinks testingClass;
	testingClass.networkLaneVector.clear();
	//Testing against 2 Links with two Lanes in vertical shape, first in positive direction and seccond in negative direction:
	EXPECT_EQ(testingClass.networkLaneVector.size(), 0);
	//Construction 1st Link:
	testingClass.establishLane(2, 90, 80, true);
	testingClass.establishLane(2, 90, 250, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 1);
	//Construction 2nd Link:
	testingClass.establishLane(2, 90, 590, true);
	testingClass.establishLane(2, 90, 300, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//******************************************************************
	//Construction 1st Link(with shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(1, 90, 100, true);
	testingClass.establishLane(1, 90, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(1, 90, 200, true);
	testingClass.establishLane(1, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(1, 90, 100, true);
	testingClass.establishLane(1, 90, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(1, 90, 350, true);
	testingClass.establishLane(1, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 90, 100, true);
	testingClass.establishLane(1, 90, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 90, 380, true);
	testingClass.establishLane(1, 90, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(1, 90, 400, true);
	testingClass.establishLane(1, 90, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(1, 90, 280, true);
	testingClass.establishLane(1, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(1, 90, 40, true);
	testingClass.establishLane(1, 90, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(1, 90, 280, true);
	testingClass.establishLane(1, 90, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(1, 90, 0, true);
	testingClass.establishLane(1, 90, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(1, 90, 650, true);
	testingClass.establishLane(1, 90, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	//Construction 1st Link(without shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(1, 100, 200, true);
	testingClass.establishLane(1, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(1, 100, 350, true);
	testingClass.establishLane(1, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 100, true);
	testingClass.establishLane(1, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(1, 100, 380, true);
	testingClass.establishLane(1, 100, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(1, 100, 400, true);
	testingClass.establishLane(1, 100, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(1, 100, 280, true);
	testingClass.establishLane(1, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(1, 100, 40, true);
	testingClass.establishLane(1, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(1, 100, 280, true);
	testingClass.establishLane(1, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(1, 100, 0, true);
	testingClass.establishLane(1, 100, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(1, 100, 650, true);
	testingClass.establishLane(1, 100, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	////with Links with two Lanes(with extra shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 80, 100, true);
	testingClass.establishLane(2, 80, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 80, 200, true);
	testingClass.establishLane(2, 80, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 80, 100, true);
	testingClass.establishLane(2, 80, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 80, 350, true);
	testingClass.establishLane(2, 80, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 80, 100, true);
	testingClass.establishLane(2, 80, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 80, 380, true);
	testingClass.establishLane(2, 80, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 80, 400, true);
	testingClass.establishLane(2, 80, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 80, 280, true);
	testingClass.establishLane(2, 80, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 80, 40, true);
	testingClass.establishLane(2, 80, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 80, 280, true);
	testingClass.establishLane(2, 80, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 80, 0, true);
	testingClass.establishLane(2, 80, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 80, 650, true);
	testingClass.establishLane(2, 80, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//**********************************************************************
	////with Links with two Lanes(with shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 90, 100, true);
	testingClass.establishLane(2, 90, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 90, 200, true);
	testingClass.establishLane(2, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 90, 100, true);
	testingClass.establishLane(2, 90, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 90, 350, true);
	testingClass.establishLane(2, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 90, 100, true);
	testingClass.establishLane(2, 90, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 90, 380, true);
	testingClass.establishLane(2, 90, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 90, 400, true);
	testingClass.establishLane(2, 90, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 90, 280, true);
	testingClass.establishLane(2, 90, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 90, 40, true);
	testingClass.establishLane(2, 90, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 90, 280, true);
	testingClass.establishLane(2, 90, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 90, 0, true);
	testingClass.establishLane(2, 90, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 90, 650, true);
	testingClass.establishLane(2, 90, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//************************************************************************
	// //with Links with two Lanes(without shift):
	//Test if construction inside a link works(positve direction): 
	testingClass.establishLane(2, 100, 100, true);
	testingClass.establishLane(2, 100, 200, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction inside a link works(negative direction): 
	testingClass.establishLane(2, 100, 200, true);
	testingClass.establishLane(2, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(positve direction): 
	testingClass.establishLane(2, 100, 100, true);
	testingClass.establishLane(2, 100, 350, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if construction between two links works(negative direction): 
	testingClass.establishLane(2, 100, 350, true);
	testingClass.establishLane(2, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 100, true);
	testingClass.establishLane(2, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(positve direction): 
	testingClass.establishLane(2, 100, 380, true);
	testingClass.establishLane(2, 100, 400, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(1)Test if construction with link overlapping works(negatve direction): 
	testingClass.establishLane(2, 100, 400, true);
	testingClass.establishLane(2, 100, 380, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//(2)Test if construction with link overlapping works(negative direction): 
	testingClass.establishLane(2, 100, 280, true);
	testingClass.establishLane(2, 100, 100, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(postive direction): 
	testingClass.establishLane(2, 100, 40, true);
	testingClass.establishLane(2, 100, 280, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover an existing link(negative direction): 
	testingClass.establishLane(2, 100, 280, true);
	testingClass.establishLane(2, 100, 40, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(postive direction): 
	testingClass.establishLane(2, 100, 0, true);
	testingClass.establishLane(2, 100, 650, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//Test if a link can cover two existing links(negative direction): 
	testingClass.establishLane(2, 100, 650, true);
	testingClass.establishLane(2, 100, 0, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 2);
	//****************************************************************
	//Construction 3rd Link:
	testingClass.establishLane(1, 110, 80, true);
	testingClass.establishLane(1, 110, 250, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 3);
	//Construction 4th Link:
	testingClass.establishLane(2, 120, 80, true);
	testingClass.establishLane(2, 120, 250, false);
	EXPECT_EQ(testingClass.networkLaneVector.size(), 4);
	testingClass.networkLaneVector.clear();
}

TEST(TestCaseName, TestName) {
	velocityToLength o;
	EXPECT_EQ(o.VLStepConversion(99), 25);
}


/*TEST(TestCaseName2, TestName2) {
	std::ofstream file;
	file.open("D:/vs_Community/simi_projekt/oberflaeche_versuch/23_Sommer2021/unitTest1.txt");
	
	edge e1;
	edge e2;
	edge e3;
	edge e4;
	e1.m_startVertex = 10;
	e1.m_endVertex = 12;
	e2.m_startVertex = 12;
	e2.m_endVertex = 13;
	e3.m_startVertex = 12;
	e3.m_endVertex = 14;
	e4.m_startVertex = 12;
	e4.m_endVertex = 15;
	std::shared_ptr<vertex>v1 = std::make_shared<vertexStart>(200, 0, 1);
	std::shared_ptr<vertex>v2 = std::make_shared<vertexFlex>(200, 200, 0);
	std::shared_ptr<vertex>v3 = std::make_shared<vertexEnd>(0, 200, 2);
	std::shared_ptr<vertex>v4 = std::make_shared<vertexEnd>(200, 400, 2);
	std::shared_ptr<vertex>v5 = std::make_shared<vertexEnd>(400, 200, 2);
	e1.m_startVertexPtr = v1;
	e1.m_endVertexPtr = v2;
	e1.m_endVertex = 12;
	e2.m_startVertexPtr = v2;
	e2.m_endVertexPtr = v3;
	e2.m_endVertex = 13;
	e3.m_startVertexPtr = v2;
	e3.m_endVertexPtr = v4;
	e3.m_endVertex = 14;
	e4.m_startVertexPtr = v2;
	e4.m_endVertexPtr = v5;
	e4.m_endVertex = 15;
	e1.m_length = 200;
	e2.m_length = 200;
	e3.m_length = 200;
	e4.m_length = 200;
	e1.m_risingOrDescention = true;
	e2.m_risingOrDescention = false;
	e3.m_risingOrDescention = true;
	e4.m_risingOrDescention = true;
	e1.sFs.vehicleSetPtr = std::make_unique<flowSimulation1PosStraight>(120, 200);
	e2.sFs.vehicleSetPtr = std::make_unique<flowSimulation1NegStraight>(120, 200);
	e3.sFs.vehicleSetPtr = std::make_unique<flowSimulation1PosStraight>(120, 200);
	e4.sFs.vehicleSetPtr = std::make_unique<flowSimulation1PosStraight>(120, 200);
	e2.p1Shape = 0;
	e3.p1Shape = 0;
	e4.p1Shape = 0;

	v1->m_vertexID = 10;
	v2->m_vertexID = 12;
	v3->m_vertexID = 13;
	v4->m_vertexID = 14;
	v5->m_vertexID = 15;
	file << "\nv2 Size of Transmissiontable: " << v2->sizeOfTransmissiontable() << "\n";
	v2->setTransmissionTable(13);
	v2->setTransmissionTable(14);
	v2->setTransmissionTable(15);
	file << "\nv1 Size of Transmissiontable: " << v1->sizeOfTransmissiontable() << "\n";
	file << "\nv2 Size of Transmissiontable: " << v2->sizeOfTransmissiontable() << "\n";
	file << "\nv3 Size of Transmissiontable: " << v3->sizeOfTransmissiontable() << "\n";
	file << "\nv4 Size of Transmissiontable: " << v4->sizeOfTransmissiontable() << "\n";
	file << "\nv5 Size of Transmissiontable: " << v5->sizeOfTransmissiontable() << "\n";
	std::vector<vehicle*> vehicle_vector;
	vehicle* vehicleArray = new vehicle[91];
	int counter = 0;
	for (int i = 0; i < 90; i++) {

		//file << "Hilfe "<<v3->m_numberOfVehicle<<"\n";
		vehicleArray[i].m_lane = 1;
		vehicleArray[i].m_position = 0;
		vehicleArray[i].m_pref_speed = 100;
		vehicleArray[i].m_inRange = true;
		vehicleArray[i].serviceBool = false;
		vehicleArray[i].processedByIteration = true;
		vehicleArray[i].m_riseOrDecline = true;
		vehicleArray[i].m_moblieORStationary = true;

		if (counter == 0) {
			vehicleArray[i].m_routeID = 1;
			vehicleArray[i].m_routeVertexID_vehicle = { 10,12,13 };
		}
		if (counter == 1) {
			vehicleArray[i].m_routeID = 2;
			vehicleArray[i].m_routeVertexID_vehicle = { 10,12,14 };
		}
		if (counter == 2) {
			vehicleArray[i].m_routeID = 3;
			vehicleArray[i].m_routeVertexID_vehicle = { 10,12,15 };
		}
		counter++;
		if (counter == 3) {
			counter = 0;
		}
	}
	file << "\nvehicleArray[i].m_routeVertexID_vehicle.size: " << vehicleArray[4].m_routeVertexID_vehicle.size() << "\n";
	for (int j = 0; j < 90; j++) {
		for (int i = 0; i < vehicleArray[j].m_routeVertexID_vehicle.size(); i++) {
			file << vehicleArray[j].m_routeVertexID_vehicle[i] << "\t";
		}
		file << "\n";
	}
	file << "\n";
	counter = 0;
	for (int i = 0; i < 500; i++) {
		file << "counter:" << counter << " i: " << i << "in der Schleife\n";
		if (counter < 90) {
			e1.sFs.vehicleSetPtr->insertSET(&vehicleArray[i]);
			//e1.sFs.vehicleSetPtr->flow(1, e1.m_length, e1.m_risingOrDescention);
		}
		file << "e1 size von SET: " << e1.sFs.vehicleSetPtr->getVehicleSetSize() << " RoD: " << e1.m_risingOrDescention << " length:" << e1.m_length << "\ne1: ";
		counter++;
		for (auto &j : e1.sFs.vehicleSetPtr->m_vehicleSet) {
			file << j->m_position << "\t";
		}
		file << "\nVehicleEraseVector.size: " << e1.vehicleEraseVector.size() << "\n";

		e1.singleSimulationStep(220);
		//file << "e1 Counter: " << e1.counter << "\n";
		file << " e1 zwischen singleSimulationStep und deallocation\n";
		e1.deallocateVehicleAtEnd(true);
		file << "v2->m_numberOfVehicle: " << v2->m_numberOfVehicle << "\n";
		file << "e1 " << i << "e2\n";
		e2.flow1L(1, 220);
		file << "e2 size von SET: " << e2.sFs.vehicleSetPtr->getVehicleSetSize() << " RoD: " << e2.m_risingOrDescention << " length:" << e2.m_length << "\ne2: ";
		for (auto &j : e2.sFs.vehicleSetPtr->m_vehicleSet) {
			file << j->m_position << "\t";
		}
		e2.singleSimulationStep(220);
		e2.deallocateVehicleAtEnd(true);
		file << "\nv3->m_numberOfVehicle: " << v3->m_numberOfVehicle << "\n";
		file << "e2 " << i << "e3\n";
		e3.flow1L(1, 220);
		file << "e3 size von SET: " << e3.sFs.vehicleSetPtr->getVehicleSetSize() << " RoD: " << e3.m_risingOrDescention << " length:" << e3.m_length << "\ne3: ";

		for (auto &j : e3.sFs.vehicleSetPtr->m_vehicleSet) {
			file << j->m_position << "\t";
		}
		e3.singleSimulationStep(220);
		e3.deallocateVehicleAtEnd(true);
		file << "\nv4->m_numberOfVehicle: " << v4->m_numberOfVehicle << "\n";
		file << "e3 " << i << "e4\n";
		e4.flow1L(1, 220);
		file << "e4 size von SET: " << e4.sFs.vehicleSetPtr->getVehicleSetSize() << " RoD: " << e4.m_risingOrDescention << " length:" << e4.m_length << "\ne4: ";
		for (auto &j : e4.sFs.vehicleSetPtr->m_vehicleSet) {
			file << j->m_position << "\t";
		}
		e4.singleSimulationStep(220);
		e4.deallocateVehicleAtEnd(true);
		file << "\nv5->m_numberOfVehicle: " << v5->m_numberOfVehicle << "\n";
		file << "*****************************************\n";
		file << "v2->v3: " << v2->sizeOfSingleTransmissiontable(0) << "\n";
		file << "v2->v4: " << v2->sizeOfSingleTransmissiontable(1) << "\n";
		file << "v2->v5: " << v2->sizeOfSingleTransmissiontable(2) << "\n";
		file << "*****************************************\n";
	}
	file << "v3->m_numberOfVehicle: " << v3->m_numberOfVehicle << "\n";
	file << "v4->m_numberOfVehicle: " << v4->m_numberOfVehicle << "\n";
	file << "v5->m_numberOfVehicle: " << v5->m_numberOfVehicle << "\n";

	EXPECT_EQ(v3->m_numberOfVehicle, 30);
	//EXPECT_TRUE(true);

	EXPECT_EQ(v4->m_numberOfVehicle, 28);
	//EXPECT_TRUE(true);
	EXPECT_EQ(v5->m_numberOfVehicle, 28);
	//EXPECT_TRUE(true);

	//std::this_thread::sleep_for(std::chrono::milliseconds(250000));
	
	delete[] vehicleArray;
	file.close();

}*/


TEST(TestCaseName3, TestName3) {
	

	edge e1;
	edge e2;
	
	e1.m_startVertex = 10;
	e1.m_endVertex = 12;
	e2.m_startVertex = 12;
	e2.m_endVertex = 13;
	
	std::shared_ptr<vertex>v1 = std::make_shared<vertexStart>(200, 0, 1);
	std::shared_ptr<vertex>v2 = std::make_shared<vertexFlex>(200, 200, 0);
	std::shared_ptr<vertex>v3 = std::make_shared<vertexEnd>(0, 200, 2);
	
	e1.m_startVertexPtr = v1;
	e1.m_endVertexPtr = v2;
	e1.m_endVertex = 12;
	e2.m_startVertexPtr = v2;
	e2.m_endVertexPtr = v3;
	e2.m_endVertex = 13;
	
	e1.m_length = 200;
	e2.m_length = 200;
	
	e1.m_risingOrDescention = true;
	e2.m_risingOrDescention = false;
	
	e1.sFs.vehicleSetPtr = std::make_unique<flowSimulation1PosStraight>(120, 200);
	e2.sFs.vehicleSetPtr = std::make_unique<flowSimulation1NegStraight>(120, 200);
	
	e2.p1Shape = 0;
	
	

	v1->m_vertexID = 10;
	v2->m_vertexID = 12;
	v3->m_vertexID = 13;
	
	v2->setTransmissionTable(13);
	
	
	std::vector<vehicle*> vehicle_vector;
	vehicle* vehicleArray = new vehicle[91];
	
	for (int i = 0; i < 90; i++) {

		//file << "Hilfe "<<v3->m_numberOfVehicle<<"\n";
		vehicleArray[i].m_lane = 1;
		vehicleArray[i].m_position = 0;
		vehicleArray[i].m_pref_speed = 100;
		vehicleArray[i].m_inRange = true;
		vehicleArray[i].serviceBool = false;
		vehicleArray[i].processedByIteration = true;
		vehicleArray[i].m_riseOrDecline = true;
		vehicleArray[i].m_moblieORStationary = true;

		
		vehicleArray[i].m_routeID = 1;
		vehicleArray[i].m_routeVertexID_vehicle = { 10,12,13 };
		
	}
	
	
	for (int i = 0; i < 500; i++) {
		
		if (i < 90) {
			e1.sFs.vehicleSetPtr->insertSET(&vehicleArray[i]);
			//e1.sFs.vehicleSetPtr->flow(1, e1.m_length, e1.m_risingOrDescention);
		}
		
		
		

		e1.singleSimulationStep(220);
		
		e1.deallocateVehicleAtEnd(true);
		
		e2.flow1L(1, 220);
		
		e2.singleSimulationStep(220);
		e2.deallocateVehicleAtEnd(true);
		
		
		
		
	}
	std::ofstream file;
	file.open("D:/vs_Community/simi_projekt/oberflaeche_versuch/23_Sommer2021/unitTest2.txt");
	file << v3->m_numberOfVehicle;
	file.close();

	EXPECT_EQ(v3->m_numberOfVehicle, 90);
	//EXPECT_TRUE(true);

	

	//std::this_thread::sleep_for(std::chrono::milliseconds(250000));
	
	delete[] vehicleArray;
	

}
/*TEST(TestCaseName4, TestName4) {
	std::ofstream file;
	file.open("D:/vs_Community/simi_projekt/oberflaeche_versuch/23_Sommer2021/unitTest3.txt");

	edge e1;
	
	edge e3;
	edge e4;
	e1.m_startVertex = 10;
	e1.m_endVertex = 12;
	
	e3.m_startVertex = 12;
	e3.m_endVertex = 14;
	e4.m_startVertex = 12;
	e4.m_endVertex = 15;
	std::shared_ptr<vertex>v1 = std::make_shared<vertexStart>(200, 0, 1);
	std::shared_ptr<vertex>v2 = std::make_shared<vertexFlex>(200, 200, 0);
	
	std::shared_ptr<vertex>v4 = std::make_shared<vertexEnd>(200, 400, 2);
	std::shared_ptr<vertex>v5 = std::make_shared<vertexEnd>(400, 200, 2);
	e1.m_startVertexPtr = v1;
	e1.m_endVertexPtr = v2;
	e1.m_endVertex = 12;
	
	e3.m_startVertexPtr = v2;
	e3.m_endVertexPtr = v4;
	e3.m_endVertex = 14;
	e4.m_startVertexPtr = v2;
	e4.m_endVertexPtr = v5;
	e4.m_endVertex = 15;
	e1.m_length = 200;
	
	e3.m_length = 200;
	e4.m_length = 200;
	e1.m_risingOrDescention = true;
	
	e3.m_risingOrDescention = true;
	e4.m_risingOrDescention = true;
	e1.sFs.vehicleSetPtr = std::make_unique<flowSimulation1PosStraight>(120, 200);
	
	e3.sFs.vehicleSetPtr = std::make_unique<flowSimulation1PosStraight>(120, 200);
	e4.sFs.vehicleSetPtr = std::make_unique<flowSimulation1PosStraight>(120, 200);
	
	e3.p1Shape = 0;
	e4.p1Shape = 0;

	v1->m_vertexID = 10;
	v2->m_vertexID = 12;
	
	v4->m_vertexID = 14;
	v5->m_vertexID = 15;
	file << "\nv2 Size of Transmissiontable: " << v2->sizeOfTransmissiontable() << "\n";
	
	v2->setTransmissionTable(14);
	v2->setTransmissionTable(15);
	file << "\nv1 Size of Transmissiontable: " << v1->sizeOfTransmissiontable() << "\n";
	file << "\nv2 Size of Transmissiontable: " << v2->sizeOfTransmissiontable() << "\n";
	
	file << "\nv4 Size of Transmissiontable: " << v4->sizeOfTransmissiontable() << "\n";
	file << "\nv5 Size of Transmissiontable: " << v5->sizeOfTransmissiontable() << "\n";
	std::vector<vehicle*> vehicle_vector;
	vehicle* vehicleArray = new vehicle[101];
	int counter = 0;
	for (int i = 0; i < 100; i++) {

		//file << "Hilfe "<<v3->m_numberOfVehicle<<"\n";
		vehicleArray[i].m_lane = 1;
		vehicleArray[i].m_position = 0;
		vehicleArray[i].m_pref_speed = 100;
		vehicleArray[i].m_inRange = true;
		vehicleArray[i].serviceBool = false;
		vehicleArray[i].processedByIteration = true;
		vehicleArray[i].m_riseOrDecline = true;
		vehicleArray[i].m_moblieORStationary = true;

		if (counter == 0) {
			vehicleArray[i].m_routeID = 1;
			vehicleArray[i].m_routeVertexID_vehicle = { 10,12,14 };
		}
		if (counter == 1) {
			vehicleArray[i].m_routeID = 2;
			vehicleArray[i].m_routeVertexID_vehicle = { 10,12,15 };
		}
		
		counter++;
		if (counter == 2) {
			counter = 0;
		}
	}
	file << "\nvehicleArray[i].m_routeVertexID_vehicle.size: " << vehicleArray[4].m_routeVertexID_vehicle.size() << "\n";
	for (int j = 0; j < 100; j++) {
		for (int i = 0; i < vehicleArray[j].m_routeVertexID_vehicle.size(); i++) {
			file << vehicleArray[j].m_routeVertexID_vehicle[i] << "\t";
		}
		file << "\n";
	}
	file << "\n";
	counter = 0;
	for (int i = 0; i < 500; i++) {
		file << "counter:" << counter << " i: " << i << "in der Schleife\n";
		if (counter < 100) {
			e1.sFs.vehicleSetPtr->insertSET(&vehicleArray[i]);
			//e1.sFs.vehicleSetPtr->flow(1, e1.m_length, e1.m_risingOrDescention);
		}
		file << "e1 size von SET: " << e1.sFs.vehicleSetPtr->getVehicleSetSize() << " RoD: " << e1.m_risingOrDescention << " length:" << e1.m_length << "\ne1: ";
		counter++;
		for (auto &j : e1.sFs.vehicleSetPtr->m_vehicleSet) {
			file << j->m_position << "\t";
		}
		file << "\nVehicleEraseVector.size: " << e1.vehicleEraseVector.size() << "\n";

		e1.singleSimulationStep(220);
		//file << "e1 Counter: " << e1.counter << "\n";
		file << " e1 zwischen singleSimulationStep und deallocation\n";
		e1.deallocateVehicleAtEnd(true);
		file << "v2->m_numberOfVehicle: " << v2->m_numberOfVehicle << "\n";
		file << "e1 " << i << "e2\n";
		
		
		
		
		file << "e2 " << i << "e3\n";
		e3.flow1L(1, 220);
		file << "e3 size von SET: " << e3.sFs.vehicleSetPtr->getVehicleSetSize() << " RoD: " << e3.m_risingOrDescention << " length:" << e3.m_length << "\ne3: ";

		for (auto &j : e3.sFs.vehicleSetPtr->m_vehicleSet) {
			file << j->m_position << "\t";
		}
		e3.singleSimulationStep(220);
		e3.deallocateVehicleAtEnd(true);
		file << "\nv4->m_numberOfVehicle: " << v4->m_numberOfVehicle << "\n";
		file << "e3 " << i << "e4\n";
		e4.flow1L(1, 220);
		file << "e4 size von SET: " << e4.sFs.vehicleSetPtr->getVehicleSetSize() << " RoD: " << e4.m_risingOrDescention << " length:" << e4.m_length << "\ne4: ";
		for (auto &j : e4.sFs.vehicleSetPtr->m_vehicleSet) {
			file << j->m_position << "\t";
		}
		e4.singleSimulationStep(220);
		e4.deallocateVehicleAtEnd(true);
		file << "\nv5->m_numberOfVehicle: " << v5->m_numberOfVehicle << "\n";
		file << "*****************************************\n";
		file << "v2->v3: " << v2->sizeOfSingleTransmissiontable(0) << "\n";
		file << "v2->v4: " << v2->sizeOfSingleTransmissiontable(1) << "\n";
		
		file << "*****************************************\n";
	}
	
	file << "v4->m_numberOfVehicle: " << v4->m_numberOfVehicle << "\n";
	file << "v5->m_numberOfVehicle: " << v5->m_numberOfVehicle << "\n";

	EXPECT_EQ(v2->m_numberOfVehicle, 100);
	EXPECT_TRUE(true);

	EXPECT_EQ(v4->m_numberOfVehicle, 48);
	EXPECT_TRUE(true);
	EXPECT_EQ(v5->m_numberOfVehicle, 47);
	EXPECT_TRUE(true);

	//std::this_thread::sleep_for(std::chrono::milliseconds(250000));

	delete[] vehicleArray;
	file.close();

}*/



