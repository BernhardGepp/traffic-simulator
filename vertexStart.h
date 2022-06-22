#pragma once
//#include "vertex.h"
#include "PrecompiledHeadersEdges.h"
#include "vehicle.h"
class vertexStart :public vertex {
private:
	std::vector<int> m_transmissionTableInt;
public:
	explicit vertexStart::vertexStart(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd) : vertex(xCoordinate, yCoordinate, BeginnOrEnd) {

	}
	explicit vertexStart::vertexStart(const vertexStart& other) {
		m_transmissionTableInt = other.m_transmissionTableInt;
	}
	explicit vertexStart::vertexStart(const vertexStart&& other) {
		m_transmissionTableInt = other.m_transmissionTableInt;
	}
	vertexStart& operator=(const vertexStart& other) {
		if (&other == this) {
			return *this;
		}
		m_transmissionTableInt = other.m_transmissionTableInt;
		return *this;
	}
	vertexStart& operator=(const vertexStart&& other) {
		if (&other == this) {
			return *this;
		}
		m_transmissionTableInt = other.m_transmissionTableInt;
		return *this;
	}
	vertexStart::~vertexStart() noexcept {

	}
	vehicle* getVehiclePtrOutOfVertex(const int& endVertexNumber, const int& param) override {
		return m_VPAptr->allocate(1, param);
	}
	void setTransmissionTable(int param)override {
		m_transmissionTableInt.push_back(param);
	}
	void vehiclePTRmanipulationInV(vehicle* vehiclePTR) override {

	}
	int checkIfVehicleIsInV(vehicle* vehiclePTR)override {
		return 0;
	}
	void deleteVehicleInV(vehicle* vehiclePTR) override {

	}
	size_t sizeOfTransmissiontable() override {
		return m_transmissionTableInt.size();
	}
	virtual std::vector<std::pair<int, int>> getAdjacentEdges()override {
		std::vector<std::pair<int, int>> param1;
		param1.clear();
		if (!m_transmissionTableInt.empty()) {
			for (auto &i : m_transmissionTableInt) {
				param1.push_back(std::make_pair(m_vertexID, i));
			}
		}
		return param1;
	}
	size_t sizeOfSingleTransmissiontable(int iter) override {

		return 0;
	}
	void setPrintShape(size_t param) override {
		
	}
	size_t getPrintShape() override {
		return 0;
	}
};