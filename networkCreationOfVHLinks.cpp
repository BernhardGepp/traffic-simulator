#include "PrecompiledHeadersEdges.h"
#include "networkCreationOfVHLinks.h"
#include "vertexEnd.h"
#include "vertexFlex.h"
#include "vertexStart.h"
#include "graphTrafficGenerationOnAllRoutes.h"
#include "graphTrafficGenerationOnFastRoutes.h"

bool sortBottomUp(const std::pair<int, int>& a, const std::pair<int, int>& b) {
	return a.first > b.first;
}
bool sortTopDown(const std::pair<int, int>& a, const std::pair<int, int>& b) {
	return a.first < b.first;
}

//Constructor and destructor of the class:
networkDataStructure::networkDataStructure() {}
networkDataStructure::~networkDataStructure() {}

//********************************************************************
//Methods of the class:

/*void networkCreationOfVHLinks::iniziallizationOfPointer(callBackLinks* CBL, concreteObserverSubjekt* cOS) {
	m_CBLptr = CBL;
	m_cObSptr = cOS;
}*/

/*void networkCreationOfVHLinks::fillNetworkLaneVector(std::pair<int, int> startingPoint, std::pair<int, int> endingPoint, bool horizontalOrVertival, int NoL) {
	if (NoL == 1)
		networkLaneVector.push_back(std::make_tuple(startingPoint, endingPoint, horizontalOrVertival, oneLane));
	if (NoL == 2)
		networkLaneVector.push_back(std::make_tuple(startingPoint, endingPoint, horizontalOrVertival, twoLanes));
}*/

bool networkDataStructure::checkIfInNetworkLaneVector() {
	return true;
}

