#pragma once
#include "PrecompiledHeadersEdges.h"


class createVertex {
	public:
		int counter=1 ;
		std::shared_ptr<vertex> createdVertex;
		std::shared_ptr <vertex> create(const int& xvalue, const int& yvalue, const int& shapeOfThatVertex);
};