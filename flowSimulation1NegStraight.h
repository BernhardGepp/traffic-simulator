#pragma once
#include "sectionVehicleSet.h"
#include "velocityToLength.h"
#include "PrintInGDIplusWin1LN.h"

class flowSimulation1NegStraight : public sectionVehicleSet {
private:
public:
	velocityToLength VL;
	bool flag = false;
	int ownSpeed = 0;
	int speedAheadVehicleAt1L = 0;
	int positionAheadVehicleAt1L = 0;
	int numberOfVehicleinRange = 0;
	int m_maxVelocity = 0;
	int m_maxVelocity_Density = 0;

	//Constructor
	explicit flowSimulation1NegStraight(callBackLinks* CBLptr, const int& maxVelocity, const int& maxVelocity_Density);
	//Constructor used for unittest
	explicit flowSimulation1NegStraight(const int& maxVelocity, const int& maxVelocity_Density);

	flowSimulation1NegStraight::flowSimulation1NegStraight(const flowSimulation1NegStraight &other) = delete;
	flowSimulation1NegStraight& operator=(const flowSimulation1NegStraight& other) = delete;
	flowSimulation1NegStraight::flowSimulation1NegStraight(const flowSimulation1NegStraight &&other) = delete;
	flowSimulation1NegStraight& operator=(const flowSimulation1NegStraight&& other) = delete;
	~flowSimulation1NegStraight() noexcept;

	int flow(const int&, const int&, const bool&)override;
};