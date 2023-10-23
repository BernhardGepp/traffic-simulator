#include "PrecompiledHeadersEdges.h"
#include "flowSimulation1PosStraight.h"

//Constructor
flowSimulation1PosStraight::flowSimulation1PosStraight(callBackLinks* CBLptr, const int& maxVelocity, const int& maxVelocity_Density)
	:sectionVehicleSet(CBLptr), m_maxVelocity(maxVelocity), m_maxVelocity_Density(maxVelocity_Density) {
	m_CBLptr = CBLptr;
}

//Constructor used for unittest
flowSimulation1PosStraight::flowSimulation1PosStraight(const int& maxVelocity, const int& maxVelocity_Density)
	: sectionVehicleSet(), m_maxVelocity(maxVelocity), m_maxVelocity_Density(maxVelocity_Density) {
}

flowSimulation1PosStraight::~flowSimulation1PosStraight() noexcept {}

//********************************************************************
//Traffic flow algorithm for one directional lane in positive direction:
int flowSimulation1PosStraight::flow(const int& numberOfLanes, const int& length, const bool& riseOrDecline) {
	//********************************************************************
	//Traffic flow simulation algorithm for connections with one lane in ascending direction
	
	flag = false;
	ownSpeed = 0;
	speedAheadVehicleAt1L = 0;
	positionAheadVehicleAt1L = 0;
	numberOfVehicleinRange = 0;
	if (riseOrDecline) {
		numberOfVehicleinRange = 0;
		std::set<vehicle*>::reverse_iterator ii = m_vehicleSet.rbegin();
		vehicle* i = nullptr;
		for(ii = m_vehicleSet.rbegin(); ii != m_vehicleSet.rend(); ++ii){
			i = *ii;
			if (i->m_position > length) {
				i->m_inRange = false;
				i->m_processedByIteration = true;
			}
			//Determination of the velocity of the vehicle objects as a reference variable, which is used to determine the changes in the relevant variables.
			if (i->m_pref_speed <= 0){
				if (i->m_moblieORStationary){
					if (m_CBLptr->m_callback_getRandomNumber == nullptr) {
						ownSpeed = 100;
					}
					else {
						ownSpeed = m_CBLptr->m_callback_getRandomNumber();
					}
				}
				else {
					ownSpeed = 0;
					i->m_pref_speed = 0;
				}
			}
			else {
				if (i->m_moblieORStationary) {
					if (i->m_pref_speed < 50) {
						ownSpeed = (i->m_pref_speed) + 30;
					}
					if (i->m_pref_speed >= 50) {
						ownSpeed = i->m_pref_speed;
					}
				}
				else {
					i->m_pref_speed = 0;
					ownSpeed = 0;
				}
			}//**************************************************
			//In the following section, changes in the positions and velocities of the vehicle objects are determined. This section forms the core of the simulation.
			if ((flag == false) && (i->m_ID_ptr!=nullptr) && (i->m_inRange == true) && (m_vehicleSet.size() >= 1)) {
				if (i->m_processedByIteration == false) {
					flag = true;
					//Vehicles outside the range are not observed
					if ((i->m_position > length) || (i->m_position < -3)) {
						i->m_inRange = false;
						i->m_position = length + 50;
						//i->m_speed = 0;
						i->m_pref_speed = 0;
					}
					else {
						//For vehicles within the range, a distinction is made between vehicles that are newly inserted into the lane and those that are already present.
						i->m_processedByIteration = true;
						if (i->m_position <= 0) {	
							if ((speedAheadVehicleAt1L > 0) && (speedAheadVehicleAt1L <= ownSpeed)) {
								ownSpeed = speedAheadVehicleAt1L;
							}
							if (ownSpeed > m_maxVelocity) {
								ownSpeed = m_maxVelocity;
							}
							if (ownSpeed > m_maxVelocity_Density) {
								ownSpeed = m_maxVelocity_Density;
							}

							if ((speedAheadVehicleAt1L == 0) && (m_vehicleSet.size() >= 1)) {
								i->m_pref_speed = ownSpeed;
								if (i->m_position <= (i->m_position + VL.VLStepConversion(ownSpeed))) {
									i->m_position = i->m_position + VL.VLStepConversion(ownSpeed);
								}
							}
							if (VL.VLStepConversion(ownSpeed) < positionAheadVehicleAt1L) {
								if (i->m_position <= (i->m_position + VL.VLStepConversion(ownSpeed))) {
									i->m_position = i->m_position + VL.VLStepConversion(ownSpeed);
								}
								i->m_pref_speed = ownSpeed;
							}
							if ((VL.VLStepConversion(ownSpeed) >= positionAheadVehicleAt1L) && (0 < positionAheadVehicleAt1L)) {
								if (i->m_position <= positionAheadVehicleAt1L) {
									i->m_position = (positionAheadVehicleAt1L - 2);
								}
								i->m_pref_speed = ownSpeed;
							}
						}
						else {//m_postiion >0 && m_postion<length	
							if ((speedAheadVehicleAt1L > 0) && (speedAheadVehicleAt1L >= ownSpeed)) {
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
							if ((i->m_position >= (length - 30))&&(ownSpeed>0)) {
								ownSpeed = 30;
							}

							if (i->m_moblieORStationary == false) {
								ownSpeed = 0;
								i->m_pref_speed = 0;
								speedAheadVehicleAt1L = 0;
							}
								
							if (i->m_moblieORStationary == true) {
								i->m_pref_speed = ownSpeed + 1;
								if (positionAheadVehicleAt1L <= 0) {
									i->m_position = (i->m_position) + VL.VLStepConversion(ownSpeed);
								}
								else {
									if (positionAheadVehicleAt1L > (i->m_position + VL.VLStepConversion(ownSpeed))) {
										i->m_position = (i->m_position) + VL.VLStepConversion(ownSpeed);
									}
									else if (positionAheadVehicleAt1L == (i->m_position + VL.VLStepConversion(ownSpeed))) {
										ownSpeed = speedAheadVehicleAt1L - 5;
										i->m_position = (i->m_position + VL.VLStepConversion(ownSpeed));
										if (ownSpeed <= 0) {
											if (i->m_position <= (positionAheadVehicleAt1L - 1)) {
												i->m_position = positionAheadVehicleAt1L - 1;
											}
											i->m_pref_speed = 0;
											ownSpeed = 0;
										}
									}
									else if (positionAheadVehicleAt1L > i->m_position) {
										if (i->m_position <= (positionAheadVehicleAt1L - 1)) {
											i->m_position = positionAheadVehicleAt1L - 1;
										}
										i->m_pref_speed = 0;
									}
									else if (positionAheadVehicleAt1L < ((i->m_position) + VL.VLStepConversion(ownSpeed))) {
										if (positionAheadVehicleAt1L > i->m_position) {
											if (i->m_position <= (positionAheadVehicleAt1L - 1)) {
												i->m_position = positionAheadVehicleAt1L - 1;
											}
										}
										i->m_position = positionAheadVehicleAt1L - 2;
										ownSpeed = speedAheadVehicleAt1L;
									}
									else if (positionAheadVehicleAt1L < i->m_position) {
											i->m_position = positionAheadVehicleAt1L - 1;
									}
								}
							}
							else {
								ownSpeed = 0;
							}
						}
					}
				}
			}
			//After completion of the simulation iteration, the position as well as the velocity of the treated vehicle object are written into variables to be available as a comparison value for the next iteration.
			if ((i->m_ID_ptr != nullptr) && (m_vehicleSet.size() >= 1)) {
				if ((i->m_position >= length) || (i->m_position < -3)) {
					i->m_inRange = false;
				}
				else {
					if (i->m_moblieORStationary == true) {
						speedAheadVehicleAt1L = i->m_pref_speed;
					}
					else {
						speedAheadVehicleAt1L = 0;
					}
					positionAheadVehicleAt1L = i->m_position;
					i->m_speed = i->m_pref_speed;
					numberOfVehicleinRange++;
				}
			}
		}
	}
	return numberOfVehicleinRange;
}
