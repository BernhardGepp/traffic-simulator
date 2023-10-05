#pragma once
#include "PrecompiledHeadersEdges.h"
#include "edgeObjectCreator.h"

createEdge::createEdge(callBackLinks* CBL, concreteObserverSubject* cOS) {
	m_CBLptr = CBL;
	m_cObSptr = cOS;
}
createEdge::~createEdge() {
}
void createEdge::iniziallizationOfPointer(callBackLinks* CBL, concreteObserverSubject* cOS) {
	m_CBLptr = CBL;
	m_cObSptr = cOS;
}
std::unique_ptr <edge>&& createEdge::create(const std::shared_ptr<vertex>& startVertex, const std::shared_ptr<vertex>& endVertex, const int& numberOfLanes) {
	m_startVertex = startVertex;
	m_endVertex = endVertex;
	m_numberOfLanes = numberOfLanes;
	m_p1x = m_startVertex->m_XcoordinateVertex;
	m_p1y = m_startVertex->m_YcoordinateVertex;
	m_p2x = m_endVertex->m_XcoordinateVertex;
	m_p2y = m_endVertex->m_YcoordinateVertex;
	
	createdEdge = std::make_unique<edge>(m_startVertex, m_endVertex, m_numberOfLanes, choosePrintPattern(), m_cObSptr);
	return std::move(createdEdge);
}
std::unique_ptr<PrintPattern> createEdge::choosePrintPattern() {
	//********************************************************************
	//Selection of the appropriate print pattern
	//This method is called by the method "graphGenerationFromClickPairs". This method is part of the traffic graph generation. 
	if ((m_p1x < m_p2x) && (m_p1y == m_p2y)) {
		if (m_numberOfLanes == 1) {
			return std::make_unique<PrintPatternLine1LaneHoriPos>(m_p1x, m_p1y, m_p2x, m_p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
		else if (m_numberOfLanes == 2) {
			return std::make_unique<PrintPatternLine2LaneHoriPos>(m_p1x, m_p1y, m_p2x, m_p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
	}
	if ((m_p1x > m_p2x) && (m_p1y == m_p2y)) {
		if (m_numberOfLanes == 1) {
			return std::make_unique<PrintPatternLine1LaneHoriNeg>(m_p1x, m_p1y, m_p2x, m_p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
		else if (m_numberOfLanes == 2) {
			return std::make_unique<PrintPatternLine2LaneHoriNeg>(m_p1x, m_p1y, m_p2x, m_p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
	}
	if ((m_p1x == m_p2x) && (m_p1y < m_p2y)) {
		if (m_numberOfLanes == 1) {
			return std::make_unique<PrintPatternLine1LaneVertiPos>(m_p1x, m_p1y, m_p2x, m_p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
		else if (m_numberOfLanes == 2) {
			return std::make_unique<PrintPatternLine2LaneVertiPos>(m_p1x, m_p1y, m_p2x, m_p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
	}
	if ((m_p1x == m_p2x) && (m_p1y > m_p2y)) {
		if (m_numberOfLanes == 1) {
			return std::make_unique<PrintPatternLine1LaneVertiNeg>(m_p1x, m_p1y, m_p2x, m_p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
		else if (m_numberOfLanes == 2) {
			return std::make_unique<PrintPatternLine2LaneVertiNeg>(m_p1x, m_p1y, m_p2x, m_p2y, gsl::not_null<callBackLinks*>(m_CBLptr));
		}
	}
}