#include "PrecompiledHeadersEdges.h"
#include "networkDataStructure.h"
#include "vertexEnd.h"
#include "vertexFlex.h"
#include "vertexStart.h"
#include "graphTrafficGenerationOnAllRoutes.h"
#include "graphTrafficGenerationOnFastRoutes.h"


//Constructor and destructor of the class:
networkDataStructure::networkDataStructure() {}
networkDataStructure::~networkDataStructure() {}

//********************************************************************
//Methods of the class:

void networkDataStructure::printLanesAndVehiclesOfAllEdges() {

	for (auto& i : appliedGraph) {
		i->printLanesAndVehiclesOfAllEdges();
	}
	m_PWE.fullemptyPrintContainer(m_CBLptr->m_hdc, m_CBLptr->m_f5PaintLane);
}

void networkDataStructure::iniziallizationOfPointer(callBackLinks* CBL) {
	m_CBLptr = CBL;
}