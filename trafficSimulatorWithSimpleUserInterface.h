#pragma once
#include "simpleWindowUserInterface.h"
#include "TRAFFICSIMULATOR.H"

class trafficSimulatorWithSimpleUserInterface: public trafficSimulator {
public:
	simpleWindowUserInterface* n = nullptr;
	HDC hdc;
	int height;
	int width;
	int m_serviceInt1 = 0;
	int m_serviceInt2 = 0;
	int m_determinationVariableOfNumberOfLanes = 0;
	int m_choiceOfRouteFinding = 2;
	bool m_statusDuringPointPairDetermination = true;

	explicit trafficSimulatorWithSimpleUserInterface(HDC hdc);

	bool queryOnTheSelectedNumberOfLanes();
	void clickPointsResetInTheField();
	bool waitIfDubbleClick(const int& a, const int& b);
	int mainFunctionOfTheTrafficSimulator();
	void rightClick(const int&,const int&);
	void leftClick(const int&, const int&);
};