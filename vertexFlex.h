#pragma once
#include "PrecompiledHeadersEdges.h"
#include "vehicle.h"
#include "vertex.h"
class transmissionTable {
public:

	int param1 = 0;
	std::vector<vehicle*> param2;
	transmissionTable::transmissionTable() {
		//param2.reserve(40);
	}
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
		else {
			param1 = other.param1;
			param2 = other.param2;
		}
	}
	transmissionTable& operator=(transmissionTable&& other) {
		if (&other == this) {
			return *this;
		}
		else {
			param1 = other.param1;
			param2 = other.param2;
		}
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
	//transmissionTable tm;
	std::vector<transmissionTable> m_transmissionTable;
	explicit vertexFlex::vertexFlex() :vertex() {
		//m_transmissionTable.reserve(4);
	}
	explicit vertexFlex::vertexFlex(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd) : vertex(xCoordinate, yCoordinate, BeginnOrEnd) {
		//m_transmissionTable.reserve(4);
	}
	explicit vertexFlex::vertexFlex(const int& xCoordinate, const int& yCoordinate, const std::pair<int, int>& numberOfLanes) : vertex(xCoordinate, yCoordinate, numberOfLanes) {
		//m_transmissionTable.reserve(4);
	}
	explicit vertexFlex::vertexFlex(vertexFlex& other){
		a = other.a;
		m_transmissionTable = other.m_transmissionTable;
		
	}
	vertexFlex& operator=(vertexFlex& other) {
		if (&other == this) {
			return *this;
		}
		else {
			a = other.a;
			m_transmissionTable = other.m_transmissionTable;
			return *this;
		}
	}
	
	vertexFlex::vertexFlex(vertexFlex&& other) = default;
	
	vertexFlex& operator=(vertexFlex&& other) = default;
	
	vertexFlex::~vertexFlex() {

	}
	vehicle* getVehiclePtrOutOfVertex(const int& endVertexNumber,const int& param) override {
		serviceBool = false;
		if (!m_transmissionTable.empty()) {
			for (auto &i : m_transmissionTable) {
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
					
					
					m_VPAptr->deallocateClean(i.getPTR());
					
					serviceBool = true;
				}
				if (i.param2.size() > 33) {
					for (auto &k : i.param2) {
						serviceBool = false;
						for (auto &l : m_VPAptr->m_quarantine) {
							if (l == m_VPAptr->xxxx(k)) {
								serviceBool = true;

							}
						}
						if (serviceBool == false) {
							if (i.param1 != endVertexNumber) {
								m_VPAptr->deallocateClean(k);
							}
						}
					}
					
				}
				if (i.param2.size() > 35) {
					i.param2.clear();
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
		m_transmissionTable.push_back(tmT);
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
			//i->m_sectionID = 0;
			vehiclePTR->serviceBool = false;
			vehiclePTR->processedByIteration = false;
			m_VPAptr->deallocate(vehiclePTR);//Stoppautos!!!
		}
		else {
			a = 0;
			serviceBool = false;
			while (a < vehiclePTR->m_routeVertexID_vehicle.size() - 1) {
				if (vehiclePTR->m_routeVertexID_vehicle[a] == m_vertexID) {
					if (!m_transmissionTable.empty()) {
						for (auto &i : m_transmissionTable) {
							if (vehiclePTR->m_routeVertexID_vehicle[a + 1] == i.param1) {
								i.param2.push_back(vehiclePTR);
								serviceBool = true;
							}
						}
					}
				}
				a++;
			}
			if (serviceBool == false) {
				m_VPAptr->deallocateClean(vehiclePTR);
			}
		}
		
	}
	/*int getNumberOfVehicleInTMT()override {
		if (!m_transmissionTable.empty()) {
			for (auto &i : m_transmissionTable) {
				sum += i.param2.size();
			}
		}
		else {
			return 0;
		}
	}*/
	int getNumberOfVehicleInV()override {
		int sum = 0;
		if (!m_transmissionTable.empty()) {
			for (auto &i : m_transmissionTable) {
				sum += i.param2.size();
			}
		}
		return sum;
	}
	int checkIfVehicleIsInV(vehicle* vehiclePTR)override {
		int retVal = 0;
		if (!m_transmissionTable.empty()) {
			for (auto &i : m_transmissionTable) {
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
		if (!m_transmissionTable.empty()) {
			for (auto &i : m_transmissionTable) {
				for(auto &j:i.param2){
					if(j== vehiclePTR){
						serviceBool = true;
					}
				}
			}
			if (serviceBool == true) {
				for (auto &i : m_transmissionTable) {
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
	/*std::pair<int, int> sizeOfTT()override {
		return std::make_pair<int, int>(m_transmissionTable[0].param2.size(), m_transmissionTable[1].param2.size());
	
	}*/
	size_t sizeOfTransmissiontable() override {
		return m_transmissionTable.size();
	}
	virtual std::vector<std::pair<int, int>> getAdjacentEdges()override {
		std::vector<std::pair<int, int>> returnValue;
		returnValue.clear();
		if (!m_transmissionTable.empty()) {
			for (auto &i : m_transmissionTable) {
				returnValue.push_back(std::make_pair(m_vertexID, i.param1));
			}
		}
		return returnValue;
	}
};
