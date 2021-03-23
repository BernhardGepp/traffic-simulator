#pragma once
#include "sectionVehicleSet.h"
#include "velocityToLength.h"
#include "PrintInGDIplusWin1LN.h"
#include "PrecompiledHeadersEdges.h"

class flowSimulation1NegStraight: public sectionVehicleSet {
private:
	PrintInGDIplusWin1LN m_P1LN;
public:
	velocityToLength VL;
	bool flag = false;
	int ownSpeed = 0;
	int ownPosition = 0;
	int speedAheadVehicleAt1L = 0;
	int positionAheadVehicleAt1L = 0;
	HDC m_hdc1;
	int numberOfVehicleinRange = 0;
	int m_maxVelocity = 0;
	int m_maxVelocity_Density = 0;
	int(*m_callback_getRandomNumber)() = nullptr;
	void(*m_f6PrintLaneInNumbers)(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV) = nullptr;

	
	explicit flowSimulation1NegStraight::flowSimulation1NegStraight(int(*callback_getRandomNumber)(), 
		void(*f6PrintLaneInNumbers)(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV),
		HDC hdc, 
		const int& maxVelocity, 
		const int& maxVelocity_Density) 
		:sectionVehicleSet(callback_getRandomNumber,hdc), 
		m_callback_getRandomNumber(callback_getRandomNumber), 
		m_f6PrintLaneInNumbers(f6PrintLaneInNumbers),
		m_hdc1(hdc),
		m_maxVelocity(maxVelocity),
		m_maxVelocity_Density(maxVelocity_Density)
		{
	

	}
	flowSimulation1NegStraight::flowSimulation1NegStraight(const flowSimulation1NegStraight &other) = delete; 
	flowSimulation1NegStraight& operator=(flowSimulation1NegStraight& other) = delete;
	flowSimulation1NegStraight::flowSimulation1NegStraight(const flowSimulation1NegStraight &&other) = delete; 
	flowSimulation1NegStraight& operator=(flowSimulation1NegStraight&& other) = delete; 
	void flowSimulation1NegStraight::printContentOfSection(const int& p1xx, const int& p1yy,
		const int& p2xx, const int& p2yy) override {
		vehicle* i = nullptr;
		for (std::set<vehicle*, boost::indirect_fun<std::less<vehicle>>>::reverse_iterator a = m_vehicleSet.rbegin();
			a != m_vehicleSet.rend(); ++a) {
			i = *a;
			i->serviceBool = false;
			if (!i->m_routeVertexID_vehicle.empty()) {
				m_P1LN.addPrintContent(p1xx, p1yy, p2xx, p2yy, 1, i->m_position, i->m_routeVertexID_vehicle.back());
			}

		}
	}
	int flowSimulation1NegStraight::flow(const int &numberOfLanes,
		const int &length,
		const bool &riseOrDecline)override {
		flag = false;
		ownSpeed = 0;
		ownPosition = 0;
		speedAheadVehicleAt1L = 0;
		positionAheadVehicleAt1L = 0;
		numberOfVehicleinRange = 0;
		if (riseOrDecline == false) {
			positionAheadVehicleAt1L = length;
			speedAheadVehicleAt1L = 0;
			numberOfVehicleinRange = 0;
			std::set<vehicle*>::iterator ii = m_vehicleSet.begin();
			vehicle* i = *ii;
			if (m_vehicleSet.size() > 1) {
				positionAheadVehicleAt1L = i->m_position;
			}
			for (ii = m_vehicleSet.begin(); ii != m_vehicleSet.end(); ++ii) {//Geschwingskeitsteil!
				i = *ii;
				if (i->m_pref_speed <= 0) {
					if (i->m_moblieORStationary == false) {
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
					else {
						i->m_pref_speed = 0;
						ownSpeed = 0;
					}
				}//****************Ende Geschwindigkeitsteil!!**********************************
				if ((flag == false) && (length > 0) && (i->m_inRange == true)) {

					if (i->serviceBool == false) {
						flag = true;
						i->serviceBool = true;
						if ((i->m_position > length) || (i->m_position < 0)) {
							i->m_inRange = false;
						}
						else {
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
								if ((speedAheadVehicleAt1L == 0) && (m_vehicleSet.size() == 1)) {
									i->m_pref_speed = ownSpeed;
									if (i->m_position >= (i->m_position - VL.VLStepConversion(ownSpeed))) {
										//i->m_position = ownPosition;
										i->m_position = i->m_position - VL.VLStepConversion(ownSpeed);
									}
								}
								if ((speedAheadVehicleAt1L == 0) && (m_vehicleSet.size() > 1)) {//muss nicht sein!
									i->m_pref_speed = ownSpeed;
									if (i->m_position >= (i->m_position - VL.VLStepConversion(ownSpeed))) {
										i->m_position = i->m_position - VL.VLStepConversion(ownSpeed);
									}
								}
								if ((positionAheadVehicleAt1L == length) && (m_vehicleSet.size() == 1)) {
									if (i->m_position >= ownPosition) {
										i->m_position = ownPosition;
									}
									i->m_pref_speed = ownSpeed;
								}
								if ((positionAheadVehicleAt1L == length) && (m_vehicleSet.size() > 1)) {
									if (i->m_position >= (i->m_position - VL.VLStepConversion(ownSpeed))) {
										i->m_position = i->m_position - VL.VLStepConversion(ownSpeed);
									}
									i->m_pref_speed = ownSpeed;
								}
								if (ownPosition > positionAheadVehicleAt1L) {
									if (i->m_position >= (i->m_position - VL.VLStepConversion(ownSpeed))) {
										//i->m_position = ownPosition;
										i->m_position = i->m_position - VL.VLStepConversion(ownSpeed);
									}
									i->m_pref_speed = ownSpeed;
								}
								if ((positionAheadVehicleAt1L > 0) && (ownPosition <= positionAheadVehicleAt1L) && (length>positionAheadVehicleAt1L)) {
									if (i->m_position >= (positionAheadVehicleAt1L + 1)) {
										i->m_position = (positionAheadVehicleAt1L + 1);
									}
									ownPosition = i->m_position;
									i->m_pref_speed = ownSpeed;
								}
							}
							else {//m_postiion >0 && m_postion<length
								if (speedAheadVehicleAt1L == 0) {
									ownSpeed = m_maxVelocity;
								}
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
								if (i->m_moblieORStationary == false) {
									ownSpeed = 0;
									i->m_pref_speed = 0;
									speedAheadVehicleAt1L = 0;
								}
								ownPosition = VL.VLStepConversion(ownSpeed);
								i->m_pref_speed = ownSpeed;

								if (positionAheadVehicleAt1L >= length) {

									if (i->m_moblieORStationary == true) {
										if (i->m_position >= (i->m_position - ownPosition)) {
											i->m_position = (i->m_position) - ownPosition;//length-ownPosition;
										}
										i->m_pref_speed = ownSpeed;
									}
								}
								else {
									if (positionAheadVehicleAt1L == i->m_position) {
										if (i->m_moblieORStationary == true) {
											if (i->m_position >= (i->m_position - ownPosition)) {
												i->m_position = (i->m_position) - ownPosition;
											}
											i->m_pref_speed = ownSpeed;
										}
									}
									else if (positionAheadVehicleAt1L < ((i->m_position) - ownPosition)) {
										if (i->m_moblieORStationary == true) {
											if (i->m_position >= (i->m_position - ownPosition)) {
												i->m_position = (i->m_position) - ownPosition;
											}
											i->m_pref_speed = ownSpeed;

										}
									}
									else if (positionAheadVehicleAt1L < i->m_position) {
										if (i->m_moblieORStationary == true) {

											if (i->m_position >= (positionAheadVehicleAt1L + 1)) {
												i->m_position = positionAheadVehicleAt1L + 1;
											}
										}
									}
									else if (positionAheadVehicleAt1L == ((i->m_position) - ownPosition)) {
										if (i->m_moblieORStationary == true) {
											ownSpeed = speedAheadVehicleAt1L - 5;
											if (i->m_position >= (i->m_position - VL.VLStepConversion(ownSpeed))) {
												i->m_position = ((i->m_position) - VL.VLStepConversion(ownSpeed));
											}
											i->m_pref_speed = ownSpeed;
											if (ownSpeed < 0) {
												if (i->m_position >= (positionAheadVehicleAt1L + 1)) {
													i->m_position = positionAheadVehicleAt1L + 1;
												}
												ownPosition = positionAheadVehicleAt1L + 1;
												i->m_pref_speed = 0;
												ownSpeed = 0;
											}
										}
									}
									else if (positionAheadVehicleAt1L >((i->m_position) - ownPosition)) {
										if (i->m_moblieORStationary == true) {
											if (positionAheadVehicleAt1L < i->m_position) {
												if (i->m_position >= (positionAheadVehicleAt1L + 1)) {
													i->m_position = positionAheadVehicleAt1L + 1;
												}
											}
											if (i->m_position >= (positionAheadVehicleAt1L + 3)) {

												i->m_position = positionAheadVehicleAt1L + 2;
											}
											ownSpeed = speedAheadVehicleAt1L;
										}
									}

									else if (positionAheadVehicleAt1L > i->m_position) {
										if (i->m_moblieORStationary == true) {
											if (i->m_position >= (positionAheadVehicleAt1L + 1)) {
												i->m_position = positionAheadVehicleAt1L + 1;
											}
										}
									}
								}
							}
							//i->m_sectionID = sectionID;								
						}
					}
				}
				if ((i->m_position > length) || (i->m_position <= 0)) {
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
};
