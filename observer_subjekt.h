#pragma once
#include "observer.h"
class observerSubject {
private:
public:
	std::vector<observer*>m_observerPTRvector;
	virtual void toRegister(observer* obserPTR) = 0;
	virtual void toRemove() = 0;
	virtual void toNotify(const int& param1, const int& param2) = 0;
};

class concreteObserverSubject :public observerSubject {
public:
	void toRegister(observer* obserPTR) override;
	void toRemove() override;
	void toNotify(const int& param1, const int& param2) override;
};
