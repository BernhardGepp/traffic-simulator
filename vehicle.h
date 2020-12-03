#pragma once
#include "PrecompiledHeadersEdges.h"

//#include "route.h"  // Wenn hier eine route deklariert wird, dickt das Programm völlig aus!! Warum?
class vehicle {
private:
	//vehicle* m_ID_ptr = nullptr;


	//static int numberOfVehicleConstructorActivations;
public:
	vehicle* m_ID_ptr = nullptr;
	//route* m_routeID_ptr = nullptr; // Wenn hier eine route deklariert wird, dickt das Programm völlig aus!! Warum?
	//route& m_routeID_ref;
	//std::shared_ptr<route>m_routeID_ptr;
	int m_routeID = -1;
	std::vector<int>m_routeVertexID_vehicle;
	

	//int m_sectionID = 0;
	int m_lane = 1;
	int m_position = 0;
	//int m_expectedSpeed = 100;   ??
	int m_pref_speed = 0;
	bool m_inRange = true;
	bool serviceBool = false;
	bool processedByIteration = true;
	bool m_riseOrDecline = true;
	bool m_moblieORStationary = true;
	


	vehicle();
	explicit vehicle( int lane, int position);
	void setPtr(vehicle* vehiclePtr);
	~vehicle();
	//static bool sortByPosition(vehicle a, vehicle b);

	bool operator<(const vehicle& l) const;

	int position() const;

};

