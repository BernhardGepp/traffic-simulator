#pragma once
#include "graph.h"

class graphTrafficGenerationOnAllRoutes : public graph {
private:
public:
	explicit graphTrafficGenerationOnAllRoutes(const std::set<int>& setOfVertexes,
		std::vector<std::shared_ptr<vertex>>& vectorOfVertex,
		std::vector<std::shared_ptr<edge>>& vectorOfEdges);

	~graphTrafficGenerationOnAllRoutes()noexcept;

	void calculationOfRouteIndex() override;
};