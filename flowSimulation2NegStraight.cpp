#include "PrecompiledHeadersEdges.h"
#include "flowSimulation2NegStraight.h"

//Constructor and destructor of the class:
flowSimulation2NegStraight::flowSimulation2NegStraight(callBackLinks* CBLptr, const int& maxVelocity, const int& maxVelocity_Density)
	:sectionVehicleSet(CBLptr), m_maxVelocity(maxVelocity), m_maxVelocity_Density(maxVelocity_Density) {
	m_CBLptr = CBLptr;
	file5.open(textaa);
	hilfezahlerzuio++;
}

flowSimulation2NegStraight::~flowSimulation2NegStraight() noexcept {
	file5.close();
}

void flowSimulation2NegStraight::printContentOfSection(const int& p1xx, const int& p1yy, const int& p2xx, const int& p2yy) {
	//********************************************************************
	//This method and the method "addPrintContent" of the inheriting classes of "PrintInGDIPlusWindow" form a unit, 
	//whose goal is to fill the positions of the vehicle objects in a visually suitable form in a data container(m_pointContainer in class "PrintInGDIplusWindow").
	vehicle* i = nullptr;
	for (std::set<vehicle*, boost::indirect_fun<std::less<vehicle>>>::reverse_iterator a = m_vehicleSet.rbegin();
		a != m_vehicleSet.rend(); ++a) {
		i = *a;
		i->m_processedByIteration = false;
		if (!i->m_routeVertexID_vehicle.empty()) {
			m_P2LN.addPrintContent(p1xx, p1yy, p2xx, p2yy, i->m_lane, i->m_position, i->m_routeVertexID_vehicle.back());
		}
		else {
			m_P2LN.addPrintContent(p1xx, p1yy, p2xx, p2yy, i->m_lane, i->m_position, 0);
		}
	}
}

