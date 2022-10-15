#pragma once
#include "sectionVehicleSet.h"
#include "velocityToLength.h"
#include "PrintInGDIplusWin1LN.h"
#include "PrecompiledHeadersEdges.h"

class flowSimulation1NegStraight : public sectionVehicleSet {
private:
	PrintInGDIplusWin1LN m_P1LN;
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

	void printContentOfSection(const int&, const int&, const int&, const int&) override;
	int flow(const int&, const int&, const bool&)override;
};