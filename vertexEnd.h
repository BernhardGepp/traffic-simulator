#pragma once
#include "PrecompiledHeadersEdges.h"
#include "vertex.h"
#include "vehicle.h"

class vertexEnd :public vertex {
private:
public:
	explicit vertexEnd::vertexEnd(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd) : vertex(xCoordinate, yCoordinate, BeginnOrEnd) {

	}
	vertexEnd::vertexEnd(const vertexEnd& other) = default;
	vertexEnd::vertexEnd( vertexEnd&& other) = default;
	vertexEnd& operator=(const vertexEnd& other) {
		return *this;		
	}
	vertexEnd& operator=(const vertexEnd&& other) {
		return *this;
	}
	vertexEnd::~vertexEnd() noexcept {}

	vehicle* getVehiclePtrOutOfVertex(const int& endVertexNumber, const int& param) override {
		return nullptr;
	}
	void setTransmissionTable(int param)override {

	}
	void vehiclePTRmanipulationInV(vehicle* vehiclePTR) override {
		m_numberOfVehicle++;

		vehiclePTR->m_inRange = false;
		vehiclePTR->m_lane = 0;
		vehiclePTR->m_moblieORStationary = true;
		vehiclePTR->m_position = 0;
		vehiclePTR->m_pref_speed = 0;
		vehiclePTR->m_riseOrDecline = true;
		vehiclePTR->m_routeID = 0;
		vehiclePTR->m_routeVertexID_vehicle.clear();
		vehiclePTR->serviceBool = false;
		vehiclePTR->processedByIteration = false;
		if (m_VPAptr != nullptr) {
			m_VPAptr->deallocate(vehiclePTR);
		}
	}
	int checkIfVehicleIsInV(vehicle* vehiclePTR)override {
		return 0;
	}
	void deleteVehicleInV(vehicle* vehiclePTR) override {

	}
	size_t sizeOfTransmissiontable() override {
		return 0;
	}
	virtual std::vector<std::pair<int, int>> getAdjacentEdges()override {
		std::vector<std::pair<int, int>> returnValue;
		returnValue.clear();
		
		return returnValue;
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
