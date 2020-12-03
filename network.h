#pragma once
#include "PrecompiledHeadersEdges.h"
#include "vertex.h"
#include "vertexFlex.h"
#include "vertexStart.h"
#include "vertexEnd.h"
#include "edge.h"
#include "graph.h"
#include "vehicle.h"
#include "random_speed_neu.h"
#include "PrintInGDIplusWinEmpty.h"
#include "callBackLinks.h"
#include "observer_subjekt.h"

bool sortBottomUp(const std::pair<int, int> &a, const std::pair<int, int> &b) {
	return a.first > b.first;
}
bool sortTopDown(const std::pair<int, int> &a, const std::pair<int, int> &b) {
	return a.first < b.first;
}
class network {
private:
	static network* instance;
	explicit network::network(const int& width, const int& height) :width(width), height(height) {
		m_cObSptr = std::make_unique<concreteObserverSubjekt>();
	}
	
	network::network(network& other) = delete;
	network::network(network&& other) = delete;
	network& operator=(const network& other) = delete;
	network&& operator=(network&& other) = delete;
	network::~network() {
		
	}
	const int &width;
	const int &height;
	bool lButtonServiceBool = false;
	int xCordinadte_store_LB = 0;
	int yCordinadte_store_LB = 0;
	void(*m_f1PaintBoxLB)(HDC hdc) = nullptr;
	void(*m_f2PaintBoxRB)(HDC hdc) = nullptr;
	void(*m_f3PaintFrame)(HDC hdc) = nullptr;
	void(*m_f4OnPaint)(HDC hdc) = nullptr;
	void(*m_f5PaintLane)(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV, const int &m_numberOfLanes, const std::vector<std::tuple<int, int, int>> &PointsToBePrinted) = nullptr;
	
	void(*m_f7PrintVertexNumber)(HDC hdc, const int &iPosX, const int &iPosY, const int &iVertexID) = nullptr;
	void(*m_f8PaintPoint)(HDC hdc, const std::vector<std::tuple<int, int, int>> &PointsToBePrinted) = nullptr;
	int(*m_callback_getRandomNumber)() = nullptr;// &rSn.getRandomNumber;//&rSn.getRandomNumber;
	void(*m_f10PaintBox)(HDC hdc, const int &param1, const int &param2, const int &param3, const int &param4)=nullptr;
	void(*m_f11PaintWhiteLine)(HDC hdc, const int &param1, const int &param2, const int &param3, const int &param4, const int &param5)=nullptr;
	//HDC m_hdc;
	enum m_numberOfLanes { oneLane = 1, twoLanes = 2 };
	randomSpeed_neu rSn;
	
	//static std::unique_ptr<callBackLinks>& getInstance;
	
public:
	std::unique_ptr<concreteObserverSubjekt> m_cObSptr;
	//int zaehler = 0;
	int serviceInt1 = 0;
	int serviceInt2 = 0;
	HDC m_hdc;
	void(*m_f6PrintLaneInNumbers)(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV) = nullptr;
	callBackLinks m_cbl;
	int iPosXLK = 0;
	int iPosYLK = 0;
	int iPosXRK = 0;
	int iPosYRK = 0;
	PrintInGDIplusWinEmpty m_PWE;
	std::vector<std::tuple<std::pair<int, int>, std::pair<int, int>, bool, m_numberOfLanes>> networkLaneVector;//vertical=true, horizontal=false;
	std::vector<std::unique_ptr<graph>>appliedGraph;
	static network* getInstance(const int& width, const int& height);
	static void destroy();
	
	/*int network::getRandomNumber() {
		return rSn.getRandomNumber();
	}*/
	
	int getRandomNumber() {
		rSn.randomNumberRequest();
		return  rSn.a;
	}
	
	
	

	void network::fieldInitialisation(void(*f1PaintBoxLB)(HDC hdc), void(*f2PaintBoxRB)(HDC hdc), void(*f3PaintFrame)(HDC hdc),
		void(*f4OnPaint)(HDC hdc),
		void(*f5PaintLane)(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV, const int &numberOfLanes, const std::vector<std::tuple<int, int, int>> &PointsToBePrinted),
		void(*f6PrintLaneInNumbers)(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV),
		void(*f7PrintVertexNumber)(HDC hdc, const int &iPosX, const int &iPosY, const int &iVertexID),
		void(*f8PaintPoint)(HDC hdc, const std::vector<std::tuple<int, int, int>> &PointsToBePrinted),
		int (*f9getRandomNumber)(),
		void(*f10PaintBox)(HDC hdc, const int &param1, const int &param2, const int &param3, const int &param4),
		void(*f11PaintWhiteLine)(HDC hdc, const int &param1, const int &param2, const int &param3, const int &param4, const int &param5)
		
	) {
		
		m_f1PaintBoxLB = f1PaintBoxLB;
		m_f2PaintBoxRB = f2PaintBoxRB;
		m_f3PaintFrame = f3PaintFrame;
		m_f4OnPaint = f4OnPaint;
		m_f5PaintLane = f5PaintLane;
		m_f6PrintLaneInNumbers = f6PrintLaneInNumbers;
		m_f7PrintVertexNumber = f7PrintVertexNumber;
		m_f8PaintPoint = f8PaintPoint;
		m_callback_getRandomNumber = f9getRandomNumber;
		m_f10PaintBox = f10PaintBox;
		m_f11PaintWhiteLine = f11PaintWhiteLine;
		iPosXRK = width - 110;
		iPosYRK = height - 110;
		
		m_cbl.m_f10PaintBox = m_f10PaintBox;
		m_cbl.m_f11PaintWhiteLine = m_f11PaintWhiteLine;
		iPosYRK = height - 110;
		//m_cbl = std::move(callBackLinks::getInstance());
	}
	void network::fieldRecalibarte(HDC hdc) {
		m_hdc = hdc;
		iPosXRK = width - 110;
		iPosYRK = height - 110;
		
		
		//m_cbl->m_hdc = hdc;
	}

