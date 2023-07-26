#include "PrecompiledHeadersEdges.h"
#include "edge.h"

//Constructor and destructor of the class:
edge::edge() = default;
edge::edge(const int& startVertex, const int& endVertex, const int& numberOfLanes, std::unique_ptr<PrintPattern>&pp_ptr,
	concreteObserverSubjekt * cOSptr)
	: m_startVertex(startVertex), m_endVertex(endVertex), m_numberOfLanes(numberOfLanes), m_ppPtr(std::move(pp_ptr)), m_cOSptr(cOSptr) {
	vehicleEraseVector.reserve(150);
	m_routeServiceBool = false;
	sFs.m_CBLptr = m_ppPtr->m_CBLptr;
	 //m_maxVelocity, m_maxVelocity_Density);
	m_observerPTR = m_ppPtr->createObserver();
	m_cOSptr->registrieren(m_observerPTR);
	m_length = m_ppPtr->m_length;
	m_risingOrDescention = m_ppPtr->m_risingOrDescention;
	
	m_ppPtr->accept(sFs);
}
edge::edge(edge && other) = default;
edge::~edge() noexcept {}
//********************************************************************
//Methods of the class:
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
}


void edge::sectionDestruct() {
	//****************************************************************
	//In this method the vehicles are taken out of the lane, that means out of the edge of the traffic graph.
	//The vehicle objects, which are controlled in the lane via pointer, are prepared again for a new use in 
	//the simulation by calling the method "deallocate" of the class "PoolAllocator".
	//****************************************************************
	vehicle* vehiclePtr = nullptr;
	while (!sFs.vehicleSetPtr->m_vehicleSet.empty()) {

		vehiclePtr = *sFs.vehicleSetPtr->m_vehicleSet.begin();
		sFs.vehicleSetPtr->m_vehicleSet.erase(sFs.vehicleSetPtr->m_vehicleSet.begin());
		m_VPAptr->deallocate(vehiclePtr);
		vehiclePtr = nullptr;
	}
}



//********************************************************************
//Two methods for calculating the characteristics of simulated traffic in the lane (in the edge of the network-graph):
void edge::computeWeightOfEdge() {
	m_weight = 1 / ((static_cast<float>(sFs.vehicleSetPtr->sumOfVehicleSpeedInEdge())) / (static_cast<float>(m_length)));
}

void edge::computeEdgesCharactaristics() {
	m_density = 0.0f;
	m_averageSpeed = 0.0f;
	if (m_length > 0) {
		if (sFs.vehicleSetPtr->trafficCharacteristics().second > 0) {//vehicleSetPtr->trafficCharacteristics().second  =>> Anzahl der Fahrzeuge in Edge
			m_density = static_cast<float>(static_cast<float>(sFs.vehicleSetPtr->trafficCharacteristics().second) / (static_cast<float>(m_length) * 0.001));
			m_averageSpeed = (static_cast<float>(sFs.vehicleSetPtr->trafficCharacteristics().first)) / (static_cast<float>(sFs.vehicleSetPtr->trafficCharacteristics().second));
		}
	}
	if (m_averageSpeed > 0) {
		m_averageTravelTime = (1.0f / (static_cast<float>(m_averageSpeed / (static_cast<float>(m_length)))))+m_startVertexPtr->getVertexDelay(m_endVertex);
	}
	else {
		m_averageTravelTime = 1.0f/(static_cast<float>(static_cast<float>(m_maxVelocity) / (static_cast<float>(m_length))));
	}	
}

