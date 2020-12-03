#include "PrecompiledHeadersEdges.h"
#include "vehicle.h"
//#pragma once


vehicle::vehicle() {
	
	m_routeVertexID_vehicle.reserve(5);
	m_routeVertexID_vehicle.clear();
}

vehicle::vehicle(int lane, int position)
	: m_lane(lane), m_position(position) {
	m_routeVertexID_vehicle.reserve(5);
	m_routeVertexID_vehicle.clear();
	
}
void vehicle::setPtr(vehicle* vehiclePtr) {
	/*if (m_ID_ptr == nullptr) {
		m_ID_ptr = vehiclePtr;
	}*/
	m_ID_ptr = vehiclePtr;
}

vehicle::~vehicle() {
	m_routeVertexID_vehicle.clear();
}



int vehicle::position()const {
	return m_position;
}

bool vehicle::operator<(const vehicle& l) const
{
	bool schau = true;
	if (m_riseOrDecline == true) {
		schau = (position() > l.position());
	}
	else {
		
		schau = (position() < l.position());
	}
	
	return schau;
}

