#pragma once
#include "PrecompiledHeadersEdges.h"
#include"vehicle.h"
#include "random_speed_neu.h"
#include "callBackLinks.h"

class sectionVehicleSet 
{
private:
public:
	unsigned int m_sumOfVehicleSpeed = 0;
	callBackLinks* m_CBLptr = nullptr;
	std::set<vehicle*, boost::indirect_fun<std::less<vehicle>>>m_vehicleSet;
	
	explicit sectionVehicleSet();
	explicit sectionVehicleSet(callBackLinks* CBLptr);
	sectionVehicleSet::sectionVehicleSet(const sectionVehicleSet& other) = delete;
	sectionVehicleSet::sectionVehicleSet(const sectionVehicleSet&& other) = delete;
	sectionVehicleSet& operator=(const sectionVehicleSet& other) = delete;
	sectionVehicleSet& operator=(const sectionVehicleSet&& other) = delete;
	~sectionVehicleSet() noexcept;

	

	virtual int sectionVehicleSet::flow(const int &numberOfLanes,
		const int &length,
		const bool &riseOrDecline) = 0;

	void insertSET(vehicle* a);
	size_t getVehicleSetSize() const;
	int sumOfVehicleSpeedInEdge();
	std::pair<int, int> trafficCharacteristics();
};

