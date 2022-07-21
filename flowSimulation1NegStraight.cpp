#include "PrecompiledHeadersEdges.h"
#include "flowSimulation1NegStraight.h"

//Constructor
flowSimulation1NegStraight::flowSimulation1NegStraight(callBackLinks* CBLptr, const int& maxVelocity, const int& maxVelocity_Density)
	: sectionVehicleSet(CBLptr), m_maxVelocity(maxVelocity), m_maxVelocity_Density(maxVelocity_Density) {
	m_CBLptr = CBLptr;
	file5.open(textaa);
	hilfezahlerqwert++;
}
//Constructor used for unittest
flowSimulation1NegStraight::flowSimulation1NegStraight(const int& maxVelocity, const int& maxVelocity_Density)
	: sectionVehicleSet(), m_maxVelocity(maxVelocity), m_maxVelocity_Density(maxVelocity_Density) {
}

flowSimulation1NegStraight::~flowSimulation1NegStraight() noexcept {
	file5.close();
}

void flowSimulation1NegStraight::printContentOfSection(const int& p1xx, const int& p1yy, const int& p2xx, const int& p2yy) {
	//********************************************************************
	//This method and the method "addPrintContent" of the inheriting classes of "PrintInGDIPlusWindow" form a unit, 
	//whose goal is to fill the positions of the vehicle objects in a visually suitable form in a data container (m_pointContainer in class "PrintInGDIplusWindow").
	vehicle* i = nullptr;
	for (std::set<vehicle*, boost::indirect_fun<std::less<vehicle>>>::reverse_iterator a = m_vehicleSet.rbegin();
		a != m_vehicleSet.rend(); ++a) {
		i = *a;
		i->m_processedByIteration = false;
		if (!i->m_routeVertexID_vehicle.empty()) {
			m_P1LN.addPrintContent(p1xx, p1yy, p2xx, p2yy, 1, i->m_position, i->m_routeVertexID_vehicle.back());
		}
		else {
			m_P1LN.addPrintContent(p1xx, p1yy, p2xx, p2yy, 1, i->m_position, 0);
		}
	}
}

