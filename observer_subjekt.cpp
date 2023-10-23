#include "PrecompiledHeadersEdges.h"
#include "observer_subjekt.h"

//********************************************************************
//Methods of concrete implementations of the observer subjects. 
//The method "toRegister" is charged by a method of the "PrintPattern" classes, which contains the coordinates of the lanes. 
//This way the ObserverSubject implementation is told where the lanes are located.
void concreteObserverSubject::toRegister(observer* obserPTR){
	m_observerPTRvector.push_back(obserPTR);
}
//The method "toRemove" is used to delete all coordinates of the lanes of the traffic simulator.
void concreteObserverSubject::toRemove(){
	m_observerPTRvector.clear();
}
//The method "toNotify" is called with the coordinates of mouse clicks. 
//By calling this method, it is checked whether the coordinates of the mouse clicks match the coordinates of the lanes.
void concreteObserverSubject::toNotify(const int& param1, const int& param2){
	for (auto& i : m_observerPTRvector) {
		i->notify(param1, param2);
	}
}