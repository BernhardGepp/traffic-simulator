#include "PrecompiledHeadersEdges.h"
#include "vehicle.h"

//Constructor and destructor of the class:
vehicle::vehicle() {
	m_routeVertexID_vehicle.reserve(10);
	m_routeVertexID_vehicle.clear();
}
vehicle::vehicle(const int& lane, const int& position)
	: m_lane(lane), m_position(position) {
	m_routeVertexID_vehicle.reserve(10);
	m_routeVertexID_vehicle.clear();
}
vehicle::~vehicle() noexcept{
	m_routeVertexID_vehicle.clear();
}

//********************************************************************
//Methods of the class:

int vehicle::position()const {
	return m_position;
}
bool vehicle::operator<(const vehicle& l) const
{
	if (m_riseOrDecline) {
		return (position() < l.position());
	}
	else {
		return (position() > l.position());
	}
}
void vehicle::setPtr(vehicle* vehiclePtr) {
	m_ID_ptr = vehiclePtr;
}

