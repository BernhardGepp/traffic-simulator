#include "PrecompiledHeadersEdges.h"
#include "observer_subjekt.h"

void concreteObserverSubjekt::registrieren(observer* obserPTR){
	m_observerPTRvector.push_back(obserPTR);
}
void concreteObserverSubjekt::entfernen(){
	m_observerPTRvector.clear();
}
void concreteObserverSubjekt::benachrichtigen(const int& param1, const int& param2){
	for (auto& i : m_observerPTRvector) {
		i->notify(param1, param2);
	}
}