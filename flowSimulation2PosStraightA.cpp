#include "PrecompiledHeadersEdges.h"
#include "flowSimulation2PosStraight.h"

//Constructor and destructor of the class:
flowSimulation2PosStraightA::flowSimulation2PosStraightA(callBackLinks* CBLptr, const int& maxVelocity, const int& maxVelocity_Density)
	:sectionVehicleSet(CBLptr), m_maxVelocity(maxVelocity), m_maxVelocity_Density(maxVelocity_Density) {
	m_CBLptr = CBLptr;

	file5.open(textaa);
	hilfezahlerasdf++;
}
flowSimulation2PosStraightA::~flowSimulation2PosStraightA()noexcept {
	file5.close();
}

void flowSimulation2PosStraightA::printContentOfSection(const int& p1xx, const int& p1yy, const int& p2xx, const int& p2yy) {
	//********************************************************************
	//This method and the method "addPrintContent" of the inheriting classes of "PrintInGDIPlusWindow" form a unit, 
	//whose goal is to fill the positions of the vehicle objects in a visually suitable form in a data container(m_pointContainer in class "PrintInGDIplusWindow").
	for (auto& i : m_vehicleSet) {
		i->m_processedByIteration = false;
		if (!i->m_routeVertexID_vehicle.empty()) {
			m_P2LP.addPrintContent(p1xx, p1yy, p2xx, p2yy, i->m_lane, i->m_position, i->m_routeVertexID_vehicle.back());
		}
		else {
			m_P2LP.addPrintContent(p1xx, p1yy, p2xx, p2yy, i->m_lane, i->m_position, 0);
		}
	}
}

int flowSimulation2PosStraightA::flow(const int& numberOfLanes, const int& length, const bool& riseOrDecline) {
	//********************************************************************
	//Traffic flow simulation algorithm for connections with two lanes in ascending direction
	int zahler = 0;
	flag = false;
	ownSpeed = 0;
	ownPosition = 0;
	speedAheadVehicleAt1L = 0;
	positionAheadVehicleAt1L = 0;
	speedAheadVehicleAt2L = 0;
	positionAheadVehicleAt2L = 0;
	std::set<vehicle*>::reverse_iterator ii = m_vehicleSet.rbegin();
	vehicle* i = nullptr;
	if (riseOrDecline && (length>0)) {
		numberOfVehicleinRange = 0;
		file5 << "\n\nneuer Zyklus: " << length;
		for (ii = m_vehicleSet.rbegin(); ii != m_vehicleSet.rend(); ++ii) {
			i = *ii;
			zahler++;
			file5 << "\nzähler: " << zahler << " " << i->m_ID_ptr << "\tv prev: " << i->m_pref_speed << "\ti->m_moblieORStationary: " << i->m_moblieORStationary<<"\ti->m_lane: " << i->m_lane;
			if (i->m_moblieORStationary == true) {
				ownPosition = i->m_position;
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
				ownPosition = i->m_position;
			}
			file5 << "\n" << i->m_ID_ptr <<"\ti->position: "<<i->m_position<< "\tv prev: " << i->m_pref_speed << " ownSpeed: " << ownSpeed << " speedAheadVehicleAt1L\t" << speedAheadVehicleAt1L << " speedAheadVehicleAt2L\t" << speedAheadVehicleAt2L << " positionAheadVehicleAt1L\t " << positionAheadVehicleAt1L << " positionAheadVehicleAt2L\t " << positionAheadVehicleAt2L << " ownPosition:\t" << ownPosition<<"/ti->m_lane: "<<i->m_lane;
			if ((flag == false) && (i->m_ID_ptr!=nullptr) && (i->m_inRange == true) && (m_vehicleSet.size() >= 1)) {
				if (i->m_processedByIteration == false) {
					flag = true;
					if ((i->m_position > length) || (i->m_position < 0)) {
						i->m_inRange = false;
						//i->serviceBool = true;
					}
					else {
						if (i->m_position == 0) {
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
							//ownPosition = VL.VLStepConversion(ownSpeed);
							file5 << "\n" << VL.VLStepConversion(ownSpeed) << " VL.VLStepConversion( " << ownSpeed << " In Beginn i->m_position:" << i->m_position;
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
							file5 << "\nspeedAheadVehicleAt1L: " << speedAheadVehicleAt1L << "\tspeedAheadVehicleAt2L: " << speedAheadVehicleAt2L << "\t" << i->m_ID_ptr << "\townSpeed: " << ownSpeed << "i->m_position: \t" << i->m_position;
							file5 << "\ti->m_pref_speed: " << i->m_pref_speed << "\t" << i->m_ID_ptr << " Am Beginn i->m_lane:" << i->m_lane;
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
												file5 << "\nLane switch!1->2";
											}
											else {
												ownSpeed += 7;
											}
										}
										else if ((speedAheadVehicleAt1L - ownSpeed) >= 1) {
											if (((positionAheadVehicleAt2L > 0) && ((positionAheadVehicleAt2L - i->m_position) > 10)) || (positionAheadVehicleAt2L == 0)) {
												ownSpeed += 10;
												i->m_lane = 2;
												file5 << "\nLane switch!1->2";
											}
											else {
												ownSpeed += 2;
											}
										}
									}
									if ((speedAheadVehicleAt1L == 0)&& (speedAheadVehicleAt2L > 0) && (ownSpeed > 20)&&(positionAheadVehicleAt1L>0)) {
										i->m_lane = 2;
										ownSpeed -= 10;
										file5 << "\nLane switch!1->2";
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
										file5 << "\nLane switch2->1!";
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
									if ((speedAheadVehicleAt2L == 0) && (speedAheadVehicleAt1L > 0)&& (ownSpeed > 20) && (positionAheadVehicleAt2L > 0)) {
										i->m_lane = 1;
										ownSpeed -= 10;
										file5 << "\nLane switch!2->1";
									}
								}
								else{
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
							//ownPosition = VL.VLStepConversion(ownSpeed);
							file5 << "\n" << VL.VLStepConversion(ownSpeed) << " VL.VLStepConversion( " << ownSpeed;
							//i->m_pref_speed = ownSpeed;
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
										if (positionAheadVehicleAt1L == (i->m_position + VL.VLStepConversion(ownSpeed))) {
											ownSpeed = speedAheadVehicleAt1L - 5;
											if (ownSpeed <= 0) {
												ownSpeed = 0;
											}
											i->m_position = (i->m_position + VL.VLStepConversion(ownSpeed));
											i->m_pref_speed = ownSpeed;
										}
										if (positionAheadVehicleAt1L < (i->m_position + VL.VLStepConversion(ownSpeed))) {
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
										if (positionAheadVehicleAt2L == (i->m_position + VL.VLStepConversion(ownSpeed))) {
											ownSpeed = speedAheadVehicleAt2L - 5;
											if (ownSpeed <= 0) {
												ownSpeed = 0;
											}
											i->m_position = ((i->m_position) + VL.VLStepConversion(ownSpeed));
											i->m_pref_speed = ownSpeed;
										}
										if (positionAheadVehicleAt2L < (i->m_position + VL.VLStepConversion(ownSpeed))) {
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
			if ((i->m_ID_ptr != nullptr) && (m_vehicleSet.size() >= 1)) {
				if (i->m_lane == 1) {
					speedAheadVehicleAt1L = i->m_pref_speed;
					positionAheadVehicleAt1L = i->m_position;
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
				file5 << "\ni->m_pref_speed: " << i->m_pref_speed;
			}
		}
	}
	return numberOfVehicleinRange;
}