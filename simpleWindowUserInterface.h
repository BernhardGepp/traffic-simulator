#pragma once
#include "PrecompiledHeadersEdges.h"
//#include "vertex.h"
#include "vertexFlex.h"
#include "vertexStart.h"
#include "vertexEnd.h"
//#include "edge.h"
#include "graph.h"
//#include "vehicle.h"
#include "random_speed_neu.h"
#include "PrintInGDIplusWinEmpty.h"
#include "callBackLinks.h"
#include "observer_subjekt.h"
#include "userFunctionsOfTheSimpleWindowInterface.h"
#include "networkDataStructure.h"

class simpleWindowUserInterface {
private:
	static simpleWindowUserInterface* instance;

	
	const int& width;
	const int& height;
	bool lButtonServiceBool = true;

	//Constructors and Destructor:
	explicit simpleWindowUserInterface::simpleWindowUserInterface(const int& width, const int& height, const callBackLinks& CBL) :width(width), height(height) {

		m_cObSptr = std::make_unique<concreteObserverSubjekt>();
		//m_nCptr = std::make_unique<userFunctionsOfTheSimpleWindowInterface> ();
		//m_nCptr->m_CBLptr = std::make_unique<callBackLinks>(CBL);
		
		m_CBLptr = std::make_unique<callBackLinks>(CBL);
		//m_nCptr->m_CBLptr = m_CBLptr.get();
		iPosXRK = width - 110;
		iPosYRK = height - 110;
		m_CBLptr->m_callback_getRandomNumber = &getRandomNumber;

	}
	simpleWindowUserInterface::simpleWindowUserInterface(simpleWindowUserInterface& other) = delete;
	simpleWindowUserInterface::simpleWindowUserInterface(simpleWindowUserInterface&& other) = delete;
	simpleWindowUserInterface& operator=(const simpleWindowUserInterface& other) = delete;
	simpleWindowUserInterface&& operator=(simpleWindowUserInterface&& other) = delete;
	simpleWindowUserInterface::~simpleWindowUserInterface() noexcept {}

public:
	networkDataStructure m_networkDataStructure;
	//std::unique_ptr <userFunctionsOfTheSimpleWindowInterface> m_nCptr;
	userFunctionsOfTheSimpleWindowInterface m_networkCreationFunctions;
	std::unique_ptr<callBackLinks>m_CBLptr;
	std::unique_ptr<concreteObserverSubjekt> m_cObSptr;
	int serviceInt1 = 0;
	int serviceInt2 = 0;
	int iPosXLK = 0;
	int iPosYLK = 0;
	int iPosXRK = 0;
	int iPosYRK = 0;
	PrintInGDIplusWinEmpty m_PWE;
	

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

	void simpleWindowUserInterface::fieldRecalibarte() {
		iPosXRK = width - 110;
		iPosYRK = height - 110;
	}

	bool simpleWindowUserInterface::setPoints(HDC hdc, const int& numberOfLanes) {
		m_networkCreationFunctions.establishLane(numberOfLanes, iPosXLK, iPosYLK, lButtonServiceBool);
		m_CBLptr->topLevelFunctionPTR_f1PaintBoxLB();
		m_CBLptr->topLevelFunctionPTR_f2PaintBoxRB();
		m_CBLptr->topLevelFunctionPTR_f3PaintFrame();

		if (lButtonServiceBool) {
			lButtonServiceBool = false;
			return false;
		}
		else {
			lButtonServiceBool = true;
			return true;
		}
	}

	void  simpleWindowUserInterface::establishVertexOfGraph(const int& choiceOfRouteFinding) {
		callBackLinks* CBL = nullptr;
		concreteObserverSubjekt* cOS = nullptr;
		CBL = m_CBLptr.get();
		cOS = m_cObSptr.get();
		m_networkCreationFunctions.iniziallizationOfPointer(gsl::not_null<callBackLinks*>(CBL), gsl::not_null<concreteObserverSubjekt* >(cOS));
		m_networkCreationFunctions.graphGenerationFromClickPairs(choiceOfRouteFinding);
		
		for (auto& i : m_networkCreationFunctions.appliedGraph) {
			m_networkDataStructure.appliedGraph.push_back(std::move(i));
		}
		m_networkCreationFunctions.networkLaneVector.clear();
		m_networkCreationFunctions.appliedGraph.clear();
	}
	

	void simpleWindowUserInterface::printLanesAndVehiclesOfAllEdges() {

		m_networkDataStructure.printLanesAndVehiclesOfAllEdges();
		m_PWE.fullemptyPrintContainer(m_CBLptr->m_hdc, m_CBLptr->m_f5PaintLane);
	}

	void simpleWindowUserInterface::waitIfDubbleClick(const int& a, const int& b) {
		if ((a == serviceInt1) && (b == serviceInt2)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
		}
		else {
			serviceInt1 = a;
			serviceInt2 = b;
		}
	}
};


