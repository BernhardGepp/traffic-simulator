#pragma once

class vertexStart :public vertex {
private:
	std::vector<int> m_transmissionTableInt;
public:
	explicit vertexStart(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd)noexcept;
	explicit vertexStart::vertexStart(const vertexStart& other)noexcept {
		m_transmissionTableInt = other.m_transmissionTableInt;
	}
	explicit vertexStart::vertexStart(const vertexStart&& other) noexcept {
		m_transmissionTableInt = other.m_transmissionTableInt;
	}
	vertexStart& operator=(const vertexStart& other)noexcept {
		if (&other == this) {
			return *this;
		}
		m_transmissionTableInt = other.m_transmissionTableInt;
		return *this;
	}
	vertexStart& operator=(const vertexStart&& other)noexcept {
		if (&other == this) {
			return *this;
		}
		m_transmissionTableInt = other.m_transmissionTableInt;
		return *this;
	}
	~vertexStart();

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