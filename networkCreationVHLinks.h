#pragma once
#include "callBackLinks.h"
#include "PrecompiledHeadersEdges.h"
class networkCreationVHLinks {
private:
	int xCordinadte_store_LB=0;
	int yCordinadte_store_LB=0;
	enum m_numberOfLanes { oneLane = 1, twoLanes = 2 };
	int width=1200;
	int height=700;
	
public:
	std::unique_ptr<callBackLinks> m_CBLptr;
	std::vector<std::tuple<std::pair<int, int>, std::pair<int, int>, bool, m_numberOfLanes>> networkLaneVector;//vertical=true, horizontal=false;
	networkCreationVHLinks::networkCreationVHLinks() {
	}
	networkCreationVHLinks::~networkCreationVHLinks() {
	}
	int edgeCaseDisplacement(const int& transferParm, const int& boundary) {
		return (transferParm > boundary ? boundary : transferParm);
	}
	
	void networkCreationVHLinks::establishLane( const int& numberOfLanes, const int& iPosXLK_transfer, const int& iPosYLK_transfer, bool lButtonServiceBool) {
		int laneNumbers = 1;
		laneNumbers = m_numberOfLanes::oneLane;
		int iPosXLK = edgeCaseDisplacement(iPosXLK_transfer, (width - 110));
		int iPosYLK = edgeCaseDisplacement(iPosYLK_transfer, (height - 110));
		bool horizontalOrVertival = true;
		std::tuple<std::pair<int, int>, std::pair<int, int>, bool, m_numberOfLanes> laneCoordinate;
		std::pair<int, int> startingPoint;
		std::pair<int, int> endingPoint;
		if (lButtonServiceBool == true) {
			xCordinadte_store_LB = iPosXLK;
			yCordinadte_store_LB = iPosYLK;
			startingPoint.first = iPosXLK;
			startingPoint.second = iPosYLK;
			endingPoint.first = 0;
			endingPoint.second = 0;
		}
		else {//false	  
			
			//Left down
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
			//Left up
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
			//Right up
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
			//Right down
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
			//^^^^ Location of the Edges***
			else if (((iPosXLK - xCordinadte_store_LB) != 0) && ((iPosYLK - yCordinadte_store_LB) == 0)) {
				endingPoint.first = iPosXLK;
				endingPoint.second = iPosYLK;
				horizontalOrVertival = true;
			}
			else if (((iPosXLK - xCordinadte_store_LB) == 0) && ((iPosYLK - yCordinadte_store_LB) != 0)) {
				endingPoint.first = iPosXLK;
				endingPoint.second = iPosYLK;
				horizontalOrVertival = false;
				//^^^^Location of Edges ***Concretization
			}
			else {
				lButtonServiceBool = true;//Error Cancel!
			}
			//**********************************************************
			//Edge case displacement
			if (numberOfLanes == twoLanes) {
				laneNumbers = m_numberOfLanes::twoLanes;
				if ((xCordinadte_store_LB == (width - 110)) && (horizontalOrVertival == false)) {
					xCordinadte_store_LB = edgeCaseDisplacement(xCordinadte_store_LB, (width - 120));
					endingPoint.first = edgeCaseDisplacement(endingPoint.first, (width - 120));
				}
				if ((yCordinadte_store_LB == (height - 110)) && (horizontalOrVertival == true)) {
					yCordinadte_store_LB = edgeCaseDisplacement(yCordinadte_store_LB, (height - 120));
					endingPoint.second = edgeCaseDisplacement(endingPoint.second, (height - 120));
				}
			}
			//**********************************************************
			if (lButtonServiceBool == false) {//Continue if no error!
				startingPoint.first = xCordinadte_store_LB;
				startingPoint.second = yCordinadte_store_LB;
				if (laneNumbers == 1) {
					laneCoordinate = std::make_tuple(startingPoint, endingPoint, horizontalOrVertival, oneLane);//oneLane
				}
				if (laneNumbers == 2) {
					laneCoordinate = std::make_tuple(startingPoint, endingPoint, horizontalOrVertival, twoLanes);//twoLanes
				}

				bool addCoordinate = true;
				int secondLaneExtension = 0;
				
				//bool secondLaneExist = false;				//Flag for indicating links with 2 lanes
				if (std::get<0>(laneCoordinate).first == std::get<1>(laneCoordinate).first) {
					if ((std::get<0>(laneCoordinate).second - std::get<1>(laneCoordinate).second) <= -40) {
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
				if (std::get<3>(laneCoordinate) == twoLanes) {
					secondLaneExtension = secondLaneExtension - 10;
				}
				
				do {
					for (auto& i : networkLaneVector) {
						if ((std::get<3>(i) == oneLane) && (secondLaneExtension == 10)) {
							secondLaneExtension = 50000;
						}
						if ((std::get<0>(laneCoordinate).first < std::get<1>(laneCoordinate).first) || (std::get<0>(laneCoordinate).second < std::get<1>(laneCoordinate).second)) {
								if ( ((std::get<0>(i).second + secondLaneExtension ) == std::get<0>(laneCoordinate).second) && 
									 ((std::get<1>(i).second + secondLaneExtension ) == std::get<1>(laneCoordinate).second) &&
									  (std::get<0>(i).second == std::get<1>(i).second)
									) {
									
									if (std::get<0>(i).first < std::get<1>(i).first) {
										if (std::get<1>(i).first <= std::get<0>(laneCoordinate).first) {
											
										}
										else if (std::get<1>(laneCoordinate).first <= std::get<0>(i).first) {
											
										}
										else {
											addCoordinate = false;
										}
									}
									else {//(std::get<0>(i).first) >= (std::get<1>(i).first)
										if (std::get<0>(i).first <= std::get<0>(laneCoordinate).first) {
											
										}
										else if (std::get<1>(laneCoordinate).first <= std::get<1>(i).first) {
											
										}
										else {
											addCoordinate = false;
										}
									}
								}

								else if (((std::get<0>(i).first + secondLaneExtension) == std::get<0>(laneCoordinate).first) && 
									     ((std::get<1>(i).first + secondLaneExtension) == std::get<1>(laneCoordinate).first) &&
									      (std::get<0>(i).first == std::get<1>(i).first)
									) {
									
									if (std::get<0>(i).second < std::get<1>(i).second) {
										//addCoordinate = false;
										//finished(1)
										
										if (std::get<1>(i).second <= std::get<0>(laneCoordinate).second) {
											//addCoordinate = true;
										}
										else if (std::get<1>(laneCoordinate).second < std::get<0>(i).second) {
											//addCoordinate = true;
										}
										else {
											addCoordinate = false;
										}
									}
									else {
										//finished(2)
										if (std::get<0>(i).second <= std::get<0>(laneCoordinate).second) {
											
										}
										else if (std::get<1>(laneCoordinate).second <= std::get<1>(i).second) {
											
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
							
								if (((std::get<0>(i).second + secondLaneExtension) == std::get<0>(laneCoordinate).second) && 
									((std::get<1>(i).second + secondLaneExtension) == std::get<1>(laneCoordinate).second)
									) {
									if (std::get<0>(i).first < std::get<1>(i).first) {
										if (std::get<1>(i).first <= std::get<1>(laneCoordinate).first) {
											//addCoordinate = true;
										}
										else if (std::get<0>(laneCoordinate).first <= std::get<0>(i).first) {
											//addCoordinate = true;
										}
										else {
											addCoordinate = false;
										}
									}
									else {
										
										if ((std::get<0>(i).first >= std::get<0>(laneCoordinate).first) && (std::get<1>(laneCoordinate).first > std::get<1>(i).first)) {
											//addCoordinate = true;
										}
										else if ((std::get<0>(i).first <= std::get<0>(laneCoordinate).first) && (std::get<0>(i).first < std::get<1>(laneCoordinate).first)) {
										}
										else if ((std::get<1>(i).first >= std::get<0>(laneCoordinate).first) && (std::get<1>(i).first > std::get<1>(laneCoordinate).first)) {
										}
										else {
											addCoordinate = false;
										}
									}
								}
								else if (((std::get<0>(i).first + secondLaneExtension) == std::get<0>(laneCoordinate).first) && 
									     ((std::get<1>(i).first + secondLaneExtension) == std::get<1>(laneCoordinate).first)
									) {
									
									if (std::get<0>(i).second < std::get<1>(i).second) {
										
										if (std::get<1>(i).second <= std::get<1>(laneCoordinate).second) {
											
										}
										else if (std::get<0>(laneCoordinate).second <= std::get<0>(i).second) {
											
										}
										else {
											addCoordinate = false;
											
										}
									}
									else {
										if (std::get<1>(i).second >= std::get<0>(laneCoordinate).second) {
											
										}
										else if (std::get<1>(laneCoordinate).second > std::get<0>(i).second) {
											
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
						if (secondLaneExtension == 50000) {
							secondLaneExtension = 10;
						}
					}
					
					secondLaneExtension = secondLaneExtension + 10;
				} while (secondLaneExtension <= 10);
				if (addCoordinate == true) {
					networkLaneVector.push_back(laneCoordinate);
				}
				xCordinadte_store_LB = width;
				yCordinadte_store_LB = height;
			}
		}
	}
};