void edge::simiRun(const int& simulationIterator) {
	sort();
	//********************************************************************
	//This method orchestrates together with the subordinated methods "flow1L" and "singleSimulationStep" the simulation in the lane.
	m_simulationIterator = simulationIterator;
	for (auto& i : sFs.vehicleSetPtr->m_vehicleSet) {
		i->m_riseOrDecline = m_risingOrDescention;
	}
	switch(m_numberOfLanes){
	case 1:
		flow1L(1, 220);					//Insertion of new vehicles into the edge
		singleSimulationStep(220);		//Treatment of all vehicles in the edge according the traffic flow simulation alg.
		break;
	
	case 2:
		flow1L(1, 440);					//Insertion of new vehicles into the edge
		singleSimulationStep(440);		//Treatment of all vehicles in the edge according the traffic flow simulation alg.
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
	//Print of the simulation result:
	sFs.vehicleSetPtr->printContentOfSection(m_startVertexPtr->m_XcoordinateVertex, m_startVertexPtr->m_YcoordinateVertex, m_endVertexPtr->m_XcoordinateVertex, m_endVertexPtr->m_YcoordinateVertex);
}

void edge::flow1L(const int& a, const int& b) {
	bool checkIfPositionIsEmpty = false;
	//************************************************************
	//Check whether the first position in the set is occupied!
	for (auto& i : sFs.vehicleSetPtr->m_vehicleSet) {
		i->m_riseOrDecline = m_risingOrDescention;
		if ((i->m_position == 0) && (m_risingOrDescention == true)) {
			checkIfPositionIsEmpty = true;
		}
		if ((i->m_position == m_length) && (m_risingOrDescention == false)) {
			checkIfPositionIsEmpty = true;
		}
	}
	//If the first position of the lane is not occupied, the program continues with the insertion of the vehicle objects into the lane.
	if (checkIfPositionIsEmpty == false) {
		if (m_startVertexPtr->m_shapeOfThatVertex == 1) {
			if (a < 150) {
				vehicle* VPAEptr = nullptr;
				VPAEptr = m_startVertexPtr->getVehiclePtrOutOfVertex(0, 0);
				if (VPAEptr != nullptr) {
					VPAEptr->m_routeVertexID_vehicle.clear();
					VPAEptr->m_routeID = -1;
					VPAEptr = routeAssignment(VPAEptr);
					if(VPAEptr != nullptr)
						sFs.vehicleSetPtr->insertSET(insertion(VPAEptr));// Inserting the vehicle objects into the set(lane)! New!
				}
			}
		}
		if ((m_startVertexPtr->m_shapeOfThatVertex == 0) || (m_startVertexPtr->m_shapeOfThatVertex == 11)) {
			sFs.vehicleSetPtr->insertSET(insertion(m_startVertexPtr->getVehiclePtrOutOfVertex(m_endVertex, 0)));
			if ((m_startVertexPtr->getVertexDelay(m_endVertex) > 11.0f) && (m_numberOfLanes == 2)) {
				m_numberOfVehicleinRange++;
				sFs.vehicleSetPtr->insertSET(insertion(m_startVertexPtr->getVehiclePtrOutOfVertex(m_endVertex, 0)));
			}
			sort();
		}
	}
}

void edge::singleSimulationStep(const int& param) {
	//Treatment of all vehicles in the edge in order to execute the simulation!
	size_t vehicleSetSize = 0;
	vehicleSetSize = sFs.vehicleSetPtr->getVehicleSetSize();
	size_t counter = 0;
	do {
		counter++;

		if (sFs.vehicleSetPtr->m_vehicleSet.size() > 0) {
			//Determination of the maximum speed from certain traffic densities!
			if ((m_length / sFs.vehicleSetPtr->m_vehicleSet.size()) >= param) {
				m_maxVelocity_Density = 80;
			}
			else {
				m_maxVelocity_Density = 140;
			}
			//The methode "flow" of the inheriting classes of the class "selectionFlow Simulation" contains the traffic flow simulation algorithm!
			m_numberOfVehicleinRange = sFs.vehicleSetPtr->flow(m_numberOfLanes, m_length, m_risingOrDescention);
		}
	} while (counter < vehicleSetSize);
	//Vehicles who reached the end of the lane will be removed of the lane by the methode "deallocateVehicleAtEnd"!
	deallocateVehicleAtEnd(true);
}

void edge::sort() {
	std::vector <vehicle*> vehicleVector;
	vehicleVector.reserve(sFs.vehicleSetPtr->m_vehicleSet.size() + 1);
	for (auto i : sFs.vehicleSetPtr->m_vehicleSet) {
		if (i != nullptr) {
			if((i->m_lane>0)&&(i->m_ID_ptr!=nullptr))
				vehicleVector.emplace_back(i);
		}
	}
	sFs.vehicleSetPtr->m_vehicleSet.clear();
	for (auto& i : vehicleVector) {
		sFs.vehicleSetPtr->m_vehicleSet.insert(i);
	}
}

vehicle* edge::routeAssignment(vehicle* VPAEptr) {
	//********************************************************************
	//This method is called when a route is assigned in a vehicle object.
	VPAEptr->m_routeVertexID_vehicle.clear();

	if (!m_routeTable_IDrValueIDvertex.empty()) {
		if (m_routeTableIterator >= m_routeTable_IDrValueIDvertex.size()) {
			m_routeTableIterator = 0;//Reset Iterator!
		}
		if (m_routeServiceBool == false) {
			m_routeServiceBool = true;
		}
		if (m_routeTableIterator < m_routeTable_IDrValueIDvertex.size()) {
			VPAEptr->m_routeVertexID_vehicle.clear();
			VPAEptr->m_routeID = m_routeTable_IDrValueIDvertex[m_routeTableIterator].first.first;

			for (size_t i = 0; i < m_routeTable_IDrValueIDvertex[m_routeTableIterator].second.size(); i++) {
				VPAEptr->m_routeVertexID_vehicle.push_back(m_routeTable_IDrValueIDvertex[m_routeTableIterator].second[i]);
			}
			m_routeTableIterator++;
		}
		else {
			m_VPAptr->deallocate(VPAEptr);
			return nullptr;
		}
	}
	return VPAEptr;
}

vehicle* edge::insertion(vehicle* VPAEptr) {
	//********************************************************************
	//This method is used to insert vehicle objects into the lane.
	if (VPAEptr != nullptr) {
		VPAEptr->setPtr(VPAEptr);
		VPAEptr->m_moblieORStationary = true;
		VPAEptr->m_riseOrDecline = m_risingOrDescention;
		VPAEptr->m_inRange = true;
		VPAEptr->m_processedByIteration = false;
		if (m_risingOrDescention == true) {
			VPAEptr->m_position = 0;
		}
		if (m_risingOrDescention == false) {
			VPAEptr->m_position = m_length;
		}
		if (m_numberOfLanes == 2) {
			if ((m_numberOfVehicleinRange % 2) == 0)
				VPAEptr->m_lane = 1;
			else {
				VPAEptr->m_lane = 2;
				VPAEptr->m_position -= 1;
			}
		}
		else
			VPAEptr->m_lane = 1;
		return VPAEptr;
		
	}
	return nullptr;
}

void edge::allocateVehicleAtPositionX() {
	//********************************************************************
	//The method "allocateVehicleAtPositionX()" can be used to block the link (edge). 
	//The method is executed when a lane should to be blocked at a certain position												
	bool checkIfPositionIsEmpty = false;
	if (m_observerPTR->m_position.second > 0) {
		for (auto& i : sFs.vehicleSetPtr->m_vehicleSet) {
			if (i->m_position == m_observerPTR->m_position.first) {
				checkIfPositionIsEmpty = true;
				i->m_moblieORStationary = true;
				m_observerPTR->m_position.first = 0;
				m_observerPTR->m_position.second = 0;

				break;
			}
			else {
				checkIfPositionIsEmpty = false;
			}
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
				VPAEptr->setPtr(gsl::not_null <vehicle*> (VPAEptr));  //Setting the ID in vehicle object
				int nullIntInit = 0;
				VPAEptr->m_pref_speed = nullIntInit;
				VPAEptr->m_moblieORStationary = false;
				VPAEptr->m_position = m_observerPTR->m_position.first;
				VPAEptr->m_inRange = true;
				VPAEptr->m_riseOrDecline = m_risingOrDescention;
				sFs.vehicleSetPtr->insertSET(VPAEptr);
			}

			sort();
			m_observerPTR->m_position.first = 0;
			m_observerPTR->m_position.second = 0;
		}
	}
}

void edge::deallocateVehicleAtEnd(bool totalRelease) {
	//********************************************************************
	//This method removes vehicles from the edge, which have already passed it
	size_t a = 0;
	vehicleEraseVector.clear();
	if (!sFs.vehicleSetPtr->m_vehicleSet.empty()) {
		for (auto& ii : sFs.vehicleSetPtr->m_vehicleSet) {
			ii->m_processedByIteration = false;
			ii->m_riseOrDecline = m_risingOrDescention;
			if (totalRelease == true) {
				if (ii->m_inRange == false) {
					vehicleEraseVector.push_back(ii);
				}
			}
			else {
				vehicleEraseVector.push_back(ii);
			}
		}
		if (!vehicleEraseVector.empty()) {
			for (auto i : vehicleEraseVector) {
				sFs.vehicleSetPtr->m_vehicleSet.erase(i);
				m_endVertexPtr->vehiclePTRmanipulationInV(i);
			}
		}
	}
}