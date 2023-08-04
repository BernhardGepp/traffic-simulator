#pragma once
#include "PrecompiledHeadersEdges.h"
#include "graph.h"

class graphTrafficGenerationOnFastRoutes : public graph {
private:
public:
	explicit graphTrafficGenerationOnFastRoutes(const std::set<int>& setOfVertexes,
		std::vector<std::shared_ptr<vertex>>& vectorOfVertex,
		std::vector<std::shared_ptr<edge>>& vectorOfEdges);

	~graphTrafficGenerationOnFastRoutes()noexcept;

	void calculationOfRouteIndex() override;
};