#pragma once
#include "PrecompiledHeadersEdges.h"
#include "trafficSimulator.h"
#include "trafficSimulatorWithSimpleUserInterface.h"

using namespace Gdiplus;
//********************************************************************

simpleWindowUserInterface* simpleWindowUserInterface::instance = 0;
trafficSimulatorWithSimpleUserInterface::trafficSimulatorWithSimpleUserInterface(HDC hdc):trafficSimulator(){
	n = gsl::not_null<simpleWindowUserInterface*>(simpleWindowUserInterface::getInstance(width, height, callBackLinks(hdc, PaintBoxLB, PaintBoxRB, PaintFrame, PaintLane, PrintVertexNumber,PaintBox, PaintWhiteLine, PaintBoxStart,
		 PaintBoxEnd, PaintBoxFex11, PaintBoxFex12, PaintBoxFex21, PaintBoxFex22,PrintLaneIF,PaintWhiteClearLane)));
}

int trafficSimulatorWithSimpleUserInterface::mainFunctionOfTheTrafficSimulator() {
	if ((m_currentSimulationStep > 0) && (m_programStatus)) {
		//***********************************************************************
		// Option 1: Carrying out a simulation sequence of the traffic simulator
		
		//Reduction of the number of simulation iterations to be performed
		m_currentSimulationStep--;
		if (n->m_networkDataStructure.appliedGraph.size() >= 1) {
			//Command to call a simulation sequence (for all graphs)
			for (auto& i : n->m_networkDataStructure.appliedGraph) {
				i->simulation(m_currentSimulationStep);
			}
			//Pause between the calculation of the result of a simulation sequence and its display
			if (n->m_networkDataStructure.appliedGraph[0]->m_vectorOfEdgesPtr.size() <= 6) {
				std::this_thread::sleep_for(std::chrono::milliseconds(250));
			}
			else {
				std::this_thread::sleep_for(std::chrono::milliseconds(260));
			}
			//Commands for displaying the result of the simulation
			n->displayNetworkWithSimulationStepResult();
			n->m_networkDataStructure.printLanesAndVehiclesOfAllEdges();
		}
		
		return 1;
	}
	if ((m_currentSimulationStep == 0) && (m_programStatus)) {
		//***********************************************************************
		// Option 2: After running the simulation (traffic simulator counter is zero)
		return 2;
	}
	if ((n->m_networkDataStructure.appliedGraph.size() == 0) && (m_programStatus)) {
		//***********************************************************************
		//Option 3: This programe path prevents a simulation process from being executed if no traffic graphs are available.
		return 3;
	}
	//***********************************************************************
	// Option 4: This option becomes effective if no traffic graphs have been created yet and no traffic simulation is possible!
	return 0;
}

void trafficSimulatorWithSimpleUserInterface::clickPointsResetInTheField() {
	n->iPosYLK = 0;
	n->iPosXLK = 0;
	n->iPosXRK = width - 110;
	n->iPosYRK = height - 110;
}

bool trafficSimulatorWithSimpleUserInterface::waitIfDubbleClick(const int& a, const int& b) {
	if ((a == m_serviceInt1) && (b == m_serviceInt2)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
		m_serviceInt1 = 0;
		m_serviceInt2 = 0;
		return false;
	}
	else {
		m_serviceInt1 = a;
		m_serviceInt2 = b;
		return true;
	}
}

bool trafficSimulatorWithSimpleUserInterface::queryOnTheSelectedNumberOfLanes() {
	if ((m_programStatus == false) && (m_statusDuringPointPairDetermination == false)) {
		return true;
	}
	else {
		return false;
	}
}

void trafficSimulatorWithSimpleUserInterface::rightClick(const int& paramX, const int& paramY) {
	int iPosXRK = paramX;
	int iPosYRK = paramY;
	waitIfDubbleClick(iPosXRK, iPosYRK);
	if (iPosXRK > (width - 100))
		iPosXRK = (width - 100);
	if (iPosYRK > (height - 100))
		iPosYRK = (height - 110);
	n->iPosXRK = iPosXRK;
	n->iPosYRK = iPosYRK;
}

void trafficSimulatorWithSimpleUserInterface::leftClick(const int& paramX, const int& paramY) {
	bool serviceBool = false;
	int iPosXLK= paramX;
	int iPosYLK = paramY;
	serviceBool=waitIfDubbleClick(iPosXLK, iPosYLK);
	if (iPosXLK > (width - 100))
		iPosXLK = (width - 110);
	if (iPosYLK > (height - 100))
		iPosYLK = (height - 110);
	n->iPosXLK = iPosXLK;
	n->iPosYLK = iPosYLK;
	if (serviceBool) {
		n->m_cObSptr->toNotify(iPosXLK, iPosYLK);
		if (m_programStatus == false) {
			switch (m_determinationVariableOfNumberOfLanes) {
			case 1:
				m_statusDuringPointPairDetermination = n->setClickPoints(hdc, 1);
				break;
			case 2:
				m_statusDuringPointPairDetermination = n->setClickPoints(hdc, 2);
				break;
			default:
				m_statusDuringPointPairDetermination = n->setClickPoints(hdc, 1);
				break;
			}
		}
	}

}