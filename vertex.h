#pragma once
#include "PrecompiledHeadersEdges.h"
#include "vehicle.h"
#include "PoolAllocator.h"


enum shapeOfVertex { transision = 0, begin = 1, end = 2, oneByone = 11, oneBytwo = 12, twoByone = 21, twoBytwo = 22, undefindShape = 99, unused = 100 };
class vertex {
private:
	

	

protected:



public:
	bbe::PoolAllocator<vehicle>* m_VPAptr = nullptr; //Pointer auf den Poolallocator
	int m_vertexID = 0;
	std::pair<int, int> m_vertexIDpair;
	
	int m_XcoordinateVertex = 0;
	int m_YcoordinateVertex = 0;	
	std::pair<int, int> m_numberOfLanes;
	int m_numberOfLanesVertical = 0;
	int m_numberOfLanesHorizontal = 0;
	unsigned int m_shapeOfThatVertex = unused;
	
	explicit vertex::vertex() {

	}
	explicit vertex::vertex(const int& xCoordinate, const int& yCoordinate, const std::pair<int, int>& numberOfLanes)
		: m_XcoordinateVertex(xCoordinate), m_YcoordinateVertex(yCoordinate), m_numberOfLanes(numberOfLanes)
	{
		
		
		m_numberOfLanesVertical = m_numberOfLanes.first;
		m_numberOfLanesHorizontal = m_numberOfLanes.second;
		m_numberOfLanes.first = 0;
		m_numberOfLanes.second = 0;
		if ((m_numberOfLanesVertical == 1) && (m_numberOfLanesHorizontal == 1)) {
			m_shapeOfThatVertex = oneByone;
		}
		else if ((m_numberOfLanesVertical == 1) && (m_numberOfLanesHorizontal == 2)) {
			m_shapeOfThatVertex = oneBytwo;
		}
		else if ((m_numberOfLanesVertical == 2) && (m_numberOfLanesHorizontal == 1)) {
			m_shapeOfThatVertex = twoByone;
		}
		else if ((m_numberOfLanesVertical == 2) && (m_numberOfLanesHorizontal == 2)) {
			m_shapeOfThatVertex = twoBytwo;
		}
		else {
			m_shapeOfThatVertex = undefindShape;
		}

		

	}
	explicit vertex::vertex(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd, const int& numberOfLane)
		:m_XcoordinateVertex(xCoordinate), m_YcoordinateVertex(yCoordinate), m_shapeOfThatVertex(BeginnOrEnd), m_numberOfLanesVertical(numberOfLane)
	{
		
		m_numberOfLanesHorizontal = m_numberOfLanesVertical;
		m_numberOfLanes.first = 0;
		m_numberOfLanes.second = 0;
		
	}
	explicit vertex::vertex(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd)
		:m_XcoordinateVertex(xCoordinate), m_YcoordinateVertex(yCoordinate), m_shapeOfThatVertex(BeginnOrEnd)
	{
		

	}
	vertex::~vertex() {
		
	}
	vertex::vertex( vertex& other) {
		m_vertexID = other.m_vertexID;
		m_vertexIDpair = other.m_vertexIDpair;
		m_XcoordinateVertex = other.m_XcoordinateVertex;
		m_YcoordinateVertex = other.m_YcoordinateVertex;
		m_numberOfLanes = other.m_numberOfLanes;
		m_numberOfLanesVertical = other.m_numberOfLanesVertical;
		m_numberOfLanesHorizontal = other.m_numberOfLanesHorizontal;
		m_shapeOfThatVertex = other.m_shapeOfThatVertex;

		
	}
	vertex::vertex(vertex&& other) = default;
	vertex& operator=( vertex& other)  {
		if (&other == this) {
			return *this;
		}
		else {
			m_vertexID = other.m_vertexID;
			m_vertexIDpair = other.m_vertexIDpair;
			m_XcoordinateVertex = other.m_XcoordinateVertex;
			m_YcoordinateVertex = other.m_YcoordinateVertex;
			m_numberOfLanes = other.m_numberOfLanes;
			m_numberOfLanesVertical = other.m_numberOfLanesVertical;
			m_numberOfLanesHorizontal = other.m_numberOfLanesHorizontal;
			m_shapeOfThatVertex = other.m_shapeOfThatVertex;
			return *this;
		}
	}
	vertex& operator=(vertex&& other) = default;

	void vertex::setPoolAllocatorPtr(bbe::PoolAllocator<vehicle>& poolAllocatorRef) {
		m_VPAptr = &poolAllocatorRef;
	}

	void vertex::changeVertexPurpose() {
		m_shapeOfThatVertex = 0;
	}
	void vertex::numberingOfVertexes(const int& number) {
		m_vertexID = number;
	}
	virtual vehicle* getVehiclePtrOutOfVertex(const int& endVertexNumber, const int& param) = 0;
	virtual void setTransmissionTable(int a) = 0;
	virtual void vehiclePTRmanipulationInV(vehicle* vehiclePTR) = 0;
	virtual int getNumberOfVehicleInV() = 0;
	//virtual int getNumberOfVehicleInTMT() = 0;
	virtual int checkIfVehicleIsInV(vehicle* vehiclePTR) = 0;
	virtual void deleteVehicleInV(vehicle* vehiclePTR) = 0;
	virtual size_t sizeOfTransmissiontable() = 0;
	//virtual std::pair<int,int> sizeOfTT() = 0;
	virtual std::vector<std::pair<int, int>> getAdjacentEdges() = 0;

};

