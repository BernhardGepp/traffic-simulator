#pragma once
#include "simpleWindowUserInterface.h"
#include "TRAFFICSIMULATOR.H"

class trafficSimulatorWithSimpleUserInterface: public trafficSimulator {
public:
	void(*m_f1PaintBoxLB)(HDC hdc) = nullptr;
	void(*m_f2PaintBoxRB)(HDC hdc) = nullptr;
	void(*m_f3PaintFrame)(HDC hdc) = nullptr;
	void(*m_f7PrintVertexNumber)(HDC hdc, const int& iPosX, const int& iPosY, const int& iVertexID) = nullptr;
	simpleWindowUserInterface* n = nullptr;
	HDC hdc;
	int height;
	int width;
	int m_serviceInt1 = 0;
	int m_serviceInt2 = 0;
	int m_determinationVariableOfNumberOfLanes = 0;
	bool m_statusDuringPointPairDetermination = true;

	explicit trafficSimulatorWithSimpleUserInterface(HDC hdc);

	bool queryOnTheSelectedNumberOfLanes();
	void clickPointsResetInTheField();
	bool waitIfDubbleClick(const int& a, const int& b);
	int mainFunctionOfTheTrafficSimulator();
	void rightClick(const int&,const int&);
	void leftClick(const int&, const int&);
};