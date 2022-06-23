#pragma once
#include "callBackLinks.h"
#include "PrecompiledHeadersEdges.h"
class networkCreationVHLinks {
private:
	int xCordinadte_store_LB=0;
	int yCordinadte_store_LB=0;
	enum m_numberOfLanes { oneLane = 1, twoLanes = 2 };
	int width=1200;
	int height=700;
	
public:
	std::unique_ptr<callBackLinks> m_CBLptr;
	std::vector<std::tuple<std::pair<int, int>, std::pair<int, int>, bool, m_numberOfLanes>> networkLaneVector;//vertical=true, horizontal=false;
	networkCreationVHLinks();
	~networkCreationVHLinks();

	int edgeCaseDisplacement(const int& transferParm, const int& boundary);
	void establishLane(const int& numberOfLanes, const int& iPosXLK_transfer, const int& iPosYLK_transfer, bool lButtonServiceBool);
};