	bool  network::establishLane(HDC hdc, const int& numberOfLanes) {
		m_hdc = hdc;
		int laneNumbers = 0;
		if (numberOfLanes == 1) {
			laneNumbers = m_numberOfLanes::oneLane;
			laneNumbers = 1;
		}
		if (numberOfLanes == 2) {
			laneNumbers = m_numberOfLanes::twoLanes;
			if (numberOfLanes == m_numberOfLanes::twoLanes) {
				laneNumbers = 2;
			}
		}

		bool horizontalOrVertival = true;
		std::tuple<std::pair<int, int>, std::pair<int, int>, bool, m_numberOfLanes> laneCoordinate;
		std::pair<int, int> startingPoint;
		std::pair<int, int> endingPoint;
		if (lButtonServiceBool == false) {
			lButtonServiceBool = true;
			xCordinadte_store_LB = iPosXLK;
			yCordinadte_store_LB = iPosYLK;
			m_f1PaintBoxLB(m_hdc);
			//m_f4OnPaint(m_hdc);
			//startingPoint = std::make_pair(iPosXLK, iPosYLK);
			startingPoint.first = iPosXLK;
			startingPoint.second = iPosYLK;
			endingPoint.first = 0;
			endingPoint.second = 0;
			//m_f6PrintLaneInNumbers(m_hdc, startingPoint.first, startingPoint.second, endingPoint.first, endingPoint.second, true);


		}
		else {//true	  

			  //m_f5PaintLane(m_hdc, xCordinadte_store_LB, yCordinadte_store_LB, iPosXLK, iPosYLK,true);
			lButtonServiceBool = false;
			//Links unten
			if (((iPosXLK - xCordinadte_store_LB) >= 0) && ((iPosYLK - yCordinadte_store_LB) >= 0)) {
				if (((-iPosXLK + xCordinadte_store_LB)) < (-iPosYLK + yCordinadte_store_LB)) {
					endingPoint.first = iPosXLK;
					endingPoint.second = yCordinadte_store_LB;
					horizontalOrVertival = true;
				}
				else {
					endingPoint.first = xCordinadte_store_LB;
					endingPoint.second = iPosYLK;
					horizontalOrVertival = false;
				}
			}
			//Links Oben
			else if (((iPosXLK - xCordinadte_store_LB) >= 0) && ((iPosYLK - yCordinadte_store_LB) <= 0)) {
				if (((-iPosXLK + xCordinadte_store_LB)) < (iPosYLK - yCordinadte_store_LB)) {
					endingPoint.first = iPosXLK;
					endingPoint.second = yCordinadte_store_LB;
					horizontalOrVertival = true;
				}
				else {
					endingPoint.first = xCordinadte_store_LB;
					endingPoint.second = iPosYLK;
					horizontalOrVertival = false;
				}
			}
			//Rechts oben
			else if (((iPosXLK - xCordinadte_store_LB) <= 0) && ((iPosYLK - yCordinadte_store_LB) <= 0)) {
				if (((iPosXLK - xCordinadte_store_LB)) < (iPosYLK - yCordinadte_store_LB)) {
					endingPoint.first = iPosXLK;
					endingPoint.second = yCordinadte_store_LB;
					horizontalOrVertival = true;
				}
				else {
					endingPoint.first = xCordinadte_store_LB;
					endingPoint.second = iPosYLK;
					horizontalOrVertival = false;
				}
			}
			//Rechts unten
			else if (((iPosXLK - xCordinadte_store_LB) <= 0) && ((iPosYLK - yCordinadte_store_LB) >= 0)) {
				if (((iPosXLK - xCordinadte_store_LB)) < (-iPosYLK + yCordinadte_store_LB)) {
					endingPoint.first = iPosXLK;
					endingPoint.second = yCordinadte_store_LB;
					horizontalOrVertival = true;
				}
				else {
					endingPoint.first = xCordinadte_store_LB;
					endingPoint.second = iPosYLK;
					horizontalOrVertival = false;
				}
			}
			//^^^^Lagebestimmung der Edges ***
			else if (((iPosXLK - xCordinadte_store_LB) != 0) && ((iPosYLK - yCordinadte_store_LB) == 0)) {
				endingPoint.first = iPosXLK;
				endingPoint.second = iPosYLK;
				horizontalOrVertival = true;
			}
			else if (((iPosXLK - xCordinadte_store_LB) == 0) && ((iPosYLK - yCordinadte_store_LB) != 0)) {
				endingPoint.first = iPosXLK;
				endingPoint.second = iPosYLK;
				horizontalOrVertival = false;
				//^^^^Lagebestimmung der Edges ***Konkretisierung
			}
			else {
				lButtonServiceBool = true;//Fehler Abbruch!
			}



			if (lButtonServiceBool == false) {//Fortsetzung wenn kein Fehler!
				startingPoint.first = xCordinadte_store_LB;
				startingPoint.second = yCordinadte_store_LB;
				if (laneNumbers == 1) {
					laneCoordinate = std::make_tuple(startingPoint, endingPoint, horizontalOrVertival, oneLane);//oneLane
				}
				if (laneNumbers == 2) {
					laneCoordinate = std::make_tuple(startingPoint, endingPoint, horizontalOrVertival, twoLanes);//twoLanes
				}
				//m_f6PrintLaneInNumbers(m_hdc, std::get<0>(laneCoordinate).first, std::get<0>(laneCoordinate).second, std::get<1>(laneCoordinate).first, std::get<1>(laneCoordinate).second, std::get<2>(laneCoordinate));

				bool addCoordinate = true;
				int secondLaneExtension = -10;
				bool secondLaneExist = false;
				if ((std::get<0>(laneCoordinate).first) == (std::get<1>(laneCoordinate).first)) {
					if ((std::get<0>(laneCoordinate).second) - (std::get<1>(laneCoordinate).second) <= -40) {
						addCoordinate = true;
					}
					else if ((std::get<0>(laneCoordinate).second - std::get<1>(laneCoordinate).second) >= 40) {
						addCoordinate = true;
					}
					else {
						addCoordinate = false;
					}
				}
				if (std::get<0>(laneCoordinate).second == std::get<1>(laneCoordinate).second) {
					if ((std::get<0>(laneCoordinate).first - std::get<1>(laneCoordinate).first) <= -40) {
						addCoordinate = true;
					}
					else if ((std::get<0>(laneCoordinate).first - std::get<1>(laneCoordinate).first) >= 40) {
						addCoordinate = true;
					}
					else {
						addCoordinate = false;
					}
				}
				do {
					for (auto &i : networkLaneVector) {
						if ((std::get<3>(i) == twoLanes) || (std::get<3>(laneCoordinate) == twoLanes)) {
							secondLaneExist = true;
						}

						if (((std::get<0>(laneCoordinate).first) < (std::get<1>(laneCoordinate).first)) || ((std::get<0>(laneCoordinate).second) < (std::get<1>(laneCoordinate).second))) {
							//Links->Rechts bzw. Oben->Unten
							if ((((std::get<0>(i).second)) == ((std::get<0>(laneCoordinate).second) + secondLaneExtension)) && ((((std::get<1>(i).second)) == ((std::get<1>(laneCoordinate).second) + secondLaneExtension)))) {
								//addCoordinate = false;

								if ((std::get<0>(i).first) < (std::get<1>(i).first)) {
									//fertig(3)

									if (((std::get<1>(i).first) <= (std::get<0>(laneCoordinate).first))) {
										//addCoordinate = true;

									}
									else if ((std::get<1>(laneCoordinate).first) < (std::get<0>(i).first)) {

									}
									else {
										addCoordinate = false;

									}
								}
								else {//(std::get<0>(i).first) >= (std::get<1>(i).first)

									if (((std::get<0>(i).first) >= (std::get<1>(laneCoordinate).first)) && ((std::get<0>(i).first)<(std::get<0>(laneCoordinate).first))) {
										//addCoordinate = true;

									}
									else if ((std::get<1>(laneCoordinate).first) < (std::get<1>(i).first)) {
										//addCoordinate = false;

									}
									else {
										//addCoordinate = false;

									}
								}
							}


							else if (((std::get<0>(i).first) == ((std::get<0>(laneCoordinate).first) + secondLaneExtension)) && ((std::get<1>(i).first) == ((std::get<1>(laneCoordinate).first) + secondLaneExtension))) {
								if ((std::get<0>(i).second) < (std::get<1>(i).second)) {
									//addCoordinate = false;
									//fertig(1)
									if (std::get<1>(i).second <= (std::get<0>(laneCoordinate).second)) {
										//addCoordinate = true;
									}
									else if ((std::get<1>(laneCoordinate).second) < std::get<0>(i).second) {
										//addCoordinate = true;
									}
									else {
										addCoordinate = false;
									}
								}
								else {
									//fertig(2)
									if ((std::get<0>(i).second) < (std::get<0>(laneCoordinate).second)) {

									}
									else if ((std::get<1>(laneCoordinate).second) < (std::get<1>(i).second)) {

									}
									else {
										addCoordinate = false;
									}
								}
							}
							else {

							}
						}
						else {
							//Rechts->Links bzw. Unten->Oben
							if (((std::get<0>(i).second) == ((std::get<0>(laneCoordinate).second) + secondLaneExtension)) && ((std::get<1>(i).second) == ((std::get<1>(laneCoordinate).second) + secondLaneExtension))) {
								if ((std::get<0>(i).first)<(std::get<1>(i).first)) {
									if ((std::get<1>(i).first) <= (std::get<1>(laneCoordinate).first)) {
										//addCoordinate = true;
									}
									else if ((std::get<0>(laneCoordinate).first) < (std::get<0>(i).first)) {
										//addCoordinate = true;
									}
									else {
										addCoordinate = false;
									}
								}
								else {
									if (((std::get<0>(i).first) >= (std::get<0>(laneCoordinate).first)) && ((std::get<1>(laneCoordinate).first) > (std::get<1>(i).first))) {
										//addCoordinate = true;
									}
									else if (((std::get<0>(i).first) <= (std::get<0>(laneCoordinate).first)) && ((std::get<0>(i).first)<(std::get<1>(laneCoordinate).first))) {

									}
									else if (((std::get<1>(i).first) >= (std::get<0>(laneCoordinate).first)) && ((std::get<1>(i).first)>(std::get<1>(laneCoordinate).first))) {

									}
									else {
										addCoordinate = false;
									}
								}
							}
							else if (((std::get<0>(i).first) == ((std::get<0>(laneCoordinate).first) + secondLaneExtension)) && ((std::get<1>(i).first) == ((std::get<1>(laneCoordinate).first) + secondLaneExtension))) {
								if ((std::get<0>(i).second) < (std::get<1>(i).second)) {
									if ((std::get<1>(i).second) <= (std::get<1>(laneCoordinate).second)) {

									}
									else if ((std::get<0>(laneCoordinate).second) < (std::get<0>(i).second)) {

									}
									else {
										addCoordinate = false;
									}
								}
								else {
									if ((std::get<1>(i).second) >= (std::get<0>(laneCoordinate).second)) {

									}
									else if ((std::get<1>(laneCoordinate).second) > (std::get<0>(i).second)) {

									}
									else {
										addCoordinate = false;
									}
								}
							}
							else {
								//addCoordinate = true;
							}
						}
					}
					if ((secondLaneExist = false) && (secondLaneExtension == 10)) {
						break;
					}
					secondLaneExtension = secondLaneExtension + 10;

				} while (secondLaneExtension <= 20);
				if (addCoordinate == true) {
					if (std::get< 3 >(laneCoordinate) == oneLane) {
						networkLaneVector.push_back(laneCoordinate);
					}
					if (std::get<3>(laneCoordinate) == twoLanes) {
						if (((std::get<0>(laneCoordinate).first) <= (width - 110)) &&
							((std::get<1>(laneCoordinate).first) <= (width - 110)) &&
							((std::get<0>(laneCoordinate).second) <= (height - 80)) &&
							((std::get<1>(laneCoordinate).second) <= (height - 80))) {
							networkLaneVector.push_back(laneCoordinate);
						}
					}
				}
				xCordinadte_store_LB = 0;
				yCordinadte_store_LB = 0;
			}
			//m_f6PrintLaneInNumbers(m_hdc, iPosXLk, iPosYLk, iPosXRk, iPosYRk, HorV);
			//m_f6PrintLaneInNumbers(m_hdc, startingPoint.first, startingPoint.second, endingPoint.first, endingPoint.second, true);
		}
		m_f1PaintBoxLB(m_hdc);
		m_f2PaintBoxRB(m_hdc);
		//m_f6PrintLaneInNumbers(m_hdc, std::get<0>(laneCoordinate).first, std::get<0>(laneCoordinate).second, std::get<1>(laneCoordinate).first, std::get<1>(laneCoordinate).second, std::get<2>(laneCoordinate));
		//showGraph();
		//printLanesAndVehiclesOfAllEdges();
		return(lButtonServiceBool);
	}
	/*void network::showGraph() {
		
		int nOL = 0;
		std::vector<std::tuple<int, int, int>> PointsToBePrinted;
		PointsToBePrinted.push_back(std::make_tuple(0, 0, 0));
		for (auto &i : networkLaneVector) {
			nOL = std::get<3>(i);
			m_f5PaintLane(m_hdc, std::get<0>(i).first, std::get<0>(i).second, std::get<1>(i).first, std::get<1>(i).second, std::get<2>(i), nOL, PointsToBePrinted);
			m_f6PrintLaneInNumbers(m_hdc, std::get<0>(i).first, std::get<0>(i).second, std::get<1>(i).first, std::get<1>(i).second, std::get<2>(i));
			m_f6PrintLaneInNumbers(m_hdc,networkLaneVector.size(),0,0,0,true);
		}
		PointsToBePrinted.clear();
	}*/
	/*void network::showVertex() {
		
		m_f3PaintFrame(m_hdc);
		
		for (auto &i : appliedGraph) {
			i->showVertex();
		}
	}*/
	

