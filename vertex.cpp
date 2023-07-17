#include "PrecompiledHeadersEdges.h"
#include "vertex.h"
/*#include "vertexEnd.h"
#include "vertexFlex.h"
#include "vertexStart.h"

std::unique_ptr <vertex> createVertex::create(const int& xvalue, const int& yvalue, const int& shapeOfThatVertex) {
	switch (shapeOfThatVertex) {
	case 1:
		return std::make_unique<vertexStart>(xvalue, yvalue, shapeOfThatVertex);
		break;
	case 2:
		return std::make_unique<vertexEnd>(xvalue, yvalue, shapeOfThatVertex);
		break;
	case 11:
		return std::make_unique<vertexFlex>(xvalue, yvalue, shapeOfThatVertex);
		break;
	default:
		return 0;
	}
}*/

//Constructor and destructor of the class:
vertex::vertex(const int& xCoordinate, const int& yCoordinate, const std::pair<int, int>& numberOfLanes)noexcept
		: m_XcoordinateVertex(xCoordinate), m_YcoordinateVertex(yCoordinate), m_numberOfLanes(numberOfLanes) {}
	
vertex::vertex(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd, const int& numberOfLane)noexcept
	:m_XcoordinateVertex(xCoordinate), m_YcoordinateVertex(yCoordinate), m_shapeOfThatVertex(BeginnOrEnd), m_numberOfLanesVertical(numberOfLane) {
	m_numberOfLanesHorizontal = m_numberOfLanesVertical;
	m_numberOfLanes.first = 0;
	m_numberOfLanes.second = 0;
}

vertex::vertex(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd)noexcept
	:m_XcoordinateVertex(xCoordinate), m_YcoordinateVertex(yCoordinate), m_shapeOfThatVertex(BeginnOrEnd){}

vertex::~vertex() noexcept {}

//********************************************************************
//Methods of the class:

void vertex::setPoolAllocatorPtr(bbe::PoolAllocator<vehicle>& poolAllocatorRef) {
	m_VPAptr = &poolAllocatorRef;
}

void vertex::changeVertexPurpose() {
	m_shapeOfThatVertex = 0;
}

void vertex::numberingOfVertexes(const int& number) {
	m_vertexID = number;
}