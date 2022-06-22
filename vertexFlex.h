#pragma once
#include "PrecompiledHeadersEdges.h"
//#include "vehicle.h"
#include "vertex.h"
class transmissionTable {
public:

	int param1 = 0;
	std::vector<vehicle*> param2;
	transmissionTable::transmissionTable() = default;
	transmissionTable::transmissionTable(const transmissionTable& other) {
		param1 = other.param1;
		param2 = other.param2;
	}
	transmissionTable::transmissionTable(const transmissionTable&& other) {
		param1 = other.param1;
		param2 = other.param2;
	}
	transmissionTable& operator=(transmissionTable& other) {
		if (&other == this) {
			return *this;
		}
		param1 = other.param1;
		param2 = other.param2;
		return *this;
	}
	transmissionTable& operator=(transmissionTable&& other) {
		if (&other == this) {
			return *this;
		}
		param1 = other.param1;
		param2 = other.param2;
		return *this;
	}
	transmissionTable::~transmissionTable() noexcept {

	}

	vehicle* transmissionTable::getPTR() {
		vehicle* PTR = nullptr;
		if (param2.size()>0) {
			PTR= param2.back();
			param2.pop_back();
		}
		
		return PTR;
	}
};
class vertexFlex :public vertex {
private:
	size_t a = 0;
	bool serviceBool = false;
public:
	size_t m_printShape = 11;
	std::vector<transmissionTable> m_vectorOfTransmissionTable;
	explicit vertexFlex::vertexFlex() :vertex() {
		
	}
	explicit vertexFlex::vertexFlex(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd) : vertex(xCoordinate, yCoordinate, BeginnOrEnd) {
		
	}
	explicit vertexFlex::vertexFlex(const int& xCoordinate, const int& yCoordinate, const std::pair<int, int>& numberOfLanes) : vertex(xCoordinate, yCoordinate, numberOfLanes) {
		
	}
	vertexFlex::vertexFlex(const vertexFlex& other) {
		a = other.a;
		m_vectorOfTransmissionTable = other.m_vectorOfTransmissionTable;
	}
	vertexFlex::vertexFlex(const vertexFlex&& other) {
		a = other.a;
		m_vectorOfTransmissionTable = other.m_vectorOfTransmissionTable;
	}
	vertexFlex& operator=(const vertexFlex& other) {
		if (&other == this) {
			return *this;
		}
		a = other.a;
		m_vectorOfTransmissionTable = other.m_vectorOfTransmissionTable;
		return *this;
	}
	vertexFlex& operator=(const vertexFlex&& other){
		if (&other == this) {
			return *this;
		}
		a = other.a;
		m_vectorOfTransmissionTable = other.m_vectorOfTransmissionTable;
		return *this;
	}
	vertexFlex::~vertexFlex() noexcept {}


	vehicle* getVehiclePtrOutOfVertex(const int& endVertexNumber,const int& param) override {
		serviceBool = false;
		if (!m_vectorOfTransmissionTable.empty()) {
			for (auto &i : m_vectorOfTransmissionTable) {
				if (i.param1 == endVertexNumber)   {
					if (i.param2.size()==0) {
						return nullptr;
					}
					else {
						return i.getPTR();
						serviceBool = false;
					}
				}
				else {	
					if (m_VPAptr != nullptr) {
						m_VPAptr->deallocateClean(i.getPTR());
					}
					serviceBool = true;
				}
				
			}
		}
		else {
			return m_VPAptr->allocate(1, param);
		}
		
	}
	void setTransmissionTable(int param)override {
		
		transmissionTable tmT;
		
		tmT.param1 = param;
		m_vectorOfTransmissionTable.push_back(tmT);
	}
	void vehiclePTRmanipulationInV(vehicle* vehiclePTR) override {
			
		if (vehiclePTR->m_routeVertexID_vehicle.empty()) {
			vehiclePTR->m_inRange = false;
			vehiclePTR->m_lane = 0;
			vehiclePTR->m_moblieORStationary = true;
			vehiclePTR->m_position = 0;
			vehiclePTR->m_pref_speed = 0;
			vehiclePTR->m_riseOrDecline = true;
			vehiclePTR->m_routeID = -1;
			vehiclePTR->m_routeVertexID_vehicle.clear();
			vehiclePTR->serviceBool = false;
			vehiclePTR->processedByIteration = false;
			if (m_VPAptr != nullptr) {
				m_VPAptr->deallocate(vehiclePTR);
			}
		}
		else {
			m_numberOfVehicle++;
			a = 0;
			serviceBool = false;
			while (a < vehiclePTR->m_routeVertexID_vehicle.size() - 1) {
				if (vehiclePTR->m_routeVertexID_vehicle[a] == m_vertexID) {
					if (!m_vectorOfTransmissionTable.empty()) {
						for (auto &i : m_vectorOfTransmissionTable) {
							if (vehiclePTR->m_routeVertexID_vehicle[a + 1] == i.param1) {
								
								i.param2.push_back(vehiclePTR);
								serviceBool = true;
								
							}
						}
					}
				}
				a++;
			}
			if ((serviceBool == false)&&(m_VPAptr!=nullptr)) {
				m_VPAptr->deallocateClean(vehiclePTR);
			}
		}
		
	}
	int checkIfVehicleIsInV(vehicle* vehiclePTR)override {
		int retVal = 0;
		if (!m_vectorOfTransmissionTable.empty()) {
			for (auto &i : m_vectorOfTransmissionTable) {
				for (auto &j : i.param2) {
					if (j == vehiclePTR) {
						retVal++;
						
					}
				}
			}
		}
		return retVal;
	}
	void deleteVehicleInV(vehicle* vehiclePTR) override {
		serviceBool = false;

		std::vector<vehicle*> param3;
		if (!m_vectorOfTransmissionTable.empty()) {
			for (auto &i : m_vectorOfTransmissionTable) {
				for(auto &j:i.param2){
					if(j== vehiclePTR){
						serviceBool = true;
					}
				}
			}
			if (serviceBool == true) {
				for (auto &i : m_vectorOfTransmissionTable) {
					for (auto &j : i.param2) {
						if (j != vehiclePTR) {
							param3.push_back(j);
						}
					}
					i.param2.clear();
					i.param2 = param3;
					param3.clear();
				}
			}
		}
	}
	size_t sizeOfTransmissiontable() override {
		return m_vectorOfTransmissionTable.size();
	}
	virtual std::vector<std::pair<int, int>> getAdjacentEdges()override {
		std::vector<std::pair<int, int>> returnValue;
		returnValue.clear();
		if (!m_vectorOfTransmissionTable.empty()) {
			for (auto &i : m_vectorOfTransmissionTable) {
				returnValue.push_back(std::make_pair(m_vertexID, i.param1));
			}
		}
		return returnValue;
	}
	size_t sizeOfSingleTransmissiontable(int iter) override {

		return m_vectorOfTransmissionTable[iter].param2.size();
	}
	void setPrintShape(size_t param) override {
		m_printShape = param;
	}
	size_t getPrintShape() override {
		return m_printShape;
	}
};
