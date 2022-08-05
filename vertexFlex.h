#pragma once
#include "PrecompiledHeadersEdges.h"

class transmissionTable {
public:
	
	int param1 = 0;
	std::queue<vehicle*> param2;
	transmissionTable::transmissionTable()noexcept {
		
	}
	transmissionTable::transmissionTable(const transmissionTable& other)noexcept {
		param1 = other.param1;
		param2 = other.param2;
	}
	transmissionTable::transmissionTable(const transmissionTable&& other)noexcept {
		param1 = other.param1;
		param2 = other.param2;
	}
	transmissionTable& operator=(transmissionTable& other)noexcept {
		if (&other == this) {
			return *this;
		}
		param1 = other.param1;
		param2 = other.param2;
		return *this;
	}
	transmissionTable& operator=(transmissionTable&& other)noexcept {
		if (&other == this) {
			return *this;
		}
		param1 = other.param1;
		param2 = other.param2;
		return *this;
	}
	transmissionTable::~transmissionTable() noexcept;
	
	vehicle*  getPTR();
};
class vertexFlex :public vertex {
private:
	size_t a = 0;
	bool serviceBool = false;
public:
	size_t m_printShape = 11;
	std::vector<transmissionTable> m_vectorOfTransmissionTable;
	explicit vertexFlex::vertexFlex()noexcept;
	explicit vertexFlex::vertexFlex(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd)noexcept;
	explicit vertexFlex::vertexFlex(const int& xCoordinate, const int& yCoordinate, const std::pair<int, int>& numberOfLanes)noexcept;
	vertexFlex::vertexFlex(const vertexFlex& other) noexcept {
		a = other.a;
		m_vectorOfTransmissionTable = other.m_vectorOfTransmissionTable;
	}
	vertexFlex::vertexFlex(const vertexFlex&& other)noexcept {
		a = other.a;
		m_vectorOfTransmissionTable = other.m_vectorOfTransmissionTable;
	}
	vertexFlex& operator=(const vertexFlex& other) noexcept {
		if (&other == this) {
			return *this;
		}
		a = other.a;
		m_vectorOfTransmissionTable = other.m_vectorOfTransmissionTable;
		return *this;
	}
	vertexFlex& operator=(const vertexFlex&& other)noexcept {
		if (&other == this) {
			return *this;
		}
		a = other.a;
		m_vectorOfTransmissionTable = other.m_vectorOfTransmissionTable;
		return *this;
	}
	~vertexFlex() noexcept;

	vehicle* getVehiclePtrOutOfVertex(const int& endVertexNumber, const int& param) override;
	void setTransmissionTable(int param)override;
	void vehiclePTRmanipulationInV(vehicle* vehiclePTR) override;
	int checkIfVehicleIsInV(vehicle* vehiclePTR)override;
	void deleteVehicleInV(vehicle* vehiclePTR) override;
	size_t sizeOfTransmissiontable() override;
	std::vector<std::pair<int, int>> getAdjacentEdges();
	size_t sizeOfSingleTransmissiontable(int iter) override;
	void setPrintShape(size_t param) override;
	size_t getPrintShape() override;
	float getVertexDelay(const int& destinationVertex) override;
};
