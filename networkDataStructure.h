#pragma once
#include "PrecompiledHeadersEdges.h"
#include "callBackLinks.h"
#include "edge.h"
#include "graph.h"
#include "vertex.h"
//#include "PrintInGDIplusWinEmpty.h"


class networkDataStructure {
public:
	//std::vector<std::unique_ptr<vertex>>vertexOfGraphPtrVectorConainer;
	//std::vector<std::unique_ptr<edge>>edgeOfGraphPtrContainer;
	enum m_numberOfLanes { oneLane = 1, twoLanes = 2 };
	//std::vector<std::tuple<std::pair<int, int>, std::pair<int, int>, bool, m_numberOfLanes>> networkLaneVector;
	callBackLinks* m_CBLptr=nullptr;
	concreteObserverSubjekt* m_cObSptr=nullptr;
	std::vector<std::unique_ptr<graph>>appliedGraph;
	//PrintInGDIplusWinEmpty m_PWE;
	networkDataStructure();
	~networkDataStructure();
	
	//void iniziallizationOfPointer(callBackLinks* CBL, concreteObserverSubjekt* cOS);
	void fillNetworkLaneVector(std::pair<int, int> startingPoint, std::pair<int, int> endingPoint, bool horizontalOrVertival, int NoL);
	bool checkIfInNetworkLaneVector();
	//void vertexCreationVH_Network(const std::pair<int, int>& XandYpostion, const int& shapeOfThatVertex);
	//void graphGenerationFromClickPairs(const int& choiceOfRouteFinding);
	//std::unique_ptr<PrintPattern> choosePrintPattern(const int& p1x, const int& p1y, const int& p2x, const int& p2y, const int& lanesH, const int& lanesV);
	void printLanesAndVehiclesOfAllEdges();
};
