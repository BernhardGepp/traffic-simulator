#pragma once
#include "PrecompiledHeadersEdges.h"
#include "vehicle.h"
#include "PoolAllocator.h"


enum shapeOfVertex { transision = 0, begin = 1, end = 2, oneByone = 11, oneBytwo = 12, twoByone = 21, twoBytwo = 22, undefindShape = 99, unused = 100 };
class vertex {
private:
protected:
public:
	bbe::PoolAllocator<vehicle>* m_VPAptr = nullptr; //Pointer to the pool allocator
	int m_vertexID = 0;
	std::pair<int, int> m_vertexIDpair;
	int m_XcoordinateVertex = 0;
	int m_YcoordinateVertex = 0;	
	std::pair<int, int> m_numberOfLanes;
	int m_numberOfLanesVertical = 0;
	int m_numberOfLanesHorizontal = 0;
	unsigned int m_shapeOfThatVertex = unused;
	int m_numberOfVehicle = 0;

	explicit vertex::vertex() = default;
	explicit vertex::vertex(const int& xCoordinate, const int& yCoordinate, const std::pair<int, int>& numberOfLanes);
	explicit vertex::vertex(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd, const int& numberOfLane);
	explicit vertex::vertex(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd);

	vertex::vertex(const vertex& other) {
		m_vertexID = other.m_vertexID;
		m_vertexIDpair = other.m_vertexIDpair;
		m_XcoordinateVertex = other.m_XcoordinateVertex;
		m_YcoordinateVertex = other.m_YcoordinateVertex;
		m_numberOfLanes = other.m_numberOfLanes;
		m_numberOfLanesVertical = other.m_numberOfLanesVertical;
		m_numberOfLanesHorizontal = other.m_numberOfLanesHorizontal;
		m_shapeOfThatVertex = other.m_shapeOfThatVertex;
	}
	vertex::vertex(const vertex&& other) {
		m_vertexID = other.m_vertexID;
		m_vertexIDpair = other.m_vertexIDpair;
		m_XcoordinateVertex = other.m_XcoordinateVertex;
		m_YcoordinateVertex = other.m_YcoordinateVertex;
		m_numberOfLanes = other.m_numberOfLanes;
		m_numberOfLanesVertical = other.m_numberOfLanesVertical;
		m_numberOfLanesHorizontal = other.m_numberOfLanesHorizontal;
		m_shapeOfThatVertex = other.m_shapeOfThatVertex;
	}
	vertex& operator=(vertex& other) {
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
	vertex& operator=(const vertex&& other) {
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
	~vertex() noexcept;
	void setPoolAllocatorPtr(bbe::PoolAllocator<vehicle>& poolAllocatorRef);

	void changeVertexPurpose();
	void numberingOfVertexes(const int& number);
	
	virtual vehicle* getVehiclePtrOutOfVertex(const int& endVertexNumber, const int& param) = 0;
	virtual void setTransmissionTable(int a) = 0;
	virtual void vehiclePTRmanipulationInV(vehicle* vehiclePTR) = 0;
	virtual int checkIfVehicleIsInV(vehicle* vehiclePTR) = 0;
	virtual void deleteVehicleInV(vehicle* vehiclePTR) = 0;
	virtual size_t sizeOfTransmissiontable() = 0;
	virtual std::vector<std::pair<int, int>> getAdjacentEdges() = 0;
	virtual size_t sizeOfSingleTransmissiontable(int iter) = 0;
	virtual void setPrintShape(size_t param) = 0;
	virtual size_t getPrintShape() = 0;
	virtual float getVertexDelay(const int& destinationVertex) = 0;
};

