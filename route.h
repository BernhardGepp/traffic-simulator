#pragma once
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
	float m_initalTravelTime = 0.0f;
	
	explicit route(std::vector<int> vertexOfRouteID, std::vector<std::shared_ptr<edge>>edgesOfRoute, int index);
	//route::route(const route& other) = delete;
	route::route(const route&& other) = delete;
	//route& operator=(const route&& other) = delete;
	route& operator=(const route& other) = delete;
	~route() noexcept;

	bool checkIfSectionWasIncluded(const int& firstVertexID, const int& startV, const int& endV);
	void routeimpactIndexCalculation();
	std::vector<int> vectorOfRouteID();
};