	void  network::establishVertexOfGraph() {
		
		std::vector<std::tuple<std::pair<int, int>, std::pair<int, int>, bool, m_numberOfLanes>>::iterator estVerITER = networkLaneVector.begin();
		std::vector<std::tuple<std::pair<int, int>, std::pair<int, int>, bool, m_numberOfLanes>>::iterator estVerITERA = networkLaneVector.begin();
		std::vector<std::unique_ptr<vertex>>vertexOfGraphPtrVectorConainer;
		std::vector<std::unique_ptr<edge>>edgeOfGraphPtrContainer;
		xCordinadte_store_LB = 0;
		yCordinadte_store_LB = 0;
		iPosXLK = 0;
		iPosYLK = 0;
		iPosXRK = 0;
		iPosYRK = 0;

		for (estVerITER = networkLaneVector.begin(); estVerITER != networkLaneVector.end(); ++estVerITER) {


			if (std::get<2>(*estVerITER) == true) {
				iPosXRK++;
				if (std::get<0>(*estVerITER).first < std::get<1>(*estVerITER).first) {
					if (std::get<1>(*estVerITER).first > xCordinadte_store_LB) {
						xCordinadte_store_LB = std::get<1>(*estVerITER).first;
					}
				}
				else {
					if (std::get<0>(*estVerITER).first > xCordinadte_store_LB) {
						xCordinadte_store_LB = std::get<0>(*estVerITER).first;
					}
				}

			}
			if (std::get<2>(*estVerITER) == false) {
				iPosYRK++;
				if (std::get<0>(*estVerITER).second < std::get<1>(*estVerITER).second) {
					if (std::get<1>(*estVerITER).second > yCordinadte_store_LB) {
						yCordinadte_store_LB = std::get<1>(*estVerITER).second;
					}
				}
				else {
					if (std::get<0>(*estVerITER).second > yCordinadte_store_LB) {
						yCordinadte_store_LB = std::get<0>(*estVerITER).second;
					}
				}
			}

		}
		

		while (xCordinadte_store_LB > 0) {
			estVerITER = networkLaneVector.begin();
			while (estVerITER != networkLaneVector.end()) {
				if ((std::get<0>(*estVerITER).first + 10 == xCordinadte_store_LB) && (std::get<2>(*estVerITER) == false)) {
					estVerITERA = networkLaneVector.begin();
					while (estVerITERA != networkLaneVector.end()) {
						if ((std::get<2>(*estVerITERA) == true) && (std::get<0>(*estVerITERA).first == xCordinadte_store_LB)) {
							if (std::get<0>(*estVerITER).second < std::get<1>(*estVerITER).second) {
								if ((std::get<0>(*estVerITER).second <= std::get<0>(*estVerITERA).second) && (std::get<1>(*estVerITERA).second <= std::get<1>(*estVerITER).second)) {
									std::get<0>(*estVerITERA).first = std::get<0>(*estVerITERA).first - 10;
								}
							}
							else {
								if ((std::get<1>(*estVerITER).second <= std::get<0>(*estVerITERA).second) && (std::get<1>(*estVerITERA).second <= std::get<0>(*estVerITER).second)) {
									std::get<0>(*estVerITERA).first = std::get<0>(*estVerITERA).first - 10;
								}
							}

						}
						if ((std::get<2>(*estVerITERA) == true) && (std::get<1>(*estVerITERA).first == xCordinadte_store_LB)) {
							if (std::get<0>(*estVerITER).second < std::get<1>(*estVerITER).second) {
								if ((std::get<0>(*estVerITER).second <= std::get<0>(*estVerITERA).second) && (std::get<1>(*estVerITERA).second <= std::get<1>(*estVerITER).second)) {
									std::get<1>(*estVerITERA).first = std::get<1>(*estVerITERA).first - 10;
								}
							}
							else {
								if ((std::get<1>(*estVerITER).second <= std::get<0>(*estVerITERA).second) && (std::get<1>(*estVerITERA).second <= std::get<0>(*estVerITER).second)) {
									std::get<1>(*estVerITERA).first = std::get<1>(*estVerITERA).first - 10;
								}
							}

						}

						++estVerITERA;

					}
				}
				++estVerITER;
			}
			xCordinadte_store_LB = xCordinadte_store_LB - 10;
		}
		while (yCordinadte_store_LB > 0) {
			estVerITER = networkLaneVector.begin();
			while (estVerITER != networkLaneVector.end()) {
				if ((std::get<0>(*estVerITER).second + 10 == yCordinadte_store_LB) && (std::get<2>(*estVerITER) == true)) {
					estVerITERA = networkLaneVector.begin();
					while (estVerITERA != networkLaneVector.end()) {
						if ((std::get<2>(*estVerITERA) == false) && (std::get<0>(*estVerITERA).second == yCordinadte_store_LB)) {
							if (std::get<0>(*estVerITER).first < std::get<1>(*estVerITER).first) {
								if ((std::get<0>(*estVerITER).first <= std::get<0>(*estVerITERA).first) && (std::get<1>(*estVerITERA).first <= std::get<1>(*estVerITER).first)) {
									std::get<0>(*estVerITERA).second = std::get<0>(*estVerITERA).second - 10;
								}
							}
							else {
								if ((std::get<1>(*estVerITER).first <= std::get<0>(*estVerITERA).first) && (std::get<1>(*estVerITERA).first <= std::get<0>(*estVerITER).first)) {
									std::get<0>(*estVerITERA).second = std::get<0>(*estVerITERA).second - 10;
								}
							}

						}
						if ((std::get<2>(*estVerITERA) == false) && (std::get<1>(*estVerITERA).second == yCordinadte_store_LB)) {
							if (std::get<0>(*estVerITER).first < std::get<1>(*estVerITER).first) {
								if ((std::get<0>(*estVerITER).first <= std::get<0>(*estVerITERA).first) && (std::get<1>(*estVerITERA).first <= std::get<1>(*estVerITER).first)) {
									std::get<1>(*estVerITERA).second = std::get<1>(*estVerITERA).second - 10;
								}
							}
							else {
								if ((std::get<1>(*estVerITER).first <= std::get<0>(*estVerITERA).first) && (std::get<1>(*estVerITERA).first <= std::get<0>(*estVerITER).first)) {
									std::get<1>(*estVerITERA).second = std::get<1>(*estVerITERA).second - 10;
								}
							}

						}
						++estVerITERA;
					}
				}
				++estVerITER;
			}
			yCordinadte_store_LB = yCordinadte_store_LB - 10;
		}

		
		vertexOfGraphPtrVectorConainer.clear();
		edgeOfGraphPtrContainer.clear();
		for (int columnIterator = 0; columnIterator <= width; columnIterator = columnIterator + 10) {
			for (auto &i : networkLaneVector) {
				//m_f6PrintLaneInNumbers(m_hdc, std::get<2>(i), std::get<0>(i).second, std::get<1>(i).first, std::get<1>(i).second, true);
				if ((std::get<0>(i).first == columnIterator) && (std::get<1>(i).first == columnIterator) && (std::get<2>(i) == false)) {//Spalte senkrecht prüfen!
					int firstYcoordinate = std::get<0>(i).second;
					int secondYcoordinate = std::get<1>(i).second;
					if (firstYcoordinate < secondYcoordinate) {
						firstYcoordinate = firstYcoordinate - 10;
						for (firstYcoordinate; firstYcoordinate <= secondYcoordinate; firstYcoordinate = firstYcoordinate + 10) {
							for (auto &innerItA : networkLaneVector) {
								if (
									(std::get<2>(innerItA) == true) &&//waagrecht
									(std::get<0>(innerItA).second == firstYcoordinate) &&//Lage im Senkrechten
									(
									((std::get<0>(innerItA).first <= columnIterator) && (columnIterator <= std::get<1>(innerItA).first)) ||
										((std::get<1>(innerItA).first <= columnIterator) && (columnIterator <= std::get<0>(innerItA).first))
										)
									)
								{
									//1)bool ob waagrecht, 2) Festellung Y Ebene, 3)Feststellung im X-Bereich
									std::pair<int, int> numberOfLanesInHandV;
									numberOfLanesInHandV.first = std::get<3>(i);//Anzahl der Fahrstreifen Vertikal
									numberOfLanesInHandV.second = std::get<3>(innerItA);//Anzahl der Fahrstreifen Horizontal
									
									
									
									if ((std::get<0>(innerItA).first == std::get<0>(i).first) && (std::get<0>(innerItA).second == std::get<0>(i).second)) {//Sonderfall BeginnEckpunkt
										//v1 = std::make_shared<vertex>(std::get<0>(innerItA).first, std::get<0>(innerItA).second, 1);
										//std::unique_ptr<vertex> v1=std::make_unique<vertex>(std::get<0>(innerItA).first, std::get<0>(innerItA).second, 1);
										vertexOfGraphPtrVectorConainer.push_back(std::make_unique<vertexStart>(std::get<0>(innerItA).first, std::get<0>(innerItA).second, 1));
									}
									else if ((std::get<1>(innerItA).first == std::get<1>(i).first) && (std::get<1>(innerItA).second == std::get<1>(i).second)) {//Sonderfall SchlussEckpunkt
										//v1 = std::make_shared<vertex>(std::get<1>(innerItA).first, std::get<1>(innerItA).second, 2);
										//std::unique_ptr<vertex> v2 =std::make_unique<vertex>(std::get<1>(innerItA).first, std::get<1>(innerItA).second, 2);
										vertexOfGraphPtrVectorConainer.push_back(std::make_unique<vertexEnd>(std::get<1>(innerItA).first, std::get<1>(innerItA).second, 2));
									}
									else {
										//std::unique_ptr<vertex> v3 =std::make_unique<vertex>(columnIterator, firstYcoordinate, numberOfLanesInHandV);
										vertexOfGraphPtrVectorConainer.push_back(std::make_unique<vertexFlex>(columnIterator, firstYcoordinate, numberOfLanesInHandV));
									}
									

								}
								else {
									//No Crossing-Vertex foun1d
								}
							}

						}
					}
					else if (firstYcoordinate > secondYcoordinate) {
						for (secondYcoordinate; secondYcoordinate <= firstYcoordinate; secondYcoordinate = secondYcoordinate + 10) {
							for (auto &innerItB : networkLaneVector) {
								if (
									(std::get<2>(innerItB) == true) &&
									(std::get<0>(innerItB).second == secondYcoordinate) &&
									(
									((std::get<0>(innerItB).first <= columnIterator) && (columnIterator <= std::get<1>(innerItB).first)) ||
										((std::get<1>(innerItB).first <= columnIterator) && (columnIterator <= std::get<0>(innerItB).first))
										)
									)
								{
									//1)bool ob waagrecht, 2) Festellung Y Ebene, 3)Feststellung im X-Bereich
									std::pair<int, int> numberOfLanesInHandV;
									numberOfLanesInHandV.first = std::get<3>(i);
									numberOfLanesInHandV.second = std::get<3>(innerItB);
									//std::shared_ptr<vertex>v2=std::make_shared<vertex>(columnIterator, secondYcoordinate, std::get<3>(i), std::get<3>(innerItB));
									//std::shared_ptr<vertex>v2 = std::make_shared<vertex>(columnIterator, secondYcoordinate, numberOfLanesInHandV);
									
									if ((std::get<0>(innerItB).first == std::get<0>(i).first) && (std::get<0>(innerItB).second == std::get<0>(i).second)) {//Sonderfall BeginnEckpunkt
										//v2 = std::make_shared<vertex>(std::get<0>(innerItB).first, std::get<0>(innerItB).second, 1);
										//std::unique_ptr<vertex> v4 =std::make_unique<vertex>(std::get<0>(innerItB).first, std::get<0>(innerItB).second, 1);
										vertexOfGraphPtrVectorConainer.push_back(std::make_unique<vertexStart>(std::get<0>(innerItB).first, std::get<0>(innerItB).second, 1));
									}
									else if ((std::get<1>(innerItB).first == std::get<1>(i).first) && (std::get<1>(innerItB).second == std::get<1>(i).second)) {//Sonderfall SchlussEckpunkt
										//v2 = std::make_shared<vertex>(std::get<1>(innerItB).first, std::get<1>(innerItB).second, 2);
										//std::unique_ptr<vertex> v5 =std::make_unique<vertex>(std::get<1>(innerItB).first, std::get<1>(innerItB).second, 2);
										vertexOfGraphPtrVectorConainer.push_back(std::make_unique<vertexEnd>(std::get<1>(innerItB).first, std::get<1>(innerItB).second, 2));
									}
									else {
										//std::unique_ptr<vertex> v6 =std::make_unique<vertex>(columnIterator, secondYcoordinate, numberOfLanesInHandV);
										vertexOfGraphPtrVectorConainer.push_back(std::make_unique<vertexFlex>(columnIterator, secondYcoordinate, numberOfLanesInHandV));
									}
									
								}
								else {
									//No Crossing-Vertex foun1d
								}
							}
						}
					}
					else {
						//m_f6PrintLaneInNumbers(m_hdc, std::get<0>(i).first, std::get<0>(i).second, std::get<1>(i).first, std::get<1>(i).second, true);
						//m_f6PrintLaneInNumbers(m_hdc, std::get<0>(i).first, std::get<0>(i).second, std::get<1>(i).first, std::get<1>(i).second, true);
						//m_f6PrintLaneInNumbers(m_hdc, std::get<0>(i).first, std::get<0>(i).second, std::get<1>(i).first, std::get<1>(i).second, true);
						//Catch Problem!
						//FristYCoordinate==SecondYCoordinate
					}
				}
			}
		}
		

		if (!vertexOfGraphPtrVectorConainer.empty()) {
			//showContentofVertexContainter()

			bool serviceBoolFirstVertex = false;
			bool serviceBoolSecondVertex = false;
			bool serviceBoolEndVertexCheck = false;

			for (auto &iC : networkLaneVector) {
				serviceBoolFirstVertex = true;
				serviceBoolSecondVertex = true;

				//std::shared_ptr<vertex>v3 = std::make_shared<vertex>(std::get<0>(iC).first, std::get<0>(iC).second, 1, std::get<3>(iC));
				std::unique_ptr<vertex> v7=std::make_unique<vertexStart>(std::get<0>(iC).first, std::get<0>(iC).second, 1, std::get<3>(iC));

				//std::shared_ptr<vertex>v4 = std::make_shared<vertex>(std::get<1>(iC).first, std::get<1>(iC).second, 2, std::get<3>(iC));
				std::unique_ptr<vertex> v8 = std::make_unique<vertexEnd>(std::get<1>(iC).first, std::get<1>(iC).second, 2, std::get<3>(iC));

				for (auto &iD : vertexOfGraphPtrVectorConainer) {
					if ((v7->m_XcoordinateVertex == iD->m_XcoordinateVertex) && (v7->m_YcoordinateVertex == iD->m_YcoordinateVertex)) {
						serviceBoolFirstVertex = false;
						if ((iD->m_shapeOfThatVertex == begin) || (iD->m_shapeOfThatVertex == oneByone) || (iD->m_shapeOfThatVertex == oneBytwo) || (iD->m_shapeOfThatVertex == twoByone) || (iD->m_shapeOfThatVertex == twoBytwo)) {

						}
						else if (iD->m_shapeOfThatVertex == end) {
							iD->changeVertexPurpose();
						}
						else {
							iD->m_shapeOfThatVertex = undefindShape;
						}
					}

					if ((v8->m_XcoordinateVertex == iD->m_XcoordinateVertex) && (v8->m_YcoordinateVertex == iD->m_YcoordinateVertex)) {
						serviceBoolSecondVertex = false;
						if ((iD->m_shapeOfThatVertex == end) || (iD->m_shapeOfThatVertex == oneByone) || (iD->m_shapeOfThatVertex == oneBytwo) || (iD->m_shapeOfThatVertex == twoByone) || (iD->m_shapeOfThatVertex == twoBytwo)) {

						}
						else if (iD->m_shapeOfThatVertex == begin) {
							iD->changeVertexPurpose();
						}
						else {
							iD->m_shapeOfThatVertex = undefindShape;
						}
					}

				}
				if (serviceBoolFirstVertex == true) {
					vertexOfGraphPtrVectorConainer.push_back(std::move(v7));
				}
				if (serviceBoolSecondVertex == true) {
					vertexOfGraphPtrVectorConainer.push_back(std::move(v8));
				}
			}
		}
		else {
			for (auto &iCa : networkLaneVector) {
				//std::shared_ptr<vertex>v3a = std::make_shared<vertex>(std::get<0>(iCa).first, std::get<0>(iCa).second, 1, std::get<3>(iCa));
				vertexOfGraphPtrVectorConainer.push_back(std::make_unique<vertexStart>(std::get<0>(iCa).first, std::get<0>(iCa).second, 1, std::get<3>(iCa)));//StartVertex
				//std::shared_ptr<vertex>v4a = std::make_shared<vertex>(std::get<1>(iCa).first, std::get<1>(iCa).second, 2, std::get<3>(iCa));
				vertexOfGraphPtrVectorConainer.push_back(std::make_unique<vertexEnd>(std::get<1>(iCa).first, std::get<1>(iCa).second, 2, std::get<3>(iCa)));//EndVertex
			}
		}
		//showVertex(m_hdc);
		//**************Aussortierung von doppelt vorkommenden Vertex!
		std::vector<std::tuple<int, int, int, int>> vectorOfDubbleVertex;
		std::vector<std::tuple<int, int, int, int>>::iterator iv = vectorOfDubbleVertex.begin();
		int counter = 0;



		for (auto &iEb : vertexOfGraphPtrVectorConainer) {
			//m_f6PrintLaneInNumbers(m_hdc, iEb->m_XcoordinateVertex, iEb->m_YcoordinateVertex, iEb->m_numberOfLanes.first, iEb->m_vertexID, true);
			iPosXLK = iEb->m_XcoordinateVertex;
			iPosYLK = iEb->m_YcoordinateVertex;
			xCordinadte_store_LB = 0;
			if (iEb->m_vertexID != 999) {
				for (auto &iEc : vertexOfGraphPtrVectorConainer) {
					if ((iEb->m_XcoordinateVertex == iEc->m_XcoordinateVertex) && (iEb->m_YcoordinateVertex == iEc->m_YcoordinateVertex)) {
						xCordinadte_store_LB++;
						if (xCordinadte_store_LB >= 2) {
							iEc->m_vertexID = 999;
						}
					}

				}
			}
			if (xCordinadte_store_LB >= 2) {
				counter = 0;
				for (auto &iEd : vertexOfGraphPtrVectorConainer) {
					if ((iPosXLK == iEd->m_XcoordinateVertex) && (iPosYLK == iEd->m_YcoordinateVertex)) {
						//iEd->m_shapeOfThatVertex = transision;
						vectorOfDubbleVertex.push_back(std::make_tuple(iEd->m_XcoordinateVertex, iEd->m_YcoordinateVertex, counter, iEd->m_shapeOfThatVertex));
					}
					counter++;
				}
			}
		}

		if (vectorOfDubbleVertex.size() > 0) {
			std::shared_ptr<vertex>v5;
			iv = vectorOfDubbleVertex.begin();
			counter = 0;
			do
			{
				//m_f6PrintLaneInNumbers(m_hdc, 999, counter, std::get<2>(*iv), std::get<2>(*iv) - counter, true);
				//m_f6PrintLaneInNumbers(m_hdc, 888, vertexOfGraphPtrVectorConainer.size(), 0, vectorOfDubbleVertex.size(), true);
				vertexOfGraphPtrVectorConainer.erase(vertexOfGraphPtrVectorConainer.begin() + (std::get<2>(*iv) - counter));
				counter++;
				++iv;
			} while (iv != vectorOfDubbleVertex.end());
			
			iv = vectorOfDubbleVertex.begin();
			counter = 0;
			iPosXLK = std::get<0>(*iv);
			iPosYLK = std::get<1>(*iv);
			std::vector<std::tuple<int, int, int>> sortVector;
			
			while (iv != vectorOfDubbleVertex.end())
			{
				//m_f6PrintLaneInNumbers(m_hdc, std::get<0>(*iv), std::get<1>(*iv), std::get<2>(*iv), std::get<3>(*iv), true);
				counter = 0;
				if (sortVector.empty()) {
					sortVector.push_back(std::make_tuple(std::get<0>(*iv), std::get<1>(*iv), std::get<3>(*iv)));
				}
				else {
					for (auto &i : sortVector) {
						if ((std::get<0>(*iv) == std::get<0>(i)) && (std::get<1>(*iv) == std::get<1>(i))) {
							if (std::get<3>(*iv) != std::get<2>(i)) {
								std::get<2>(i) = 11;
							}
							counter++;
						}
					}
					if (counter == 0) {
						sortVector.push_back(std::make_tuple(std::get<0>(*iv), std::get<1>(*iv), std::get<3>(*iv)));
					}
				}
				++iv;
			}
			for (auto &i : sortVector) {
				vertexOfGraphPtrVectorConainer.push_back(std::make_unique<vertexFlex>(std::get<0>(i), std::get<1>(i), std::get<2>(i)));
				//m_f6PrintLaneInNumbers(m_hdc, std::get<0>(i), std::get<1>(i), std::get<2>(i), 0, true);
			}
			
		}
		vectorOfDubbleVertex.clear();
		iPosXLK = 0;
		iPosYLK = 0;
		iPosXRK = 0;
		iPosYRK = 0;

		//*******************************************************
		//Nummerierung der Knoten(Vertex):
		counter = 1;
		for (auto &iEb : vertexOfGraphPtrVectorConainer) {
			iEb->numberingOfVertexes(counter);
			counter++;
		}
		
		//******************
		//Graphenerstellung

		std::vector<std::pair<int, int>>VectorOfVertex = {};
		VectorOfVertex.clear();
		std::pair<int, int> VertexIDofEdges;
		std::pair<int, int>CrossingVertex;
		for (auto &iF : networkLaneVector) {
			
			iPosXLK = std::get<0>(iF).first;
			iPosXRK = std::get<1>(iF).first;
			iPosYLK = std::get<0>(iF).second;
			iPosYRK = std::get<1>(iF).second;
			if ((std::get<0>(iF).first == std::get<1>(iF).first) && (std::get<0>(iF).second != std::get<1>(iF).second)) {//vertikalstd::get<2>(iF) == false
				if (std::get<0>(iF).second < std::get<1>(iF).second) {//positiv
					VectorOfVertex.clear();

					for (auto &iG : vertexOfGraphPtrVectorConainer) {
						if ((iG->m_XcoordinateVertex == std::get<0>(iF).first) && (iG->m_YcoordinateVertex == std::get<0>(iF).second)) {
							VertexIDofEdges.first = iG->m_vertexID;

						}
						if ((iG->m_XcoordinateVertex == std::get<1>(iF).first) && (iG->m_YcoordinateVertex == std::get<1>(iF).second)) {
							VertexIDofEdges.second = iG->m_vertexID;

						}


						if (((iG->m_XcoordinateVertex == std::get<0>(iF).first) && (iG->m_YcoordinateVertex != std::get<0>(iF).second))
							&& ((iG->m_XcoordinateVertex == std::get<1>(iF).first) && (iG->m_YcoordinateVertex != std::get<1>(iF).second))) {


							if ((iPosYLK<iG->m_YcoordinateVertex) && (iG->m_YcoordinateVertex<iPosYRK)) {
								CrossingVertex.first = iG->m_YcoordinateVertex;
								CrossingVertex.second = iG->m_vertexID;

								VectorOfVertex.push_back(CrossingVertex);
							}


						}
					}

					//*****
					if (!VectorOfVertex.empty()) {
						CrossingVertex.first = std::get<0>(iF).second;		//Vertikal positiv mit Vertexunterbrechung!
						CrossingVertex.second = VertexIDofEdges.first;
						VectorOfVertex.push_back(CrossingVertex);
						CrossingVertex.first = std::get<1>(iF).second;
						CrossingVertex.second = VertexIDofEdges.second;
						VectorOfVertex.push_back(CrossingVertex);
						std::sort(VectorOfVertex.begin(), VectorOfVertex.end(), sortTopDown);

						int iterator = 0;
						int a = 0;
						for (auto &i : VectorOfVertex) {
							if (iterator != 0) {
								//m_f6PrintLaneInNumbers(m_hdc, 1, a, i.second, 0, false);
								//std::shared_ptr<edge> e5 = std::make_shared<edge>(a, i.second, getPtrOfVertex(a), getPtrOfVertex(i.second), m_hdc, m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers);
								//edgeOfGraphPtrContainer.push_back(std::make_unique<edge>(a, i.second,  m_hdc, m_callback_getRandomNumber, m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers));
								edgeOfGraphPtrContainer.push_back(std::make_unique<edge>(a, i.second, m_hdc, 
									choosePrintPattern(vertexOfGraphPtrVectorConainer[a-1]->m_XcoordinateVertex,
										vertexOfGraphPtrVectorConainer[a - 1]->m_YcoordinateVertex,
										vertexOfGraphPtrVectorConainer[i.second - 1]->m_XcoordinateVertex,
										vertexOfGraphPtrVectorConainer[i.second - 1]->m_YcoordinateVertex,
										vertexOfGraphPtrVectorConainer[a - 1]->m_numberOfLanesHorizontal, 
										vertexOfGraphPtrVectorConainer[a - 1]->m_numberOfLanesVertical)
									,m_callback_getRandomNumber, m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers,m_cObSptr.get()));
							}

							a = i.second;
							iterator++;
						}
					}
					else {
						//std::shared_ptr<edge> e1 = std::make_shared<edge>(VertexIDofEdges.first, VertexIDofEdges.second, getPtrOfVertex(VertexIDofEdges.first), getPtrOfVertex(VertexIDofEdges.second), m_hdc, m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers);
						//edgeOfGraphPtrContainer.push_back(std::make_unique<edge>(VertexIDofEdges.first, VertexIDofEdges.second,  m_hdc, m_callback_getRandomNumber, m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers)); //Vertikal positv ohne Vertexunterbrechung!
						edgeOfGraphPtrContainer.push_back(std::make_unique<edge>(VertexIDofEdges.first, VertexIDofEdges.second, m_hdc, 
							std::move(choosePrintPattern(vertexOfGraphPtrVectorConainer[VertexIDofEdges.first - 1]->m_XcoordinateVertex,
								vertexOfGraphPtrVectorConainer[VertexIDofEdges.first - 1]->m_YcoordinateVertex,
								vertexOfGraphPtrVectorConainer[VertexIDofEdges.second - 1]->m_XcoordinateVertex,
								vertexOfGraphPtrVectorConainer[VertexIDofEdges.second - 1]->m_YcoordinateVertex,
								vertexOfGraphPtrVectorConainer[VertexIDofEdges.first - 1]->m_numberOfLanesHorizontal,
								vertexOfGraphPtrVectorConainer[VertexIDofEdges.first - 1]->m_numberOfLanesVertical))
							,m_callback_getRandomNumber, m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers,  m_cObSptr.get()));
					}
				}
				else {//std::get<0>(iF).second < std::get<1>(iF).second
					VectorOfVertex.clear();
					for (auto &iH : vertexOfGraphPtrVectorConainer) {
						if ((iH->m_XcoordinateVertex == std::get<1>(iF).first) && (iH->m_YcoordinateVertex == std::get<1>(iF).second)) {
							//VertexIDofEdges.first = iH->m_vertexID;
							VertexIDofEdges.second = iH->m_vertexID;

						}
						if ((iH->m_XcoordinateVertex == std::get<0>(iF).first) && (iH->m_YcoordinateVertex == std::get<0>(iF).second)) {
							//VertexIDofEdges.second = iH->m_vertexID;
							VertexIDofEdges.first = iH->m_vertexID;

						}
						if (((iH->m_XcoordinateVertex == std::get<0>(iF).first) && (iH->m_YcoordinateVertex != std::get<0>(iF).second)) && ((iH->m_XcoordinateVertex == std::get<1>(iF).first) && (iH->m_YcoordinateVertex != std::get<1>(iF).second))) {
							if ((iPosYRK < iH->m_YcoordinateVertex) && (iH->m_YcoordinateVertex<iPosYLK)) {
								CrossingVertex.first = iH->m_YcoordinateVertex;
								CrossingVertex.second = iH->m_vertexID;
								VectorOfVertex.push_back(CrossingVertex);
							}
						}
					}

					if (!VectorOfVertex.empty()) {
						CrossingVertex.first = std::get<0>(iF).second;	//Vertikal negativ mit Vertexunterbrechung!
						CrossingVertex.second = VertexIDofEdges.first;
						VectorOfVertex.push_back(CrossingVertex);
						CrossingVertex.first = std::get<1>(iF).second;
						CrossingVertex.second = VertexIDofEdges.second;
						VectorOfVertex.push_back(CrossingVertex);
						std::sort(VectorOfVertex.begin(), VectorOfVertex.end(), sortBottomUp);
						int iterator = 0;
						int b = 0;
						for (auto &i : VectorOfVertex) {
							if (iterator != 0) {

								//std::shared_ptr<edge> e6 = std::make_shared<edge>(b, i.second, getPtrOfVertex(b), getPtrOfVertex(i.second), m_hdc, m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers);
								//edgeOfGraphPtrContainer.push_back(std::make_unique<edge>(b, i.second,  m_hdc, m_callback_getRandomNumber,m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers));
								edgeOfGraphPtrContainer.push_back(std::make_unique<edge>(b, i.second, m_hdc, 
										choosePrintPattern(vertexOfGraphPtrVectorConainer[b - 1]->m_XcoordinateVertex,
										vertexOfGraphPtrVectorConainer[b - 1]->m_YcoordinateVertex,
										vertexOfGraphPtrVectorConainer[i.second - 1]->m_XcoordinateVertex,
										vertexOfGraphPtrVectorConainer[i.second - 1]->m_YcoordinateVertex,
										vertexOfGraphPtrVectorConainer[b - 1]->m_numberOfLanesHorizontal,
										vertexOfGraphPtrVectorConainer[b - 1]->m_numberOfLanesVertical)
									,m_callback_getRandomNumber, m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers, m_cObSptr.get()));
							}
							b = i.second;
							iterator++;
						}
					}
					else {
						//std::shared_ptr<edge> e2 = std::make_shared<edge>(VertexIDofEdges.first, VertexIDofEdges.second, getPtrOfVertex(VertexIDofEdges.first), getPtrOfVertex(VertexIDofEdges.second), m_hdc, m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers);
						//edgeOfGraphPtrContainer.push_back(std::make_unique<edge>(VertexIDofEdges.first, VertexIDofEdges.second, m_hdc, m_callback_getRandomNumber, m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers)); //Vertikal negativ ohne Vertexunterbrechung!
						edgeOfGraphPtrContainer.push_back(std::make_unique<edge>(VertexIDofEdges.first, VertexIDofEdges.second,  m_hdc,
								choosePrintPattern(vertexOfGraphPtrVectorConainer[VertexIDofEdges.first - 1]->m_XcoordinateVertex,
								vertexOfGraphPtrVectorConainer[VertexIDofEdges.first - 1]->m_YcoordinateVertex,
								vertexOfGraphPtrVectorConainer[VertexIDofEdges.second - 1]->m_XcoordinateVertex,
								vertexOfGraphPtrVectorConainer[VertexIDofEdges.second - 1]->m_YcoordinateVertex,
								vertexOfGraphPtrVectorConainer[VertexIDofEdges.first - 1]->m_numberOfLanesHorizontal,
								vertexOfGraphPtrVectorConainer[VertexIDofEdges.first - 1]->m_numberOfLanesVertical)
							, m_callback_getRandomNumber, m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers, m_cObSptr.get()));
					}

				}
			}
			else {//true = horizontal
				if (std::get<0>(iF).first < std::get<1>(iF).first) {
					VectorOfVertex.clear();

					for (auto &iI : vertexOfGraphPtrVectorConainer) {
						if ((iI->m_YcoordinateVertex == std::get<0>(iF).second) && (iI->m_XcoordinateVertex == std::get<0>(iF).first)) {
							VertexIDofEdges.first = iI->m_vertexID;
						}
						if ((iI->m_YcoordinateVertex == std::get<1>(iF).second) && (iI->m_XcoordinateVertex == std::get<1>(iF).first)) {
							VertexIDofEdges.second = iI->m_vertexID;
						}

						if (((iI->m_YcoordinateVertex == std::get<0>(iF).second) && (iI->m_XcoordinateVertex != std::get<0>(iF).first)) && ((iI->m_YcoordinateVertex == std::get<0>(iF).second) && (iI->m_XcoordinateVertex != std::get<1>(iF).first))) {
							if ((iPosXLK<iI->m_XcoordinateVertex) && (iI->m_XcoordinateVertex<iPosXRK)) {
								CrossingVertex.first = iI->m_XcoordinateVertex;
								CrossingVertex.second = iI->m_vertexID;
								VectorOfVertex.push_back(CrossingVertex);
							}
						}
					}

					if (!VectorOfVertex.empty()) {
						CrossingVertex.first = std::get<0>(iF).first; //Horizontal Positiv mit Vertexunterbrechung!
						CrossingVertex.second = VertexIDofEdges.first;
						VectorOfVertex.push_back(CrossingVertex);
						CrossingVertex.first = std::get<1>(iF).first;
						CrossingVertex.second = VertexIDofEdges.second;
						VectorOfVertex.push_back(CrossingVertex);
						std::sort(VectorOfVertex.begin(), VectorOfVertex.end(), sortTopDown);
						int iterator = 0;
						int c = 0;
						for (auto &i : VectorOfVertex) {
							if (iterator != 0) {
								//std::shared_ptr<edge> e7 = std::make_shared<edge>(c, i.second, getPtrOfVertex(c), getPtrOfVertex(i.second), m_hdc, m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers);
								//edgeOfGraphPtrContainer.push_back(std::make_unique<edge>(c, i.second, m_hdc, m_callback_getRandomNumber,m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers));
								edgeOfGraphPtrContainer.push_back(std::make_unique<edge>(c, i.second, m_hdc, 
										choosePrintPattern(vertexOfGraphPtrVectorConainer[c - 1]->m_XcoordinateVertex,
										vertexOfGraphPtrVectorConainer[c - 1]->m_YcoordinateVertex,
										vertexOfGraphPtrVectorConainer[i.second - 1]->m_XcoordinateVertex,
										vertexOfGraphPtrVectorConainer[i.second - 1]->m_YcoordinateVertex,
										vertexOfGraphPtrVectorConainer[c - 1]->m_numberOfLanesHorizontal,
										vertexOfGraphPtrVectorConainer[c - 1]->m_numberOfLanesVertical)
									,m_callback_getRandomNumber, m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers, m_cObSptr.get()));
							}
							c = i.second;
							iterator++;
						}
					}
					else {
						//std::shared_ptr<edge> e3 = std::make_shared<edge>(VertexIDofEdges.first, VertexIDofEdges.second, getPtrOfVertex(VertexIDofEdges.first), getPtrOfVertex(VertexIDofEdges.second), m_hdc, m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers);
						//edgeOfGraphPtrContainer.push_back(std::make_unique<edge>(VertexIDofEdges.first, VertexIDofEdges.second, m_hdc, m_callback_getRandomNumber, m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers));	//Horizintal  Positiv ohne Vertexunterbrechung!
						edgeOfGraphPtrContainer.push_back(std::make_unique<edge>(VertexIDofEdges.first, VertexIDofEdges.second, m_hdc, 
								choosePrintPattern(vertexOfGraphPtrVectorConainer[VertexIDofEdges.first - 1]->m_XcoordinateVertex,
								vertexOfGraphPtrVectorConainer[VertexIDofEdges.first - 1]->m_YcoordinateVertex,
								vertexOfGraphPtrVectorConainer[VertexIDofEdges.second - 1]->m_XcoordinateVertex,
								vertexOfGraphPtrVectorConainer[VertexIDofEdges.second - 1]->m_YcoordinateVertex,
								vertexOfGraphPtrVectorConainer[VertexIDofEdges.first - 1]->m_numberOfLanesHorizontal,
								vertexOfGraphPtrVectorConainer[VertexIDofEdges.first - 1]->m_numberOfLanesVertical)
							,m_callback_getRandomNumber, m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers, m_cObSptr.get()));
					}

				}
				else {
					VectorOfVertex.clear();

					for (auto &iJ : vertexOfGraphPtrVectorConainer) {
						if ((iJ->m_YcoordinateVertex == std::get<1>(iF).second) && (iJ->m_XcoordinateVertex == std::get<1>(iF).first)) {
							//VertexIDofEdges.first = iJ->m_vertexID;
							VertexIDofEdges.second = iJ->m_vertexID;
							//iPosXRK = iJ->m_XcoordinateVertex;
						}
						if ((iJ->m_YcoordinateVertex == std::get<0>(iF).second) && (iJ->m_XcoordinateVertex == std::get<0>(iF).first)) {
							//VertexIDofEdges.second = iJ->m_vertexID;
							VertexIDofEdges.first = iJ->m_vertexID;
							//iPosXLK = iJ->m_XcoordinateVertex;
						}

						if (((iJ->m_YcoordinateVertex == std::get<0>(iF).second) && (iJ->m_XcoordinateVertex != std::get<0>(iF).first)) && ((iJ->m_YcoordinateVertex == std::get<0>(iF).second) && (iJ->m_XcoordinateVertex != std::get<1>(iF).first))) {

							if ((iPosXRK < iJ->m_XcoordinateVertex) && (iJ->m_XcoordinateVertex<iPosXLK)) {
								CrossingVertex.first = iJ->m_XcoordinateVertex;
								CrossingVertex.second = iJ->m_vertexID;
								VectorOfVertex.push_back(CrossingVertex);
							}
						}
					}

					if (!VectorOfVertex.empty()) {
						CrossingVertex.first = std::get<0>(iF).first; //Horizontal negativ mit Vertexunterbrechung!
						CrossingVertex.second = VertexIDofEdges.first;
						VectorOfVertex.push_back(CrossingVertex);
						CrossingVertex.first = std::get<1>(iF).first;
						CrossingVertex.second = VertexIDofEdges.second;
						VectorOfVertex.push_back(CrossingVertex);
						std::sort(VectorOfVertex.begin(), VectorOfVertex.end(), sortBottomUp);

						int iterator = 0;
						int d = 0;
						for (auto &i : VectorOfVertex) {
							if (iterator != 0) {

								//std::shared_ptr<edge> e8 = std::make_shared<edge>(d, i.second, getPtrOfVertex(d), getPtrOfVertex(i.second), m_hdc, m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers);
								//edgeOfGraphPtrContainer.push_back(std::make_unique<edge>(d, i.second, m_hdc, m_callback_getRandomNumber, m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers));
								edgeOfGraphPtrContainer.push_back(std::make_unique<edge>(d, i.second, m_hdc, 
										choosePrintPattern(vertexOfGraphPtrVectorConainer[d - 1]->m_XcoordinateVertex,
										vertexOfGraphPtrVectorConainer[d - 1]->m_YcoordinateVertex,
										vertexOfGraphPtrVectorConainer[i.second - 1]->m_XcoordinateVertex,
										vertexOfGraphPtrVectorConainer[i.second - 1]->m_YcoordinateVertex,
										vertexOfGraphPtrVectorConainer[d - 1]->m_numberOfLanesHorizontal,
										vertexOfGraphPtrVectorConainer[d - 1]->m_numberOfLanesVertical)
									,m_callback_getRandomNumber, m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers, m_cObSptr.get()));
							}
							iterator++;
							d = i.second;
						}
					}
					else {
						//std::shared_ptr<edge> e4 = std::make_shared<edge>(VertexIDofEdges.first, VertexIDofEdges.second, getPtrOfVertex(VertexIDofEdges.first), getPtrOfVertex(VertexIDofEdges.second), m_hdc, m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers);
						//std::shared_ptr<edge> e4 = std::make_shared<edge>(VertexIDofEdges.second, VertexIDofEdges.first, getPtrOfVertex(VertexIDofEdges.second), getPtrOfVertex(VertexIDofEdges.first), m_hdc, m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers);

						//edgeOfGraphPtrContainer.push_back(std::make_unique<edge>(VertexIDofEdges.first, VertexIDofEdges.second, m_hdc, m_callback_getRandomNumber, m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers));// Horizintal negativ ohne Vertexunterbrechung!
						edgeOfGraphPtrContainer.push_back(std::make_unique<edge>(VertexIDofEdges.first, VertexIDofEdges.second, m_hdc, 
							std::move(choosePrintPattern(vertexOfGraphPtrVectorConainer[VertexIDofEdges.first - 1]->m_XcoordinateVertex,
								vertexOfGraphPtrVectorConainer[VertexIDofEdges.first - 1]->m_YcoordinateVertex,
								vertexOfGraphPtrVectorConainer[VertexIDofEdges.second - 1]->m_XcoordinateVertex,
								vertexOfGraphPtrVectorConainer[VertexIDofEdges.second - 1]->m_YcoordinateVertex,
								vertexOfGraphPtrVectorConainer[VertexIDofEdges.first - 1]->m_numberOfLanesHorizontal,
								vertexOfGraphPtrVectorConainer[VertexIDofEdges.first - 1]->m_numberOfLanesVertical))
							,m_callback_getRandomNumber, m_f8PaintPoint, m_f5PaintLane, m_f6PrintLaneInNumbers, m_cObSptr.get()));// Horizintal negativ ohne Vertexunterbrechung!
					}

				}

			}
		}
		for (auto &i : edgeOfGraphPtrContainer) {
			i->m_ppPtr->m_cbl = m_cbl;
			i->m_ppPtr->m_cbl.m_hdc = m_hdc;
		}
		iPosXLK = 0;
		iPosXRK = 0;
		iPosYLK = 0;
		iPosYRK = 0;
		//showEdge(m_hdc);
		//showVertex();
		m_f3PaintFrame(m_hdc);
		int numberOfEdges = edgeOfGraphPtrContainer.size();
		bool serviceBool = false;
		std::set<int>setOfVertexes;
		size_t sizeOfSetOfVertexes = setOfVertexes.size();
		std::vector<int>vectorOfVertexes;
		std::set<int>setOfVertexesNotOfPrimeGraph;
		std::vector<std::unique_ptr<edge>>::iterator i = edgeOfGraphPtrContainer.begin();
		
		std::vector<std::shared_ptr<vertex>> vectorOfVertexPTR;
		std::vector<std::shared_ptr<edge>> vectorOfEdgePTR;
		
		
		
		std::set<int>::iterator ii = setOfVertexes.begin();
		if (!edgeOfGraphPtrContainer.empty()) {
			appliedGraph.clear();
			setOfVertexes.insert(edgeOfGraphPtrContainer[0]->m_startVertex);
			setOfVertexes.insert(edgeOfGraphPtrContainer[0]->m_endVertex);

			do {
				setOfVertexesNotOfPrimeGraph.clear();
				
				do {
					ii = setOfVertexes.begin();
					vectorOfVertexes.clear();
					sizeOfSetOfVertexes = 0;
					while (ii != setOfVertexes.end()) {

						i = edgeOfGraphPtrContainer.begin();
						while (i != edgeOfGraphPtrContainer.end()) {
							if (*i != nullptr) {
								if ((((*ii) == (*i)->m_startVertex) && ((*ii) != (*i)->m_endVertex)) || (((*ii) != (*i)->m_startVertex) && ((*ii) == (*i)->m_endVertex))) {
									vectorOfVertexes.push_back((*i)->m_startVertex);
									vectorOfVertexes.push_back((*i)->m_endVertex);

								}
							}
							i++;
						}
						ii++;
					}
					sizeOfSetOfVertexes = setOfVertexes.size();
					for (auto &iii : vectorOfVertexes) {
						
						setOfVertexes.insert(iii);
					}
				} while (sizeOfSetOfVertexes < setOfVertexes.size());
				

				for (auto &ja : edgeOfGraphPtrContainer) {
					if (ja != nullptr) {
						serviceBool = false;
						for (auto &jb : setOfVertexes) {
							if ((jb == ja->m_startVertex) || (jb == ja->m_endVertex)) {
								serviceBool = true;//hier liegt das Problem
							}
						}

						if (!appliedGraph.empty()) {
							for (auto &id : appliedGraph) {
								for (auto &ie : id->m_setOfVertexes) {
									if ((ie == ja->m_startVertex) || (ie == ja->m_endVertex)) {
										serviceBool = true;
									}
								}
							}

						}
						if (serviceBool == false) {
							setOfVertexesNotOfPrimeGraph.insert(ja->m_startVertex);//Bei in "in einer Linie" wird nix insertet!!
						}
						serviceBool = false;
					}
				}
				
				vectorOfVertexPTR.clear();
				vectorOfEdgePTR.clear();
				
				
				for (auto &jcx : setOfVertexes) {
					
					for (auto &jcy : vertexOfGraphPtrVectorConainer) {
						if (jcy != nullptr) {
							if (jcx == jcy->m_vertexID) {
								

								vectorOfVertexPTR.push_back(std::move(jcy));
								

							}
						}
					}
					bool inVectorEdgePTR = false;
					for (auto &jcz : edgeOfGraphPtrContainer) {
						inVectorEdgePTR = false;
						if (jcz != nullptr) {
							if ((jcx == jcz->m_startVertex) || (jcx == jcz->m_endVertex)) {

								std::shared_ptr<edge> edgePTR = std::move(jcz);

								for (auto &jcza : vectorOfEdgePTR) {
									
									if (jcza == edgePTR) {
										inVectorEdgePTR = true;
									}
								}
								if (inVectorEdgePTR == false) {
									vectorOfEdgePTR.push_back(edgePTR);


								}
							}
						}
					}

				}
				
				appliedGraph.push_back(std::make_unique<graph>(setOfVertexes, vectorOfVertexPTR,vectorOfEdgePTR, m_f5PaintLane, m_f6PrintLaneInNumbers, m_f7PrintVertexNumber, m_hdc));
				setOfVertexes.clear();
				vectorOfVertexPTR.clear();
				vectorOfEdgePTR.clear();
				if (!setOfVertexesNotOfPrimeGraph.empty()) {
					std::set<int>::iterator jc = setOfVertexesNotOfPrimeGraph.begin();
					serviceBool = false;
					do {
						if (appliedGraph.empty()) {
							setOfVertexes.insert(*jc);
							serviceBool = false;
						}
						else {
							if (serviceBool == false) {
								setOfVertexes.insert(*jc);
								
								serviceBool = true;
							}
						}

						
						jc++;
					} while (jc != setOfVertexesNotOfPrimeGraph.end());

					setOfVertexesNotOfPrimeGraph.clear();
				}

				

				
				if (setOfVertexes.empty()) {
					serviceBool = false;
				}
				else {
					serviceBool = true;
				}

			} while (serviceBool);



		}
		
		vertexOfGraphPtrVectorConainer.clear();
		edgeOfGraphPtrContainer.clear();
		//showGraph();
		
	}
	
