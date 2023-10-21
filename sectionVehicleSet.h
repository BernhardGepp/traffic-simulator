#pragma once
#include "random_speed_neu.h"
#include "callBackLinks.h"

class sectionVehicleSet 
{
private:
	bbe::PoolAllocator<vehicle>* m_VPAptr = nullptr; //Pointer auf den Poolallocator
public:
	unsigned int m_sumOfVehicleSpeed = 0;
	callBackLinks* m_CBLptr = nullptr;
	std::set<vehicle*, boost::indirect_fun<std::less<vehicle>>>m_vehicleSet;
	std::vector<vehicle*> vehicleEraseVector;
	
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
	void sectionVehicleSet::setPoolAllocatorPtr(bbe::PoolAllocator<vehicle>& poolAllocatorRef);
	void sort();
	void deallocateVehicleAtEnd(const bool&, const bool&, std::shared_ptr<vertex> m_endVertexPtr);
	void sectionDestruct();
	float computeWeightOfSection(const int&);
	float computeTrafficDensityOfSection(const int&);
	float computeAverageSpeedOfSection();
};

