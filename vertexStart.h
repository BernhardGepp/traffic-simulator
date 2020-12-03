#pragma once
#include "vertex.h"
#include "PrecompiledHeadersEdges.h"
#include "vehicle.h"
class vertexStart :public vertex {
private:
	std::vector<int> m_transmissionTableInt;
public:
	explicit vertexStart::vertexStart(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd, const int& numberOfLane) :vertex(xCoordinate, yCoordinate, BeginnOrEnd, numberOfLane) {

		
	}
	explicit vertexStart::vertexStart(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd) : vertex(xCoordinate, yCoordinate, BeginnOrEnd) {

		
	}
	explicit vertexStart::vertexStart(const vertexStart& other) {
		m_transmissionTableInt = other.m_transmissionTableInt;
	}
	explicit vertexStart::vertexStart(vertexStart&& other) = default;
		
	vertexStart& operator=(vertexStart& other) {
		if (&other == this) {
			return *this;
		}
		m_transmissionTableInt = other.m_transmissionTableInt;
		return *this;
	}
	vertexStart& operator=(vertexStart&& other) = default;
	
	vertexStart::~vertexStart() {

	}
	vehicle* getVehiclePtrOutOfVertex(const int& endVertexNumber, const int& param) override {
		
		
		return m_VPAptr->allocate(1, param);
	}
	void setTransmissionTable(int param)override {
		
		m_transmissionTableInt.push_back(param);
	}
	void vehiclePTRmanipulationInV(vehicle* vehiclePTR) override {

	}
	int getNumberOfVehicleInV()override {
		return 0;
	}
	/*int getNumberOfVehicleInTMT()override {
		return 0;
	}*/
	int checkIfVehicleIsInV(vehicle* vehiclePTR)override {
		return 0;
	}
	void deleteVehicleInV(vehicle* vehiclePTR) override {

	}
	/*std::pair<int, int> sizeOfTT()override{
		return std::make_pair<int, int>(0, 0);
	}*/
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
};