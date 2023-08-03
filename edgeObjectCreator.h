#pragma once
#include "PrecompiledHeadersEdges.h"
#include "callBackLinks.h"
#include "observer_subjekt.h"
#include "selectionFlowSimulation.h"
#include "edge.h"


class createEdge {
	public:
		
		concreteObserverSubjekt* m_cObSptr = nullptr;
		callBackLinks* m_CBLptr = nullptr;
		std::shared_ptr<vertex> m_startVertex;
		std::shared_ptr<vertex> m_endVertex;
		int m_numberOfLanes = 0;
		int m_p1x = 0;
		int m_p1y = 0;
		int m_p2x = 0; 
		int m_p2y = 0; 
		int m_lanesH = 0;
		int m_lanesV = 0;
		
		std::unique_ptr<edge> createdEdge;
		createEdge(callBackLinks* CBL, concreteObserverSubjekt* cOS);
		~createEdge();
		std::unique_ptr <edge>&& create(const std::shared_ptr<vertex>&, const std::shared_ptr<vertex>&, const int&, const int& p1x, const int& p1y, const int& p2x, const int& p2y, const int& lanesH, const int& lanesV);
		//std::unique_ptr<PrintPattern>&& choosePrintPattern(const int& p1x, const int& p1y, const int& p2x, const int& p2y, const int& lanesH, const int& lanesV);
		std::unique_ptr<PrintPattern> choosePrintPattern();
		void iniziallizationOfPointer(callBackLinks* CBL, concreteObserverSubjekt* cOS);
		
};