int flowSimulation2NegStraight::flow(const int& numberOfLanes, const int& length, const bool& riseOrDecline) {
	//********************************************************************
	//Traffic flow simulation algorithm for connections with two lanes in descending direction
	int zahler = 0;
	int serviceInt = 0;
	flag = false;
	ownSpeed = 0;
	//ownPosition = 0;
	speedAheadVehicleAt1L = 0;
	positionAheadVehicleAt1L = 0;
	speedAheadVehicleAt2L = 0;
	positionAheadVehicleAt2L = 0;
	numberOfVehicleinRange = 0;
	if (riseOrDecline == false) {
		//for (auto &i : m_vehicleSet)
		positionAheadVehicleAt1L = length;
		positionAheadVehicleAt2L = length;
		numberOfVehicleinRange = 0;
		std::set<vehicle*>::reverse_iterator ii = m_vehicleSet.rbegin();
		vehicle* i = *ii;
		
		file5 << "\n\nneuer Zyklus: " << length;
		for (ii = m_vehicleSet.rbegin(); ii != m_vehicleSet.rend(); ++ii){
			i = *ii;
			if (ii == m_vehicleSet.rbegin()) {
				file5 << "\tNEUE FOR SCHLEIFE";
			}
			if (i->m_position < 0) {
				i->m_inRange = false;
				i->m_processedByIteration = true;
				file5 << "\nBeginn am Ende: " << i->m_ID_ptr << " i->m_position: " << i->m_position;
			}
			file5 << "\nzähler: " << zahler << " m_vehicleSet.size() " << m_vehicleSet.size()<<" " << i->m_ID_ptr << "\tv prev: " << i->m_pref_speed << "\ti->m_moblieORStationary: " << i->m_moblieORStationary << "\ti->m_lane: " << i->m_lane;
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
			if (serviceInt > 1) {
				ownSpeed = 10000;
				i->m_routeVertexID_vehicle.clear();
				file5 << "\nLöschen size von Set: " << m_vehicleSet.size()<<" "<<i->m_ID_ptr;
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
			if (i != nullptr)
				file5 << "\n" << i->m_ID_ptr << "\ti->position: " << i->m_position << "\tv prev: " << i->m_pref_speed << " ownSpeed: " << ownSpeed << " speedAheadVehicleAt1L\t" << speedAheadVehicleAt1L << " speedAheadVehicleAt2L\t" << speedAheadVehicleAt2L << " positionAheadVehicleAt1L\t " << positionAheadVehicleAt1L << " positionAheadVehicleAt2L\t " << positionAheadVehicleAt2L <<  "\ti->m_lane: " << i->m_lane;
			if (i != nullptr) {
				if (i->m_lane == 0) {
					i->m_inRange = false;
					i->m_routeVertexID_vehicle.clear();
				}
				if ((flag == false) && (i->m_ID_ptr != nullptr) && (i->m_inRange == true) && (m_vehicleSet.size() >= 1)) {
					if (i->m_processedByIteration == false) {
						flag = true;
						if ((i->m_position > length) || (i->m_position <= 0)) {
							i->m_inRange = false;
							file5 << "\nEnde: " << i->m_ID_ptr << " i->m_position: " << i->m_position;
						}
						else {
							if (i->m_position >= (length-1)) {
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
								file5 << "\n" << length - VL.VLStepConversion(ownSpeed) << " VL.VLStepConversion( " << ownSpeed << " In Beginn i->m_position:" << i->m_position;
								i->m_pref_speed = ownSpeed;
								if (i->m_lane == 1) {
									if (positionAheadVehicleAt1L == length) {
										i->m_position = length - VL.VLStepConversion(ownSpeed)-1;
										file5 << "\nBeginnAusgang011"<<i->m_ID_ptr;
									}
									if ((length - VL.VLStepConversion(ownSpeed)) > positionAheadVehicleAt1L) {
										i->m_position = length - VL.VLStepConversion(ownSpeed) - 2;
										file5 << "\nBeginnAusgang012 " << i->m_ID_ptr<<" "<<length<<"  "<< VL.VLStepConversion(ownSpeed)<<" positionAheadVehicleAt1L "<< positionAheadVehicleAt1L <<" ownspeed " << ownSpeed << " ->m_position " << i->m_position;
										
									}
									if ((positionAheadVehicleAt1L > 0) && ((length - VL.VLStepConversion(ownSpeed)) <= positionAheadVehicleAt1L) && (length > positionAheadVehicleAt1L)) {
										i->m_position = length - VL.VLStepConversion(ownSpeed) - 1;
										file5 << "\nBeginnAusgang02";
									}
								}
								if (i->m_lane == 2) {
									if ((positionAheadVehicleAt2L == length) || ((length - VL.VLStepConversion(ownSpeed)) > positionAheadVehicleAt2L)) {
										i->m_position = length - VL.VLStepConversion(ownSpeed) - 2;
										file5 << "\nBeginnAusgang03";
									}
									if ((positionAheadVehicleAt2L > 0) && ((length - VL.VLStepConversion(ownSpeed)) <= positionAheadVehicleAt2L) && (length > positionAheadVehicleAt2L)) {
										i->m_position = (positionAheadVehicleAt2L + 1);
										//ownPosition = i->m_position;
										file5 << "\nBeginnAusgang04";
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
												file5 << "\nAusgang1";
											}
											else if ((speedAheadVehicleAt1L - ownSpeed) > 10) {
												if (((positionAheadVehicleAt2L > 0) && ((positionAheadVehicleAt2L - i->m_position) > -36)) || (positionAheadVehicleAt2L == length)) {
													ownSpeed += 11;
													i->m_lane = 2;
													file5 << "\nLane switch!1->2";
												}
												else {
													ownSpeed += 7;
												}
												file5 << "\nAusgang2";
											}
											else if ((speedAheadVehicleAt1L - ownSpeed) >= 1) {
												if (((positionAheadVehicleAt2L > 0) && ((positionAheadVehicleAt2L - i->m_position) > -10)) || (positionAheadVehicleAt2L == length)) {
													ownSpeed += 10;
													i->m_lane = 2;
													file5 << "\nLane switch!1->2";
												}
												else {
													ownSpeed += 2;
												}
												file5 << "\nAusgang3 positionAheadVehicleAt2L " << positionAheadVehicleAt2L;
											}
										}
										if ((speedAheadVehicleAt1L == 0) && (speedAheadVehicleAt2L > 0) && (ownSpeed > 20) && (positionAheadVehicleAt1L < length)) {
											i->m_lane = 2;
											ownSpeed -= 10;
											file5 << "\nAusgang4 Lane switch!1->2";
										}
									}
									else {
										i->m_lane = 1;
										i->m_pref_speed = 0;
										ownSpeed = 0;
										file5 << "\nAusgang5";
									}
								}
								else if (i->m_lane == 2) {
									if (i->m_moblieORStationary == true) {
										if ((positionAheadVehicleAt1L == 0) || ((positionAheadVehicleAt1L - i->m_position) >= -36)) {
											i->m_lane = 1;
											file5 << "\nAusgang6 Lane switch2->1!";
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
											file5 << "\nAusgang7";
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
										if ((speedAheadVehicleAt2L == 0) && (speedAheadVehicleAt1L > 0) && (ownSpeed > 20) && (positionAheadVehicleAt2L < length)) {
											i->m_lane = 1;
											ownSpeed -= 10;
											file5 << "\nAusgang8 Lane switch!2->1";
										}
									}
									else {
										i->m_lane = 2;
										i->m_pref_speed = 0;
										ownSpeed = 0;
										file5 << "\nAusgang9";
									}
								}

								if (ownSpeed > m_maxVelocity) {
									ownSpeed = m_maxVelocity;
								}
								if (ownSpeed > m_maxVelocity_Density) {
									ownSpeed = m_maxVelocity_Density;
								}
								
								file5 << "\n" << VL.VLStepConversion(ownSpeed) << " VL.VLStepConversion( " << ownSpeed;
								if (i->m_moblieORStationary == true) {
									if (i->m_lane == 1) {
										if (positionAheadVehicleAt1L >= length) {
											i->m_position = (i->m_position) - VL.VLStepConversion(ownSpeed);
											i->m_pref_speed = ownSpeed;
											file5 << "\nAusgang10";
										}
										else {
											if (positionAheadVehicleAt1L < (i->m_position - VL.VLStepConversion(ownSpeed))) {
												i->m_position = i->m_position - VL.VLStepConversion(ownSpeed);
												i->m_pref_speed = ownSpeed;
												file5 << "\nAusgang11";
											}
											else if (positionAheadVehicleAt1L == (i->m_position - VL.VLStepConversion(ownSpeed))) {
												ownSpeed = speedAheadVehicleAt1L - 5;
												i->m_position = i->m_position - VL.VLStepConversion(ownSpeed);
												i->m_pref_speed = ownSpeed;
												file5 << "\nAusgang12";
												if (ownSpeed <= 0) {
													i->m_position = positionAheadVehicleAt1L + 1;
													i->m_pref_speed = 0;
													ownSpeed = 0;
													file5 << "\tSubausgang12";
												}
											}
											else if (positionAheadVehicleAt1L > (i->m_position - VL.VLStepConversion(ownSpeed))) {
												i->m_position = positionAheadVehicleAt1L + 3;
												ownSpeed = speedAheadVehicleAt1L - 5;
												file5 << "\nAusgang13";
												//if (positionAheadVehicleAt1L < i->m_position) {
												if (ownSpeed <= 0) {
													i->m_position = positionAheadVehicleAt1L + 1;
													ownSpeed = 0;
													file5 << "\tSubausgang13";
												}
												i->m_pref_speed = ownSpeed;
											}
										}
									}
									if (i->m_lane == 2) {
										if (positionAheadVehicleAt2L >= length) {
											i->m_position = i->m_position - VL.VLStepConversion(ownSpeed);
											i->m_pref_speed = ownSpeed;
											file5 << "\nAusgang14";
										}
										else {
											if (positionAheadVehicleAt2L < (i->m_position - VL.VLStepConversion(ownSpeed))) {
												i->m_position = i->m_position - VL.VLStepConversion(ownSpeed);
												i->m_pref_speed = ownSpeed;
												file5 << "\nAusgang15";
											}
											else if (positionAheadVehicleAt2L == (i->m_position - VL.VLStepConversion(ownSpeed))) {
												ownSpeed = speedAheadVehicleAt2L - 5;
												i->m_position = ((i->m_position) - VL.VLStepConversion(ownSpeed));
												file5 << "\nAusgang15";
												if (ownSpeed <= 0) {
													i->m_position = positionAheadVehicleAt2L + 1;
													ownSpeed = 0;
													file5 << "\tSubausgang15";
												}
												i->m_pref_speed = ownSpeed;
											}
											else if (positionAheadVehicleAt2L > (i->m_position - VL.VLStepConversion(ownSpeed))) {
												i->m_position = positionAheadVehicleAt2L - 3;
												ownSpeed = speedAheadVehicleAt2L - 5;
												file5 << "\nAusgang16";
												if (ownSpeed <= 0) {
													ownSpeed = 0;
												}
												i->m_pref_speed = ownSpeed;
												file5 << "\tSubausgang16";
											}
										}
									}
								}
							}
						}
					}
				}
				if ((i != nullptr) && (i->m_ID_ptr != nullptr) && (m_vehicleSet.size() >= 1)&&(i->m_position>0)) {
					if (i->m_lane == 1) {
						speedAheadVehicleAt1L = i->m_pref_speed;
						positionAheadVehicleAt1L = i->m_position;
						laneAheadVehicle = i->m_lane;
						if ((positionAheadVehicleAt2L > 0) && ((positionAheadVehicleAt2L - i->m_position) >= 20)) {
							positionAheadVehicleAt2L = length;
							speedAheadVehicleAt2L = 0;
						}
						if ((positionAheadVehicleAt2L > 0) && ((i->m_position - positionAheadVehicleAt2L) >= 20)) {
							positionAheadVehicleAt2L = length;
							speedAheadVehicleAt2L = 0;
						}
					}
					if (i->m_lane == 2) {
						speedAheadVehicleAt2L = i->m_pref_speed;
						positionAheadVehicleAt2L = i->m_position;
						laneAheadVehicle = i->m_lane;
						if ((positionAheadVehicleAt1L > 0) && ((positionAheadVehicleAt1L - i->m_position) >= 20)) {
							positionAheadVehicleAt1L = length;
							speedAheadVehicleAt1L = 0;
						}
						if ((positionAheadVehicleAt1L > 0) && ((i->m_position - positionAheadVehicleAt1L) >= 20)) {
							positionAheadVehicleAt1L = length;
							speedAheadVehicleAt1L = 0;
						}

						
					}
					numberOfVehicleinRange++;
					i->m_speed = i->m_pref_speed;
					file5 << "\ni->m_pref_speed: " << i->m_pref_speed;
				}
				if (i->m_processedByIteration)
					file5 << "\tTRUE\ti->m_processedByIteration";
				else
					file5 << "\tFALSE\ti->m_processedByIteration";
			}
			zahler++;
			if (zahler == m_vehicleSet.size()) {
				for (int bull = 1; bull <= 1500; ++bull) {
					file5 << "\t" << bull;
				}
			}
		}
	}
	return numberOfVehicleinRange;
}