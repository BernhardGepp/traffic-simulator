#pragma once
#include "callBackLinks.h"
#include "userFunctionsOfTheSimpleWindowInterface.h"
#include "networkDataStructure.h"
#include "callBackFunctions.h"

class simpleWindowUserInterface {
private:
	static simpleWindowUserInterface* instance;
	const int& m_ref_width;
	const int& m_ref_height;
	bool lButtonServiceBool = true;

	//Constructors and Destructor:
	explicit simpleWindowUserInterface::simpleWindowUserInterface(const int& width, const int& height, const callBackLinks& CBL) :m_ref_width(width), m_ref_height(height) {
		m_cObSptr = std::make_unique<concreteObserverSubject>();
		m_CBLptr = std::make_unique<callBackLinks>(CBL);
	
		iPosXRK = width - 110;
		iPosYRK = height - 110;
		m_CBLptr->m_callback_getRandomNumber = &getRandomNumber;
		m_networkCreationFunctions.iniziallizationOfPointer(gsl::not_null<callBackLinks*>(m_CBLptr.get()), gsl::not_null<concreteObserverSubject* >(m_cObSptr.get()));
		m_networkDataStructure.iniziallizationOfPointer(gsl::not_null<callBackLinks*>(m_CBLptr.get()));
	}
	simpleWindowUserInterface::simpleWindowUserInterface(simpleWindowUserInterface& other) = delete;
	simpleWindowUserInterface::simpleWindowUserInterface(simpleWindowUserInterface&& other) = delete;
	simpleWindowUserInterface& operator=(const simpleWindowUserInterface& other) = delete;
	simpleWindowUserInterface&& operator=(simpleWindowUserInterface&& other) = delete;
	simpleWindowUserInterface::~simpleWindowUserInterface() noexcept {}

public:
	networkDataStructure m_networkDataStructure;
	userFunctionsOfTheSimpleWindowInterface m_networkCreationFunctions;
	std::unique_ptr<callBackLinks>m_CBLptr;
	std::unique_ptr<concreteObserverSubject> m_cObSptr;
	int iPosXLK = 0;
	int iPosYLK = 0;
	int iPosXRK = 0;
	int iPosYRK = 0;
	
	
	//***************************************************************
	//Implementation methods:
	static void simpleWindowUserInterface::destroy() {
		delete instance;
		instance = nullptr;
	}

	static simpleWindowUserInterface* simpleWindowUserInterface::getInstance(const int& width, const int& height, const callBackLinks& CBL) {
		if (instance == 0) {
			instance = new simpleWindowUserInterface(width, height, CBL);
			return instance;
		}
		else {
			return instance;
		}
		
	}

	static int simpleWindowUserInterface::getRandomNumber() {
		static randomSpeed_neu rSn;
		rSn.randomNumberRequest();
		return  rSn.a;
	}

	//***************************************************************
	//Network generation methods:
	bool simpleWindowUserInterface::setClickPoints(HDC hdc, const int& numberOfLanes) {
		m_networkCreationFunctions.establishLane(m_ref_width, m_ref_height,numberOfLanes, iPosXLK, iPosYLK, lButtonServiceBool);
		m_CBLptr->m_hdc = hdc;
		
		m_CBLptr->topLevelFunctionPTR_f1PaintBoxLB(iPosXLK, iPosYLK, iPosXRK, iPosYRK);
		m_CBLptr->topLevelFunctionPTR_f2PaintBoxRB(iPosXLK, iPosYLK, iPosXRK, iPosYRK);
		m_CBLptr->topLevelFunctionPTR_f3PaintFrame(m_ref_height, m_ref_width);
			
		if (lButtonServiceBool) {
			lButtonServiceBool = false;
			return false;
		}
		else {
			lButtonServiceBool = true;
			return true;
		}
	}

	bool  simpleWindowUserInterface::generationOfTheNetworkGraphsFromNetworkLanes(const int& choiceOfRouteFinding) {
		if (!m_networkCreationFunctions.networkLaneVector.empty()) {
			m_networkCreationFunctions.graphGenerationFromClickPairs(m_ref_width, m_ref_height, choiceOfRouteFinding);
			for (auto& i : m_networkCreationFunctions.appliedGraph) {
				m_networkDataStructure.appliedGraph.push_back(std::move(i));
			}
			m_networkCreationFunctions.networkLaneVector.clear();
			m_networkCreationFunctions.appliedGraph.clear();
			return true;
		}
		else {
			return false;
		}
	}

