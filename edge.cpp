#include "PrecompiledHeadersEdges.h"
#include "edge.h"

edge::edge() = default;
edge::edge(const int& startVertex, const int& endVertex, const int& numberOfLanes, std::unique_ptr<PrintPattern>&pp_ptr,
	concreteObserverSubjekt * cOSptr)
	: m_startVertex(startVertex), m_endVertex(endVertex), m_numberOfLanes(numberOfLanes), m_ppPtr(std::move(pp_ptr)), m_cOSptr(cOSptr) {

	vehicleEraseVector.reserve(30);
	m_routeServiceBool = false;
	sFs.m_CBLptr = m_ppPtr->m_CBLptr;
	m_observerPTR = m_ppPtr->createObserver();
	m_cOSptr->registrieren(m_observerPTR);
}
edge::edge(edge && other) = default;
edge::~edge() noexcept {	}
int edge::getStartVertex() {
	return m_startVertex;
}

int edge::getEndVertex() {
	return m_endVertex;
}

void edge::sectionDestruct() {

	vehicle* vehiclePtr = nullptr;
	while (!sFs.vehicleSetPtr->m_vehicleSet.empty()) {

		vehiclePtr = *sFs.vehicleSetPtr->m_vehicleSet.begin();
		sFs.vehicleSetPtr->m_vehicleSet.erase(sFs.vehicleSetPtr->m_vehicleSet.begin());
		m_VPAptr->deallocate(vehiclePtr);
		vehiclePtr = nullptr;
	}
}

void edge::initialisation() {

	p1x = m_startVertexPtr->m_XcoordinateVertex;
	p1y = m_startVertexPtr->m_YcoordinateVertex;
	p1Shape = m_startVertexPtr->m_shapeOfThatVertex;
	p2x = m_endVertexPtr->m_XcoordinateVertex;
	p2y = m_endVertexPtr->m_YcoordinateVertex;
	p2Shape = m_endVertexPtr->m_shapeOfThatVertex;

	if (p1x == p2x) {
		m_verticalOrHorizontal = true;
		if (p1y < p2y) {
			m_risingOrDescention = true;
			m_length = p2y - p1y;

		}
		if (p1y > p2y) {
			m_risingOrDescention = false;
			m_length = p1y - p2y;

		}
	}
	if (p1y == p2y) {
		m_verticalOrHorizontal = false;
		if (p1x < p2x) {
			m_risingOrDescention = true;
			m_length = p2x - p1x;

		}
		if (p1x > p2x) {
			m_risingOrDescention = false;
			m_length = p1x - p2x;

		}
	}
	sFs.setEndingPoints(m_startVertexPtr->m_XcoordinateVertex, m_startVertexPtr->m_YcoordinateVertex, m_endVertexPtr->m_XcoordinateVertex, m_endVertexPtr->m_YcoordinateVertex, m_maxVelocity, m_maxVelocity_Density);
	m_ppPtr->accept(sFs);

}

void edge::setPoolAllocatorPtr(bbe::PoolAllocator<vehicle>&poolAllocatorRef) {
	m_VPAptr = &poolAllocatorRef;
}

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
		m_averageTravelTime = static_cast<float>(m_averageSpeed / (static_cast<float>(m_length) * 0.001));
	}
	else {
		m_averageTravelTime = static_cast<float>(static_cast<float>(m_maxVelocity) / (static_cast<float>(m_length) * 0.001));
	}
}

void edge::simiRun(const int& simulationIterator) {
	m_simulationIterator = simulationIterator;

	for (auto& i : sFs.vehicleSetPtr->m_vehicleSet) {

		i->m_riseOrDecline = m_risingOrDescention;

	}
	if (m_numberOfLanes == 1) {
		flow1L(1, 220);										//Insertion of new vehicles into the edge
		singleSimulationStep(220);							//Treatment of all vehicles in the edge according the traffic flow simulation alg.
	}
	if (m_numberOfLanes == 2) {
		flow1L(1, 440);										//Insertion of new vehicles into the edge
		singleSimulationStep(440);							//Treatment of all vehicles in the edge according the traffic flow simulation alg.
	}
	if (m_observerPTR->m_position.first > 0) {				//Possible blocking of the Link
		allocateVehicleAtPositionX();
	}
	if (simulationIterator % 10 == 0) {
		computeEdgesCharactaristics();
	}
	sFs.vehicleSetPtr->printContentOfSection(m_startVertexPtr->m_XcoordinateVertex, m_startVertexPtr->m_YcoordinateVertex, m_endVertexPtr->m_XcoordinateVertex, m_endVertexPtr->m_YcoordinateVertex);
	//Print of the simulation result
}

