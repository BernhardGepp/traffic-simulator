#pragma once
//#include "selectionFlowSimulation.h"
#include "sectionVehicleSet.h"
#include "velocityToLength.h"
#include "PrintInGDIplusWin2LN.h"
#include "PrecompiledHeadersEdges.h"
class flowSimulation2NegStraight : public sectionVehicleSet{
private:
	PrintInGDIplusWin2LN m_P2LN;
public:
	velocityToLength VL;
	bool flag = false;
	int ownSpeed = 0;
	int ownPosition = 0;
	int speedAheadVehicleAt1L = 0;
	int positionAheadVehicleAt1L = 0;
	int speedAheadVehicleAt2L = 0;
	int positionAheadVehicleAt2L = 0;
	int numberOfVehicleinRange = 0;
	int m_maxVelocity = 0;
	int m_maxVelocity_Density = 0;
	HDC m_hdc1;
	int(*m_callback_getRandomNumber)() = nullptr;
	void(*m_f6PrintLaneInNumbers)(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV) = nullptr;
	//flowSimulation2NegStraight::flowSimulation2NegStraight(int(*callback_getRandomNumber)(), void(*f6PrintLaneInNumbers)(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV)) :sectionVehicleSet(callback_getRandomNumber, f6PrintLaneInNumbers), m_callback_getRandomNumber(callback_getRandomNumber), m_f6PrintLaneInNumbers(f6PrintLaneInNumbers) {
	explicit flowSimulation2NegStraight::flowSimulation2NegStraight(int(*callback_getRandomNumber)(), 
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
	flowSimulation2NegStraight::flowSimulation2NegStraight(const flowSimulation2NegStraight &other) = delete; 	
	flowSimulation2NegStraight& operator=(flowSimulation2NegStraight& other) = delete; 
	flowSimulation2NegStraight::flowSimulation2NegStraight(const flowSimulation2NegStraight &&other) = delete; 
	flowSimulation2NegStraight& operator=(flowSimulation2NegStraight&& other) = delete; 
	flowSimulation2NegStraight::~flowSimulation2NegStraight() {

	}
	void flowSimulation2NegStraight::printContentOfSection(const int& p1xx, const int& p1yy,
		const int& p2xx, const int& p2yy) override {
		
		vehicle* i = nullptr;
		for (std::set<vehicle*, boost::indirect_fun<std::less<vehicle>>>::reverse_iterator a = m_vehicleSet.rbegin();
			a != m_vehicleSet.rend(); ++a) {
			i = *a;
			i->serviceBool = false;
			if (!i->m_routeVertexID_vehicle.empty()) {
				m_P2LN.addPrintContent(p1xx, p1yy, p2xx, p2yy, i->m_lane, i->m_position, i->m_routeVertexID_vehicle.back());
			}

		}
	}
	int flowSimulation2NegStraight::flow(const int &numberOfLanes,
		const int &length,
		const bool &riseOrDecline) override{
		flag = false;
		ownSpeed = 0;
		ownPosition = 0;
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
			std::set<vehicle*>::iterator ii = m_vehicleSet.begin();
			vehicle* i = *ii;
			if ((m_vehicleSet.size() > 1) && (i->m_lane == 1)) {
				positionAheadVehicleAt1L = i->m_position;
			}
			if ((m_vehicleSet.size() > 1) && (i->m_lane == 2)) {
				positionAheadVehicleAt2L = i->m_position;
			}
			for (ii = m_vehicleSet.begin(); ii != m_vehicleSet.end(); ++ii)
			{
				i = *ii;
				if (i->m_moblieORStationary == true) {
					if (i->m_pref_speed <= 0) {
						//ownSpeed = rs.random();	
						ownSpeed = m_callback_getRandomNumber();
						//ownSpeed = randomSpeed_neu::getRandomNumber();
					}
					else {
						//ownPosition = i->m_position;
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
					i->m_pref_speed = 0;
					ownSpeed = 0;
				}
				if ((flag == false) && (length > 0) && (i->m_inRange) == true && (i->processedByIteration) == true) {
					if (i->serviceBool == false) {
						flag = true;
						i->serviceBool = true;
						if ((i->m_position > length) || (i->m_position <= 0)) {

							i->m_inRange = false;

						}
						else {
							if (i->m_position == length) {

								if ((speedAheadVehicleAt1L > 0) && (speedAheadVehicleAt1L <= ownSpeed) && (i->m_lane == 1)) {
									ownSpeed = speedAheadVehicleAt1L;
								}
								if ((speedAheadVehicleAt2L > 0) && (speedAheadVehicleAt2L <= ownSpeed) && (i->m_lane == 2)) {
									ownSpeed = speedAheadVehicleAt2L;
								}
								if (ownSpeed > m_maxVelocity) {
									ownSpeed = m_maxVelocity;
								}
								if (ownSpeed > m_maxVelocity_Density) {
									ownSpeed = m_maxVelocity_Density;
								}
								ownPosition = length - VL.VLStepConversion(ownSpeed);
								//i->m_pref_speed = ownSpeed;
								if (i->m_lane == 1) {
									if ((speedAheadVehicleAt1L == 0) && (m_vehicleSet.size() == 1)) {
										i->m_pref_speed = ownSpeed;
										i->m_position = ownPosition;
										i->m_position = i->m_position - VL.VLStepConversion(ownSpeed);
									}
									if ((speedAheadVehicleAt1L == 0) && (m_vehicleSet.size() > 1)) {//muss nicht sein!
										i->m_pref_speed = ownSpeed;
										i->m_position = i->m_position - VL.VLStepConversion(ownSpeed);
									}
									if ((positionAheadVehicleAt1L == length) && (m_vehicleSet.size() == 1)) {
										i->m_position = ownPosition;
										i->m_pref_speed = ownSpeed;
									}
									if ((positionAheadVehicleAt1L == length) && (m_vehicleSet.size() > 1)) {
										i->m_position = i->m_position - VL.VLStepConversion(ownSpeed);
										i->m_pref_speed = ownSpeed;
									}
									if (ownPosition > positionAheadVehicleAt1L) {
										//i->m_position = ownPosition;
										i->m_position = i->m_position - VL.VLStepConversion(ownSpeed);
										i->m_pref_speed = ownSpeed;
									}
									if ((positionAheadVehicleAt1L > 0) && (ownPosition <= positionAheadVehicleAt1L) && (length>positionAheadVehicleAt1L)) {
										i->m_position = (positionAheadVehicleAt1L + 1);
										ownPosition = i->m_position;
										i->m_pref_speed = ownSpeed;
									}
									/*if ((positionAheadVehicleAt1L == length) || (ownPosition > positionAheadVehicleAt1L)) {
									i->m_position = ownPosition;
									}
									if ((positionAheadVehicleAt1L > length ) && (ownPosition <= positionAheadVehicleAt1L)) {
									i->m_position = (ownPosition + 1);
									}
									if ((speedAheadVehicleAt1L == 0) && (m_vehicleSet.size() == 1)) {
									i->m_position = ownPosition;
									}*/
								}
								if (i->m_lane == 2) {
									if ((speedAheadVehicleAt2L == 0) && (m_vehicleSet.size() == 1)) {
										i->m_pref_speed = ownSpeed;
										i->m_position = ownPosition;
										i->m_position = i->m_position - VL.VLStepConversion(ownSpeed);
									}
									if ((speedAheadVehicleAt2L == 0) && (m_vehicleSet.size() > 1)) {//muss nicht sein!
										i->m_pref_speed = ownSpeed;
										i->m_position = i->m_position - VL.VLStepConversion(ownSpeed);
									}
									if ((positionAheadVehicleAt2L == length) && (m_vehicleSet.size() == 1)) {
										i->m_position = ownPosition;
										i->m_pref_speed = ownSpeed;
									}
									if (ownPosition > positionAheadVehicleAt2L) {
										//i->m_position = ownPosition;
										i->m_position = i->m_position - VL.VLStepConversion(ownSpeed);
										i->m_pref_speed = ownSpeed;
									}
									if ((positionAheadVehicleAt2L > 0) && (ownPosition <= positionAheadVehicleAt2L) && (length>positionAheadVehicleAt2L)) {
										i->m_position = (positionAheadVehicleAt2L + 1);
										ownPosition = i->m_position;
										i->m_pref_speed = ownSpeed;
									}
								}
							}
							else {//m_postiion >0 && m_postion<length

								  //std::cout << "randomOwnSpeed: " << ownSpeed << std::endl;
								if ((speedAheadVehicleAt1L == 0) && (speedAheadVehicleAt2L == 0)) {
									ownSpeed = m_maxVelocity;
								}

								if ((i->m_lane == 1) && (i->serviceBool == false)) {
									i->serviceBool = true;
									if ((speedAheadVehicleAt1L > 0) && (speedAheadVehicleAt1L >= ownSpeed)) {
										if ((speedAheadVehicleAt1L - ownSpeed) > 20) {
											if (i->m_moblieORStationary == true) {
												ownSpeed += 21;
											}
										}
										else if ((speedAheadVehicleAt1L - ownSpeed) > 10) {
											if (((positionAheadVehicleAt2L > 0) && ((positionAheadVehicleAt2L - ownPosition) > 36)) || (positionAheadVehicleAt2L == length)) {
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
											//std::cout << "\t\t\t\t\tis unterste!\n";
											if (((positionAheadVehicleAt2L > 0) && ((positionAheadVehicleAt2L - ownPosition) > 10)) || (positionAheadVehicleAt2L == length)) {
												if (i->m_moblieORStationary == true) {
													ownSpeed += 10;
													i->m_lane = 2;
												}
											}
											else {
												if (i->m_moblieORStationary == true) {
													if (i->m_moblieORStationary == true) {
														ownSpeed += 2;
													}
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

									if (positionAheadVehicleAt1L >= length) {
										if (i->m_moblieORStationary == true) {
											i->m_position = (i->m_position) - ownPosition;//length-ownPosition;
											i->m_pref_speed = ownSpeed;
										}
									}
									else {
										if (positionAheadVehicleAt1L == i->m_position) {
											if (i->m_moblieORStationary == true) {
												i->m_position = (i->m_position) - ownPosition;
												i->m_pref_speed = ownSpeed;
											}
										}
										else if (positionAheadVehicleAt1L < ((i->m_position) - ownPosition)) {
											if (i->m_moblieORStationary == true) {
												i->m_position = (i->m_position) - ownPosition;
												i->m_pref_speed = ownSpeed;

											}
										}
										else if (positionAheadVehicleAt1L < i->m_position) {
											if (i->m_moblieORStationary == true) {


												i->m_position = positionAheadVehicleAt1L + 1;
											}
										}
										else if (positionAheadVehicleAt1L == ((i->m_position) - ownPosition)) {
											if (i->m_moblieORStationary == true) {
												ownSpeed = speedAheadVehicleAt1L - 5;
												if (ownSpeed <= 0) {
													ownSpeed = 0;
												}
												i->m_position = ((i->m_position) - VL.VLStepConversion(ownSpeed));
												i->m_pref_speed = ownSpeed;
												if (ownSpeed < 0) {
													i->m_position = positionAheadVehicleAt1L + 1;
													ownPosition = positionAheadVehicleAt1L + 1;
													i->m_pref_speed = 0;
													ownSpeed = 0;
												}
											}
										}
										else if (positionAheadVehicleAt1L >((i->m_position) - ownPosition)) {
											if (i->m_moblieORStationary == true) {
												if (positionAheadVehicleAt1L < i->m_position) {
													i->m_position = positionAheadVehicleAt1L + 1;
												}
												if (i->m_position>(positionAheadVehicleAt1L + 3))
													i->m_position = positionAheadVehicleAt1L + 2;
												ownSpeed = speedAheadVehicleAt1L;

											}
										}

										else if (positionAheadVehicleAt1L > i->m_position) {
											if (i->m_moblieORStationary == true) {
												i->m_position = positionAheadVehicleAt1L + 1;
											}
										}
									}
								}
								if (i->m_lane == 2) {
									if (positionAheadVehicleAt2L >= length) {
										if (i->m_moblieORStationary == true) {
											i->m_position = (i->m_position) - ownPosition;//length-ownPosition;
											i->m_pref_speed = ownSpeed;
										}
									}
									else {
										if (positionAheadVehicleAt2L == i->m_position) {
											if (i->m_moblieORStationary == true) {
												i->m_position = (i->m_position) - ownPosition;
												i->m_pref_speed = ownSpeed;
											}
										}
										else if (positionAheadVehicleAt2L < ((i->m_position) - ownPosition)) {
											if (i->m_moblieORStationary == true) {
												i->m_position = (i->m_position) - ownPosition;
												i->m_pref_speed = ownSpeed;

											}
										}
										else if (positionAheadVehicleAt2L < i->m_position) {
											if (i->m_moblieORStationary == true) {


												i->m_position = positionAheadVehicleAt2L + 1;
											}
										}
										else if (positionAheadVehicleAt2L == ((i->m_position) - ownPosition)) {
											if (i->m_moblieORStationary == true) {
												ownSpeed = speedAheadVehicleAt2L - 5;
												if (ownSpeed <= 0) {
													ownSpeed = 0;
												}
												i->m_position = ((i->m_position) - VL.VLStepConversion(ownSpeed));
												i->m_pref_speed = ownSpeed;
												if (ownSpeed < 0) {
													i->m_position = positionAheadVehicleAt2L + 1;
													ownPosition = positionAheadVehicleAt2L + 1;
													i->m_pref_speed = 0;
													ownSpeed = 0;
												}
											}
										}
										else if (positionAheadVehicleAt2L >((i->m_position) - ownPosition)) {
											if (i->m_moblieORStationary == true) {
												if (positionAheadVehicleAt2L < i->m_position) {
													i->m_position = positionAheadVehicleAt2L + 1;
												}
												if (i->m_position>(positionAheadVehicleAt2L + 3))
													i->m_position = positionAheadVehicleAt2L + 2;
												ownSpeed = speedAheadVehicleAt2L;

											}
										}

										else if (positionAheadVehicleAt2L > i->m_position) {
											if (i->m_moblieORStationary == true) {
												i->m_position = positionAheadVehicleAt2L + 1;
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
};