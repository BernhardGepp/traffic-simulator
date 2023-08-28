#pragma once
#include "PrecompiledHeadersEdges.h"
#include "simpleWindowUserInterface.h"
#include "callBackFunctions.h"
#include "TRAFFICSIMULATOR.H"



class trafficSimulatorWithSimpleUserInterface: public trafficSimulator {
public:
	void(*m_f1PaintBoxLB)(HDC hdc) = nullptr;
	void(*m_f2PaintBoxRB)(HDC hdc) = nullptr;
	void(*m_f3PaintFrame)(HDC hdc) = nullptr;
	void(*m_f7PrintVertexNumber)(HDC hdc, const int& iPosX, const int& iPosY, const int& iVertexID) = nullptr;
	simpleWindowUserInterface* n = nullptr;
	//simpleWindowUserInterface* simpleWindowUserInterface::instance=0;
	//void displaySimulationStepResult()override;
	HDC hdc;
	explicit trafficSimulatorWithSimpleUserInterface::trafficSimulatorWithSimpleUserInterface(HDC hdc);
};