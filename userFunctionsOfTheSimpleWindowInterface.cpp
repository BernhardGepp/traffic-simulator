#include "PrecompiledHeadersEdges.h"
#include "userFunctionsOfTheSimpleWindowInterface.h"
#include "graphTrafficGenerationOnAllRoutes.h"
#include "graphTrafficGenerationOnFastRoutes.h"

//********************************************************************
//Constructor and destructor of the class:
userFunctionsOfTheSimpleWindowInterface::userFunctionsOfTheSimpleWindowInterface() { 
	vertrexCreator_ptr = new createVertex; 
	edgeCreator_ptr = new createEdge(m_CBLptr, m_cObSptr);
}
userFunctionsOfTheSimpleWindowInterface::~userFunctionsOfTheSimpleWindowInterface() {
	delete vertrexCreator_ptr;
	delete edgeCreator_ptr;
}

//********************************************************************
//Methods of the class:

void userFunctionsOfTheSimpleWindowInterface::iniziallizationOfPointer(callBackLinks* CBL, concreteObserverSubject* cOS) {
	m_CBLptr = CBL;
	m_cObSptr = cOS;
}

void userFunctionsOfTheSimpleWindowInterface::establishLane(const int& width, const int& height, const int& numberOfLanes, const int& iPosXLK_transfer, const int& iPosYLK_transfer, bool lButtonServiceBool) {
	//********************************************************************
	//This method is used to generate pairs of points.
	//This method ensures that only feasible point pairs are generated, from which the links of the simulation graph are later created.
	//********************************************************************
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
						if (((std::get<0>(i).second + secondLaneExtension) == std::get<0>(laneCoordinate).second) &&
							((std::get<1>(i).second + secondLaneExtension) == std::get<1>(laneCoordinate).second) &&
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
								else if (std::get<1>(laneCoordinate).second <= std::get<0>(i).second) {
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

								if (std::get<0>(i).first <= std::get<1>(laneCoordinate).first) {

								}
								else if (std::get<0>(laneCoordinate).first <= std::get<1>(i).first) {

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
								else if (std::get<1>(laneCoordinate).second >= std::get<0>(i).second) {

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

int userFunctionsOfTheSimpleWindowInterface::edgeCaseDisplacement(const int& transferParm, const int& boundary) {
	//********************************************************************
	//This method is called by the method "establishLane" of that class.
	return (transferParm > boundary ? boundary : transferParm);
}

void  userFunctionsOfTheSimpleWindowInterface::graphGenerationFromClickPairs(const int& width, const int& height, const int& choiceOfRouteFinding) {
	edgeCreator_ptr->iniziallizationOfPointer(m_CBLptr, m_cObSptr);
	//********************************************************************
	//This method generates one or more traffic graphs from a set of point pairs in which the traffic simulation is executed.
	//A traffic graph (object "graph")consists of edges and vertices, which are created in this method in the form of objects.
	//********************************************************************
	std::pair<int, int> startingPoint;
	std::pair<int, int> endingPoint;
	std::vector<std::tuple<std::pair<int, int>, std::pair<int, int>, bool, m_numberOfLanes>>::iterator estVerITER = networkLaneVector.begin();
	std::vector<std::tuple<std::pair<int, int>, std::pair<int, int>, bool, m_numberOfLanes>>::iterator estVerITERA = networkLaneVector.begin();
	int xCordinadte_store_LB = 0;
	int yCordinadte_store_LB = 0;
	int iPosXLK = 0;
	int iPosYLK = 0;
	int iPosXRK = 0;
	int iPosYRK = 0;
	//Preparation for coordinate correction, narrowing down the search space:
	for (estVerITER = networkLaneVector.begin(); estVerITER != networkLaneVector.end(); ++estVerITER) {

		if (std::get<2>(*estVerITER) == true) {
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
	//Correction of coordinates for multi-lane links on the X-axis:
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
	//Correction of coordinates for multi-lane links on the Y-axis:
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
	//Generation of vertex objects at intersection accounts or common start and end nodes:
	vertexOfGraphPtrVectorConainer.clear();
	edgeOfGraphPtrContainer.clear();
	std::pair<int, int>XsearchBoundary;//min == first, max == second
	XsearchBoundary.first = width;
	XsearchBoundary.second = 0;
	std::pair<int, int>YsearchBoundary;//min == first, max == second
	YsearchBoundary.first = height;
	YsearchBoundary.second = 0;
	std::vector<std::tuple<int, int, bool>> orientationMap;//Notation: first and second lane which will be compared. Comparison performed/or not necessary (true) or not yet performed (false).
	int counter = 0;
	int secondCounter = 0;
	for (auto& i : networkLaneVector) {
		secondCounter = 0;
		for (auto& ia : networkLaneVector) {
			if (std::get<2>(i) == std::get<2>(ia))
				orientationMap.push_back(std::make_tuple(counter, secondCounter, false));	//same arrangement in the field
			if (std::get<2>(i) != std::get<2>(ia))
				orientationMap.push_back(std::make_tuple(counter, secondCounter, true)); //orthogonal arrangement in the field
			secondCounter++;
		}
		counter++;
	}

	for (auto& i : orientationMap) {
		if (std::get<0>(i) == std::get<1>(i))		//prevention of comparison between same entries
			std::get<2>(i) = true;
	}
	counter = 0;
	secondCounter = 0;
	for (auto& i : orientationMap) {
		if (std::get<2>(i) == false) {
			std::get<2>(i) = true;					//mark vertex-pair as done! set it TRUE!
			counter = std::get<0>(i);				// the variable "counter" is used to address the data-field in the arry "networkLaneVector"
			secondCounter = std::get<1>(i);			// the variable "secondCounter" is used to address the data-field in the arry "networkLaneVector"
			for (auto& ia : orientationMap) {
				if ((counter == std::get<1>(ia)) && (secondCounter == std::get<0>(ia)))
					std::get<2>(ia) = true;  //Mark the comparison pair as done!
			}
			//***Begin of comparison:
			//Ending Link(1) vs. Beginning Link(2) in case of two singelLaneLinks
			if ((std::get<1>(networkLaneVector[counter]).first == std::get<0>(networkLaneVector[secondCounter]).first) &&
				(std::get<1>(networkLaneVector[counter]).second == std::get<0>(networkLaneVector[secondCounter]).second)) {
				vertexCreationVH_Network(std::get<1>(networkLaneVector[counter]), 11);
			}
			//Ending Link(1) vs. Ending Link(2) in case of two singelLaneLinks
			if ((std::get<1>(networkLaneVector[counter]).first == std::get<1>(networkLaneVector[secondCounter]).first) &&
				(std::get<1>(networkLaneVector[counter]).second == std::get<1>(networkLaneVector[secondCounter]).second)) {
				vertexCreationVH_Network(std::get<1>(networkLaneVector[counter]), 2);
			}
			//Beginning Link(1) vs. Beginning Link(2) in case of two singelLaneLinks
			if ((std::get<0>(networkLaneVector[counter]).first == std::get<0>(networkLaneVector[secondCounter]).first) &&
				(std::get<0>(networkLaneVector[counter]).second == std::get<0>(networkLaneVector[secondCounter]).second)) {
				vertexCreationVH_Network(std::get<0>(networkLaneVector[counter]), 1);
			}
			//Beginning Link(1) vs. Ending Link(2) in case of two singelLaneLinks
			if ((std::get<0>(networkLaneVector[counter]).first == std::get<1>(networkLaneVector[secondCounter]).first) &&
				(std::get<0>(networkLaneVector[counter]).second == std::get<1>(networkLaneVector[secondCounter]).second)) {
				vertexCreationVH_Network(std::get<0>(networkLaneVector[counter]), 11);
			}
		}
	}

	for (auto& i : networkLaneVector) {
		vertexCreationVH_Network(std::get<0>(i), 1);	//Creation of start and end vertices if not already created
		vertexCreationVH_Network(std::get<1>(i), 2);
	}
	counter = 0;
	secondCounter = 0;
	bool serviceBool1 = false;
	for (auto& i : networkLaneVector) {
		XsearchBoundary.first = 10000;
		XsearchBoundary.second = 10000;
		serviceBool1 = false;
		if (std::get<2>(i) == true) {
			if (std::get<0>(i).first < std::get<1>(i).first) {
				XsearchBoundary.first = std::get<0>(i).first;
				XsearchBoundary.second = std::get<1>(i).first;
				serviceBool1 = true;
			}
			if (std::get<0>(i).first > std::get<1>(i).first) {
				XsearchBoundary.first = std::get<1>(i).first;
				XsearchBoundary.second = std::get<0>(i).first;
				serviceBool1 = false;
			}
			YsearchBoundary.first = std::get<0>(i).second;
			YsearchBoundary.second = std::get<0>(i).second;
			if (std::get<3>(i) == 2)
				YsearchBoundary.second = std::get<0>(i).second + 10;
		}
		secondCounter = 0;
		for (auto& ia : networkLaneVector) {
			if (std::get<2>(ia) == false) {

				if ((XsearchBoundary.first <= std::get<0>(ia).first) && (std::get<0>(ia).first <= XsearchBoundary.second) &&
					(
						((std::get<0>(ia).second <= YsearchBoundary.first) && (YsearchBoundary.first <= std::get<1>(ia).second)) ||
						((std::get<1>(ia).second <= YsearchBoundary.first) && (YsearchBoundary.first <= std::get<0>(ia).second))
						)
					) {
					if ((XsearchBoundary.first == std::get<0>(ia).first) && (std::get<0>(ia).second == YsearchBoundary.first) && (serviceBool1 == true)) {

					}
					else if ((XsearchBoundary.second == std::get<0>(ia).first) && (std::get<1>(ia).second == YsearchBoundary.first) && (serviceBool1 == true)) {

					}
					else if ((XsearchBoundary.second == std::get<0>(ia).first) && (std::get<0>(ia).second == YsearchBoundary.first) && (serviceBool1 == false)) {

					}
					else if ((XsearchBoundary.first == std::get<0>(ia).first) && (std::get<1>(ia).second == YsearchBoundary.first) && (serviceBool1 == false)) {

					}
					else {
						std::pair<int, int>transferePair;
						transferePair.first = std::get<0>(ia).first;
						transferePair.second = YsearchBoundary.first;
						vertexCreationVH_Network(transferePair, 11);//Creation of intersection nodes in the graph
					}
				}
			}
			secondCounter++;
		}
		counter++;
	}
	iPosXLK = 0;
	iPosYLK = 0;
	iPosXRK = 0;
	iPosYRK = 0;
	//*******************************************************
	//Numbering of the nodes(Vertex):

	for (auto& iEb : vertexOfGraphPtrVectorConainer) {
		iEb->setPrintShape(iEb->m_shapeOfThatVertex);
	}

	iPosXLK = 0;
	iPosYLK = 0;
	iPosXRK = 0;
	iPosYRK = 0;
	counter = 0;
	//******************
	//Graph generation

	std::vector<std::pair<int, int>>VectorOfVertex = {};
	VectorOfVertex.clear();
	std::pair<std::pair<int, int>, std::pair<int, int>> possibleEdge;
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>VectorOfPossibleEdge = {};
	std::vector<bool>directionOfLink;
	std::pair<int, int> VertexIDofEdges;
	std::pair<int, int>CrossingVertex;
	bool increasingOrDecreasing = true;
	int maxValue = 0;
	
	for (auto& ia : networkLaneVector) {
		possibleEdge.first.first = 0;
		possibleEdge.second.first = 0;
		if (std::get<2>(ia) == true) {
			int iterHori = 0;
			if (std::get<0>(ia).first < std::get<1>(ia).first) {
				iterHori = std::get<0>(ia).first;
				maxValue = std::get<1>(ia).first;
				increasingOrDecreasing = true;
			}
			else {
				iterHori = std::get<1>(ia).first;
				maxValue = std::get<0>(ia).first;
				increasingOrDecreasing = false;
			}
			for (iterHori; iterHori <= maxValue; iterHori = iterHori + 10) {
				for (auto& iG : vertexOfGraphPtrVectorConainer) {
					//Vertikal
					if ((iG->m_XcoordinateVertex == iterHori) && (iG->m_YcoordinateVertex == std::get<0>(ia).second) && (possibleEdge.first.first == 0)) {
						possibleEdge.first.first = iG->m_vertexID;
						possibleEdge.first.second = iG->m_shapeOfThatVertex;
						iterHori = iterHori + 10;
					}
				}
				if (possibleEdge.first.first != 0) {
					for (auto& iG : vertexOfGraphPtrVectorConainer) {
						if ((iG->m_XcoordinateVertex == iterHori) && (iG->m_YcoordinateVertex == std::get<0>(ia).second)) {
							possibleEdge.second.first = iG->m_vertexID;
							possibleEdge.second.second = iG->m_shapeOfThatVertex;
						}
					}
					if ((possibleEdge.first.first != 0) && (possibleEdge.second.first != 0)) {
						
							
						if (increasingOrDecreasing) {
							edgeOfGraphPtrContainer.push_back(edgeCreator_ptr->create(vertexOfGraphPtrVectorConainer[possibleEdge.first.first - 1], vertexOfGraphPtrVectorConainer[possibleEdge.second.first - 1], std::get<3>(ia)));
						}

						if (!increasingOrDecreasing) {
							edgeOfGraphPtrContainer.push_back(edgeCreator_ptr->create(vertexOfGraphPtrVectorConainer[possibleEdge.second.first - 1], vertexOfGraphPtrVectorConainer[possibleEdge.first.first - 1], std::get<3>(ia)));
						}

						possibleEdge.first.first = possibleEdge.second.first;
						possibleEdge.first.second = possibleEdge.second.second;
						possibleEdge.second.first = 0;
						possibleEdge.second.second = 0;
					}
				}
			}
		}
		if (std::get<2>(ia) == false) {
			int iterVerti = 0;
			if (std::get<0>(ia).second < std::get<1>(ia).second) {
				iterVerti = std::get<0>(ia).second;
				maxValue = std::get<1>(ia).second;
				increasingOrDecreasing = true;
			}
			else {
				iterVerti = std::get<1>(ia).second;
				maxValue = std::get<0>(ia).second;
				increasingOrDecreasing = false;
			}
			for (iterVerti; iterVerti <= maxValue; iterVerti = iterVerti + 10) {
				for (auto& iG : vertexOfGraphPtrVectorConainer) {
					//Vertical
					if ((iG->m_XcoordinateVertex == std::get<0>(ia).first) && (iG->m_YcoordinateVertex == iterVerti) && (possibleEdge.first.first == 0)) {
						possibleEdge.first.first = iG->m_vertexID;
						possibleEdge.first.second = iG->m_shapeOfThatVertex;
						iterVerti = iterVerti + 10;
					}
				}
				if (possibleEdge.first.first != 0) {
					for (auto& iG : vertexOfGraphPtrVectorConainer) {
						if ((iG->m_XcoordinateVertex == std::get<0>(ia).first) && (iG->m_YcoordinateVertex == iterVerti)) {
							possibleEdge.second.first = iG->m_vertexID;
							possibleEdge.second.second = iG->m_shapeOfThatVertex;
						}
					}
					if ((possibleEdge.first.first != 0) && (possibleEdge.second.first != 0)) {
						if (increasingOrDecreasing) {
							edgeOfGraphPtrContainer.push_back(edgeCreator_ptr->create(vertexOfGraphPtrVectorConainer[possibleEdge.first.first - 1], vertexOfGraphPtrVectorConainer[possibleEdge.second.first - 1], std::get<3>(ia)));
						}
						if (!increasingOrDecreasing) {
							edgeOfGraphPtrContainer.push_back(edgeCreator_ptr->create(vertexOfGraphPtrVectorConainer[possibleEdge.second.first - 1], vertexOfGraphPtrVectorConainer[possibleEdge.first.first - 1], std::get<3>(ia)));
						}

						possibleEdge.first.first = possibleEdge.second.first;
						possibleEdge.first.second = possibleEdge.second.second;
						possibleEdge.second.first = 0;
						possibleEdge.second.second = 0;
					}
				}
			}
		}
	}

	counter = 0;
	iPosXLK = 0;
	iPosXRK = 0;
	iPosYLK = 0;
	iPosYRK = 0;
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
				for (auto& iii : vectorOfVertexes) {

					setOfVertexes.insert(iii);
				}
			} while (sizeOfSetOfVertexes < setOfVertexes.size());


			for (auto& ja : edgeOfGraphPtrContainer) {
				if (ja != nullptr) {
					serviceBool = false;
					for (auto& jb : setOfVertexes) {
						if ((jb == ja->m_startVertex) || (jb == ja->m_endVertex)) {
							serviceBool = true;
						}
					}

					if (!appliedGraph.empty()) {
						for (auto& id : appliedGraph) {
							for (auto& ie : id->m_vectorOfVertexPtr/*m_setOfVertexes*/) {
								if ((ie->m_vertexID == ja->m_startVertex) || (ie->m_vertexID == ja->m_endVertex)) {
									serviceBool = true;
								}
							}
						}
					}
					if (serviceBool == false) {
						setOfVertexesNotOfPrimeGraph.insert(ja->m_startVertex);
					}
					serviceBool = false;
				}
			}

			vectorOfVertexPTR.clear();
			vectorOfEdgePTR.clear();
			
		
			for (auto& jcx : setOfVertexes) {
				for (auto& jcy : vertexOfGraphPtrVectorConainer) {
					if (jcy != nullptr) {
						if (jcx == jcy->m_vertexID) {
							vectorOfVertexPTR.push_back(std::move(jcy));
						}
					}
				}
				bool inVectorEdgePTR = false;
				for (auto& jcz : edgeOfGraphPtrContainer) {
					inVectorEdgePTR = false;
					if (jcz != nullptr) {
						if ((jcx == jcz->m_startVertex) || (jcx == jcz->m_endVertex)) {

							std::shared_ptr<edge> edgePTR = std::move(jcz);

							for (auto& jcza : vectorOfEdgePTR) {

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
			
			if (choiceOfRouteFinding == 1)
				appliedGraph.push_back(std::make_unique<graphTrafficGenerationOnAllRoutes>(setOfVertexes, vectorOfVertexPTR, vectorOfEdgePTR));
			if (choiceOfRouteFinding == 2)
				appliedGraph.push_back(std::make_unique<graphTrafficGenerationOnFastRoutes>(setOfVertexes, vectorOfVertexPTR, vectorOfEdgePTR));
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
}

void userFunctionsOfTheSimpleWindowInterface::vertexCreationVH_Network(const std::pair<int, int>& XandYpostion, const int& shapeOfThatVertex) {
	//********************************************************************
	//Vertex generation for a graph with vertical and horizontal links
	//This method is called by the method "graphGenerationFromClickPairs". This method is part of the traffic graph generation. 
	
	bool serviceBool = false;
	int shapeOfThatVertex_var = shapeOfThatVertex;
	int counter = 1;
	if (vertexOfGraphPtrVectorConainer.size() == 0) {
		serviceBool = true;
	}
	else {
		serviceBool = true;
		for (auto i = vertexOfGraphPtrVectorConainer.begin(); i != vertexOfGraphPtrVectorConainer.end(); i++) {
			if ((XandYpostion.first == (*i)->m_XcoordinateVertex) && (XandYpostion.second == (*i)->m_YcoordinateVertex)) {
				if ((*i)->m_shapeOfThatVertex == shapeOfThatVertex_var) {
					serviceBool = false;
				}
				if ((*i)->m_shapeOfThatVertex != shapeOfThatVertex_var) {
					serviceBool = true;
					shapeOfThatVertex_var = 11;
					vertexOfGraphPtrVectorConainer.erase(i--);
					vertrexCreator_ptr->decrementCounter();
					for (auto ii = vertexOfGraphPtrVectorConainer.begin(); ii != vertexOfGraphPtrVectorConainer.end(); ii++) {
						(*ii)->numberingOfVertexes(counter);
						counter++;
					}
					counter = 1;
					break;
				}
			}
		}
	}
	if (serviceBool) {
		
		vertexOfGraphPtrVectorConainer.push_back(vertrexCreator_ptr->create(XandYpostion.first, XandYpostion.second, shapeOfThatVertex_var));
	}
	
}


