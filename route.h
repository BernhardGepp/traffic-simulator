#pragma once
#include "PrecompiledHeadersEdges.h"
#include "vertex.h"
#include "edge.h"
class route {
private:
public:
	
	std::vector<int> m_vertexOfRouteID;
	std::vector<int>::iterator iterator;
	std::vector<std::shared_ptr<edge>>m_edgesOfRoute;
	int routeID = 0;
	int m_routeLength = 0;
	int m_index = 0;
	float m_impactIndexRoute = 0.0f;
	float m_maxDensity = 0.0f;
	float m_currentTravelTime = 0.0f;
	
	explicit route::route(std::vector<int> vertexOfRouteID, std::vector<std::shared_ptr<edge>>edgesOfRoute,int index) :m_vertexOfRouteID(vertexOfRouteID), m_edgesOfRoute(edgesOfRoute),m_index(index) {
		
	}
	route::route(const route& other) = delete;
	route::route(const route&& other) = delete;
	route& operator=(const route&& other) = delete;
	route& operator=(const route& other) = delete;
	route::~route() noexcept{	}

	bool checkIfSectionWasIncluded(const int& firstVertexID,const int& startV, const int& endV) {
		bool returnbool=false;
		if (firstVertexID == m_vertexOfRouteID[0]) {
			
			for (size_t i = 1; i < m_vertexOfRouteID.size();i++) {
				if ((startV == m_vertexOfRouteID[i-1]) && (endV == m_vertexOfRouteID[i])) {
					returnbool= true;
				}
			}
		}		
		return returnbool;
	}

	void route::routeimpactIndexCalculation() {
		if (m_routeLength == 0) {
			m_impactIndexRoute = 0.0f;
			//****
			m_maxDensity = 0.0f;
			m_routeLength = 0;
			m_currentTravelTime = 0.0f;
			//****
			for (auto &i : m_edgesOfRoute) {
				m_impactIndexRoute = i->m_weight + m_impactIndexRoute;
				//****
				m_routeLength = m_routeLength + i->m_length;
				m_currentTravelTime = m_currentTravelTime + i->m_averageTravelTime;
				if (i->m_density > m_maxDensity) {
					m_maxDensity = i->m_density;
				}
				//****
			}
		}
	}

	void route::routeTrafficCharacteristics() {
		
	}

	std::vector<int> vectorOfRouteID() {
		return m_vertexOfRouteID;
	}
};

