#include "PrecompiledHeadersEdges.h"
#include "graph.h"

//Constructor and destructor of the class:
graph::graph(const std::set<int>& setOfVertexes,
	std::vector<std::shared_ptr<vertex>>& vectorOfVertex,
	std::vector<std::shared_ptr<edge>>& vectorOfEdges
)
	:m_vectorOfVertexPtr(vectorOfVertex),
	m_vectorOfEdgesPtr(vectorOfEdges)
{
	int counter = 0;
	for (auto& i : m_vectorOfVertexPtr) {
		i->setPoolAllocatorPtr(m_poolAllocator);		//Assigning the corresponding PoolAllocator to the vertices of the graph
		i->m_vertexIDpair.first = i->m_vertexID;
		i->m_vertexIDpair.second = counter;
		counter++;
	}
	for (auto& i : m_vectorOfEdgesPtr) {				//Assigning the corresponding PoolAllocator to the edges of the graph
		i->setPoolAllocatorPtr(m_poolAllocator);
		for (auto& j : m_vectorOfVertexPtr) {			//Initialization of the vertices in the graph
			if (j->m_vertexID == i->m_startVertex) {
				j->setTransmissionTable(i->m_endVertex);
			}
		}
	}
	generationOfRoutesNeu();
}

graph::~graph() noexcept {}

//********************************************************************
//Methods of the class:

void graph::simulation(const int& simulationIterator) {
	//*************************************************
	//method for carrying out the simulation
	if (simulationIterator % 5 == 0) {
		calculationOfRouteIndex();
	}
	if (m_vectorOfEdgesPtr.size() != 0) {
		for (auto& i : m_vectorOfEdgesPtr) {
			i->simiRun(simulationIterator);		//Command to execute a simulation iteration
		}
	}
	if (simulationIterator % 20 == 0) {			//Calling a methode for cleaning up multiple captured vehicles
		clean();
	}
}

void graph::clean() {
	//*************************************************
	//methode for cleaning up multiple captured vehicles within the simulation
	std::vector<std::pair<vehicle*, int>>vectorOfVehicleToErase;
	vectorOfVehicleToErase.clear();
	if (!m_poolAllocator.m_vectorOfAllocatedObjekts.empty()) {
		m_poolAllocator.buildVectorOfObjektPtr();
		for (auto& i : m_poolAllocator.m_vectorOfAllocatedObjekts) {
			vectorOfVehicleToErase.push_back(
				std::make_pair(reinterpret_cast<vehicle*>(i), 0)
			);
		}
	}
	if (!vectorOfVehicleToErase.empty()) {
		size_t serviceInt = 0;
		for (auto& i : m_vectorOfEdgesPtr) {
			auto ii = i->sFs.vehicleSetPtr->m_vehicleSet.rbegin();
			for (ii = i->sFs.vehicleSetPtr->m_vehicleSet.rbegin(); ii != i->sFs.vehicleSetPtr->m_vehicleSet.rend(); ++ii) {
				for (auto& j : vectorOfVehicleToErase) {
					if ((*ii) == j.first) {
						j.second++;
					}
				}
			}
		}
		for (auto& i : m_vectorOfVertexPtr) {
			for (auto& j : vectorOfVehicleToErase) {
				j.second = i->checkIfVehicleIsInV(j.first) + j.second;
			}
		}

		for (auto& j : vectorOfVehicleToErase) {

			if (j.second >= 2) {
				j.first->m_inRange = false;
				j.first->m_lane = 0;
				j.first->m_moblieORStationary = true;
				j.first->m_pref_speed = 0;
				j.first->m_routeID = 0;
				j.first->m_routeVertexID_vehicle.clear();
				j.first->m_processedByIteration = true;
				if (j.first->m_riseOrDecline)
					j.first->m_position = 999999;
				else
					j.first->m_position = -500;

				m_poolAllocator.deallocateClean(j.first);
			}
		}
	}
}

bool graph::isInsideRouteVertexIDs(const std::vector<std::pair<int, int>>& routeVertexIDs, const int& checkValue) {
	//this method complements the "generationOfRoutesNeu()"-method
	bool checkBool = false;
	for (auto& i : routeVertexIDs) {
		if (i.first == checkValue) {
			checkBool = true;
		}
	}
	return checkBool;
}

bool graph::recheckroute(const std::vector<int>& routeVertexIDs) {
	int checkint = 0;
	for (auto& ii : m_vectorOfEdgesPtr) {
		for (size_t i = 1; i < routeVertexIDs.size(); i++) {
			if ((ii->m_startVertex == routeVertexIDs[i - 1]) && (ii->m_endVertex == routeVertexIDs[i])) {
				checkint++;
			}
		}
	}
	return checkint == (routeVertexIDs.size() - 1) ? true : false;
}

