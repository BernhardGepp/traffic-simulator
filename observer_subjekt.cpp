#include "PrecompiledHeadersEdges.h"
#include "observer_subjekt.h"

void concreteObserverSubject::toRegister(observer* obserPTR){
	m_observerPTRvector.push_back(obserPTR);
}
void concreteObserverSubject::toRemove(){
	m_observerPTRvector.clear();
}
void concreteObserverSubject::toNotify(const int& param1, const int& param2){
	for (auto& i : m_observerPTRvector) {
		i->notify(param1, param2);
	}
}