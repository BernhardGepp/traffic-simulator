#pragma once
#include "sectionVehicleSet.h"
#include "velocityToLength.h"
#include "PrecompiledHeadersEdges.h"
#include "PrintInGDIplusWin1LP.h"

class flowSimulation1PosStraight : public sectionVehicleSet {
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
	explicit flowSimulation1PosStraight(callBackLinks* CBLptr, const int& maxVelocity, const int& maxVelocity_Density);
		
	//Constructor used for unittest
	explicit flowSimulation1PosStraight(const int& maxVelocity, const int& maxVelocity_Density);

	flowSimulation1PosStraight::flowSimulation1PosStraight(const flowSimulation1PosStraight &other) = delete; 
	flowSimulation1PosStraight& operator=(const flowSimulation1PosStraight& other) = delete; 
	flowSimulation1PosStraight::flowSimulation1PosStraight(const flowSimulation1PosStraight &&other) = delete; 
	flowSimulation1PosStraight& operator=(const flowSimulation1PosStraight&& other) = delete; 
	flowSimulation1PosStraight::~flowSimulation1PosStraight() noexcept;

	
	int flow(const int&, const int&, const bool&)override; 
};