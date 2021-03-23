#pragma once
#include "sectionVehicleSet.h"
#include "velocityToLength.h"
#include "PrecompiledHeadersEdges.h"
#include "PrintInGDIplusWin1LP.h"
class flowSimulation1PosStraight : public sectionVehicleSet {
private:
	PrintInGDIplusWin1LP m_P1LP;
public:
	void(*m_f6PrintLaneInNumbers)(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV) = nullptr;
	velocityToLength VL;
	bool flag = false;
	int ownSpeed = 0;
	int ownPosition = 0;
	int speedAheadVehicleAt1L = 0;
	int positionAheadVehicleAt1L = 0;

	int numberOfVehicleinRange = 0;
	int m_maxVelocity = 0;
	int m_maxVelocity_Density = 0;
	int(*m_callback_getRandomNumber)() = nullptr;
	HDC m_hdc1;

	explicit flowSimulation1PosStraight::flowSimulation1PosStraight(int(*callback_getRandomNumber)(),
		void(*f6PrintLaneInNumbers)(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV),
		HDC hdc,
		const int& maxVelocity,
		const int& maxVelocity_Density)
		:sectionVehicleSet(callback_getRandomNumber,hdc), 
		m_callback_getRandomNumber(callback_getRandomNumber), 
		m_f6PrintLaneInNumbers(f6PrintLaneInNumbers),
		m_hdc1(hdc),
		m_maxVelocity(maxVelocity),
		m_maxVelocity_Density(maxVelocity_Density){

	}
	flowSimulation1PosStraight::flowSimulation1PosStraight(const flowSimulation1PosStraight &other) = delete; 
	flowSimulation1PosStraight& operator=(flowSimulation1PosStraight& other) = delete; 
	flowSimulation1PosStraight::flowSimulation1PosStraight(const flowSimulation1PosStraight &&other) = delete; 
	flowSimulation1PosStraight& operator=(flowSimulation1PosStraight&& other) = delete; 
	flowSimulation1PosStraight::~flowSimulation1PosStraight() {

	}
	void flowSimulation1PosStraight::printContentOfSection(const int& p1xx, const int& p1yy,
		const int& p2xx, const int& p2yy) override {
		
		for (auto &i : m_vehicleSet) {
			i->serviceBool = false;
			if (!i->m_routeVertexID_vehicle.empty()) {
				m_P1LP.addPrintContent(p1xx, p1yy, p2xx, p2yy, 1, i->m_position, i->m_routeVertexID_vehicle.back());
			}
			
		}
		
	}
	int flowSimulation1PosStraight::flow(const int &numberOfLanes,
		const int &length,
		const bool &riseOrDecline)override {
		
		flag = false;
		ownSpeed = 0;
		ownPosition = 0;
		speedAheadVehicleAt1L = 0;
		positionAheadVehicleAt1L = 0;
		numberOfVehicleinRange = 0;
		if (riseOrDecline == true) {
			numberOfVehicleinRange = 0;
			//********************************************
			for (auto &i : m_vehicleSet) {
				
				
				if (i->m_pref_speed <= 0)
				{
					if (i->m_moblieORStationary == false)
					{
						ownSpeed = 0;
					}
					else {

						ownSpeed = m_callback_getRandomNumber();
					}
				}
				else {
					if (i->m_moblieORStationary == true) {
						if (i->m_pref_speed < 50) {
							ownSpeed = (i->m_pref_speed) + 30;
						}
						else {
							ownSpeed = i->m_pref_speed;
						}
					}
				}
				if ((flag == false) && (length > 0) && ((i->m_inRange) == true) && ((i->processedByIteration) == true)) {
					if (i->serviceBool == false) {
						flag = true;
						i->serviceBool = true;
						if ((i->m_position > length) || (i->m_position < 0)) {
							i->m_inRange = false;
						}
						else {
							if (i->m_position == 0) {
								if ((speedAheadVehicleAt1L > 0) && (speedAheadVehicleAt1L <= ownSpeed)) {
									ownSpeed = speedAheadVehicleAt1L;
								}
								if (ownSpeed > m_maxVelocity) {
									ownSpeed = m_maxVelocity;
								}
								if (ownSpeed > m_maxVelocity_Density) {
									ownSpeed = m_maxVelocity_Density;
								}
								ownPosition = VL.VLStepConversion(ownSpeed);
								//ownPosition = VLStepConversion(ownSpeed);
								i->m_pref_speed = ownSpeed;
								if ((positionAheadVehicleAt1L == 0) || (ownPosition < positionAheadVehicleAt1L)) {
									if (ownPosition >= i->m_position) {
										i->m_position = ownPosition;
									}
									else {

									}
								}
								if ((positionAheadVehicleAt1L > 0) && (ownPosition >= positionAheadVehicleAt1L)) {
									if ((ownPosition - 1) >= i->m_position) {
										i->m_position = (ownPosition - 1);
									}
									else {

									}
								}
							}
							else {//m_postiion >0 && m_postion<length									  
								if ((speedAheadVehicleAt1L > 0) && (speedAheadVehicleAt1L <= ownSpeed)) {
									if ((speedAheadVehicleAt1L - ownSpeed) > 20) {
										if (i->m_moblieORStationary == true) {
											ownSpeed += 21;
										}
									}
									else if ((speedAheadVehicleAt1L - ownSpeed) > 10) {
										if (i->m_moblieORStationary == true) {
											ownSpeed += 11;
										}
									}
									else if ((speedAheadVehicleAt1L - ownSpeed) >= 1) {
										if (i->m_moblieORStationary == true) {
											ownSpeed += 2;
										}
									}
								}
								if (ownSpeed > m_maxVelocity) {
									ownSpeed = m_maxVelocity;
								}
								if (ownSpeed > m_maxVelocity_Density) {
									ownSpeed = m_maxVelocity_Density;
								}
								ownPosition = VL.VLStepConversion(ownSpeed);
								
								//i->m_pref_speed = ownSpeed;
								if (positionAheadVehicleAt1L <= 0) {
									if (i->m_moblieORStationary == true) {
										i->m_position = (i->m_position) + ownPosition;
										i->m_pref_speed = ownSpeed;
									}
								}
								else {
									if (positionAheadVehicleAt1L > ((i->m_position) + ownPosition)) {
										if (i->m_moblieORStationary == true) {
											i->m_position = (i->m_position) + ownPosition;
											i->m_pref_speed = ownSpeed;
										}
									}
									if (positionAheadVehicleAt1L == ((i->m_position) + ownPosition)) {
										if (i->m_moblieORStationary == true) {
											ownSpeed = speedAheadVehicleAt1L - 5;
											if (ownSpeed <= 0) {
												ownSpeed = 0;
											}
											i->m_position = ((i->m_position) + VL.VLStepConversion(ownSpeed));
											i->m_pref_speed = ownSpeed;
										}
									}
									if (positionAheadVehicleAt1L < ((i->m_position) + ownPosition)) {
										if (i->m_moblieORStationary == true) {
											if ((positionAheadVehicleAt1L - 3) >= i->m_position) {
												i->m_position = positionAheadVehicleAt1L - 3;
											}
											else {

											}
											ownSpeed = speedAheadVehicleAt1L - 5;
											if (ownSpeed <= 0) {
												ownSpeed = 0;
											}
											i->m_pref_speed = ownSpeed;
										}
									}
								}
							}
							//i->m_sectionID = sectionID;
							//i->m_lane = lane;
						}
					}
				}
				
				if ((i->m_position > length) || (i->m_position < 0)) {
					i->m_inRange = false;
				}
				else {
					speedAheadVehicleAt1L = i->m_pref_speed;
					positionAheadVehicleAt1L = i->m_position;
				}
			}
		}
		return numberOfVehicleinRange;
	}
};
