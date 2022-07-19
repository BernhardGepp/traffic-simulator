#pragma once
#include "sectionVehicleSet.h"
#include "velocityToLength.h"
#include "PrintInGDIplusWin2LN.h"
#include "PrecompiledHeadersEdges.h"
static int hilfezahlerzuio;
class flowSimulation2NegStraight : public sectionVehicleSet{
private:
	PrintInGDIplusWin2LN m_P2LN;
public:
	std::string textaa = "C:/Users/bernh/Desktop/flow2N" + std::to_string(hilfezahlerzuio) + ".txt";
	std::ofstream file5;
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
	
	explicit flowSimulation2NegStraight(callBackLinks* CBLptr, const int& maxVelocity, const int& maxVelocity_Density);
	flowSimulation2NegStraight::flowSimulation2NegStraight(const flowSimulation2NegStraight &other) = delete; 	
	flowSimulation2NegStraight& operator=(const flowSimulation2NegStraight& other) = delete; 
	flowSimulation2NegStraight::flowSimulation2NegStraight(const flowSimulation2NegStraight &&other) = delete; 
	flowSimulation2NegStraight& operator=(const flowSimulation2NegStraight&& other) = delete; 
	~flowSimulation2NegStraight() noexcept;

	void printContentOfSection(const int&, const int&, const int&, const int&) override;
	int flow(const int&, const int&, const bool&) override;
};