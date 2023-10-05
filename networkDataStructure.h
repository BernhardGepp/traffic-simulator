#pragma once
#include "graph.h"
#include "PrintInGDIplusWinEmpty.h"

class networkDataStructure {
public:
	enum m_numberOfLanes { oneLane = 1, twoLanes = 2 };
	callBackLinks* m_CBLptr=nullptr;
	std::vector<std::unique_ptr<graph>>appliedGraph;
	PrintInGDIplusWinEmpty m_PWE;
	networkDataStructure();
	~networkDataStructure();
	
	void printLanesAndVehiclesOfAllEdges();
	void iniziallizationOfPointer(callBackLinks* CBL);
};
