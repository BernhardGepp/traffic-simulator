#include "PrecompiledHeadersEdges.h"
#include "sectionVehicleSet.h"

//Constructor and destructor of the class:
sectionVehicleSet::sectionVehicleSet() {
	vehicleEraseVector.reserve(150);
}
	
sectionVehicleSet::sectionVehicleSet(callBackLinks* CBLptr)
	:m_CBLptr(CBLptr){
	vehicleEraseVector.reserve(150);
}

sectionVehicleSet::~sectionVehicleSet() noexcept {}

//********************************************************************
//Methods of the class:

void sectionVehicleSet::sectionDestruct() {
	//****************************************************************
	//In this method the vehicles are taken out of the lane, that means out of the edge of the traffic graph.
	//The vehicle objects, which are controlled in the lane via pointer, are prepared again for a new use in 
	//the simulation by calling the method "deallocate" of the class "PoolAllocator".
	//****************************************************************
	vehicle* vehiclePtr = nullptr;
	while (!(m_vehicleSet.empty())) {

		vehiclePtr = *m_vehicleSet.begin();
		m_vehicleSet.erase(m_vehicleSet.begin());
		m_VPAptr->deallocate(vehiclePtr);
		vehiclePtr = nullptr;
	}
}

void sectionVehicleSet::insertSET(vehicle* a)
{
	if (a != nullptr) {
		m_vehicleSet.insert(a);
	}
	else {
		//std::cout << "Allocation in VehicleSet failed!\n";
	}
}

size_t sectionVehicleSet::getVehicleSetSize() const {
	return m_vehicleSet.size();
}

int sectionVehicleSet::sumOfVehicleSpeedInEdge() {
	int sumOfVehicleSpeed = 0;
	for (auto& i : m_vehicleSet) {
		sumOfVehicleSpeed = i->m_pref_speed + sumOfVehicleSpeed;
	}
	return sumOfVehicleSpeed;
}

std::pair<int, int> sectionVehicleSet::trafficCharacteristics() {
	int sumOfVehicleSpeed = 0;
	int sumOfVehicles = 0;
	for (auto& i : m_vehicleSet) {
		
		sumOfVehicleSpeed = i->m_speed + sumOfVehicleSpeed;
		sumOfVehicles++;
	}
	return std::pair<int, int>(sumOfVehicleSpeed, sumOfVehicles);
}

void sectionVehicleSet::setPoolAllocatorPtr(bbe::PoolAllocator<vehicle>& poolAllocatorRef) {
	//****************************************************************
	//This method sets the pointer that points to the "PoolAllocator" associated with the graph whose part this link is.
	m_VPAptr = &poolAllocatorRef;
}

void sectionVehicleSet::sort() {
	std::vector <vehicle*> vehicleVector;
	vehicleVector.reserve(m_vehicleSet.size() + 1);
	for (auto i : m_vehicleSet) {
		if (i != nullptr) {
			if ((i->m_lane > 0) && (i->m_ID_ptr != nullptr))
				vehicleVector.emplace_back(i);
		}
	}
	m_vehicleSet.clear();
	for (auto& i : vehicleVector) {
		m_vehicleSet.insert(i);
	}
}

void sectionVehicleSet::deallocateVehicleAtEnd(const bool& totalRelease, const bool& risingOrDescention, std::shared_ptr<vertex> endVertexPtr) {
	//********************************************************************
	//This method removes vehicles from the edge, which have already passed it
	size_t a = 0;
	vehicleEraseVector.clear();
	if (!m_vehicleSet.empty()) {
		for (auto& ii : m_vehicleSet) {
			ii->m_processedByIteration = false;
			ii->m_riseOrDecline = risingOrDescention;
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
				m_vehicleSet.erase(i);
				endVertexPtr->vehiclePTRmanipulationInV(i);
			}
		}
	}
}