/*void  networkCreationOfVHLinks::graphGenerationFromClickPairs(const int& choiceOfRouteFinding) {
	//********************************************************************
	//This method generates one or more traffic graphs from a set of point pairs in which the traffic simulation is executed.
	//A traffic graph (object "graph")consists of edges and vertices, which are created in this method in the form of objects.
	//********************************************************************
	std::pair<int, int> startingPoint;
	std::pair<int, int> endingPoint;
	std::vector<std::tuple<std::pair<int, int>, std::pair<int, int>, bool, m_numberOfLanes>>::iterator estVerITER = networkLaneVector.begin();
	std::vector<std::tuple<std::pair<int, int>, std::pair<int, int>, bool, m_numberOfLanes>>::iterator estVerITERA = networkLaneVector.begin();
	int xCordinadte_store_LB = 0;
	int yCordinadte_store_LB = 0;
	int iPosXLK = 0;
	int iPosYLK = 0;
	int iPosXRK = 0;
	int iPosYRK = 0;
	int width = 1200;
	int height = 700;
	//Preparation for coordinate correction, narrowing down the search space:
	for (estVerITER = networkLaneVector.begin(); estVerITER != networkLaneVector.end(); ++estVerITER) {

		if (std::get<2>(*estVerITER) == true) {
			if (std::get<0>(*estVerITER).first < std::get<1>(*estVerITER).first) {
				if (std::get<1>(*estVerITER).first > xCordinadte_store_LB) {
					xCordinadte_store_LB = std::get<1>(*estVerITER).first;
				}
			}
			else {
				if (std::get<0>(*estVerITER).first > xCordinadte_store_LB) {
					xCordinadte_store_LB = std::get<0>(*estVerITER).first;
				}
			}
		}
		if (std::get<2>(*estVerITER) == false) {
			if (std::get<0>(*estVerITER).second < std::get<1>(*estVerITER).second) {
				if (std::get<1>(*estVerITER).second > yCordinadte_store_LB) {
					yCordinadte_store_LB = std::get<1>(*estVerITER).second;
				}
			}
			else {
				if (std::get<0>(*estVerITER).second > yCordinadte_store_LB) {
					yCordinadte_store_LB = std::get<0>(*estVerITER).second;
				}
			}
		}
	}
	//Correction of coordinates for multi-lane links on the X-axis:
	while (xCordinadte_store_LB > 0) {
		estVerITER = networkLaneVector.begin();
		while (estVerITER != networkLaneVector.end()) {
			if ((std::get<0>(*estVerITER).first + 10 == xCordinadte_store_LB) && (std::get<2>(*estVerITER) == false)) {
				estVerITERA = networkLaneVector.begin();
				while (estVerITERA != networkLaneVector.end()) {
					if ((std::get<2>(*estVerITERA) == true) && (std::get<0>(*estVerITERA).first == xCordinadte_store_LB)) {
						if (std::get<0>(*estVerITER).second < std::get<1>(*estVerITER).second) {
							if ((std::get<0>(*estVerITER).second <= std::get<0>(*estVerITERA).second) && (std::get<1>(*estVerITERA).second <= std::get<1>(*estVerITER).second)) {
								std::get<0>(*estVerITERA).first = std::get<0>(*estVerITERA).first - 10;
							}
						}
						else {
							if ((std::get<1>(*estVerITER).second <= std::get<0>(*estVerITERA).second) && (std::get<1>(*estVerITERA).second <= std::get<0>(*estVerITER).second)) {
								std::get<0>(*estVerITERA).first = std::get<0>(*estVerITERA).first - 10;
							}
						}

					}
					if ((std::get<2>(*estVerITERA) == true) && (std::get<1>(*estVerITERA).first == xCordinadte_store_LB)) {
						if (std::get<0>(*estVerITER).second < std::get<1>(*estVerITER).second) {
							if ((std::get<0>(*estVerITER).second <= std::get<0>(*estVerITERA).second) && (std::get<1>(*estVerITERA).second <= std::get<1>(*estVerITER).second)) {
								std::get<1>(*estVerITERA).first = std::get<1>(*estVerITERA).first - 10;
							}
						}
						else {
							if ((std::get<1>(*estVerITER).second <= std::get<0>(*estVerITERA).second) && (std::get<1>(*estVerITERA).second <= std::get<0>(*estVerITER).second)) {
								std::get<1>(*estVerITERA).first = std::get<1>(*estVerITERA).first - 10;
							}
						}

					}
					++estVerITERA;
				}
			}
			++estVerITER;
		}
		xCordinadte_store_LB = xCordinadte_store_LB - 10;
	}
	//Correction of coordinates for multi-lane links on the Y-axis:
	while (yCordinadte_store_LB > 0) {
		estVerITER = networkLaneVector.begin();
		while (estVerITER != networkLaneVector.end()) {
			if ((std::get<0>(*estVerITER).second + 10 == yCordinadte_store_LB) && (std::get<2>(*estVerITER) == true)) {
				estVerITERA = networkLaneVector.begin();
				while (estVerITERA != networkLaneVector.end()) {
					if ((std::get<2>(*estVerITERA) == false) && (std::get<0>(*estVerITERA).second == yCordinadte_store_LB)) {
						if (std::get<0>(*estVerITER).first < std::get<1>(*estVerITER).first) {
							if ((std::get<0>(*estVerITER).first <= std::get<0>(*estVerITERA).first) && (std::get<1>(*estVerITERA).first <= std::get<1>(*estVerITER).first)) {
								std::get<0>(*estVerITERA).second = std::get<0>(*estVerITERA).second - 10;
							}
						}
						else {
							if ((std::get<1>(*estVerITER).first <= std::get<0>(*estVerITERA).first) && (std::get<1>(*estVerITERA).first <= std::get<0>(*estVerITER).first)) {
								std::get<0>(*estVerITERA).second = std::get<0>(*estVerITERA).second - 10;
							}
						}
					}
					if ((std::get<2>(*estVerITERA) == false) && (std::get<1>(*estVerITERA).second == yCordinadte_store_LB)) {
						if (std::get<0>(*estVerITER).first < std::get<1>(*estVerITER).first) {
							if ((std::get<0>(*estVerITER).first <= std::get<0>(*estVerITERA).first) && (std::get<1>(*estVerITERA).first <= std::get<1>(*estVerITER).first)) {
								std::get<1>(*estVerITERA).second = std::get<1>(*estVerITERA).second - 10;
							}
						}
						else {
							if ((std::get<1>(*estVerITER).first <= std::get<0>(*estVerITERA).first) && (std::get<1>(*estVerITERA).first <= std::get<0>(*estVerITER).first)) {
								std::get<1>(*estVerITERA).second = std::get<1>(*estVerITERA).second - 10;
							}
						}
					}
					++estVerITERA;
				}
			}
			++estVerITER;
		}
		yCordinadte_store_LB = yCordinadte_store_LB - 10;
	}
	//Generation of vertex objects at intersection accounts or common start and end nodes:
	vertexOfGraphPtrVectorConainer.clear();
	edgeOfGraphPtrContainer.clear();
	std::pair<int, int>XsearchBoundary;//min == first, max == second
	XsearchBoundary.first = width;
	XsearchBoundary.second = 0;
	std::pair<int, int>YsearchBoundary;//min == first, max == second
	YsearchBoundary.first = height;
	YsearchBoundary.second = 0;
	std::vector<std::tuple<int, int, bool>> orientationMap;//Notation: first and second lane which will be compared. Comparison performed/or not necessary (true) or not yet performed (false).
	int counter = 0;
	int secondCounter = 0;
	for (auto& i : networkLaneVector) {
		secondCounter = 0;
		for (auto& ia : networkLaneVector) {
			if (std::get<2>(i) == std::get<2>(ia))
				orientationMap.push_back(std::make_tuple(counter, secondCounter, false));	//same arrangement in the field
			if (std::get<2>(i) != std::get<2>(ia))
				orientationMap.push_back(std::make_tuple(counter, secondCounter, true)); //orthogonal arrangement in the field
			secondCounter++;
		}
		counter++;
	}

	for (auto& i : orientationMap) {
		if (std::get<0>(i) == std::get<1>(i))		//prevention of comparison between same entries
			std::get<2>(i) = true;
	}
	counter = 0;
	secondCounter = 0;
	for (auto& i : orientationMap) {
		if (std::get<2>(i) == false) {
			std::get<2>(i) = true;					//mark vertex-pair as done! set it TRUE!
			counter = std::get<0>(i);				// the variable "counter" is used to address the data-field in the arry "networkLaneVector"
			secondCounter = std::get<1>(i);			// the variable "secondCounter" is used to address the data-field in the arry "networkLaneVector"
			for (auto& ia : orientationMap) {
				if ((counter == std::get<1>(ia)) && (secondCounter == std::get<0>(ia)))
					std::get<2>(ia) = true;  //Mark the comparison pair as done!
			}
			//***Begin of comparison:
			//Ending Link(1) vs. Beginning Link(2) in case of two singelLaneLinks
			if ((std::get<1>(networkLaneVector[counter]).first == std::get<0>(networkLaneVector[secondCounter]).first) &&
				(std::get<1>(networkLaneVector[counter]).second == std::get<0>(networkLaneVector[secondCounter]).second)) {
				vertexCreationVH_Network(std::get<1>(networkLaneVector[counter]), 11);
			}
			//Ending Link(1) vs. Ending Link(2) in case of two singelLaneLinks
			if ((std::get<1>(networkLaneVector[counter]).first == std::get<1>(networkLaneVector[secondCounter]).first) &&
				(std::get<1>(networkLaneVector[counter]).second == std::get<1>(networkLaneVector[secondCounter]).second)) {
				vertexCreationVH_Network(std::get<1>(networkLaneVector[counter]), 2);
			}
			//Beginning Link(1) vs. Beginning Link(2) in case of two singelLaneLinks
			if ((std::get<0>(networkLaneVector[counter]).first == std::get<0>(networkLaneVector[secondCounter]).first) &&
				(std::get<0>(networkLaneVector[counter]).second == std::get<0>(networkLaneVector[secondCounter]).second)) {
				vertexCreationVH_Network(std::get<0>(networkLaneVector[counter]), 1);
			}
			//Beginning Link(1) vs. Ending Link(2) in case of two singelLaneLinks
			if ((std::get<0>(networkLaneVector[counter]).first == std::get<1>(networkLaneVector[secondCounter]).first) &&
				(std::get<0>(networkLaneVector[counter]).second == std::get<1>(networkLaneVector[secondCounter]).second)) {
				vertexCreationVH_Network(std::get<0>(networkLaneVector[counter]), 11);
			}
		}
	}

	for (auto& i : networkLaneVector) {
		vertexCreationVH_Network(std::get<0>(i), 1);	//Creation of start and end vertices if not already created
		vertexCreationVH_Network(std::get<1>(i), 2);
	}
	counter = 0;
	secondCounter = 0;
	bool serviceBool1 = false;
	for (auto& i : networkLaneVector) {
		XsearchBoundary.first = 10000;
		XsearchBoundary.second = 10000;
		serviceBool1 = false;
		if (std::get<2>(i) == true) {
			if (std::get<0>(i).first < std::get<1>(i).first) {
				XsearchBoundary.first = std::get<0>(i).first;
				XsearchBoundary.second = std::get<1>(i).first;
				serviceBool1 = true;
			}
			if (std::get<0>(i).first > std::get<1>(i).first) {
				XsearchBoundary.first = std::get<1>(i).first;
				XsearchBoundary.second = std::get<0>(i).first;
				serviceBool1 = false;
			}
			YsearchBoundary.first = std::get<0>(i).second;
			YsearchBoundary.second = std::get<0>(i).second;
			if (std::get<3>(i) == 2)
				YsearchBoundary.second = std::get<0>(i).second + 10;
		}
		secondCounter = 0;
		for (auto& ia : networkLaneVector) {
			if (std::get<2>(ia) == false) {

				if ((XsearchBoundary.first <= std::get<0>(ia).first) && (std::get<0>(ia).first <= XsearchBoundary.second) &&
					(
						((std::get<0>(ia).second <= YsearchBoundary.first) && (YsearchBoundary.first <= std::get<1>(ia).second)) ||
						((std::get<1>(ia).second <= YsearchBoundary.first) && (YsearchBoundary.first <= std::get<0>(ia).second))
						)
					) {
					if ((XsearchBoundary.first == std::get<0>(ia).first) && (std::get<0>(ia).second == YsearchBoundary.first) && (serviceBool1 == true)) {

					}
					else if ((XsearchBoundary.second == std::get<0>(ia).first) && (std::get<1>(ia).second == YsearchBoundary.first) && (serviceBool1 == true)) {

					}
					else if ((XsearchBoundary.second == std::get<0>(ia).first) && (std::get<0>(ia).second == YsearchBoundary.first) && (serviceBool1 == false)) {

					}
					else if ((XsearchBoundary.first == std::get<0>(ia).first) && (std::get<1>(ia).second == YsearchBoundary.first) && (serviceBool1 == false)) {

					}
					else {
						std::pair<int, int>transferePair;
						transferePair.first = std::get<0>(ia).first;
						transferePair.second = YsearchBoundary.first;
						vertexCreationVH_Network(transferePair, 11);//Creation of intersection nodes in the graph
					}
				}
			}
			secondCounter++;
		}
		counter++;
	}
	iPosXLK = 0;
	iPosYLK = 0;
	iPosXRK = 0;
	iPosYRK = 0;
	//*******************************************************
	//Numbering of the nodes(Vertex):
	counter = 1;
	for (auto& iEb : vertexOfGraphPtrVectorConainer) {
		iEb->numberingOfVertexes(counter);
		counter++;
		iEb->setPrintShape(iEb->m_shapeOfThatVertex);
	}

	iPosXLK = 0;
	iPosYLK = 0;
	iPosXRK = 0;
	iPosYRK = 0;
	counter = 0;
	//******************
	//Graph generation

	std::vector<std::pair<int, int>>VectorOfVertex = {};
	VectorOfVertex.clear();
	std::pair<std::pair<int, int>, std::pair<int, int>> possibleEdge;
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>VectorOfPossibleEdge = {};
	std::vector<bool>directionOfLink;
	std::pair<int, int> VertexIDofEdges;
	std::pair<int, int>CrossingVertex;
	bool increasingOrDecreasing = true;
	int maxValue = 0;
	for (auto& ia : networkLaneVector) {
		possibleEdge.first.first = 0;
		possibleEdge.second.first = 0;
		if (std::get<2>(ia) == true) {
			int iterHori = 0;
			if (std::get<0>(ia).first < std::get<1>(ia).first) {
				iterHori = std::get<0>(ia).first;
				maxValue = std::get<1>(ia).first;
				increasingOrDecreasing = true;
			}
			else {
				iterHori = std::get<1>(ia).first;
				maxValue = std::get<0>(ia).first;
				increasingOrDecreasing = false;
			}
			for (iterHori; iterHori <= maxValue; iterHori = iterHori + 10) {
				for (auto& iG : vertexOfGraphPtrVectorConainer) {
					//Vertikal
					if ((iG->m_XcoordinateVertex == iterHori) && (iG->m_YcoordinateVertex == std::get<0>(ia).second) && (possibleEdge.first.first == 0)) {
						possibleEdge.first.first = iG->m_vertexID;
						possibleEdge.first.second = iG->m_shapeOfThatVertex;
						iterHori = iterHori + 10;
					}
				}
				if (possibleEdge.first.first != 0) {
					for (auto& iG : vertexOfGraphPtrVectorConainer) {
						if ((iG->m_XcoordinateVertex == iterHori) && (iG->m_YcoordinateVertex == std::get<0>(ia).second)) {
							possibleEdge.second.first = iG->m_vertexID;
							possibleEdge.second.second = iG->m_shapeOfThatVertex;
						}
					}
					if ((possibleEdge.first.first != 0) && (possibleEdge.second.first != 0)) {
						if (increasingOrDecreasing)
							edgeOfGraphPtrContainer.push_back(std::make_unique<edge>(possibleEdge.first.first - 1, possibleEdge.second.first - 1, std::get<3>(ia),
								std::move(choosePrintPattern(vertexOfGraphPtrVectorConainer[possibleEdge.first.first - 1]->m_XcoordinateVertex,
									vertexOfGraphPtrVectorConainer[possibleEdge.first.first - 1]->m_YcoordinateVertex,
									vertexOfGraphPtrVectorConainer[possibleEdge.second.first - 1]->m_XcoordinateVertex,
									vertexOfGraphPtrVectorConainer[possibleEdge.second.first - 1]->m_YcoordinateVertex,

									std::get<3>(ia), 0)),
								m_cObSptr));

						if (!increasingOrDecreasing)

							edgeOfGraphPtrContainer.push_back(std::make_unique<edge>(possibleEdge.second.first - 1, possibleEdge.first.first - 1, std::get<3>(ia),
								std::move(choosePrintPattern(vertexOfGraphPtrVectorConainer[possibleEdge.second.first - 1]->m_XcoordinateVertex,
									vertexOfGraphPtrVectorConainer[possibleEdge.second.first - 1]->m_YcoordinateVertex,
									vertexOfGraphPtrVectorConainer[possibleEdge.first.first - 1]->m_XcoordinateVertex,
									vertexOfGraphPtrVectorConainer[possibleEdge.first.first - 1]->m_YcoordinateVertex,

									std::get<3>(ia), 0)),
								m_cObSptr));


						possibleEdge.first.first = possibleEdge.second.first;
						possibleEdge.first.second = possibleEdge.second.second;
						possibleEdge.second.first = 0;
						possibleEdge.second.second = 0;
					}
				}
			}
		}
		if (std::get<2>(ia) == false) {
			int iterVerti = 0;
			if (std::get<0>(ia).second < std::get<1>(ia).second) {
				iterVerti = std::get<0>(ia).second;
				maxValue = std::get<1>(ia).second;
				increasingOrDecreasing = true;
			}
			else {
				iterVerti = std::get<1>(ia).second;
				maxValue = std::get<0>(ia).second;
				increasingOrDecreasing = false;
			}
			for (iterVerti; iterVerti <= maxValue; iterVerti = iterVerti + 10) {
				for (auto& iG : vertexOfGraphPtrVectorConainer) {
					//Vertical
					if ((iG->m_XcoordinateVertex == std::get<0>(ia).first) && (iG->m_YcoordinateVertex == iterVerti) && (possibleEdge.first.first == 0)) {
						possibleEdge.first.first = iG->m_vertexID;
						possibleEdge.first.second = iG->m_shapeOfThatVertex;
						iterVerti = iterVerti + 10;
					}
				}
				if (possibleEdge.first.first != 0) {
					for (auto& iG : vertexOfGraphPtrVectorConainer) {
						if ((iG->m_XcoordinateVertex == std::get<0>(ia).first) && (iG->m_YcoordinateVertex == iterVerti)) {
							possibleEdge.second.first = iG->m_vertexID;
							possibleEdge.second.second = iG->m_shapeOfThatVertex;
						}
					}
					if ((possibleEdge.first.first != 0) && (possibleEdge.second.first != 0)) {
						if (increasingOrDecreasing)
							edgeOfGraphPtrContainer.push_back(std::make_unique<edge>(possibleEdge.first.first - 1, possibleEdge.second.first - 1, std::get<3>(ia),
								std::move(choosePrintPattern(vertexOfGraphPtrVectorConainer[possibleEdge.first.first - 1]->m_XcoordinateVertex,
									vertexOfGraphPtrVectorConainer[possibleEdge.first.first - 1]->m_YcoordinateVertex,
									vertexOfGraphPtrVectorConainer[possibleEdge.second.first - 1]->m_XcoordinateVertex,
									vertexOfGraphPtrVectorConainer[possibleEdge.second.first - 1]->m_YcoordinateVertex,
									0,
									std::get<3>(ia))),
								m_cObSptr));

						if (!increasingOrDecreasing)

							edgeOfGraphPtrContainer.push_back(std::make_unique<edge>(possibleEdge.second.first - 1, possibleEdge.first.first - 1, std::get<3>(ia),
								std::move(choosePrintPattern(vertexOfGraphPtrVectorConainer[possibleEdge.second.first - 1]->m_XcoordinateVertex,
									vertexOfGraphPtrVectorConainer[possibleEdge.second.first - 1]->m_YcoordinateVertex,
									vertexOfGraphPtrVectorConainer[possibleEdge.first.first - 1]->m_XcoordinateVertex,
									vertexOfGraphPtrVectorConainer[possibleEdge.first.first - 1]->m_YcoordinateVertex,
									0,
									std::get<3>(ia))),
								m_cObSptr));

						possibleEdge.first.first = possibleEdge.second.first;
						possibleEdge.first.second = possibleEdge.second.second;
						possibleEdge.second.first = 0;
						possibleEdge.second.second = 0;
					}
				}
			}
		}
	}

	if (!edgeOfGraphPtrContainer.empty()) {
		for (auto& i : edgeOfGraphPtrContainer) {
			i->m_startVertex++;
			i->m_endVertex++;
		}
	}
	counter = 0;
	iPosXLK = 0;
	iPosXRK = 0;
	iPosYLK = 0;
	iPosYRK = 0;
	int numberOfEdges = edgeOfGraphPtrContainer.size();
	bool serviceBool = false;
	std::set<int>setOfVertexes;
	size_t sizeOfSetOfVertexes = setOfVertexes.size();
	std::vector<int>vectorOfVertexes;
	std::set<int>setOfVertexesNotOfPrimeGraph;
	std::vector<std::unique_ptr<edge>>::iterator i = edgeOfGraphPtrContainer.begin();
	std::vector<std::shared_ptr<vertex>> vectorOfVertexPTR;
	std::vector<std::shared_ptr<edge>> vectorOfEdgePTR;

	std::set<int>::iterator ii = setOfVertexes.begin();

	if (!edgeOfGraphPtrContainer.empty()) {
		appliedGraph.clear();
		setOfVertexes.insert(edgeOfGraphPtrContainer[0]->m_startVertex);
		setOfVertexes.insert(edgeOfGraphPtrContainer[0]->m_endVertex);

		do {
			setOfVertexesNotOfPrimeGraph.clear();

			do {
				ii = setOfVertexes.begin();
				vectorOfVertexes.clear();
				sizeOfSetOfVertexes = 0;
				while (ii != setOfVertexes.end()) {

					i = edgeOfGraphPtrContainer.begin();
					while (i != edgeOfGraphPtrContainer.end()) {
						if (*i != nullptr) {
							if ((((*ii) == (*i)->m_startVertex) && ((*ii) != (*i)->m_endVertex)) || (((*ii) != (*i)->m_startVertex) && ((*ii) == (*i)->m_endVertex))) {
								vectorOfVertexes.push_back((*i)->m_startVertex);
								vectorOfVertexes.push_back((*i)->m_endVertex);
							}
						}
						i++;
					}
					ii++;
				}
				sizeOfSetOfVertexes = setOfVertexes.size();
				for (auto& iii : vectorOfVertexes) {

					setOfVertexes.insert(iii);
				}
			} while (sizeOfSetOfVertexes < setOfVertexes.size());


			for (auto& ja : edgeOfGraphPtrContainer) {
				if (ja != nullptr) {
					serviceBool = false;
					for (auto& jb : setOfVertexes) {
						if ((jb == ja->m_startVertex) || (jb == ja->m_endVertex)) {
							serviceBool = true;
						}
					}

					if (!appliedGraph.empty()) {
						for (auto& id : appliedGraph) {
							for (auto& ie : id->m_setOfVertexes) {
								if ((ie == ja->m_startVertex) || (ie == ja->m_endVertex)) {
									serviceBool = true;
								}
							}
						}
					}
					if (serviceBool == false) {
						setOfVertexesNotOfPrimeGraph.insert(ja->m_startVertex);
					}
					serviceBool = false;
				}
			}

			vectorOfVertexPTR.clear();
			vectorOfEdgePTR.clear();


			for (auto& jcx : setOfVertexes) {
				for (auto& jcy : vertexOfGraphPtrVectorConainer) {
					if (jcy != nullptr) {
						if (jcx == jcy->m_vertexID) {
							vectorOfVertexPTR.push_back(std::move(jcy));
						}
					}
				}
				bool inVectorEdgePTR = false;
				for (auto& jcz : edgeOfGraphPtrContainer) {
					inVectorEdgePTR = false;
					if (jcz != nullptr) {
						if ((jcx == jcz->m_startVertex) || (jcx == jcz->m_endVertex)) {

							std::shared_ptr<edge> edgePTR = std::move(jcz);

							for (auto& jcza : vectorOfEdgePTR) {

								if (jcza == edgePTR) {
									inVectorEdgePTR = true;
								}
							}
							if (inVectorEdgePTR == false) {
								vectorOfEdgePTR.push_back(edgePTR);
							}
						}
					}
				}
			}
			if (choiceOfRouteFinding == 1)
				appliedGraph.push_back(std::make_unique<graphTrafficGenerationOnAllRoutes>(setOfVertexes, vectorOfVertexPTR, vectorOfEdgePTR, gsl::not_null<callBackLinks*>(m_CBLptr)));
			if (choiceOfRouteFinding == 2)
				appliedGraph.push_back(std::make_unique<graphTrafficGenerationOnFastRoutes>(setOfVertexes, vectorOfVertexPTR, vectorOfEdgePTR, gsl::not_null<callBackLinks*>(m_CBLptr)));
			setOfVertexes.clear();
			vectorOfVertexPTR.clear();
			vectorOfEdgePTR.clear();
			if (!setOfVertexesNotOfPrimeGraph.empty()) {
				std::set<int>::iterator jc = setOfVertexesNotOfPrimeGraph.begin();
				serviceBool = false;
				do {
					if (appliedGraph.empty()) {
						setOfVertexes.insert(*jc);
						serviceBool = false;
					}
					else {
						if (serviceBool == false) {
							setOfVertexes.insert(*jc);

							serviceBool = true;
						}
					}
					jc++;
				} while (jc != setOfVertexesNotOfPrimeGraph.end());

				setOfVertexesNotOfPrimeGraph.clear();
			}
			if (setOfVertexes.empty()) {
				serviceBool = false;
			}
			else {
				serviceBool = true;
			}
		} while (serviceBool);
	}
	vertexOfGraphPtrVectorConainer.clear();
	edgeOfGraphPtrContainer.clear();
}

void networkCreationOfVHLinks::vertexCreationVH_Network(const std::pair<int, int>& XandYpostion, const int& shapeOfThatVertex) {
	//********************************************************************
	//Vertex generation for a graph with vertical and horizontal links
	//This method is called by the method "graphGenerationFromClickPairs". This method is part of the traffic graph generation. 
	bool serviceBool = false;
	int shapeOfThatVertex_var = shapeOfThatVertex;
	if (vertexOfGraphPtrVectorConainer.size() == 0) {
		serviceBool = true;
	}
	else {
		serviceBool = true;
		for (auto i = vertexOfGraphPtrVectorConainer.begin(); i != vertexOfGraphPtrVectorConainer.end(); i++) {
			if ((XandYpostion.first == (*i)->m_XcoordinateVertex) && (XandYpostion.second == (*i)->m_YcoordinateVertex)) {
				if ((*i)->m_shapeOfThatVertex == shapeOfThatVertex_var) {
					serviceBool = false;
				}
				if ((*i)->m_shapeOfThatVertex != shapeOfThatVertex_var) {
					serviceBool = true;
					shapeOfThatVertex_var = 11;
					vertexOfGraphPtrVectorConainer.erase(i--);
					break;
				}
			}
		}
	}
	if (serviceBool) {
		if (shapeOfThatVertex_var == 1) {
			vertexOfGraphPtrVectorConainer.push_back(std::make_unique<vertexStart>(XandYpostion.first, XandYpostion.second, shapeOfThatVertex_var));
		}
		if (shapeOfThatVertex_var == 2) {
			vertexOfGraphPtrVectorConainer.push_back(std::make_unique<vertexEnd>(XandYpostion.first, XandYpostion.second, shapeOfThatVertex_var));
		}
		if (shapeOfThatVertex_var == 11) {
			vertexOfGraphPtrVectorConainer.push_back(std::make_unique<vertexFlex>(XandYpostion.first, XandYpostion.second, shapeOfThatVertex_var));
		}
	}
}


std::unique_ptr<PrintPattern> networkCreationOfVHLinks::choosePrintPattern(const int& p1x, const int& p1y, const int& p2x, const int& p2y, const int& lanesH, const int& lanesV) {
	//********************************************************************
	//Selection of the appropriate print pattern
	//This method is called by the method "graphGenerationFromClickPairs". This method is part of the traffic graph generation. 
	if ((p1x < p2x) && (p1y == p2y)) {
		if (lanesH == 1) {
			return std::make_unique<PrintPatternLine1LaneHoriPos>(p1x, p1y, p2x, p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
		else if (lanesH == 2) {
			return std::make_unique<PrintPatternLine2LaneHoriPos>(p1x, p1y, p2x, p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
	}
	if ((p1x > p2x) && (p1y == p2y)) {
		if (lanesH == 1) {
			return std::make_unique<PrintPatternLine1LaneHoriNeg>(p1x, p1y, p2x, p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
		else if (lanesH == 2) {
			return std::make_unique<PrintPatternLine2LaneHoriNeg>(p1x, p1y, p2x, p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
	}
	if ((p1x == p2x) && (p1y < p2y)) {
		if (lanesV == 1) {
			return std::make_unique<PrintPatternLine1LaneVertiPos>(p1x, p1y, p2x, p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
		else if (lanesV == 2) {
			return std::make_unique<PrintPatternLine2LaneVertiPos>(p1x, p1y, p2x, p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
	}
	if ((p1x == p2x) && (p1y > p2y)) {
		if (lanesV == 1) {
			return std::make_unique<PrintPatternLine1LaneVertiNeg>(p1x, p1y, p2x, p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
		else if (lanesV == 2) {
			return std::make_unique<PrintPatternLine2LaneVertiNeg>(p1x, p1y, p2x, p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
	}
	return nullptr;
}*/

void networkDataStructure::printLanesAndVehiclesOfAllEdges() {

	for (auto& i : appliedGraph) {
		i->printLanesAndVehiclesOfAllEdges();
	}
	//m_PWE.fullemptyPrintContainer(m_CBLptr->m_hdc, m_CBLptr->m_f5PaintLane);
}