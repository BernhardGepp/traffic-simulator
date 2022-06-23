#pragma once
#include "PrecompiledHeadersEdges.h"

class vertexStart :public vertex {
private:
	std::vector<int> m_transmissionTableInt;
public:
	explicit vertexStart(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd);
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
	~vertexStart() noexcept;

	vehicle* getVehiclePtrOutOfVertex(const int& endVertexNumber, const int& param) override;
	void setTransmissionTable(int param)override;
	void vehiclePTRmanipulationInV(vehicle* vehiclePTR) override;
	int checkIfVehicleIsInV(vehicle* vehiclePTR)override;
	void deleteVehicleInV(vehicle* vehiclePTR) override;
	size_t sizeOfTransmissiontable() override;
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
	size_t sizeOfSingleTransmissiontable(int iter) override;
	void setPrintShape(size_t param) override;
	size_t getPrintShape() override;
};