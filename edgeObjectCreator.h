#pragma once
#include "edge.h"

class createEdge {
	public:
		
		concreteObserverSubject* m_cObSptr = nullptr;
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

		createEdge(callBackLinks* CBL, concreteObserverSubject* cOS);
		~createEdge();
		std::unique_ptr <edge>&& create(const std::shared_ptr<vertex>&, const std::shared_ptr<vertex>&, const int&);
		std::unique_ptr<PrintPattern> choosePrintPattern();
		void iniziallizationOfPointer(callBackLinks* CBL, concreteObserverSubject* cOS);
};