	void simpleWindowUserInterface::displayNetworkWithSimulationStepResult() {
		//********************************************************************
		//method for displaying all vertexes, edges and vehicles on the surface
		int counter = 0;
		bool doubleVerticalVertex = false;
		bool doubleHorizontalVertex = false;
		for (auto& i : m_networkDataStructure.appliedGraph) {
			for (auto& ii : i->m_vectorOfEdgesPtr) {
				ii->m_ppPtr->paintWhiteLinePP();
			}
			for (auto& ii : i->m_vectorOfVertexPtr) {
				m_CBLptr->topLevelFunctionPTR_f7PrintVertexNumber(ii->m_XcoordinateVertex, ii->m_YcoordinateVertex, ii->m_vertexID);
				switch (ii->m_shapeOfThatVertex) {
				case 1:
					m_CBLptr->topLevelFunctionPTR_f12PaintBoxStart(ii->m_XcoordinateVertex, ii->m_YcoordinateVertex);
					break;

				case 2:
					m_CBLptr->topLevelFunctionPTR_f13PaintBoxEnd(ii->m_XcoordinateVertex, ii->m_YcoordinateVertex);
					break;

				case 11:
					counter = 0;
					doubleVerticalVertex = false;
					doubleHorizontalVertex = false;
					for (auto& iii : i->m_vectorOfEdgesPtr) {
						if ((iii->m_startVertexPtr->m_vertexID == ii->m_vertexID) || (iii->m_endVertexPtr->m_vertexID == ii->m_vertexID)) {
							if ((iii->m_startVertexPtr->m_shapeOfThatVertex == 11) && (ii->m_shapeOfThatVertex == 11) && (iii->m_startVertexPtr->m_vertexID == ii->m_vertexID)) {
								iii->m_ppPtr->paintStartVertex11();
							}
							if ((iii->m_endVertexPtr->m_shapeOfThatVertex == 11) && (ii->m_shapeOfThatVertex == 11) && (iii->m_endVertexPtr->m_vertexID == ii->m_vertexID)) {
								iii->m_ppPtr->paintEndVertex11();
							}
							if (iii->m_numberOfLanes == 2)
								counter++;
							if ((iii->m_verticalOrHorizontal == true) && (iii->m_numberOfLanes == 2))
								doubleVerticalVertex = true;
							if ((iii->m_verticalOrHorizontal == false) && (iii->m_numberOfLanes == 2))
								doubleHorizontalVertex = true;
						}

						if (counter >= 3) {
							m_CBLptr->topLevelFunctionPTR_f17PaintBoxFlex22(ii->m_XcoordinateVertex, ii->m_YcoordinateVertex);
							for (auto& iiii : i->m_vectorOfEdgesPtr) {
								if ((iiii->m_startVertexPtr->m_vertexID == ii->m_vertexID) && (iiii->m_risingOrDescention == true)) {
									iiii->m_ppPtr->setStartVertexShort(true);
								}
								if ((iiii->m_endVertexPtr->m_vertexID == ii->m_vertexID) && (iiii->m_risingOrDescention == false)) {
									iiii->m_ppPtr->setEndVertexShort(true);
								}
							}
						}
					}

					m_CBLptr->topLevelFunctionPTR_f14PaintBoxFlex11(ii->m_XcoordinateVertex, ii->m_YcoordinateVertex);
					counter = 0;
					if ((doubleVerticalVertex == true) || (doubleHorizontalVertex == true)) {
						for (auto& iii : i->m_vectorOfEdgesPtr) {
							if (doubleHorizontalVertex == true) {
								if ((iii->m_startVertexPtr->m_vertexID == ii->m_vertexID) && (iii->m_verticalOrHorizontal == true) && (iii->m_risingOrDescention == true))
									iii->m_ppPtr->setStartVertexShort(true);
								if ((iii->m_endVertexPtr->m_vertexID == ii->m_vertexID) && (iii->m_verticalOrHorizontal == true) && (iii->m_risingOrDescention == false))
									iii->m_ppPtr->setEndVertexShort(true);
								if ((iii->m_endVertexPtr->m_vertexID == ii->m_vertexID) && (iii->m_verticalOrHorizontal == true) && (iii->m_risingOrDescention == true))
									iii->m_ppPtr->setEndVertexShort(true);
							}
							if (doubleVerticalVertex == true) {
								if ((iii->m_startVertexPtr->m_vertexID == ii->m_vertexID) && (iii->m_verticalOrHorizontal == false) && (iii->m_risingOrDescention == true))
									iii->m_ppPtr->setStartVertexShort(true);
								if ((iii->m_endVertexPtr->m_vertexID == ii->m_vertexID) && (iii->m_verticalOrHorizontal == false) && (iii->m_risingOrDescention == false))
									iii->m_ppPtr->setEndVertexShort(true);
								if ((iii->m_endVertexPtr->m_vertexID == ii->m_vertexID) && (iii->m_verticalOrHorizontal == false) && (iii->m_risingOrDescention == true))
									iii->m_ppPtr->setEndVertexShort(true);
							}
						}
					}
					break;
				}
			}
			for (auto& ii : i->m_vectorOfEdgesPtr) {
				ii->m_ppPtr->paintBoxPP();
			}
		}
	}
};


