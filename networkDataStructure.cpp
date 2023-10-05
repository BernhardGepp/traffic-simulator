#include "PrecompiledHeadersEdges.h"
#include "networkDataStructure.h"

//Constructor and destructor of the class:
networkDataStructure::networkDataStructure() {}
networkDataStructure::~networkDataStructure() {}

//********************************************************************
//Methods of the class:

void networkDataStructure::printLanesAndVehiclesOfAllEdges() {
	m_PWE.fullemptyPrintContainer(m_CBLptr->m_hdc, m_CBLptr->m_f5PaintLane);
}

void networkDataStructure::iniziallizationOfPointer(callBackLinks* CBL) {
	m_CBLptr = CBL;
}