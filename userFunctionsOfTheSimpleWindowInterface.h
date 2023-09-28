#pragma once
#include "callBackLinks.h"
#include "PrecompiledHeadersEdges.h"
#include "edge.h"
#include "graph.h"
#include "vertex.h"
#include "vertexObjectCreator.h"
#include "edgeObjectCreator.h"
class userFunctionsOfTheSimpleWindowInterface {
private:
	int xCordinadte_store_LB=0;
	int yCordinadte_store_LB=0;
	
public:
	enum m_numberOfLanes { oneLane = 1, twoLanes = 2 };
	std::vector<std::tuple<std::pair<int, int>, std::pair<int, int>, bool, m_numberOfLanes>> networkLaneVector;//vertical=true, horizontal=false;

	concreteObserverSubject* m_cObSptr = nullptr;
	callBackLinks* m_CBLptr = nullptr;
	createVertex* vertrexCreator_ptr=nullptr;
	createEdge* edgeCreator_ptr = nullptr;
	std::vector<std::shared_ptr<vertex>>vertexOfGraphPtrVectorConainer;
	std::vector<std::unique_ptr<edge>>edgeOfGraphPtrContainer;
	std::vector<std::unique_ptr<graph>>appliedGraph;

	userFunctionsOfTheSimpleWindowInterface();
	~userFunctionsOfTheSimpleWindowInterface();

	int edgeCaseDisplacement(const int& transferParm, const int& boundary);
	void establishLane(const int& width, const int& height, const int& numberOfLanes, const int& iPosXLK_transfer, const int& iPosYLK_transfer, bool lButtonServiceBool);

	void iniziallizationOfPointer(callBackLinks* CBL, concreteObserverSubject* cOS);
	void vertexCreationVH_Network(const std::pair<int, int>& XandYpostion, const int& shapeOfThatVertex);
	void graphGenerationFromClickPairs(const int& width, const int& height, const int& choiceOfRouteFinding);
};