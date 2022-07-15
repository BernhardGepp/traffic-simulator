#include "PrecompiledHeadersEdges.h"
#include "graphTrafficGenerationOnAllRoutes.h"


//Constructor and destructor of the class:
graphTrafficGenerationOnAllRoutes::graphTrafficGenerationOnAllRoutes(const std::set<int>& setOfVertexes, std::vector<std::shared_ptr<vertex>>& vectorOfVertex,
	std::vector<std::shared_ptr<edge>>& vectorOfEdges, callBackLinks* CBLptr) : graph(setOfVertexes, vectorOfVertex, vectorOfEdges, CBLptr) {}

graphTrafficGenerationOnAllRoutes::~graphTrafficGenerationOnAllRoutes() {}

void graphTrafficGenerationOnAllRoutes::calculationOfRouteIndex() {
	int serviceInt = 0;
	for (std::vector<std::unique_ptr<route>>::reverse_iterator i = m_vectorOfRoutesPtr.rbegin(); i != m_vectorOfRoutesPtr.rend(); ++i) {
		(*i)->routeimpactIndexCalculation();
	}

	for (auto& i : m_vectorOfEdgesPtr) {
		i->m_routeTable_IDrValueIDvertex.clear();

		serviceInt = 0;
		for (auto& ii : m_vectorOfRoutesPtr) {
			if ((i->m_startVertex == ii->m_vertexOfRouteID[0]) && (i->m_endVertex == ii->m_vertexOfRouteID[1])) {
				std::pair<int, float> p = std::make_pair(serviceInt, ii->m_currentTravelTime);
				std::pair<std::pair<int, float>, std::vector<int>> p1 = std::make_pair(p, ii->m_vertexOfRouteID);
				i->m_routeTable_IDrValueIDvertex.push_back(p1);
			}
			serviceInt++;
		}
	}
}