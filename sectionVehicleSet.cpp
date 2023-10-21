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
int sectionVehicleSet::singleSimulationStep(const int& param, const int& length, const int& numberOfLanes, const bool& risingOrDescention, const std::shared_ptr<vertex>& endVertexPtr) {
	//Treatment of all vehicles in the edge in order to execute the simulation!
	size_t vehicleSetSize = 0;
	int maxVelocity_Density = 0;
	vehicleSetSize = getVehicleSetSize();
	size_t counter = 0;
	do {
		counter++;

		if (m_vehicleSet.size() > 0) {
			//Determination of the maximum speed from certain traffic densities!
			if ((length / m_vehicleSet.size()) >= param) {
				maxVelocity_Density = 80;
			}
			else {
				maxVelocity_Density = 140;
			}
			//The methode "flow" of the inheriting classes of the class "selectionFlow Simulation" contains the traffic flow simulation algorithm!
			m_numberOfVehicleinRange = flow(numberOfLanes, length, risingOrDescention);
		}
	} while (counter < vehicleSetSize);
	//Vehicles who reached the end of the lane will be removed of the lane by the methode "deallocateVehicleAtEnd"!
	deallocateVehicleAtEnd(true, risingOrDescention, endVertexPtr);
	return maxVelocity_Density;
}

vehicle* sectionVehicleSet::routeAssignment(vehicle* VPAEptr) {
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
void sectionVehicleSet::flow1L(const int& a, const int& b,const int& length, const bool& risingOrDescention, const std::shared_ptr<vertex>& startVertexPtr, 
	const int& endVertex, const int& numberOfLanes) {
	bool checkIfPositionIsEmpty = false;
	//************************************************************
	//Check whether the first position in the set is occupied!
	for (auto& i : m_vehicleSet) {
		i->m_riseOrDecline = risingOrDescention;
		if ((i->m_position == 0) && (risingOrDescention == true)) {
			checkIfPositionIsEmpty = true;
		}
		if ((i->m_position == length) && (risingOrDescention == false)) {
			checkIfPositionIsEmpty = true;
		}
	}
	//If the first position of the lane is not occupied, the program continues with the insertion of the vehicle objects into the lane.
	if (checkIfPositionIsEmpty == false) {
		if (startVertexPtr->m_shapeOfThatVertex == 1) {
			if (a < 150) {
				vehicle* VPAEptr = nullptr;
				VPAEptr = startVertexPtr->getVehiclePtrOutOfVertex(0, 0);
				if (VPAEptr != nullptr) {
					VPAEptr->m_routeVertexID_vehicle.clear();
					VPAEptr->m_routeID = -1;
					VPAEptr = routeAssignment(VPAEptr);
					if (VPAEptr != nullptr)
						insertSET(insertion(VPAEptr, length, numberOfLanes, risingOrDescention, true));// Inserting the vehicle objects into the set(lane)! New!
				}
			}
		}
		if ((startVertexPtr->m_shapeOfThatVertex == 0) || (startVertexPtr->m_shapeOfThatVertex == 11)) {
			insertSET(insertion(startVertexPtr->getVehiclePtrOutOfVertex(endVertex, 0),length,numberOfLanes,risingOrDescention,true));
			if ((startVertexPtr->getVertexDelay(endVertex) > 11.0f) && (numberOfLanes == 2)) {
				m_numberOfVehicleinRange++;
				insertSET(insertion(startVertexPtr->getVehiclePtrOutOfVertex(endVertex, 0), length, numberOfLanes, risingOrDescention, true));
			}
			sort();
		}
	}
}

vehicle* sectionVehicleSet::insertion(vehicle* VPAEptr, const int& length, const int& numberOfLanes, const bool& risingOrDescention, const bool& moblieORStationary) {
	//********************************************************************
	//This method is used to insert vehicle objects into the lane.
	if (VPAEptr != nullptr) {
		VPAEptr->setPtr(VPAEptr);
		VPAEptr->m_moblieORStationary = moblieORStationary;
		VPAEptr->m_riseOrDecline = risingOrDescention;
		VPAEptr->m_inRange = true;
		VPAEptr->m_processedByIteration = false;
		if (risingOrDescention == true) {
			VPAEptr->m_position = 0;
		}
		if (risingOrDescention == false) {
			VPAEptr->m_position = length;
		}
		if (numberOfLanes == 2) {
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

float sectionVehicleSet::computeAverageSpeedOfSection() {
	float averageSpeed = 0.0f;
	averageSpeed = (static_cast<float>(trafficCharacteristics().first)) / (static_cast<float>(trafficCharacteristics().second));
	return averageSpeed;
}

float sectionVehicleSet::computeTrafficDensityOfSection(const int& length) {
	float density = 0.0f;
	density= static_cast<float>(static_cast<float>(trafficCharacteristics().second) / (static_cast<float>(length) * 0.001));
	return density;
}
float sectionVehicleSet::computeWeightOfSection(const int& length) {
	float weight = 0.0f;
	weight = 1 / ((static_cast<float>(sumOfVehicleSpeedInEdge())) / (static_cast<float>(length)));
	return weight;
}

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