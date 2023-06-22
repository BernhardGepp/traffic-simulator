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
#include "networkCreationVHLinks.h"
#include "networkCreationOfVHLinks.h"

class SimpleWindowUserInterface {
private:
	static SimpleWindowUserInterface* instance;

	
	const int& width;
	const int& height;
	bool lButtonServiceBool = true;

	//Constructors and Destructor:
	//explicit network(const int& width, const int& height, const callBackLinks& CBL);
	explicit SimpleWindowUserInterface::SimpleWindowUserInterface(const int& width, const int& height, const callBackLinks& CBL) :width(width), height(height) {

		m_cObSptr = std::make_unique<concreteObserverSubjekt>();
		m_nCptr = std::make_unique<userFunctionsOfTheSimpleWindowInterface> ();
		//m_nCptr->m_CBLptr = std::make_unique<callBackLinks>(CBL);
		
		m_CBLptr = std::make_unique<callBackLinks>(CBL);
		//m_nCptr->m_CBLptr = m_CBLptr.get();
		iPosXRK = width - 110;
		iPosYRK = height - 110;
		m_CBLptr->m_callback_getRandomNumber = &getRandomNumber;

	}
	SimpleWindowUserInterface::SimpleWindowUserInterface(SimpleWindowUserInterface& other) = delete;
	SimpleWindowUserInterface::SimpleWindowUserInterface(SimpleWindowUserInterface&& other) = delete;
	SimpleWindowUserInterface& operator=(const SimpleWindowUserInterface& other) = delete;
	SimpleWindowUserInterface&& operator=(SimpleWindowUserInterface&& other) = delete;
	SimpleWindowUserInterface::~SimpleWindowUserInterface() noexcept {}

public:
	networkDataStructure networkCreationClass;
	std::unique_ptr <userFunctionsOfTheSimpleWindowInterface> m_nCptr;
	std::unique_ptr<callBackLinks>m_CBLptr;
	std::unique_ptr<concreteObserverSubjekt> m_cObSptr;
	int serviceInt1 = 0;
	int serviceInt2 = 0;
	int iPosXLK = 0;
	int iPosYLK = 0;
	int iPosXRK = 0;
	int iPosYRK = 0;
	PrintInGDIplusWinEmpty m_PWE;
	

	static void SimpleWindowUserInterface::destroy() {
		delete instance;
		instance = nullptr;
	}

	static SimpleWindowUserInterface* SimpleWindowUserInterface::getInstance(const int& width, const int& height, const callBackLinks& CBL) {
		if (instance == 0) {
			instance = new SimpleWindowUserInterface(width, height, CBL);
			return instance;
		}
		else {
			return instance;
		}
	}

	static int SimpleWindowUserInterface::getRandomNumber() {
		static randomSpeed_neu rSn;
		rSn.randomNumberRequest();
		return  rSn.a;
	}

	void SimpleWindowUserInterface::fieldRecalibarte() {
		iPosXRK = width - 110;
		iPosYRK = height - 110;
	}

	bool SimpleWindowUserInterface::setPoints(HDC hdc, const int& numberOfLanes) {
		m_nCptr->establishLane(numberOfLanes, iPosXLK, iPosYLK, lButtonServiceBool);
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

	/*void  network::establishVertexOfGraph(const int& choiceOfRouteFinding) {

		callBackLinks* CBL = nullptr;
		concreteObserverSubjekt* cOS = nullptr;
		CBL = m_CBLptr.get();
		cOS = m_cObSptr.get();
		networkCreationClass.iniziallizationOfPointer(gsl::not_null<callBackLinks*>(CBL), gsl::not_null<concreteObserverSubjekt* >(cOS));
		std::pair<int, int> startingPoint;
		std::pair<int, int> endingPoint;
		if (m_nCptr->networkLaneVector.size() > 0) {
			for (auto& i : m_nCptr->networkLaneVector) {
				startingPoint.first = std::get<0>(i).first;
				startingPoint.second = std::get<0>(i).second;
				endingPoint.first = std::get<1>(i).first;
				endingPoint.second = std::get<1>(i).second;

				if (std::get<3>(i) == m_nCptr->oneLane) {
					networkCreationClass.fillNetworkLaneVector(startingPoint, endingPoint, std::get<2>(i), 1);
				}
				if (std::get<3>(i) == m_nCptr->twoLanes) {
					networkCreationClass.fillNetworkLaneVector(startingPoint, endingPoint, std::get<2>(i), 2);
				}
			}
		}
		networkCreationClass.graphGenerationFromClickPairs(choiceOfRouteFinding);
		m_nCptr->networkLaneVector.clear();
		networkCreationClass.networkLaneVector.clear();
	}*/
	void  SimpleWindowUserInterface::establishVertexOfGraph(const int& choiceOfRouteFinding) {
		callBackLinks* CBL = nullptr;
		concreteObserverSubjekt* cOS = nullptr;
		CBL = m_CBLptr.get();
		cOS = m_cObSptr.get();
		m_nCptr->iniziallizationOfPointer(gsl::not_null<callBackLinks*>(CBL), gsl::not_null<concreteObserverSubjekt* >(cOS));
		m_nCptr->graphGenerationFromClickPairs(choiceOfRouteFinding);
		
		for (auto& i : m_nCptr->appliedGraph) {
			networkCreationClass.appliedGraph.push_back(std::move(i));
		}
		m_nCptr->networkLaneVector.clear();
		m_nCptr->appliedGraph.clear();
	}
	

	void SimpleWindowUserInterface::printLanesAndVehiclesOfAllEdges() {

		networkCreationClass.printLanesAndVehiclesOfAllEdges();
		m_PWE.fullemptyPrintContainer(m_CBLptr->m_hdc, m_CBLptr->m_f5PaintLane);
	}

	void SimpleWindowUserInterface::waitIfDubbleClick(const int& a, const int& b) {
		if ((a == serviceInt1) && (b == serviceInt2)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
		}
		else {
			serviceInt1 = a;
			serviceInt2 = b;
		}
	}
};


