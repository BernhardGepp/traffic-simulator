#pragma once
#include "PrecompiledHeadersEdges.h"
#include "observer.h"
class observerSubjekt {
private:
public:
	std::vector<observer*>m_observerPTRvector;
	virtual void registrieren(observer* obserPTR) = 0;
	virtual void entfernen() {
	}
	virtual void benachrichtigen(const int& param1, const int& param2) = 0;
	
};

class concreteObserverSubjekt :public observerSubjekt {
public:
	void registrieren(observer* obserPTR) override;
	void entfernen() override;
	void benachrichtigen(const int& param1, const int& param2) override;
};
