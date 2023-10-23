#include "PrecompiledHeadersEdges.h"
#include "vertexEnd.h"
//********************************************************************
//Constructor and destructor of the class:
vertexEnd::vertexEnd(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd)noexcept : vertex(xCoordinate, yCoordinate, BeginnOrEnd){
	m_shapeOfThatVertex = 2;
}
vertexEnd::~vertexEnd()noexcept {}

//********************************************************************
//Implementations of the methods of the virtual functions of the parent class:

vehicle* vertexEnd::getVehiclePtrOutOfVertex(const int& endVertexNumber, const int& param){
	return nullptr;
}

void vertexEnd::setTransmissionTable(int param) {

}

void vertexEnd::vehiclePTRmanipulationInV(vehicle* vehiclePTR) {
	m_numberOfVehicle++;

	vehiclePTR->m_inRange = false;
	vehiclePTR->m_lane = 0;
	vehiclePTR->m_moblieORStationary = true;
	vehiclePTR->m_position = 0;
	vehiclePTR->m_pref_speed = 0;
	vehiclePTR->m_riseOrDecline = true;
	vehiclePTR->m_routeID = 0;
	vehiclePTR->m_routeVertexID_vehicle.clear();
	vehiclePTR->m_processedByIteration = false;
	if (m_VPAptr != nullptr) {
		m_VPAptr->deallocate(vehiclePTR);
	}
}

int vertexEnd::checkIfVehicleIsInV(vehicle* vehiclePTR) {
	return 0;
}

void vertexEnd::deleteVehicleInV(vehicle* vehiclePTR) {

}

size_t vertexEnd::sizeOfTransmissiontable() {
	return 0;
}

size_t vertexEnd::sizeOfSingleTransmissiontable(int iter) {

	return 0;
}

void vertexEnd::setPrintShape(size_t param) {

}

size_t vertexEnd::getPrintShape() {
	return 0;
}

std::vector<std::pair<int, int>> vertexEnd::getAdjacentEdges() {
	std::vector<std::pair<int, int>> returnValue;
	returnValue.clear();
	return returnValue;
}

float vertexEnd::getVertexDelay(const int& destinationVertex) {
	return 0.0f;
}