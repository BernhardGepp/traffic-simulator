#include "PrecompiledHeadersEdges.h"
#include "vertexStart.h"

vertexStart::vertexStart(const int& xCoordinate, const int& yCoordinate, const int& BeginnOrEnd) : vertex(xCoordinate, yCoordinate, BeginnOrEnd) {}

vertexStart::~vertexStart() noexcept {}

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

