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