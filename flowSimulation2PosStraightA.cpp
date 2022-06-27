#include "PrecompiledHeadersEdges.h"
#include "flowSimulation2PosStraight.h"

//Constructor and destructor of the class:
flowSimulation2PosStraightA::flowSimulation2PosStraightA(callBackLinks* CBLptr, const int& maxVelocity, const int& maxVelocity_Density)
	:sectionVehicleSet(CBLptr), m_maxVelocity(maxVelocity), m_maxVelocity_Density(maxVelocity_Density) {
	m_CBLptr = CBLptr;
}
flowSimulation2PosStraightA::~flowSimulation2PosStraightA()noexcept {}

void flowSimulation2PosStraightA::printContentOfSection(const int& p1xx, const int& p1yy, const int& p2xx, const int& p2yy) {
	//********************************************************************
	//This method and the method "addPrintContent" of the inheriting classes of "PrintInGDIPlusWindow" form a unit, 
	//whose goal is to fill the positions of the vehicle objects in a visually suitable form in a data container(m_pointContainer in class "PrintInGDIplusWindow").
	for (auto& i : m_vehicleSet) {
		i->serviceBool = false;
		if (!i->m_routeVertexID_vehicle.empty()) {
			m_P2LP.addPrintContent(p1xx, p1yy, p2xx, p2yy, i->m_lane, i->m_position, i->m_routeVertexID_vehicle.back());
		}
	}
}

