#include "PrecompiledHeadersEdges.h"
#include "vertexStart.h"

//Constructor and destructor of the class:
vertexStart::vertexStart(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd)noexcept : vertex(xCoordinate, yCoordinate, BeginnOrEnd) {
	m_shapeOfThatVertex = 1;
}

vertexStart::~vertexStart() noexcept {}

//********************************************************************
//Implementations of the methods of the virtual functions of the parent class:

vehicle* vertexStart::getVehiclePtrOutOfVertex(const int& endVertexNumber, const int& param){
	return m_VPAptr->allocate(1, param);
}

void vertexStart::setTransmissionTable(int param){
	m_transmissionTableInt.push_back(param);
}

void vertexStart::vehiclePTRmanipulationInV(vehicle* vehiclePTR){

}

int vertexStart::checkIfVehicleIsInV(vehicle* vehiclePTR){
	return 0;
}

void vertexStart::deleteVehicleInV(vehicle* vehiclePTR){

}

size_t vertexStart::sizeOfTransmissiontable(){
	return m_transmissionTableInt.size();
}

size_t vertexStart::sizeOfSingleTransmissiontable(int iter){

	return 0;
}

void vertexStart::setPrintShape(size_t param){

}

size_t vertexStart::getPrintShape(){
	return 0;
}

std::vector<std::pair<int, int>> vertexStart::getAdjacentEdges() {
	std::vector<std::pair<int, int>> param1;
	param1.clear();
	if (!m_transmissionTableInt.empty()) {
		for (auto& i : m_transmissionTableInt) {
			param1.push_back(std::make_pair(m_vertexID, i));
		}
	}
	return param1;
}

float vertexStart::getVertexDelay(const int& destinationVertex) {
	return 0.0f;
}
