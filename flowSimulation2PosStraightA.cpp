#include "PrecompiledHeadersEdges.h"
#include "flowSimulation2PosStraight.h"

//Constructor and destructor of the class:
flowSimulation2PosStraightA::flowSimulation2PosStraightA(callBackLinks* CBLptr, const int& maxVelocity, const int& maxVelocity_Density)
	:sectionVehicleSet(CBLptr), m_maxVelocity(maxVelocity), m_maxVelocity_Density(maxVelocity_Density) {
	m_CBLptr = CBLptr;
}
flowSimulation2PosStraightA::~flowSimulation2PosStraightA()noexcept {}

//********************************************************************
//Traffic flow algorithm for two directional lanes in postive direction:
int flowSimulation2PosStraightA::flow(const int& numberOfLanes, const int& length, const bool& riseOrDecline) {
	//********************************************************************
	//Traffic flow simulation algorithm for connections with two lanes in ascending direction
	int serviceInt = 0;
	flag = false;
	ownSpeed = 0;
	//ownPosition = 0;
	speedAheadVehicleAt1L = 0;
	positionAheadVehicleAt1L = 0;
	speedAheadVehicleAt2L = 0;
	positionAheadVehicleAt2L = 0;
	std::set<vehicle*>::reverse_iterator ii = m_vehicleSet.rbegin();
	vehicle* i = nullptr;
	if (riseOrDecline && (length>0)) {
		numberOfVehicleinRange = 0;
		for (ii = m_vehicleSet.rbegin(); ii != m_vehicleSet.rend(); ++ii) {
			i = *ii;
			if (i->m_position > length) {
				i->m_inRange = false;
				i->m_processedByIteration = true;
			}
			//Determination of the velocity of the vehicle objects as a reference variable, which is used to determine the changes in the relevant variables.
			if (i->m_moblieORStationary == true) {
				//ownPosition = i->m_position;
				if (i->m_pref_speed <= 0) {
					if (m_CBLptr->m_callback_getRandomNumber == nullptr) {
						ownSpeed = 0;
					}
					else {
						ownSpeed = m_CBLptr->m_callback_getRandomNumber();
					}
				}
				else {
					
					if (i->m_pref_speed < 50) {
						ownSpeed = (i->m_pref_speed) + 30;
					}
					else if ((i->m_pref_speed >= 50) && (i->m_pref_speed < 60)) {
						ownSpeed = (i->m_pref_speed) + 20;
					}
					else if ((i->m_pref_speed >= 60) && (i->m_pref_speed < 100)) {
						ownSpeed = (i->m_pref_speed) + 10;
					}
					else {
						ownSpeed = i->m_pref_speed;
					}
				}
			}
			else {
				ownSpeed = 0;
				i->m_pref_speed = 0;
			}
			//Determination of the position of the vehicles ahead
			serviceInt = 0;
			if (((laneAheadVehicle == 1) && (i->m_lane == 2)) || ((laneAheadVehicle == 2) && (i->m_lane == 1))) {
				for (auto& j : m_vehicleSet) {

					if ((laneAheadVehicle == 1) && (j->m_lane == 1) && (i->m_lane == 2) && (j->m_position < i->m_position) && (i->m_position < serviceInt)) {
						serviceInt = j->m_position;
					}
					if ((laneAheadVehicle == 2) && (j->m_lane == 1) && (i->m_lane == 1) && (j->m_position < i->m_position) && (i->m_position < serviceInt)) {
						serviceInt = j->m_position;
					}
				}
				if (laneAheadVehicle == 1)
					speedAheadVehicleAt2L = serviceInt;
				if (laneAheadVehicle == 2)
					speedAheadVehicleAt1L = serviceInt;
			}
			serviceInt = 0;
			for (auto& j : m_vehicleSet) {
				if (j->m_ID_ptr == i->m_ID_ptr)
					serviceInt++;
			}
			//Removal of vehicle objects from the section in case of multiple entry
			if (serviceInt > 1) {
				ownSpeed = 10000;
				i->m_routeVertexID_vehicle.clear();
				vehicle* additionalVPointer = nullptr;
				do {
					if (ii != m_vehicleSet.rend()) {
						additionalVPointer = i;
						m_vehicleSet.erase(std::next(ii).base());
						i = *ii;
					}
					if (i != additionalVPointer)
						break;
					if (ii == m_vehicleSet.rend())
						break;
				} while (true);
			}
			
			//In the following section, changes in the positions and velocities of the vehicle objects are determined. This section forms the core of the simulation.
			if (i != nullptr) {
				if (i->m_lane == 0) {
					i->m_inRange = false;
					i->m_routeVertexID_vehicle.clear();
				}
				if ((flag == false) && (i->m_ID_ptr != nullptr) && (i->m_inRange == true) && (m_vehicleSet.size() >= 1)) {
					if (i->m_processedByIteration == false) {
						flag = true;
						//Vehicles outside the range are not observed
						if ((i->m_position >= length) || (i->m_position < -2)) {
							i->m_inRange = false;
						}
						else {
							//For vehicles within the range, a distinction is made between vehicles that are newly inserted into the lane and those that are already present.
							if ((i->m_position == 0)||(i->m_position == -1)) {
								if (serviceInt == 1)
									i->m_processedByIteration = true;
								if ((speedAheadVehicleAt1L > 0) && (speedAheadVehicleAt1L >= ownSpeed)) {
									ownSpeed = speedAheadVehicleAt1L;
								}
								if ((speedAheadVehicleAt2L > 0) && (speedAheadVehicleAt2L >= ownSpeed)) {
									ownSpeed = speedAheadVehicleAt2L;
								}
								if (ownSpeed > m_maxVelocity) {
									ownSpeed = m_maxVelocity;
								}
								if (ownSpeed > m_maxVelocity_Density) {
									ownSpeed = m_maxVelocity_Density;
								}
								
								i->m_pref_speed = ownSpeed;
								if (i->m_lane == 1) {
									if ((positionAheadVehicleAt1L == 0) || (VL.VLStepConversion(ownSpeed) < positionAheadVehicleAt1L)) {
										i->m_position = VL.VLStepConversion(ownSpeed);
									}
									if ((positionAheadVehicleAt1L > 0) && (VL.VLStepConversion(ownSpeed) >= positionAheadVehicleAt1L)) {
										i->m_position = (VL.VLStepConversion(ownSpeed) - 1);
									}
								}
								if (i->m_lane == 2) {
									if ((positionAheadVehicleAt2L == 0) || (VL.VLStepConversion(ownSpeed) < positionAheadVehicleAt2L)) {
										i->m_position = VL.VLStepConversion(ownSpeed);
									}
									if ((positionAheadVehicleAt2L > 0) && (VL.VLStepConversion(ownSpeed) >= positionAheadVehicleAt2L)) {
										i->m_position = (VL.VLStepConversion(ownSpeed) - 1);
									}
								}
							}
							else {//m_postiion >0 && m_postion<length
								i->m_processedByIteration = true;
								if (i->m_lane == 1) {
									if (i->m_moblieORStationary == true) {
										if ((speedAheadVehicleAt1L > 0) && (speedAheadVehicleAt1L >= ownSpeed)) {
											if ((speedAheadVehicleAt1L - ownSpeed) > 20) {
												ownSpeed += 21;
											}
											else if ((speedAheadVehicleAt1L - ownSpeed) > 10) {
												if (((positionAheadVehicleAt2L > 0) && ((positionAheadVehicleAt2L - i->m_position) > 36)) || (positionAheadVehicleAt2L == 0)) {
													ownSpeed += 11;
													i->m_lane = 2;
												}
												else {
													ownSpeed += 7;
												}
											}
											else if ((speedAheadVehicleAt1L - ownSpeed) >= 1) {
												if (((positionAheadVehicleAt2L > 0) && ((positionAheadVehicleAt2L - i->m_position) > 10)) || (positionAheadVehicleAt2L == 0)) {
													ownSpeed += 10;
													i->m_lane = 2;
												}
												else {
													ownSpeed += 2;
												}
											}
										}
										if ((speedAheadVehicleAt1L == 0) && (speedAheadVehicleAt2L > 0) && (ownSpeed > 20) && (positionAheadVehicleAt1L > 0)) {
											i->m_lane = 2;
											ownSpeed -= 10;
										}
									}
									else {
										i->m_lane = 1;
										i->m_pref_speed = 0;
										ownSpeed = 0;
									}
								}
								if (i->m_lane == 2) {
									if (i->m_moblieORStationary == true) {
										if ((positionAheadVehicleAt1L == 0) || ((positionAheadVehicleAt1L - (i->m_position)) >= 36)) {
											i->m_lane = 1;
											if ((speedAheadVehicleAt1L - ownSpeed) > 20) {
												ownSpeed += 11;
											}
											else if ((speedAheadVehicleAt1L - ownSpeed) > 10) {
												ownSpeed += 7;
											}
											else if ((speedAheadVehicleAt1L - ownSpeed) >= 1) {
												ownSpeed += 2;
											}
										}
										else if ((speedAheadVehicleAt2L > 0) && (speedAheadVehicleAt2L >= ownSpeed)) {
											if ((speedAheadVehicleAt2L - ownSpeed) > 20) {
												ownSpeed += 21;
											}
											else if ((speedAheadVehicleAt2L - ownSpeed) > 10) {
												ownSpeed += 11;
											}
											else if ((speedAheadVehicleAt2L - ownSpeed) >= 1) {
												ownSpeed += 2;
											}
										}
										if ((speedAheadVehicleAt2L == 0) && (speedAheadVehicleAt1L > 0) && (ownSpeed > 20) && (positionAheadVehicleAt2L > 0)) {
											i->m_lane = 1;
											ownSpeed -= 10;
										}
									}
									else {
										i->m_lane = 2;
										i->m_pref_speed = 0;
										ownSpeed = 0;
									}
								}

								if (ownSpeed > m_maxVelocity) {
									ownSpeed = m_maxVelocity;
								}
								if (ownSpeed > m_maxVelocity_Density) {
									ownSpeed = m_maxVelocity_Density;
								}
								
								if (i->m_moblieORStationary == true) {
									if (i->m_lane == 1) {
										if (positionAheadVehicleAt1L <= 0) {
											i->m_position = i->m_position + VL.VLStepConversion(ownSpeed);
											i->m_pref_speed = ownSpeed;
										}
										else {
											if (positionAheadVehicleAt1L > (i->m_position + VL.VLStepConversion(ownSpeed))) {
												i->m_position = i->m_position + VL.VLStepConversion(ownSpeed);
												i->m_pref_speed = ownSpeed;
											}
											else if (positionAheadVehicleAt1L == (i->m_position + VL.VLStepConversion(ownSpeed))) {
												ownSpeed = speedAheadVehicleAt1L - 5;
												if (ownSpeed <= 0) {
													ownSpeed = 0;
												}
												i->m_position = (i->m_position + VL.VLStepConversion(ownSpeed));
												i->m_pref_speed = ownSpeed;
											}
											else if (positionAheadVehicleAt1L < (i->m_position + VL.VLStepConversion(ownSpeed))) {
												i->m_position = positionAheadVehicleAt1L - 3;
												ownSpeed = speedAheadVehicleAt1L - 5;
												if (ownSpeed <= 0) {
													ownSpeed = 0;
												}
												i->m_pref_speed = ownSpeed;
											}
										}
									}
									if (i->m_lane == 2) {
										if (positionAheadVehicleAt2L <= 0) {
											i->m_position = i->m_position + VL.VLStepConversion(ownSpeed);
											i->m_pref_speed = ownSpeed;
										}
										else {
											if (positionAheadVehicleAt2L > (i->m_position + VL.VLStepConversion(ownSpeed))) {
												i->m_position = i->m_position + VL.VLStepConversion(ownSpeed);
												i->m_pref_speed = ownSpeed;
											}
											else if (positionAheadVehicleAt2L == (i->m_position + VL.VLStepConversion(ownSpeed))) {
												ownSpeed = speedAheadVehicleAt2L - 5;
												if (ownSpeed <= 0) {
													ownSpeed = 0;
												}
												i->m_position = ((i->m_position) + VL.VLStepConversion(ownSpeed));
												i->m_pref_speed = ownSpeed;
											}
											else if (positionAheadVehicleAt2L < (i->m_position + VL.VLStepConversion(ownSpeed))) {
												i->m_position = positionAheadVehicleAt2L - 3;
												ownSpeed = speedAheadVehicleAt2L - 5;
												if (ownSpeed <= 0) {
													ownSpeed = 0;
												}
												i->m_pref_speed = ownSpeed;
											}
										}
									}
								}
							}
						}
					}
				}
				//After completion of the simulation iteration, the position as well as the velocity of the treated vehicle object are written into variables to be available as a comparison value for the next iteration.
				if ((i->m_ID_ptr != nullptr) && (m_vehicleSet.size() >= 1)) {
					if (i->m_lane == 1) {
						speedAheadVehicleAt1L = i->m_pref_speed;
						positionAheadVehicleAt1L = i->m_position;
						laneAheadVehicle = i->m_lane;
						if ((positionAheadVehicleAt2L > 0) && ((positionAheadVehicleAt2L - i->m_position) >= 20)) {
							positionAheadVehicleAt2L = 0;
							speedAheadVehicleAt2L = 0;
						}
						if ((positionAheadVehicleAt2L > 0) && ((i->m_position - positionAheadVehicleAt2L) >= 20)) {
							positionAheadVehicleAt2L = 0;
							speedAheadVehicleAt2L = 0;
						}
					}
					if (i->m_lane == 2) {
						speedAheadVehicleAt2L = i->m_pref_speed;
						positionAheadVehicleAt2L = i->m_position;
						laneAheadVehicle = i->m_lane;
						if ((positionAheadVehicleAt1L > 0) && ((positionAheadVehicleAt1L - i->m_position) >= 20)) {
							positionAheadVehicleAt1L = 0;
							speedAheadVehicleAt1L = 0;
						}
						if ((positionAheadVehicleAt1L > 0) && ((i->m_position - positionAheadVehicleAt1L) >= 20)) {
							positionAheadVehicleAt1L = 0;
							speedAheadVehicleAt1L = 0;
						}
					}
					numberOfVehicleinRange++;
					i->m_speed = i->m_pref_speed;
				}
			}
		}
	}
	return numberOfVehicleinRange;
}