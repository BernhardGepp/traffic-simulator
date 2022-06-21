#pragma once
#include "PrecompiledHeadersEdges.h"
#include "PoolAllocator.h"
#include "vehicle.h"
#include "vertex.h"
#include "edge.h"
#include "route.h" 

class graph {
private:
public:
	bbe::PoolAllocator<vehicle> m_poolAllocator;
	std::set<int>m_setOfVertexes;
	std::vector<std::shared_ptr<vertex>> m_vectorOfVertexPtr;
	std::vector<std::shared_ptr<edge>> m_vectorOfEdgesPtr;
	std::vector<std::unique_ptr<route>>m_vectorOfRoutesPtr;
	callBackLinks* m_CBLptr = nullptr;
	graph::graph() = default;
	explicit graph(const std::set<int>& setOfVertexes,std::vector<std::shared_ptr<vertex>>& vectorOfVertex,
		std::vector<std::shared_ptr<edge>>& vectorOfEdges, callBackLinks* CBLptr);
	
	graph::graph(const graph& other)  {
		
		m_setOfVertexes=std::move(other.m_setOfVertexes);
		m_vectorOfVertexPtr.reserve(other.m_vectorOfEdgesPtr.size());
		for (auto& i : other.m_vectorOfVertexPtr){
			m_vectorOfVertexPtr.emplace_back(std::move(i));
		}
		m_vectorOfEdgesPtr.reserve(other.m_vectorOfEdgesPtr.size());
		for (auto& i : other.m_vectorOfEdgesPtr){
			m_vectorOfEdgesPtr.emplace_back(std::move(i));
		}
	}
	graph::graph(const graph&& other) = delete;
	graph& operator=(const graph& other) = delete;
	graph& operator=(const graph&& other) = delete;
	~graph() noexcept;

	void simulation(const int&); 
	void deletePoolAllocator();
	void clean();
	bool isInsideRouteVertexIDs(const std::vector<std::pair<int, int>>& , const int&);
	bool recheckroute(const std::vector<int>& );
	void calculationOfRouteIndex();
	void generationOfRoutesNeu();
	void printLanesAndVehiclesOfAllEdges();
	void showVertex();
	void destructSectionInGraph();
	
};
