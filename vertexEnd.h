#pragma once

class vertexEnd :public vertex {
private:
public:
	explicit vertexEnd(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd)noexcept;
	vertexEnd::vertexEnd(const vertexEnd& other)noexcept = default;
	vertexEnd::vertexEnd( vertexEnd&& other)noexcept = default;
	vertexEnd& operator=(const vertexEnd& other)noexcept {
		return *this;		
	}
	vertexEnd& operator=(const vertexEnd&& other)noexcept {
		return *this;
	}
	~vertexEnd() noexcept;

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