void edge::flow1L(const int& a, const int& b) {
	//Insertion of new vehicles into the edge
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
	if (checkIfPositionIsEmpty == false) {
		if (p1Shape == 1) {
			if (a < 150) {

				vehicle* VPAEptr = nullptr;
				VPAEptr = m_startVertexPtr->getVehiclePtrOutOfVertex(0, 0);
				if (VPAEptr != nullptr) {
					VPAEptr->m_routeVertexID_vehicle.clear();
					VPAEptr->m_routeID = -1;
					VPAEptr = routeAssignment(VPAEptr);
					sFs.vehicleSetPtr->insertSET(insertion(VPAEptr));// Inserting the vehicle objects into the set! New!
				}
			}
		}
		if ((p1Shape == 0) || (p1Shape == 11)) {
			sFs.vehicleSetPtr->insertSET(insertion(m_startVertexPtr->getVehiclePtrOutOfVertex(m_endVertex, 0)));
			sort();
		}
	}
}

void edge::singleSimulationStep(const int& param) {
	//Treatment of all vehicles in the edge
	size_t vehicleSetSize = 0;
	vehicleSetSize = sFs.vehicleSetPtr->getVehicleSetSize();
	size_t counter = 0;
	do {
		counter++;

		if (sFs.vehicleSetPtr->m_vehicleSet.size() > 0) {

			if ((m_length / sFs.vehicleSetPtr->m_vehicleSet.size()) >= param) {
				m_maxVelocity_Density = 80;
			}
			else {
				m_maxVelocity_Density = 140;
			}
			m_numberOfVehicleinRange = sFs.vehicleSetPtr->flow(m_numberOfLanes, m_length, m_risingOrDescention);

		}
	} while (counter < vehicleSetSize);
	deallocateVehicleAtEnd(true);
}

void edge::sort() {
	std::vector <vehicle*> vehicleVector;
	for (auto i : sFs.vehicleSetPtr->m_vehicleSet) {
		vehicleVector.push_back(i);
	}
	sFs.vehicleSetPtr->m_vehicleSet.clear();
	for (auto& i : vehicleVector) {
		sFs.vehicleSetPtr->m_vehicleSet.insert(i);
	}
}

vehicle* edge::routeAssignment(vehicle * VPAEptr) {
	VPAEptr->m_routeVertexID_vehicle.clear();

	if (!m_routeTable_IDrValueIDvertex.empty()) {

		if ((m_routeTableIterator >= 0) && (m_routeTableIterator < m_routeTable_IDrValueIDvertex.size())) {

		}
		else {
			m_routeTableIterator = 0;//Iterator rücksetzen!
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
			if (m_routeTableIterator > m_routeTable_IDrValueIDvertex.size()) {
				m_routeTableIterator = 0;
			}

		}
		else {
			VPAEptr->m_routeID = -1;
			VPAEptr->m_routeVertexID_vehicle.clear();
			m_routeTableIterator = 0;
		}
	}
	return VPAEptr;
}

vehicle* edge::insertion(vehicle * VPAEptr) {
	if (VPAEptr != nullptr) {
		VPAEptr->setPtr(VPAEptr);
		VPAEptr->m_moblieORStationary = true;
		VPAEptr->m_riseOrDecline = m_risingOrDescention;
		VPAEptr->m_inRange = true;
		VPAEptr->m_lane = 1;
		VPAEptr->serviceBool = false;
		if (m_risingOrDescention == true) {
			VPAEptr->m_position = 0;
		}
		if (m_risingOrDescention == false) {
			VPAEptr->m_position = m_length;
		}
		return VPAEptr;

	}
	return nullptr;
}

void edge::allocateVehicleAtPositionX() {
	//The method is executed when an edge should to be blocked at a certain position												
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
			VPAEptr->setPtr(VPAEptr);  //Setzung der ID in Vehicle
			VPAEptr->m_pref_speed = 0;
			VPAEptr->m_moblieORStationary = false;
			VPAEptr->m_position = m_observerPTR->m_position.first;
			VPAEptr->m_inRange = true;
			VPAEptr->m_riseOrDecline = m_risingOrDescention;


			if (VPAEptr != nullptr) {
				sFs.vehicleSetPtr->insertSET(VPAEptr);
			}

			sort();
			m_observerPTR->m_position.first = 0;
			m_observerPTR->m_position.second = 0;
		}
	}
}

void edge::deallocateVehicleAtEnd(bool totalRelease) {
	//This method removes vehicles from the edge, which have already passed it
	size_t a = 0;
	vehicleEraseVector.clear();
	if (!sFs.vehicleSetPtr->m_vehicleSet.empty()) {
		for (auto& ii : sFs.vehicleSetPtr->m_vehicleSet) {
			ii->serviceBool = false;
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
	else {

	}
}