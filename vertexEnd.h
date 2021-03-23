#pragma once
#include "PrecompiledHeadersEdges.h"
#include "vertex.h"
#include "vehicle.h"

class vertexEnd :public vertex {
private:
public:
	explicit vertexEnd::vertexEnd(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd, const int& numberOfLane) :vertex(xCoordinate, yCoordinate, BeginnOrEnd, numberOfLane) {

		//const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd, const int& numberOfLane
	}
	explicit vertexEnd::vertexEnd(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd) : vertex(xCoordinate, yCoordinate, BeginnOrEnd) {

		//const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd, const int& numberOfLane

	}
	vertexEnd::vertexEnd(const vertexEnd& other):vertex() {

	}
	vertexEnd::vertexEnd(vertexEnd&& other) = default;
	vertexEnd& operator=(vertexEnd& other) {
		return *this;		
	}
	vertexEnd& operator=(vertexEnd&& other) = default;
	vertexEnd::~vertexEnd() {

	}
	vehicle* getVehiclePtrOutOfVertex(const int& endVertexNumber, const int& param) override {
		return nullptr;
	}
	void setTransmissionTable(int param)override {

	}
	void vehiclePTRmanipulationInV(vehicle* vehiclePTR) override {
		vehiclePTR->m_inRange = false;
		vehiclePTR->m_lane = 0;
		vehiclePTR->m_moblieORStationary = true;
		vehiclePTR->m_position = 0;
		vehiclePTR->m_pref_speed = 0;
		vehiclePTR->m_riseOrDecline = true;
		vehiclePTR->m_routeID = 0;
		vehiclePTR->m_routeVertexID_vehicle.clear();
		//i->m_sectionID = 0;
		vehiclePTR->serviceBool = false;
		vehiclePTR->processedByIteration = false;
		m_VPAptr->deallocate(vehiclePTR);
	}
	int getNumberOfVehicleInV()override {
		return 0;
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
};
