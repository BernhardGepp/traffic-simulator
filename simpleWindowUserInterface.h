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

#include "callBackLinks.h"
#include "observer_subjekt.h"
#include "userFunctionsOfTheSimpleWindowInterface.h"
#include "networkDataStructure.h"

class simpleWindowUserInterface {
private:
	static simpleWindowUserInterface* instance;

	
	const int& m_ref_width;
	const int& m_ref_height;
	bool lButtonServiceBool = true;

	//Constructors and Destructor:
	explicit simpleWindowUserInterface::simpleWindowUserInterface(const int& width, const int& height, const callBackLinks& CBL) :m_ref_width(width), m_ref_height(height) {

		m_cObSptr = std::make_unique<concreteObserverSubjekt>();
		m_CBLptr = std::make_unique<callBackLinks>(CBL);
				
		iPosXRK = width - 110;
		iPosYRK = height - 110;
		m_CBLptr->m_callback_getRandomNumber = &getRandomNumber;
		m_networkCreationFunctions.iniziallizationOfPointer(gsl::not_null<callBackLinks*>(m_CBLptr.get()), gsl::not_null<concreteObserverSubjekt* >(m_cObSptr.get()));
	}
	simpleWindowUserInterface::simpleWindowUserInterface(simpleWindowUserInterface& other) = delete;
	simpleWindowUserInterface::simpleWindowUserInterface(simpleWindowUserInterface&& other) = delete;
	simpleWindowUserInterface& operator=(const simpleWindowUserInterface& other) = delete;
	simpleWindowUserInterface&& operator=(simpleWindowUserInterface&& other) = delete;
	simpleWindowUserInterface::~simpleWindowUserInterface() noexcept {}

public:
	networkDataStructure m_networkDataStructure;
	userFunctionsOfTheSimpleWindowInterface m_networkCreationFunctions;
	PrintInGDIplusWinEmpty m_PWE;
	std::unique_ptr<callBackLinks>m_CBLptr;
	std::unique_ptr<concreteObserverSubjekt> m_cObSptr;
	int serviceInt1 = 0;
	int serviceInt2 = 0;
	int iPosXLK = 0;
	int iPosYLK = 0;
	int iPosXRK = 0;
	int iPosYRK = 0;
	
	

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
		iPosYLK = 0;
		iPosXLK = 0;
		iPosXRK = m_ref_width - 110;
		iPosYRK = m_ref_height - 110;
	}

	bool simpleWindowUserInterface::setPoints(HDC hdc, const int& numberOfLanes) {
		m_networkCreationFunctions.establishLane(m_ref_width, m_ref_height,numberOfLanes, iPosXLK, iPosYLK, lButtonServiceBool);
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
		
		m_networkCreationFunctions.graphGenerationFromClickPairs(m_ref_width, m_ref_height, choiceOfRouteFinding);
		
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