int flowSimulation1NegStraight::flow(const int& numberOfLanes, const int& length, const bool& riseOrDecline) {
	//********************************************************************
	//Traffic flow simulation algorithm for connections with one lane in descending direction
	int zahler = 0;
	flag = false;
	ownSpeed = 0;
	ownPosition = 0;
	if (riseOrDecline == false) {
		positionAheadVehicleAt1L = length;
		speedAheadVehicleAt1L = 0;
		numberOfVehicleinRange = 0;
		std::set<vehicle*>::reverse_iterator ii = m_vehicleSet.rbegin();
		vehicle* i = *ii;
		file5 << "\n\nneuer Zyklus: " << length;
		/*if (m_vehicleSet.size() > 1) {
			positionAheadVehicleAt1L = i->m_position;
		}*/
		for (ii = m_vehicleSet.rbegin(); ii != m_vehicleSet.rend(); ++ii) {//Geschwingskeitsteil!
			i = *ii;
			if (i->m_position < 0) {
				i->m_inRange = false;
				i->m_processedByIteration = true;
				file5 << "\nBeginn am Ende: " << i->m_ID_ptr << " i->m_position: " << i->m_position;
			}
			zahler++;
			file5 << "\nzähler: " << zahler << " " << i->m_ID_ptr << "\tv prev: " << i->m_pref_speed << "\ti->m_moblieORStationary: " << i->m_moblieORStationary;
			if (i->m_pref_speed <= 0) {
				if (i->m_moblieORStationary) {
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
			}//****************Ende Geschwindigkeitsteil!!**********************************
			file5 << "\n" << i->m_ID_ptr << "\tv prev: " << i->m_pref_speed << " ownSpeed: " << ownSpeed << " speedAheadVehicleAt1L\t" << speedAheadVehicleAt1L << " positionAheadVehicleAt1L\t " << positionAheadVehicleAt1L << " ownPosition:\t" << ownPosition;
			if ((flag == false) && (i->m_ID_ptr!=nullptr) && (i->m_inRange == true) && (m_vehicleSet.size() >= 1)) {
				if (i->m_processedByIteration == false) {
					flag = true;
					
					if ((i->m_position > length) || (i->m_position < 0)) {
						i->m_inRange = false;
						i->m_position = 0;
						i->m_pref_speed = 0;
					}
					else {
						i->m_processedByIteration = true;
						if (i->m_position >= length) {//Set-Beginn									
							if ((speedAheadVehicleAt1L > 0) && (speedAheadVehicleAt1L <= ownSpeed)) {
								ownSpeed = speedAheadVehicleAt1L;
							}
							if (ownSpeed > m_maxVelocity) {
								ownSpeed = m_maxVelocity;
							}
							if (ownSpeed > m_maxVelocity_Density) {
								ownSpeed = m_maxVelocity_Density;
							}
							ownPosition = length - VL.VLStepConversion(ownSpeed);
							file5 << "\n" << ownPosition << " VL.VLStepConversion( " << ownSpeed << " In Beginn i->m_position:" << i->m_position;
							if ((speedAheadVehicleAt1L == 0) && (m_vehicleSet.size() >= 1)) {
								i->m_pref_speed = ownSpeed;
								if (i->m_position >= (i->m_position - VL.VLStepConversion(ownSpeed))) {
									i->m_position = i->m_position - VL.VLStepConversion(ownSpeed);
								}
							}
							/*if ((positionAheadVehicleAt1L == length) && (m_vehicleSet.size() == 1)) {
								if (i->m_position >= ownPosition) {
									i->m_position = ownPosition;
								}
								i->m_pref_speed = ownSpeed;
							}*/
							/*if ((positionAheadVehicleAt1L == length) && (m_vehicleSet.size() > 1)) {
								if (i->m_position >= (i->m_position - VL.VLStepConversion(ownSpeed))) {
									i->m_position = i->m_position - VL.VLStepConversion(ownSpeed);
								}
								i->m_pref_speed = ownSpeed;
							}*/
							if ((length - VL.VLStepConversion(ownSpeed)) > positionAheadVehicleAt1L) {
								if (i->m_position >= (i->m_position - VL.VLStepConversion(ownSpeed))) {

									i->m_position = i->m_position - VL.VLStepConversion(ownSpeed);
								}
								//i->m_pref_speed = ownSpeed;
							}
							if ((positionAheadVehicleAt1L > 0) && ((length - VL.VLStepConversion(ownSpeed)) <= positionAheadVehicleAt1L) && (length > positionAheadVehicleAt1L)) {
								if (i->m_position >= (positionAheadVehicleAt1L + 1)) {
									i->m_position = (positionAheadVehicleAt1L + 1);
								}
								//ownPosition = i->m_position;
								if (ownSpeed == 0) {
									i->m_pref_speed = 0;
								}
							}
							file5 << "\nspeedAheadVehicleAt1L: " << speedAheadVehicleAt1L << "\t" << i->m_ID_ptr << "\townSpeed: " << ownSpeed << "i->m_position: \t" << i->m_position;
							file5 << "\ti->m_pref_speed: " << i->m_pref_speed << "\t" << i->m_ID_ptr << " Am Beginn";
						}
						else {//m_postiion >0 && m_postion<length
							/*if (speedAheadVehicleAt1L == 0) {
								ownSpeed = m_maxVelocity;
							}*/
							if ((speedAheadVehicleAt1L > 0) && (speedAheadVehicleAt1L >= ownSpeed)) {// zweiter Term:  eigendtlich größer gleich
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
							if ((i->m_position <= 30) && (ownSpeed > 0)) {
								ownSpeed = 30;
							}
							if (i->m_moblieORStationary == false) {
								ownSpeed = 0;
								i->m_pref_speed = 0;
								speedAheadVehicleAt1L = 0;
							}
							ownPosition = VL.VLStepConversion(ownSpeed);
							file5 << "\n" << ownPosition << " VL.VLStepConversion( " << ownSpeed;
							//i->m_pref_speed = ownSpeed;
							if (i->m_moblieORStationary == true) {
								i->m_pref_speed = ownSpeed + 1;
								if (i->m_pref_speed >= 135) {
									i->m_pref_speed = 80;
								}
								if (positionAheadVehicleAt1L >= length) {
									i->m_position = (i->m_position) - VL.VLStepConversion(ownSpeed);
									file5 << "\n1-i->m_position: \t" << i->m_position;
								}
								else {
									if (positionAheadVehicleAt1L == i->m_position) {
										if (i->m_position >= (i->m_position - VL.VLStepConversion(ownSpeed))) {
											i->m_position = i->m_position - VL.VLStepConversion(ownSpeed);
										}
										//i->m_pref_speed = ownSpeed;
										file5 << "\nnull7-i->m_position: \t" << i->m_position;
									}
									else if (positionAheadVehicleAt1L < (i->m_position - VL.VLStepConversion(ownSpeed))) {
										i->m_position = i->m_position - VL.VLStepConversion(ownSpeed);
										//i->m_pref_speed = ownSpeed;
										file5 << "\n2-i->m_position: \t" << i->m_position;
									}
									else if (positionAheadVehicleAt1L < i->m_position) {
										if (i->m_position >= (positionAheadVehicleAt1L + 1)) {
											i->m_position = positionAheadVehicleAt1L + 1;
										}
										file5 << "\n3-i->m_position: \t" << i->m_position;
									}
									else if (positionAheadVehicleAt1L == (i->m_position - VL.VLStepConversion(ownSpeed))) {
										ownSpeed = speedAheadVehicleAt1L - 5;
										if (i->m_position >= (i->m_position - VL.VLStepConversion(ownSpeed))) {
											i->m_position = ((i->m_position) - VL.VLStepConversion(ownSpeed));
										}
										i->m_pref_speed = ownSpeed;
										if (ownSpeed < 0) {
											if (i->m_position >= (positionAheadVehicleAt1L + 1)) {
												i->m_position = positionAheadVehicleAt1L + 1;
											}
											//ownPosition = positionAheadVehicleAt1L + 1;
											i->m_pref_speed = 0;
											ownSpeed = 0;
										}
										file5 << "\n4-i->m_position: \t" << i->m_position;
									}
									else if (positionAheadVehicleAt1L > (i->m_position - VL.VLStepConversion(ownSpeed))) {
										if (positionAheadVehicleAt1L < i->m_position) {
											if (i->m_position >= (positionAheadVehicleAt1L + 1)) {
												i->m_position = positionAheadVehicleAt1L + 1;
											}
										}
										if (i->m_position >= (positionAheadVehicleAt1L + 3)) {

											i->m_position = positionAheadVehicleAt1L + 2;
										}
										ownSpeed = speedAheadVehicleAt1L;
										file5 << "\n5-i->m_position: \t" << i->m_position;
									}
									else if (positionAheadVehicleAt1L > i->m_position) {
										if (i->m_position >= (positionAheadVehicleAt1L + 1)) {
											i->m_position = positionAheadVehicleAt1L + 1;
										}
										file5 << "\n6-i->m_position: \t" << i->m_position;
									}
								}
							}
							else {
								ownSpeed = 0;
							}
							file5 << "\ni->m_pref_speed: " << i->m_pref_speed << "\t" << i->m_ID_ptr << "\townSpeed: " << ownSpeed << " unterwegs";
						}
					}
				}
			}
			if ((i->m_ID_ptr != nullptr) && (m_vehicleSet.size() >= 1)) {
				if ((i->m_position > length) || (i->m_position <= 0)) {
					i->m_inRange = false;
					file5 << "\nAbschlussAusserhalb: " << i->m_speed << "\t" << i->m_ID_ptr << "\tspeedAheadVehicleAt1L/i->m_pref_speed: " << speedAheadVehicleAt1L << " i->m_position:\t" << i->m_position << " PaVAt1:  " << positionAheadVehicleAt1L;
				}
				else {
					if (i->m_moblieORStationary == true) {
						speedAheadVehicleAt1L = i->m_pref_speed;
						i->m_speed = ownSpeed;
					}
					else {
						speedAheadVehicleAt1L = 0;
						i->m_speed = 0;
					}
					positionAheadVehicleAt1L = i->m_position;
					file5 << "\nAbschluss in Rnage: " << i->m_speed << "\t" << i->m_ID_ptr << "\tspeedAheadVehicleAt1L/i->m_pref_speed: " << speedAheadVehicleAt1L << " positionAheadVehicleAt1L/i->m_position:\t" << positionAheadVehicleAt1L;
					numberOfVehicleinRange++;
				}
			}
		}
	}
	return numberOfVehicleinRange;
}