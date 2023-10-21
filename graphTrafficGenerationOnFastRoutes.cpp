#include "PrecompiledHeadersEdges.h"
#include "graphTrafficGenerationOnFastRoutes.h"

//Constructor and destructor of the class:
graphTrafficGenerationOnFastRoutes::graphTrafficGenerationOnFastRoutes(const std::set<int>& setOfVertexes, std::vector<std::shared_ptr<vertex>>& vectorOfVertex,
	std::vector<std::shared_ptr<edge>>& vectorOfEdges) : graph(setOfVertexes, vectorOfVertex, vectorOfEdges) {
}

graphTrafficGenerationOnFastRoutes::~graphTrafficGenerationOnFastRoutes() {}

void graphTrafficGenerationOnFastRoutes::calculationOfRouteIndex() {
	int serviceInt = 0;
	std::vector<std::tuple<int, int, float>>vectorOfMultibleRoute;
	bool serviceBool1 = false;
	bool serviceBool2 = false;
	
	for (auto& i : m_vectorOfEdgesPtr) {
		i->computeWeightOfEdge();
		i->computeEdgesCharactaristics();
	}
	serviceInt = 0;
	for (std::vector<std::unique_ptr<route>>::reverse_iterator i = m_vectorOfRoutesPtr.rbegin(); i != m_vectorOfRoutesPtr.rend(); ++i) {
		(*i)->m_currentTravelTime = 0.0f;
		(*i)->routeimpactIndexCalculation();
		if ((*i)->m_index > 0 ) {
			serviceBool1 = false;
			if (!vectorOfMultibleRoute.empty()) {
				for (auto& ii : vectorOfMultibleRoute) {
					if ((std::get<0>(ii) == (*i)->m_vertexOfRouteID[0]) && (std::get<1>(ii) == (*i)->m_vertexOfRouteID.back())) {
						serviceBool1 = true;
						if (std::get<2>(ii) > (*i)->m_currentTravelTime)
							std::get<2>(ii) = (*i)->m_currentTravelTime;
					}
				}
			}
			if (!serviceBool1) {
				vectorOfMultibleRoute.push_back(std::make_tuple((*i)->m_vertexOfRouteID[0], (*i)->m_vertexOfRouteID.back(), (*i)->m_currentTravelTime));
			}
		}
		serviceInt++;
	}
	serviceInt = 0;
	for (std::vector<std::unique_ptr<route>>::reverse_iterator i = m_vectorOfRoutesPtr.rbegin(); i != m_vectorOfRoutesPtr.rend(); ++i) {
		serviceInt = serviceInt + 10;
		for (auto& ii : vectorOfMultibleRoute) {
			serviceInt++;
			if ((std::get<0>(ii) == (*i)->m_vertexOfRouteID[0]) && (std::get<1>(ii) == (*i)->m_vertexOfRouteID.back())) {
				
				if (std::get<2>(ii) > (*i)->m_currentTravelTime) {
					std::get<2>(ii) = (*i)->m_currentTravelTime;
				}
			}

		}
	}
	serviceInt = 0;
	for (auto& i : m_vectorOfEdgesPtr) {
		i->sFs.vehicleSetPtr->m_routeTable_IDrValueIDvertex.clear();
		serviceInt = 0;
		for (auto& ii : m_vectorOfRoutesPtr) {
			serviceBool1 = false;
			serviceBool2 = false;
			for (auto& iii : vectorOfMultibleRoute) {
				if ((std::get<0>(iii) == ii->m_vertexOfRouteID[0]) && (std::get<1>(iii) == ii->m_vertexOfRouteID.back())) {
					serviceBool1 = true;
				}
				if ((std::get<0>(iii) == ii->m_vertexOfRouteID[0]) && (std::get<1>(iii) == ii->m_vertexOfRouteID.back()) && (std::get<2>(iii) == ii->m_currentTravelTime)) {
					serviceBool2 = true;
				}
			}
			if ((i->m_startVertex == ii->m_vertexOfRouteID[0]) && (i->m_endVertex == ii->m_vertexOfRouteID[1])&&
				(((serviceBool1==false)&&(serviceBool2==false))||
				((serviceBool1 == true) && (serviceBool2 == true)))
				) {
				
				if (ii->m_currentTravelTime < (ii->m_initalTravelTime * 5.0f)) {
					std::pair<int, float> p = std::make_pair(serviceInt, ii->m_currentTravelTime);
					std::pair<std::pair<int, float>, std::vector<int>> p1 = std::make_pair(p, ii->m_vertexOfRouteID);
					i->sFs.vehicleSetPtr->m_routeTable_IDrValueIDvertex.push_back(p1);
				}
			}
			serviceInt++;
		}
	}
}