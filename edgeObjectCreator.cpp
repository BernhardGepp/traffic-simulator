#pragma once
#include "PrecompiledHeadersEdges.h"
#include "edgeObjectCreator.h"
#include "callBackLinks.h"
#include "observer_subjekt.h"
#include "selectionFlowSimulation.h"
#include "edge.h"

createEdge::createEdge(callBackLinks* CBL, concreteObserverSubjekt* cOS) {
	m_CBLptr = CBL;
	m_cObSptr = cOS;
}
createEdge::~createEdge() {
	
}
void createEdge::iniziallizationOfPointer(callBackLinks* CBL, concreteObserverSubjekt* cOS) {
	m_CBLptr = CBL;
	m_cObSptr = cOS;
}
std::unique_ptr <edge>&& createEdge::create(const int& startVertex, const int& endVertex, const int& numberOfLanes, const int& p1x, const int& p1y, const int& p2x, const int& p2y, const int& lanesH, const int& lanesV, concreteObserverSubjekt* cOSptr) {
	
	createdEdge= std::make_unique<edge>(startVertex, endVertex, numberOfLanes, std::move(choosePrintPattern(p1x, p1y, p2x, p2y, lanesH, lanesV)), cOSptr);
	return std::move(createdEdge);
}

std::unique_ptr<PrintPattern> createEdge::choosePrintPattern(const int& p1x, const int& p1y, const int& p2x, const int& p2y, const int& lanesH, const int& lanesV) {
	//********************************************************************
	//Selection of the appropriate print pattern
	//This method is called by the method "graphGenerationFromClickPairs". This method is part of the traffic graph generation. 
	if ((p1x < p2x) && (p1y == p2y)) {
		if (lanesH == 1) {
			return std::make_unique<PrintPatternLine1LaneHoriPos>(p1x, p1y, p2x, p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
		else if (lanesH == 2) {
			return std::make_unique<PrintPatternLine2LaneHoriPos>(p1x, p1y, p2x, p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
	}
	if ((p1x > p2x) && (p1y == p2y)) {
		if (lanesH == 1) {
			return std::make_unique<PrintPatternLine1LaneHoriNeg>(p1x, p1y, p2x, p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
		else if (lanesH == 2) {
			return std::make_unique<PrintPatternLine2LaneHoriNeg>(p1x, p1y, p2x, p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
	}
	if ((p1x == p2x) && (p1y < p2y)) {
		if (lanesV == 1) {
			return std::make_unique<PrintPatternLine1LaneVertiPos>(p1x, p1y, p2x, p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
		else if (lanesV == 2) {
			return std::make_unique<PrintPatternLine2LaneVertiPos>(p1x, p1y, p2x, p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
	}
	if ((p1x == p2x) && (p1y > p2y)) {
		if (lanesV == 1) {
			return std::make_unique<PrintPatternLine1LaneVertiNeg>(p1x, p1y, p2x, p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
		else if (lanesV == 2) {
			return std::make_unique<PrintPatternLine2LaneVertiNeg>(p1x, p1y, p2x, p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
	}
	return nullptr;
}