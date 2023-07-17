#pragma once
#include "PrecompiledHeadersEdges.h"


class createVertex {
	public:
		std::unique_ptr<vertex> createdVertex;
		std::unique_ptr <vertex>&& create(const int& xvalue, const int& yvalue, const int& shapeOfThatVertex);
};