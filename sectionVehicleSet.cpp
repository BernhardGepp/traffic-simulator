#include "PrecompiledHeadersEdges.h"
#include "sectionVehicleSet.h"

//Constructor and destructor of the class:
sectionVehicleSet::sectionVehicleSet() {}
	
sectionVehicleSet::sectionVehicleSet(callBackLinks* CBLptr )
	:m_CBLptr(CBLptr){}

sectionVehicleSet::~sectionVehicleSet() noexcept {}

//********************************************************************
//Methods of the class:

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
		sumOfVehicleSpeed = i->m_pref_speed + sumOfVehicleSpeed;
		sumOfVehicles++;
	}
	return std::pair<int, int>(sumOfVehicleSpeed, sumOfVehicles);
}