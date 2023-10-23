#include "PrecompiledHeadersEdges.h"
#include "edge.h"

//Constructor and destructor of the class:
edge::edge() = default;
edge::edge(const std::shared_ptr<vertex>& startVertex, const std::shared_ptr<vertex>& endVertex,  int numberOfLanes, std::unique_ptr<PrintPattern> pp_ptr,
	concreteObserverSubject* cOSptr)
	: m_startVertexPtr(startVertex), m_endVertexPtr(endVertex), m_numberOfLanes(numberOfLanes), m_ppPtr(std::move(pp_ptr)), m_cOSptr(cOSptr) {
	m_startVertex = m_startVertexPtr->m_vertexID;
	m_endVertex = m_endVertexPtr->m_vertexID;
	m_observerPTR = m_ppPtr->createObserver();
	m_cOSptr->toRegister(m_observerPTR);
	m_length = m_ppPtr->m_length;
	m_risingOrDescention = m_ppPtr->m_risingOrDescention;
	sFs.m_CBLptr = m_ppPtr->m_CBLptr;
	m_ppPtr->accept(sFs);
}
edge::edge(edge && other) = default;
edge::~edge() noexcept {}
//********************************************************************
//Basic methods of the class:
int edge::getStartVertex() {
	return m_startVertex;
}

int edge::getEndVertex() {
	return m_endVertex;
}

void edge::setPoolAllocatorPtr(bbe::PoolAllocator<vehicle>& poolAllocatorRef) {
	//****************************************************************
	//This method sets the pointer that points to the "PoolAllocator" associated with the graph whose part this link is.
	m_VPAptr = &poolAllocatorRef;
	sFs.vehicleSetPtr->setPoolAllocatorPtr(poolAllocatorRef);
}

void edge::sectionDestruct() {
	//****************************************************************
	//In this method the vehicles are taken out of the lane, that means out of the edge of the traffic graph.
	//The vehicle objects, which are controlled in the lane via pointer, are prepared again for a new use in 
	//the simulation by calling the method "deallocate" of the class "PoolAllocator".
	//****************************************************************
	sFs.vehicleSetPtr->sectionDestruct();
}

//********************************************************************
//Two methods for calculating the characteristics of simulated traffic in the lane (in the edge of the network-graph):
void edge::computeWeightOfEdge() {
	m_weight = sFs.vehicleSetPtr->computeWeightOfSection(m_length);
}

void edge::computeEdgesCharactaristics() {
	m_density = 0.0f;
	m_averageSpeed = 0.0f;
	if (m_length > 0) {
		if (sFs.vehicleSetPtr->trafficCharacteristics().second > 0) {//vehicleSetPtr->trafficCharacteristics().second  =>> Anzahl der Fahrzeuge in Edge
			m_density = sFs.vehicleSetPtr->computeTrafficDensityOfSection(m_length);
			m_averageSpeed = sFs.vehicleSetPtr->computeAverageSpeedOfSection();
		}
	}
	if (m_averageSpeed > 0) {
		m_averageTravelTime = (1.0f / (static_cast<float>(m_averageSpeed / (static_cast<float>(m_length)))))+m_startVertexPtr->getVertexDelay(m_endVertex);
	}
	else {
		m_averageTravelTime = 1.0f/(static_cast<float>(static_cast<float>(m_maxVelocity) / (static_cast<float>(m_length))));
	}	
}

//********************************************************************
//Methods for carrying out traffic simulation in the lane:
void edge::simiRun(const int& simulationIterator) {
	sFs.vehicleSetPtr->sort();
	//********************************************************************
	//This method orchestrates together with the subordinated methods "flow1L" and "singleSimulationStep" the simulation in the lane.
	m_simulationIterator = simulationIterator;
	switch(m_numberOfLanes){
	case 1:
		sFs.vehicleSetPtr->flow1L(1, 220, m_length, m_risingOrDescention, m_startVertexPtr, m_endVertex, m_numberOfLanes);					//Insertion of new vehicles into the edge
		m_maxVelocity_Density= sFs.vehicleSetPtr->singleSimulationStep(220,m_length,m_numberOfLanes,m_risingOrDescention,m_endVertexPtr);		//Treatment of all vehicles in the edge according the traffic flow simulation alg.
		break;
	
	case 2:
		sFs.vehicleSetPtr->flow1L(1, 440, m_length, m_risingOrDescention, m_startVertexPtr, m_endVertex, m_numberOfLanes);					//Insertion of new vehicles into the edge
		m_maxVelocity_Density= sFs.vehicleSetPtr->singleSimulationStep(440, m_length, m_numberOfLanes, m_risingOrDescention, m_endVertexPtr);		//Treatment of all vehicles in the edge according the traffic flow simulation alg.
		break;
	}
	//********************************************************************
	//The method "allocateVehicleAtPositionX()" can be used to block the lane (edge). 
	//This is done by placing vehicle objects in the lane, which do not move further and thus block the lane.
	if (m_observerPTR->m_position.first > 0) {	//Possible blocking of the Link
		allocateVehicleAtPositionX();
	}
	//********************************************************************
	//Calculation of traffic characteristics at every tenth traffic simulation iteration!
	if (simulationIterator % 10 == 0) {
		computeEdgesCharactaristics();
	}
	//********************************************************************
	writeSimulationResultsIntoDataContainer();
}

void edge::allocateVehicleAtPositionX() {
	//********************************************************************
	//The method "allocateVehicleAtPositionX()" can be used to block the link (edge). 
	//The method is executed when a lane should to be blocked at a certain position												
	bool checkIfPositionIsEmpty = false;
	if (m_observerPTR->m_position.second > 0) {
		if (sFs.vehicleSetPtr->vehiclePositionCheckInLane(m_observerPTR->m_position.first)) {
			checkIfPositionIsEmpty = true;
			m_observerPTR->m_position.first = 0;
			m_observerPTR->m_position.second = 0;
		}
		if (checkIfPositionIsEmpty == false) {
			vehicle* VPAEptr = nullptr;
			if (m_observerPTR->m_position.second == 1) {
				VPAEptr = m_VPAptr->allocate(1, m_observerPTR->m_position.first);
				VPAEptr->m_lane = 1;
			}
			if (m_observerPTR->m_position.second == 2) {
				VPAEptr = m_VPAptr->allocate(2, m_observerPTR->m_position.first);
				VPAEptr->m_lane = 2;
			}
			if (VPAEptr != nullptr) {
				VPAEptr = sFs.vehicleSetPtr->insertion(VPAEptr, m_length, m_numberOfLanes, m_observerPTR->m_position.first, m_risingOrDescention, false);
				sFs.vehicleSetPtr->insertSET(VPAEptr);
			}
			sFs.vehicleSetPtr->sort();
			m_observerPTR->m_position.first = 0;
			m_observerPTR->m_position.second = 0;
		}
	}
}

//********************************************************************
//Method for displaying the simulation result:
void edge::writeSimulationResultsIntoDataContainer(){
	//Print of the simulation result:
	for (auto& i : sFs.vehicleSetPtr->m_vehicleSet) {
		i->m_processedByIteration = false;
		if (!i->m_routeVertexID_vehicle.empty()) {
			m_ppPtr->printContentOfSection(i->m_lane, i->m_position, i->m_routeVertexID_vehicle.back());

		}
		else {
			m_ppPtr->printContentOfSection(i->m_lane, i->m_position, 0);
		}
	}
}


