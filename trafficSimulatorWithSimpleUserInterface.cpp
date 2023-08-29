#pragma once
#include "PrecompiledHeadersEdges.h"
#include "trafficSimulator.h"
#include "trafficSimulatorWithSimpleUserInterface.h"
#include "callBackFunctions.h"
using namespace Gdiplus;


simpleWindowUserInterface* simpleWindowUserInterface::instance = 0;
trafficSimulatorWithSimpleUserInterface::trafficSimulatorWithSimpleUserInterface(HDC hdc):trafficSimulator(){
	n = simpleWindowUserInterface::getInstance(width, height, callBackLinks(hdc, PaintBoxLB, PaintBoxRB, PaintFrame, PaintLane, PrintVertexNumber,PaintBox, PaintWhiteLine, PaintBoxStart,
		 PaintBoxEnd, PaintBoxFex11, PaintBoxFex12, PaintBoxFex21, PaintBoxFex22,PrintLaneIF,PaintWhiteClearLane));
}
bool trafficSimulatorWithSimpleUserInterface::waitIfDubbleClick(const int& a, const int& b) {
	if ((a == m_serviceInt1) && (b == m_serviceInt2)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
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
	n->iPosXLK = iPosYRK;
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
		n->m_cObSptr->benachrichtigen(iPosXLK, iPosYLK);
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