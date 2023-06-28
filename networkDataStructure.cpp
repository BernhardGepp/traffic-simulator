#include "PrecompiledHeadersEdges.h"
#include "networkDataStructure.h"
#include "vertexEnd.h"
#include "vertexFlex.h"
#include "vertexStart.h"
#include "graphTrafficGenerationOnAllRoutes.h"
#include "graphTrafficGenerationOnFastRoutes.h"

bool sortBottomUp(const std::pair<int, int>& a, const std::pair<int, int>& b) {
	return a.first > b.first;
}
bool sortTopDown(const std::pair<int, int>& a, const std::pair<int, int>& b) {
	return a.first < b.first;
}

//Constructor and destructor of the class:
networkDataStructure::networkDataStructure() {}
networkDataStructure::~networkDataStructure() {}

//********************************************************************
//Methods of the class:


bool networkDataStructure::checkIfInNetworkLaneVector() {
	return true;
}

void networkDataStructure::printLanesAndVehiclesOfAllEdges() {

	for (auto& i : appliedGraph) {
		i->printLanesAndVehiclesOfAllEdges();
	}
	//m_PWE.fullemptyPrintContainer(m_CBLptr->m_hdc, m_CBLptr->m_f5PaintLane);
}