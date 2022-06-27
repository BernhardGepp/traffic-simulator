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

void flowSimulation1PosStraight::printContentOfSection(const int& p1xx, const int& p1yy, const int& p2xx, const int& p2yy) {
	//********************************************************************
	//This method and the method "addPrintContent" of the inheriting classes of "PrintInGDIPlusWindow" form a unit, 
	//whose goal is to fill the positions of the vehicle objects in a visually suitable form in a data container(m_pointContainer in class "PrintInGDIplusWindow").
	for (auto& i : m_vehicleSet) {
		i->serviceBool = false;
		if (!i->m_routeVertexID_vehicle.empty()) {
			m_P1LP.addPrintContent(p1xx, p1yy, p2xx, p2yy, 1, i->m_position, i->m_routeVertexID_vehicle.back());
		}
	}
}

int flowSimulation1PosStraight::flow(const int& numberOfLanes, const int& length, const bool& riseOrDecline) {
	//********************************************************************
	//Traffic flow simulation algorithm for connections with one lane in ascending direction
	flag = false;
	ownSpeed = 0;
	ownPosition = 0;
	speedAheadVehicleAt1L = 0;
	positionAheadVehicleAt1L = 0;
	numberOfVehicleinRange = 0;
	if (riseOrDecline == true) {
		numberOfVehicleinRange = 0;

		for (auto& i : m_vehicleSet) {
			if (i->m_pref_speed <= 0)
			{
				if (i->m_moblieORStationary == false)
				{
					ownSpeed = 0;
				}
				else {
					if (m_CBLptr->m_callback_getRandomNumber == nullptr) {
						ownSpeed = 100;
					}
					else {
						ownSpeed = m_CBLptr->m_callback_getRandomNumber();
					}
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
				else {
					i->m_pref_speed = 0;
					ownSpeed = 0;
				}
			}
			if ((flag == false) && (length > 0) && (i->m_inRange == true)) {
				if (i->serviceBool == false) {
					flag = true;
					i->serviceBool = true;
					if ((i->m_position > length) || (i->m_position < 0)) {
						i->m_inRange = false;
					}
					else {
						if (i->m_position == 0) {//Set-Beginn	
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

							if ((speedAheadVehicleAt1L == 0) && (m_vehicleSet.size() == 1)) {
								i->m_pref_speed = ownSpeed;
								if (i->m_position <= (i->m_position + VL.VLStepConversion(ownSpeed))) {

									i->m_position = i->m_position + VL.VLStepConversion(ownSpeed);
								}
							}
							if ((speedAheadVehicleAt1L == 0) && (m_vehicleSet.size() > 1)) {
								i->m_pref_speed = ownSpeed;
								if (i->m_position <= (i->m_position + VL.VLStepConversion(ownSpeed))) {
									i->m_position = i->m_position + VL.VLStepConversion(ownSpeed);
								}
							}
							if ((positionAheadVehicleAt1L == length) && (m_vehicleSet.size() == 1)) {
								if (i->m_position <= ownPosition) {
									i->m_position = ownPosition;
								}
								i->m_pref_speed = ownSpeed;
							}
							if ((positionAheadVehicleAt1L == length) && (m_vehicleSet.size() > 1)) {
								if (i->m_position <= (i->m_position + VL.VLStepConversion(ownSpeed))) {
									i->m_position = i->m_position + VL.VLStepConversion(ownSpeed);
								}
								i->m_pref_speed = ownSpeed;
							}
							if (ownPosition < positionAheadVehicleAt1L) {
								if (i->m_position <= (i->m_position + VL.VLStepConversion(ownSpeed))) {

									i->m_position = i->m_position + VL.VLStepConversion(ownSpeed);
								}
								i->m_pref_speed = ownSpeed;
							}
							if ((positionAheadVehicleAt1L < 0) && (ownPosition >= positionAheadVehicleAt1L) && (0 < positionAheadVehicleAt1L)) {
								if (i->m_position <= (positionAheadVehicleAt1L - 1)) {
									i->m_position = (positionAheadVehicleAt1L - 1);
								}
								ownPosition = i->m_position;
								i->m_pref_speed = ownSpeed;
							}

						}
						else {//m_postiion >0 && m_postion<length	
							if (speedAheadVehicleAt1L == 0) {
								ownSpeed = m_maxVelocity;
							}
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

							if (i->m_moblieORStationary == false) {
								ownSpeed = 0;
								i->m_pref_speed = 0;
								speedAheadVehicleAt1L = 0;
							}

							ownPosition = VL.VLStepConversion(ownSpeed);

							i->m_pref_speed = ownSpeed;

							if (positionAheadVehicleAt1L <= 0) {
								if (i->m_moblieORStationary == true) {

									if (i->m_position <= (i->m_position + ownPosition)) {
										i->m_position = (i->m_position) + ownPosition;
									}
									i->m_pref_speed = ownSpeed;
								}
							}
							else {

								if (positionAheadVehicleAt1L == i->m_position) {
									if (i->m_moblieORStationary == true) {
										if (i->m_position <= (i->m_position + ownPosition)) {
											i->m_position = (i->m_position) + ownPosition;
										}
										i->m_pref_speed = ownSpeed;
									}
								}
								else if (positionAheadVehicleAt1L > ((i->m_position) + ownPosition)) {
									if (i->m_moblieORStationary == true) {
										if (i->m_position <= (i->m_position + ownPosition)) {
											i->m_position = (i->m_position) + ownPosition;
										}
										i->m_pref_speed = ownSpeed;

									}
								}
								else if (positionAheadVehicleAt1L > i->m_position) {
									if (i->m_moblieORStationary == true) {

										if (i->m_position <= (positionAheadVehicleAt1L - 1)) {
											i->m_position = positionAheadVehicleAt1L - 1;
										}
									}
								}
								else if (positionAheadVehicleAt1L == ((i->m_position) + ownPosition)) {
									if (i->m_moblieORStationary == true) {
										ownSpeed = speedAheadVehicleAt1L - 5;
										if (i->m_position <= (i->m_position + VL.VLStepConversion(ownSpeed))) {
											i->m_position = ((i->m_position) + VL.VLStepConversion(ownSpeed));
										}
										i->m_pref_speed = ownSpeed;
										if (ownSpeed < 0) {
											if (i->m_position <= (positionAheadVehicleAt1L - 1)) {
												i->m_position = positionAheadVehicleAt1L - 1;
											}
											ownPosition = positionAheadVehicleAt1L - 1;
											i->m_pref_speed = 0;
											ownSpeed = 0;
										}
									}
								}
								else if (positionAheadVehicleAt1L < ((i->m_position) + ownPosition)) {
									if (i->m_moblieORStationary == true) {
										if (positionAheadVehicleAt1L > i->m_position) {
											if (i->m_position <= (positionAheadVehicleAt1L - 1)) {
												i->m_position = positionAheadVehicleAt1L - 1;
											}
										}
										if (i->m_position <= (positionAheadVehicleAt1L - 3)) {

											i->m_position = positionAheadVehicleAt1L - 2;
										}
										ownSpeed = speedAheadVehicleAt1L;
									}
								}

								else if (positionAheadVehicleAt1L < i->m_position) {
									if (i->m_moblieORStationary == true) {
										if (i->m_position <= (positionAheadVehicleAt1L - 1)) {
											i->m_position = positionAheadVehicleAt1L - 1;
										}
									}
								}
							}
						}
					}
				}
			}

			if ((i->m_position >= length) || (i->m_position < 0)) {
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
				numberOfVehicleinRange++;
			}
		}
	}
	return numberOfVehicleinRange;
}