int flowSimulation2PosStraightA::flow(const int& numberOfLanes, const int& length, const bool& riseOrDecline) {
	//********************************************************************
	//Traffic flow simulation algorithm for connections with two lanes in ascending direction
	flag = false;
	ownSpeed = 0;
	ownPosition = 0;
	speedAheadVehicleAt1L = 0;
	positionAheadVehicleAt1L = 0;
	speedAheadVehicleAt2L = 0;
	positionAheadVehicleAt2L = 0;
	numberOfVehicleinRange = 0;
	if (riseOrDecline == true) {
		numberOfVehicleinRange = 0;
		for (auto& i : m_vehicleSet)
		{
			if (i->m_moblieORStationary == true) {
				if (i->m_pref_speed <= 0) {
					if (i->m_moblieORStationary == false) {
						ownSpeed = 0;
					}
					else {
						ownSpeed = m_CBLptr->m_callback_getRandomNumber();
					}
				}
				else {
					ownPosition = i->m_position;
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
				ownPosition = i->m_position;
			}

			if ((flag == false) && (length > 0) && (i->m_inRange) == true && (i->processedByIteration) == true) {
				if (i->serviceBool == false) {
					flag = true;
					if ((i->m_position > length) || (i->m_position < 0)) {
						i->m_inRange = false;
						i->serviceBool = true;
					}
					else {
						if (i->m_position == 0) {
							if (i->m_moblieORStationary == true) {
								i->serviceBool = true;
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
								ownPosition = VL.VLStepConversion(ownSpeed);
								i->m_pref_speed = ownSpeed;
								if (i->m_lane == 1) {
									if ((positionAheadVehicleAt1L == 0) || (ownPosition < positionAheadVehicleAt1L)) {
										i->m_position = ownPosition;
									}
									if ((positionAheadVehicleAt1L > 0) && (ownPosition >= positionAheadVehicleAt1L)) {
										i->m_position = (ownPosition - 1);
									}
								}
								if (i->m_lane == 2) {
									if ((positionAheadVehicleAt2L == 0) || (ownPosition < positionAheadVehicleAt2L)) {
										i->m_position = ownPosition;
									}
									if ((positionAheadVehicleAt2L > 0) && (ownPosition >= positionAheadVehicleAt2L)) {
										i->m_position = (ownPosition - 1);
									}
								}
							}
						}
						else {//m_postiion >0 && m_postion<length
							if ((i->m_lane == 1) && (i->serviceBool == false)) {
								i->serviceBool = true;
								if ((speedAheadVehicleAt1L > 0) && (speedAheadVehicleAt1L >= ownSpeed)) {
									if ((speedAheadVehicleAt1L - ownSpeed) > 20) {
										if (i->m_moblieORStationary == true) {
											ownSpeed += 21;
										}
									}
									else if ((speedAheadVehicleAt1L - ownSpeed) > 10) {
										if (((positionAheadVehicleAt2L > 0) && ((positionAheadVehicleAt2L - ownPosition) > 36)) || (positionAheadVehicleAt2L == 0)) {
											if (i->m_moblieORStationary == true) {
												ownSpeed += 21;
												i->m_lane = 2;
											}
										}
										else {
											if (i->m_moblieORStationary == true) {
												ownSpeed += 11;
											}
										}
									}
									else if ((speedAheadVehicleAt1L - ownSpeed) >= 1) {

										if (((positionAheadVehicleAt2L > 0) && ((positionAheadVehicleAt2L - ownPosition) > 10)) || (positionAheadVehicleAt2L == 0)) {
											if (i->m_moblieORStationary == true) {
												ownSpeed += 10;
												i->m_lane = 2;
											}
										}
										else {
											if (i->m_moblieORStationary == true) {
												ownSpeed += 2;
											}
										}
									}
								}
								if (i->m_moblieORStationary == false) {
									i->m_lane = 1;
									i->m_pref_speed = 0;
									ownSpeed = 0;
								}
							}
							if ((i->m_lane == 2) && (i->serviceBool == false)) {
								i->serviceBool = true;
								if ((positionAheadVehicleAt1L == 0) || ((positionAheadVehicleAt1L - (i->m_position)) >= 36)) {
									i->m_lane = 1;
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
								else if ((speedAheadVehicleAt2L > 0) && (speedAheadVehicleAt2L >= ownSpeed)) {
									if ((speedAheadVehicleAt2L - ownSpeed) > 20) {
										if (i->m_moblieORStationary == true) {
											ownSpeed += 21;
										}
									}
									else if ((speedAheadVehicleAt2L - ownSpeed) > 10) {
										if (i->m_moblieORStationary == true) {
											ownSpeed += 11;
										}
									}
									else if ((speedAheadVehicleAt2L - ownSpeed) >= 1) {
										if (i->m_moblieORStationary == true) {
											ownSpeed += 2;
										}
									}
								}
								if (i->m_moblieORStationary == false) {
									i->m_lane = 2;
									i->m_pref_speed = 0;
									ownSpeed = 0;
								}
							}
							i->serviceBool = true;
							if (ownSpeed > m_maxVelocity) {
								ownSpeed = m_maxVelocity;
							}
							if (ownSpeed > m_maxVelocity_Density) {
								ownSpeed = m_maxVelocity_Density;
							}
							ownPosition = VL.VLStepConversion(ownSpeed);
							//i->m_pref_speed = ownSpeed;
							if (i->m_lane == 1) {
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
											i->m_position = positionAheadVehicleAt1L - 3;
											ownSpeed = speedAheadVehicleAt1L - 5;
											if (ownSpeed <= 0) {
												ownSpeed = 0;
											}
											i->m_pref_speed = ownSpeed;
										}
									}
								}
							}
							if (i->m_lane == 2) {
								if (positionAheadVehicleAt2L <= 0) {
									if (i->m_moblieORStationary == true) {
										i->m_position = (i->m_position) + ownPosition;
										i->m_pref_speed = ownSpeed;
									}
								}
								else {
									if (positionAheadVehicleAt2L > ((i->m_position) + ownPosition)) {
										if (i->m_moblieORStationary == true) {
											i->m_position = (i->m_position) + ownPosition;
											i->m_pref_speed = ownSpeed;
										}
									}
									if (positionAheadVehicleAt2L == ((i->m_position) + ownPosition)) {
										if (i->m_moblieORStationary == true) {
											ownSpeed = speedAheadVehicleAt2L - 5;
											if (ownSpeed <= 0) {
												ownSpeed = 0;
											}
											i->m_position = ((i->m_position) + VL.VLStepConversion(ownSpeed));
											i->m_pref_speed = ownSpeed;
										}
									}
									if (positionAheadVehicleAt2L < ((i->m_position) + ownPosition)) {
										if (i->m_moblieORStationary == true) {
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

			if (i->m_lane == 1) {
				speedAheadVehicleAt1L = i->m_pref_speed;
				positionAheadVehicleAt1L = i->m_position;
			}
			if (i->m_lane == 2) {
				speedAheadVehicleAt2L = i->m_pref_speed;
				positionAheadVehicleAt2L = i->m_position;
			}
			numberOfVehicleinRange++;
		}
	}
	return numberOfVehicleinRange;
}