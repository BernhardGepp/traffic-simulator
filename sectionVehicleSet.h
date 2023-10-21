#pragma once
#include "random_speed_neu.h"
#include "callBackLinks.h"

class sectionVehicleSet 
{
private:
	bbe::PoolAllocator<vehicle>* m_VPAptr = nullptr; //Pointer auf den Poolallocator
	size_t m_routeTableIterator = 0;
	bool m_routeServiceBool = false;
	int m_numberOfVehicleinRange = 0;
	
public:
	unsigned int m_sumOfVehicleSpeed = 0;
	callBackLinks* m_CBLptr = nullptr;
	std::set<vehicle*, boost::indirect_fun<std::less<vehicle>>>m_vehicleSet;
	std::vector<vehicle*> vehicleEraseVector;
	std::vector<std::pair<std::pair<int, float>, std::vector<int>>> m_routeTable_IDrValueIDvertex;
	
	explicit sectionVehicleSet();
	explicit sectionVehicleSet(callBackLinks* CBLptr);
	sectionVehicleSet::sectionVehicleSet(const sectionVehicleSet& other) = delete;
	sectionVehicleSet::sectionVehicleSet(const sectionVehicleSet&& other) = delete;
	sectionVehicleSet& operator=(const sectionVehicleSet& other) = delete;
	sectionVehicleSet& operator=(const sectionVehicleSet&& other) = delete;
	~sectionVehicleSet() noexcept;

	virtual int sectionVehicleSet::flow(const int&, const int&, const bool&) = 0;
	void insertSET(vehicle* a);
	size_t getVehicleSetSize() const;
	int sumOfVehicleSpeedInEdge();
	std::pair<int, int> trafficCharacteristics();
	void sectionVehicleSet::setPoolAllocatorPtr(bbe::PoolAllocator<vehicle>&);
	void sort();
	void deallocateVehicleAtEnd(const bool&, const bool&, std::shared_ptr<vertex>);
	void sectionDestruct();
	float computeWeightOfSection(const int&);
	float computeTrafficDensityOfSection(const int&);
	float computeAverageSpeedOfSection();
	vehicle* routeAssignment(vehicle*);
	void flow1L(const int&, const int&, const int&, const bool&, const std::shared_ptr<vertex>&, const int&, const int&);
	vehicle* insertion(vehicle*, const int&, const int&, const bool&, const bool&);
	int singleSimulationStep(const int&, const int&, const int&, const bool&, const std::shared_ptr<vertex>&);
};

