#include "PrecompiledHeadersEdges.h"
#include "vertexFlex.h"

//Constructor and destructor of the class:
transmissionTable::~transmissionTable() noexcept {}

vehicle* transmissionTable::getPTR() {
	vehicle* PTR = nullptr;
	if (param2.size() >0) {
		PTR = param2.front();
		param2.pop();
	}
	return PTR;
}

vertexFlex::vertexFlex() noexcept :vertex(){}
vertexFlex::vertexFlex(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd) noexcept : vertex(xCoordinate, yCoordinate, BeginnOrEnd) {}
vertexFlex::vertexFlex(const int& xCoordinate, const int& yCoordinate, const std::pair<int, int>& numberOfLanes) noexcept : vertex(xCoordinate, yCoordinate, numberOfLanes) {}
vertexFlex::~vertexFlex() noexcept {}

//********************************************************************
//Implementations of the methods of the virtual functions of the parent class:

vehicle* vertexFlex::getVehiclePtrOutOfVertex(const int& endVertexNumber, const int& param) {
	if (!m_vectorOfTransmissionTable.empty()) {
		for (auto& i : m_vectorOfTransmissionTable) {
			if (i.param1 == endVertexNumber) {
				if (i.param2.size() == 0) {
					return nullptr;
				}
				else {
					return i.getPTR();
				}
			}
		}
	}
	else {
		return m_VPAptr->allocate(1, param);
	}
	return nullptr;
}

void vertexFlex::setTransmissionTable(int param) {

	transmissionTable tmT;
	tmT.param1 = param;
	m_vectorOfTransmissionTable.push_back(tmT);
}

void vertexFlex::vehiclePTRmanipulationInV(vehicle* vehiclePTR) {

	if (vehiclePTR->m_routeVertexID_vehicle.empty()) {
		vehiclePTR->m_inRange = false;
		vehiclePTR->m_lane = 0;
		vehiclePTR->m_moblieORStationary = true;
		vehiclePTR->m_position = 0;
		vehiclePTR->m_pref_speed = 0;
		vehiclePTR->m_riseOrDecline = true;
		vehiclePTR->m_routeID = -1;
		vehiclePTR->m_routeVertexID_vehicle.clear();
		vehiclePTR->m_processedByIteration = false;
		if (m_VPAptr != nullptr) {
			m_VPAptr->deallocate(vehiclePTR);
		}
	}
	else {
		m_numberOfVehicle++;
		a = 0;
		serviceBool = false;
		while (a < vehiclePTR->m_routeVertexID_vehicle.size()) {
			if (vehiclePTR->m_routeVertexID_vehicle[a] == m_vertexID) {
				if (!m_vectorOfTransmissionTable.empty()) {
					for (auto& i : m_vectorOfTransmissionTable) {
						if (a < vehiclePTR->m_routeVertexID_vehicle.size()) {
							if (vehiclePTR->m_routeVertexID_vehicle[a + 1] == i.param1) {
								i.param2.push(vehiclePTR);
								serviceBool = true;
							}
						}
					}
				}
			}
			a++;
		}
		if ((serviceBool == false) && (m_VPAptr != nullptr)) {
			m_VPAptr->deallocateClean(vehiclePTR);
		}
	}
}

int vertexFlex::checkIfVehicleIsInV(vehicle* vehiclePTR) {
	int retVal = 0;
	std::queue<vehicle*>extraQueue;
	if (!m_vectorOfTransmissionTable.empty()) {
		for (auto& i : m_vectorOfTransmissionTable) {
			extraQueue = i.param2;
			while(!extraQueue.empty()) {
				if (extraQueue.front() == vehiclePTR) {
					retVal++;
				}
				extraQueue.pop();
			}
		}
	}
	return retVal;
}

void vertexFlex::deleteVehicleInV(vehicle* vehiclePTR) {
	std::queue<vehicle*>extraQueue;
	if (!m_vectorOfTransmissionTable.empty()) {
		for (auto& i : m_vectorOfTransmissionTable) {
			while (!i.param2.empty()) {
				if (i.param2.front() != vehiclePTR) {
					extraQueue.push(i.param2.front());
				}
				i.param2.pop();
			}
			i.param2 = extraQueue;
		}
	}
}

size_t vertexFlex::sizeOfTransmissiontable() {
	return m_vectorOfTransmissionTable.size();
}

size_t vertexFlex::sizeOfSingleTransmissiontable(int iter) {

	return m_vectorOfTransmissionTable[iter].param2.size();
}

void vertexFlex::setPrintShape(size_t param) {
	m_printShape = param;
}

size_t vertexFlex::getPrintShape() {
	return m_printShape;
}

std::vector<std::pair<int, int>> vertexFlex::getAdjacentEdges() {
	std::vector<std::pair<int, int>> returnValue;
	returnValue.clear();
	if (!m_vectorOfTransmissionTable.empty()) {
		for (auto& i : m_vectorOfTransmissionTable) {
			returnValue.push_back(std::make_pair(m_vertexID, i.param1));
		}
	}
	return returnValue;
}

float vertexFlex::getVertexDelay(const int& destinationVertex) {
	if (!m_vectorOfTransmissionTable.empty()) {
		for (auto& i : m_vectorOfTransmissionTable) {
			if (i.param1 == destinationVertex) {
				if (i.param2.size() > 10)
					return static_cast<float>(i.param2.size());
			}
			
		}
	}
	return 0.0f;
}
