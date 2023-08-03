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
std::unique_ptr <edge>&& createEdge::create(const std::shared_ptr<vertex>& startVertex, const std::shared_ptr<vertex>& endVertex, const int& numberOfLanes, const int& p1x, const int& p1y, const int& p2x, const int& p2y, const int& lanesH, const int& lanesV) {
	m_startVertex = startVertex;
	m_endVertex = endVertex;
	m_numberOfLanes = numberOfLanes;
	m_p1x = p1x;
	m_p1y = p1y;
	m_p2x = p2x;
	m_p2y = p2y;
	m_lanesH = lanesH;
	m_lanesV = lanesV;
	
	//std::unique_ptr<PrintPattern> pp = choosePrintPattern(p1x, p1y, p2x, p2y, lanesH, lanesV);
	//createdEdge= std::make_unique<edge>(m_startVertex, m_endVertex, m_numberOfLanes, choosePrintPattern(m_p1x, m_p1y, m_p2x, m_p2y, m_lanesH, m_lanesV), m_cOSptr);
	
	
	createdEdge = std::make_unique<edge>(m_startVertex, m_endVertex, m_numberOfLanes, choosePrintPattern(), m_cObSptr);
	
	return std::move(createdEdge);
}

/*std::unique_ptr<PrintPattern>&& createEdge::choosePrintPattern(const int& p1x, const int& p1y, const int& p2x, const int& p2y, const int& lanesH, const int& lanesV) {
	//********************************************************************
		//Selection of the appropriate print pattern
		//This method is called by the method "graphGenerationFromClickPairs". This method is part of the traffic graph generation. 
	if ((p1x < p2x) && (p1y == p2y)) {
		if (lanesH == 1) {
			return std::move(std::make_unique<PrintPatternLine1LaneHoriPos>(p1x, p1y, p2x, p2y, gsl::not_null<callBackLinks*>(m_CBLptr)));
		}
		else if (lanesH == 2) {
			return std::move(std::make_unique<PrintPatternLine2LaneHoriPos>(p1x, p1y, p2x, p2y, gsl::not_null<callBackLinks*>(m_CBLptr)));
		}
	}
	if ((p1x > p2x) && (p1y == p2y)) {
		if (lanesH == 1) {
			return std::move(std::make_unique<PrintPatternLine1LaneHoriNeg>(p1x, p1y, p2x, p2y, gsl::not_null<callBackLinks*>(m_CBLptr)));
		}
		else if (lanesH == 2) {
			return std::move(std::make_unique<PrintPatternLine2LaneHoriNeg>(p1x, p1y, p2x, p2y, gsl::not_null<callBackLinks*>(m_CBLptr)));
		}
	}
	if ((p1x == p2x) && (p1y < p2y)) {
		if (lanesV == 1) {
			return std::move(std::make_unique<PrintPatternLine1LaneVertiPos>(p1x, p1y, p2x, p2y, gsl::not_null<callBackLinks*>(m_CBLptr)));
		}
		else if (lanesV == 2) {
			return std::move(std::make_unique<PrintPatternLine2LaneVertiPos>(p1x, p1y, p2x, p2y, gsl::not_null<callBackLinks*>(m_CBLptr)));
		}
	}
	if ((p1x == p2x) && (p1y > p2y)) {
		if (lanesV == 1) {
			return std::move(std::make_unique<PrintPatternLine1LaneVertiNeg>(p1x, p1y, p2x, p2y, gsl::not_null<callBackLinks*>(m_CBLptr)));
		}
		else if (lanesV == 2) {
			return std::move(std::make_unique<PrintPatternLine2LaneVertiNeg>(p1x, p1y, p2x, p2y, gsl::not_null<callBackLinks*>(m_CBLptr)));
		}
	}
	return nullptr;
}*/
std::unique_ptr<PrintPattern> createEdge::choosePrintPattern() {
	//********************************************************************
	//Selection of the appropriate print pattern
	//This method is called by the method "graphGenerationFromClickPairs". This method is part of the traffic graph generation. 
	if ((m_p1x < m_p2x) && (m_p1y == m_p2y)) {
		if (m_lanesH == 1) {
			return std::make_unique<PrintPatternLine1LaneHoriPos>(m_p1x, m_p1y, m_p2x, m_p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
		else if (m_lanesH == 2) {
			return std::make_unique<PrintPatternLine2LaneHoriPos>(m_p1x, m_p1y, m_p2x, m_p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
	}
	if ((m_p1x > m_p2x) && (m_p1y == m_p2y)) {
		if (m_lanesH == 1) {
			return std::make_unique<PrintPatternLine1LaneHoriNeg>(m_p1x, m_p1y, m_p2x, m_p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
		else if (m_lanesH == 2) {
			return std::make_unique<PrintPatternLine2LaneHoriNeg>(m_p1x, m_p1y, m_p2x, m_p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
	}
	if ((m_p1x == m_p2x) && (m_p1y < m_p2y)) {
		if (m_lanesV == 1) {
			return std::make_unique<PrintPatternLine1LaneVertiPos>(m_p1x, m_p1y, m_p2x, m_p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
		else if (m_lanesV == 2) {
			return std::make_unique<PrintPatternLine2LaneVertiPos>(m_p1x, m_p1y, m_p2x, m_p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
	}
	if ((m_p1x == m_p2x) && (m_p1y > m_p2y)) {
		if (m_lanesV == 1) {
			return std::make_unique<PrintPatternLine1LaneVertiNeg>(m_p1x, m_p1y, m_p2x, m_p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
		else if (m_lanesV == 2) {
			return std::make_unique<PrintPatternLine2LaneVertiNeg>(m_p1x, m_p1y, m_p2x, m_p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
	}
}