void graph::calculationOfRouteIndex() {
}

void graph::generationOfRoutesNeu() {
	//*************************************************
	//Method for exploring all routes in the graph
	std::vector<std::shared_ptr<edge>> routeEdgeVector;
	std::vector<std::pair<int, int>>routeVertexIDs;
	std::vector<std::pair<int, int>>::reverse_iterator routeVertexID_RIter = routeVertexIDs.rbegin();



	//*************************************************
	//Vertex preparation
	std::vector<std::tuple<bool, int, int>>topologyMarks;
	topologyMarks.clear();
	topologyMarks.reserve(m_vectorOfVertexPtr.size()+1);
	for (auto& ic : m_vectorOfVertexPtr) {
		if (ic->sizeOfTransmissiontable() == 0) {
			topologyMarks.emplace_back(std::make_tuple(false, 0, 0));
		}
		else {
			topologyMarks.emplace_back(std::make_tuple(true, ic->sizeOfTransmissiontable(), ic->sizeOfTransmissiontable()));
		}
	}

	//*************************************************
	//Start of the exploration of all links in the graph
	routeVertexIDs.clear();
	int processedVertex = 0;
	bool serviceBool1 = false;
	size_t serviceInt1 = 0;
	std::vector<std::shared_ptr<vertex>>::iterator hj = m_vectorOfVertexPtr.begin();
	int zIter = 0;
	std::vector<std::pair<int, int>> testV;
	while (hj != m_vectorOfVertexPtr.end()) {
		
		routeVertexIDs.clear();
		if ((*hj)->m_shapeOfThatVertex == 1) {

			for (size_t topoIter = 0; topoIter < topologyMarks.size(); topoIter++) {
				std::get<2>(topologyMarks[topoIter]) = std::get<1>(topologyMarks[topoIter]);
			}
			serviceInt1 = (*hj)->sizeOfTransmissiontable() - 1;
			testV = (*hj)->getAdjacentEdges();
			processedVertex = testV[serviceInt1].second;
			routeVertexIDs.push_back((*hj)->m_vertexIDpair);//hier problem
			while (true) {
				if (std::get<2>(topologyMarks[(*hj)->m_vertexIDpair.second]) <= 0) {

					break;
				}
				serviceBool1 = isInsideRouteVertexIDs(routeVertexIDs, processedVertex);
				for (auto& j : m_vectorOfVertexPtr) {
					if ((processedVertex) == j->m_vertexIDpair.first) {
						serviceInt1 = j->m_vertexIDpair.second + 1;
						break;
					}
				}
				if ((serviceBool1) ||
					(std::get<0>(topologyMarks[serviceInt1 - 1]) == false)) {
					if (serviceBool1) {
						processedVertex = routeVertexIDs.back().first;
					}
					for (auto& j : m_vectorOfVertexPtr) {
						if ((processedVertex) == j->m_vertexIDpair.first) {
							serviceInt1 = j->m_vertexIDpair.second + 1;
							break;
						}
					}

					if (std::get<0>(topologyMarks[serviceInt1 - 1]) == false) {


						for (auto& j : m_vectorOfVertexPtr) {
							if ((serviceInt1 - 1) == j->m_vertexIDpair.second) {
								routeVertexIDs.push_back(j->m_vertexIDpair);
								break;
							}
						}

						//RoutenErstelltung:
						routeEdgeVector.clear();
						for (size_t intIterator = 1; intIterator < routeVertexIDs.size(); intIterator++) {
							for (auto& iterEdge : m_vectorOfEdgesPtr) {
								if ((routeVertexIDs[intIterator - 1].first == iterEdge->m_startVertex) && (routeVertexIDs[intIterator].first == iterEdge->m_endVertex)) {
									routeEdgeVector.push_back(iterEdge);
								}
							}
						}

						int index = 0;
						if (!m_vectorOfRoutesPtr.empty()) {
							for (auto& routeIter : m_vectorOfRoutesPtr) {
								if ((routeIter->m_vertexOfRouteID[0] == routeVertexIDs[0].first) && (routeIter->m_vertexOfRouteID.back() == routeVertexIDs.back().first)) {
									index++;
								}
							}
						}

						if (!routeVertexIDs.empty()) {
							std::vector<int>routeVertexIDsINT;
							routeVertexIDsINT.clear();
							routeVertexIDsINT.reserve(routeVertexIDs.size()+1);
							for (auto& routV_iter : routeVertexIDs) {
								routeVertexIDsINT.emplace_back(routV_iter.first);
							}

							m_vectorOfRoutesPtr.push_back(std::make_unique<route>(routeVertexIDsINT, routeEdgeVector, index));
						}
						else {

						}
					}
					routeVertexID_RIter = routeVertexIDs.rbegin();
					while (routeVertexID_RIter != routeVertexIDs.rend()) {

						std::get<2>(topologyMarks[(*routeVertexID_RIter).second])--;

						if (std::get<2>(topologyMarks[(*routeVertexID_RIter).second]) > 0) {
							for (auto& j : m_vectorOfVertexPtr) {
								if ((processedVertex) == j->m_vertexIDpair.first) {
									serviceInt1 = j->m_vertexIDpair.second + 1;
								}
							}
							hj = m_vectorOfVertexPtr.begin() + (serviceInt1 - 1);
							serviceInt1 = std::get<2>(topologyMarks[serviceInt1 - 1]) - 1;
							testV = (*hj)->getAdjacentEdges();
							processedVertex = testV[serviceInt1].second;
							hj = m_vectorOfVertexPtr.begin() + (zIter);

							if (isInsideRouteVertexIDs(routeVertexIDs, processedVertex)) {

							}
							else {

								break;
							}
						}
						else {

							++routeVertexID_RIter;

							if (routeVertexIDs.size() > 1) {
								routeVertexIDs.erase(routeVertexID_RIter.base());
							}

							routeVertexID_RIter = routeVertexIDs.rbegin();
							processedVertex = routeVertexIDs.back().first;
							for (auto& j : m_vectorOfVertexPtr) {
								if ((processedVertex) == j->m_vertexIDpair.first) {
									serviceInt1 = j->m_vertexIDpair.second + 1;
									break;
								}
							}
							if ((std::get<2>(topologyMarks[serviceInt1 - 1]) <= 0) && (routeVertexIDs.size() <= 1)) {

								break;
							}
							if ((std::get<2>(topologyMarks[serviceInt1 - 1]) <= 0)) {

								break;
							}
						}
					}
					serviceBool1 = true;
				}
				for (auto& j : m_vectorOfVertexPtr) {
					if ((processedVertex) == j->m_vertexIDpair.first) {
						serviceInt1 = j->m_vertexIDpair.second + 1;
						break;
					}
				}
				if ((std::get<0>(topologyMarks[serviceInt1 - 1]) == true) && (std::get<2>(topologyMarks[(*hj)->m_vertexIDpair.second]) > 0)) {

					if (serviceBool1 == true) {
						if ((std::get<1>(topologyMarks[serviceInt1 - 1])) > (std::get<2>(topologyMarks[serviceInt1 - 1]))) {
							std::get<2>(topologyMarks[serviceInt1 - 1]) = std::get<1>(topologyMarks[serviceInt1 - 1]);
						}
					}
					serviceBool1 = false;
					if (std::get<2>(topologyMarks[serviceInt1 - 1]) <= 0) {

						std::get<2>(topologyMarks[serviceInt1 - 1]) = std::get<1>(topologyMarks[serviceInt1 - 1]);
						for (auto& j : m_vectorOfVertexPtr) {
							if (processedVertex == j->m_vertexIDpair.first) {
								routeVertexIDs.push_back(j->m_vertexIDpair);
								break;
							}
						}

						hj = m_vectorOfVertexPtr.begin() + (serviceInt1 - 1);
						serviceInt1 = std::get<2>(topologyMarks[serviceInt1 - 1]) - 1;
						testV = (*hj)->getAdjacentEdges();
						processedVertex = testV[serviceInt1].second;

						hj = m_vectorOfVertexPtr.begin() + (zIter);


					}
					else {
						for (auto& j : m_vectorOfVertexPtr) {
							if (processedVertex == j->m_vertexIDpair.first) {
								routeVertexIDs.push_back(j->m_vertexIDpair);
								break;
							}
						}
						for (auto& j : m_vectorOfVertexPtr) {
							if ((processedVertex) == j->m_vertexIDpair.first) {
								serviceInt1 = j->m_vertexIDpair.second + 1;
								break;
							}
						}
						hj = m_vectorOfVertexPtr.begin() + (serviceInt1 - 1);
						serviceInt1 = std::get<2>(topologyMarks[serviceInt1 - 1]) - 1;
						testV = (*hj)->getAdjacentEdges();
						processedVertex = testV[serviceInt1].second;
						hj = m_vectorOfVertexPtr.begin() + (zIter);

					}
				}
			}
		}
		zIter++;
		hj++;
	}
}


void graph::destructSectionInGraph() {
	//********************************************************************
	//This method removes all pointers to vehicle objects in links of this traffic graph. 
	//This method is used for safe termination of the program and ensures that no pointers are left behind that point to nothing.
	//********************************************************************
	m_vectorOfRoutesPtr.clear();
	for (auto& i : m_vectorOfEdgesPtr) {
		i->sectionDestruct();
	}
}

void graph::deletePoolAllocator() {
	m_poolAllocator.~PoolAllocator();
}