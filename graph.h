#pragma once
#include "route.h" 

class graph {
private:
public:
	bbe::PoolAllocator<vehicle> m_poolAllocator;
	std::vector<std::shared_ptr<vertex>> m_vectorOfVertexPtr;
	std::vector<std::shared_ptr<edge>> m_vectorOfEdgesPtr;
	std::vector<std::unique_ptr<route>>m_vectorOfRoutesPtr;
	explicit graph(const std::set<int>& setOfVertexes,std::vector<std::shared_ptr<vertex>>& vectorOfVertex,
		std::vector<std::shared_ptr<edge>>& vectorOfEdges);
	
	graph::graph(const graph& other);
	graph::graph(const graph&& other) = delete;
	graph& operator=(const graph& other) = delete;
	graph& operator=(const graph&& other) = delete;
	~graph() noexcept;

	void simulation(const int&); 
	void deletePoolAllocator();
	void clean();
	bool isInsideRouteVertexIDs(const std::vector<std::pair<int, int>>& , const int&);
	bool recheckroute(const std::vector<int>& );
	virtual void calculationOfRouteIndex()=0;
	void generationOfRoutesNeu();
	void destructSectionInGraph();
};
