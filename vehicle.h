#pragma once
#include "PrecompiledHeadersEdges.h"
class vehicle {
private:
public:
	vehicle* m_ID_ptr = nullptr;
	int m_routeID = -1;
	std::vector<int>m_routeVertexID_vehicle;
	int m_lane = 1;
	int m_position = 0;
	int m_pref_speed = 0;
	bool m_inRange = true;
	bool serviceBool = false;
	bool processedByIteration = true;
	bool m_riseOrDecline = true;
	bool m_moblieORStationary = true;
	


	vehicle();
	explicit vehicle( const int& lane, const int& position);
	vehicle(const vehicle& other) = delete;
	vehicle(const vehicle&& other) = delete;
	vehicle& operator=(const vehicle& other) = delete;
	vehicle& operator=(const vehicle&& other) = delete;
	~vehicle()noexcept ;
	
	void setPtr(vehicle* vehiclePtr);
	bool operator<(const vehicle& l) const;
	int position() const;

};

