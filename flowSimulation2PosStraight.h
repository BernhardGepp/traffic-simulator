#pragma once
#include "sectionVehicleSet.h"
#include "velocityToLength.h"
#include "PrintInGDIplusWin2LP.h"

class flowSimulation2PosStraightA: public sectionVehicleSet {
private:
public:
	velocityToLength VL;
	bool flag = false;
	int ownSpeed = 0;
	int laneAheadVehicle = 0;
	int speedAheadVehicleAt1L = 0;
	int positionAheadVehicleAt1L = 0;
	int speedAheadVehicleAt2L = 0;
	int positionAheadVehicleAt2L = 0;
	int numberOfVehicleinRange = 0;
	int m_maxVelocity = 0;
	int m_maxVelocity_Density = 0;
	
	flowSimulation2PosStraightA(callBackLinks* CBLptr, const int& maxVelocity, const int& maxVelocity_Density);
	flowSimulation2PosStraightA(const flowSimulation2PosStraightA &other)=delete; 
	flowSimulation2PosStraightA& operator=(const flowSimulation2PosStraightA& other)=delete; 
	flowSimulation2PosStraightA(const flowSimulation2PosStraightA &&other)=delete; 
	flowSimulation2PosStraightA& operator=(const flowSimulation2PosStraightA&& other)=delete; 
	~flowSimulation2PosStraightA()noexcept;
	
	int flow(const int& , const int& , const bool& )override;
};

	
	
	
	


