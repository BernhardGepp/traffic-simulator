#pragma once
#include "PrecompiledHeadersEdges.h"
#include"vehicle.h"

#include "random_speed_neu.h"

class sectionVehicleSet 
{
private:	
	
public:
	void(*m_f6PrintLaneInNumbers)(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV) = nullptr;
	std::set<vehicle*, boost::indirect_fun<std::less<vehicle>>>m_vehicleSet;
	int(*m_callback_getRandomNumber)() = nullptr;
	HDC m_hdc; 
	
	explicit sectionVehicleSet::sectionVehicleSet() {

	}
	
	explicit sectionVehicleSet::sectionVehicleSet(int(*callback_getRandomNumber)(),HDC hdc)
		:m_callback_getRandomNumber(callback_getRandomNumber),m_hdc(hdc) {
		
	}
	sectionVehicleSet::~sectionVehicleSet() {
		
	}
	
	sectionVehicleSet::sectionVehicleSet(const sectionVehicleSet&& other) = delete;
	virtual void sectionVehicleSet::printContentOfSection(const int& p1xx, const int& p1yy,
		const int& p2xx, const int& p2yy) = 0;

	virtual int sectionVehicleSet::flow(const int &numberOfLanes,
		const int &length,
		const bool &riseOrDecline) = 0;

	void sectionVehicleSet::insertSET(vehicle* a)
	{
		if (a != nullptr) {
			m_vehicleSet.insert(a);
			
		}
		else {
			
		}
	}
	
	size_t sectionVehicleSet::getVehicleSetSize() const {

		return m_vehicleSet.size();

	}	

	
	int sectionVehicleSet::sumOfVehicleSpeedInEdge() {
		int sumOfVehicleSpeed = 0;
		for (auto &i : m_vehicleSet) {
			sumOfVehicleSpeed = i->m_pref_speed + sumOfVehicleSpeed;
		}
		return sumOfVehicleSpeed;
	}
	std::pair<int, int> sectionVehicleSet::trafficCharacteristics() {
		int sumOfVehicleSpeed = 0;
		int sumOfVehicles = 0;
		for (auto &i : m_vehicleSet) {
			sumOfVehicleSpeed = i->m_pref_speed + sumOfVehicleSpeed;
			sumOfVehicles++;
		}
		return std::pair<int, int>(sumOfVehicleSpeed, sumOfVehicles);
	}
};

