#pragma once
#include "PrecompiledHeadersEdges.h"

class vertexEnd :public vertex {
private:
public:
	explicit vertexEnd(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd);
	vertexEnd::vertexEnd(const vertexEnd& other) = default;
	vertexEnd::vertexEnd( vertexEnd&& other) = default;
	vertexEnd& operator=(const vertexEnd& other) {
		return *this;		
	}
	vertexEnd& operator=(const vertexEnd&& other) {
		return *this;
	}
	~vertexEnd() noexcept;

	vehicle* getVehiclePtrOutOfVertex(const int& endVertexNumber, const int& param) override;
	void setTransmissionTable(int param)override;
	void vehiclePTRmanipulationInV(vehicle* vehiclePTR) override;
	int checkIfVehicleIsInV(vehicle* vehiclePTR)override;
	void deleteVehicleInV(vehicle* vehiclePTR) override;
	size_t sizeOfTransmissiontable() override;
	//virtual std::vector<std::pair<int, int>> getAdjacentEdges()override;
	virtual std::vector<std::pair<int, int>> getAdjacentEdges()override {
		std::vector<std::pair<int, int>> returnValue;
		returnValue.clear();
		
		return returnValue;
	}
	size_t sizeOfSingleTransmissiontable(int iter) override;
	void setPrintShape(size_t param) override;
	size_t getPrintShape() override;
};
