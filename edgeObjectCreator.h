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
		std::unique_ptr<edge> createdEdge;
		createEdge(callBackLinks* CBL, concreteObserverSubjekt* cOS);
		~createEdge();
		std::unique_ptr <edge>&& create(const int&, const int&, const int&, const int& p1x, const int& p1y, const int& p2x, const int& p2y, const int& lanesH, const int& lanesV, concreteObserverSubjekt* cOSptr);
		std::unique_ptr<PrintPattern> choosePrintPattern(const int& p1x, const int& p1y, const int& p2x, const int& p2y, const int& lanesH, const int& lanesV);
		void iniziallizationOfPointer(callBackLinks* CBL, concreteObserverSubjekt* cOS);
		
};