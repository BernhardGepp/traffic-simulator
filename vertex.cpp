#include "PrecompiledHeadersEdges.h"
#include "vertex.h"

//Constructor and destructor of the class:
vertex::vertex(const int& xCoordinate, const int& yCoordinate, const std::pair<int, int>& numberOfLanes)
		: m_XcoordinateVertex(xCoordinate), m_YcoordinateVertex(yCoordinate), m_numberOfLanes(numberOfLanes){}
	
vertex::vertex(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd, const int& numberOfLane)
	:m_XcoordinateVertex(xCoordinate), m_YcoordinateVertex(yCoordinate), m_shapeOfThatVertex(BeginnOrEnd), m_numberOfLanesVertical(numberOfLane){
	m_numberOfLanesHorizontal = m_numberOfLanesVertical;
	m_numberOfLanes.first = 0;
	m_numberOfLanes.second = 0;
}

vertex::vertex(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd)
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