	void network::printLanesAndVehiclesOfAllEdges() {

		for (auto &i : appliedGraph) {
			i->printLanesAndVehiclesOfAllEdges();
		}
		m_PWE.fullemptyPrintContainer(m_hdc,m_f5PaintLane);
	}
	
	PrintPattern* network::choosePrintPattern(const int& p1x, const int& p1y, const int& p2x, const int& p2y, const int& lanesH, const int& lanesV) {
		if ((0 <= lanesH) && (lanesH <= 2) && (0 <= lanesV) && (lanesV <= 2)) {
			PrintPattern* pp_ptr=nullptr;
			if ((p1x < p2x) && (p1y == p2y)) {
				if (lanesH == 1) {
					pp_ptr = new PrintPatternLine1LaneHoriPos(p1x, p1y, p2x, p2y);
				}
				else if (lanesH == 2) {
					pp_ptr = new PrintPatternLine2LaneHoriPos(p1x, p1y, p2x, p2y);
				}
				else {

				}
			}
			if ((p1x > p2x) && (p1y == p2y)) {
				if (lanesH == 1) {
					pp_ptr = new PrintPatternLine1LaneHoriNeg(p1x, p1y, p2x, p2y);
				}
				else if (lanesH == 2) {
					pp_ptr = new PrintPatternLine2LaneHoriNeg(p1x, p1y, p2x, p2y);
				}
				else {

				}
			}
			if ((p1x == p2x) && (p1y < p2y)) {
				if (lanesV == 1) {
					pp_ptr = new PrintPatternLine1LaneVertiPos(p1x, p1y, p2x, p2y);
				}
				else if (lanesV == 2) {
					pp_ptr = new PrintPatternLine2LaneVertiPos(p1x, p1y, p2x, p2y);
				}
				else {

				}
			}
			if ((p1x == p2x) && (p1y > p2y)) {
				if (lanesV == 1) {
					pp_ptr = new PrintPatternLine1LaneVertiNeg(p1x, p1y, p2x, p2y);
				}
				else if (lanesV == 2) {
					pp_ptr = new PrintPatternLine2LaneVertiNeg(p1x, p1y, p2x, p2y);
				}
				else {

				}
			}
			return pp_ptr;
		}

	}
	bool checkIfDubbleKlick(const int& a, const int& b) {
		if ((a == serviceInt1) && (b == serviceInt2)) {
			return false;
		}
		else {
			serviceInt1 = a;
			serviceInt2 = b;
			return true;
		}
	}


};


