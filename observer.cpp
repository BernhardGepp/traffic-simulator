#include "PrecompiledHeadersEdges.h"
#include "observer.h"

concreteObserver1LaneHoriNeg::concreteObserver1LaneHoriNeg(const int& startValue, const int& endValue, const int& hightOrWidth) :observer() {
	m_startValue = startValue;
	m_endValue = endValue;
	m_hightOrWidth = hightOrWidth;
}
concreteObserver1LaneHoriNeg::~concreteObserver1LaneHoriNeg()noexcept {}
void concreteObserver1LaneHoriNeg::notify(const int& param1, const int& param2){
	if ((m_hightOrWidth == param2) && (m_startValue > param1) && (param1 >= m_endValue)) {
		m_position.first = param1 - m_endValue;
		m_position.second = 1;
	}
}

concreteObserver1LaneHoriPos::concreteObserver1LaneHoriPos(const int& startValue, const int& endValue, const int& hightOrWidth) :observer() {
	m_startValue = startValue;
	m_endValue = endValue;
	m_hightOrWidth = hightOrWidth;
}
concreteObserver1LaneHoriPos::~concreteObserver1LaneHoriPos()noexcept {}
void concreteObserver1LaneHoriPos::notify(const int& param1, const int& param2){
	if ((m_hightOrWidth == param2) && (m_startValue < param1) && (param1 <= m_endValue)) {
		m_position.first = param1 - m_startValue;
		m_position.second = 1;
	}
}

concreteObserver1LaneVertiNeg::concreteObserver1LaneVertiNeg(const int& startValue, const int& endValue, const int& hightOrWidth) :observer() {
	m_startValue = startValue;
	m_endValue = endValue;
	m_hightOrWidth = hightOrWidth;
}
concreteObserver1LaneVertiNeg::~concreteObserver1LaneVertiNeg() noexcept {}
void concreteObserver1LaneVertiNeg::notify(const int& param1, const int& param2){
	if ((m_hightOrWidth == param1) && (m_startValue > param2) && (param2 >= m_endValue)) {
		m_position.first = param2 - m_endValue;
		m_position.second = 1;
	}
}

concreteObserver1LaneVertiPos::concreteObserver1LaneVertiPos(const int& startValue, const int& endValue, const int& hightOrWidth) :observer() {
	m_startValue = startValue;
	m_endValue = endValue;
	m_hightOrWidth = hightOrWidth;
}
concreteObserver1LaneVertiPos::~concreteObserver1LaneVertiPos() noexcept {}
void concreteObserver1LaneVertiPos::notify(const int& param1, const int& param2){
	if ((m_hightOrWidth == param1) && (m_startValue < param2) && (param2 <= m_endValue)) {
		m_position.first = param2 - m_startValue + 10;
		m_position.second = 1;
	}
}

concreteObserver2LaneHoriNeg::concreteObserver2LaneHoriNeg(const int& startValue, const int& endValue, const int& hightOrWidth) :observer() {
	m_startValue = startValue;
	m_endValue = endValue;
	m_hightOrWidth = hightOrWidth;
}
concreteObserver2LaneHoriNeg::~concreteObserver2LaneHoriNeg() noexcept {}
void concreteObserver2LaneHoriNeg::notify(const int& param1, const int& param2){
	if ((m_hightOrWidth == param2) && (m_startValue > param1) && (param1 >= m_endValue)) {
		m_position.first = param1 - m_endValue;
		m_position.second = 1;
	}
	if (((m_hightOrWidth + 10) == param2) && (m_startValue > param1) && (param1 >= m_endValue)) {
		m_position.first = param1 - m_endValue;
		m_position.second = 2;
	}
}

concreteObserver2LaneHoriPos::concreteObserver2LaneHoriPos(const int& startValue, const int& endValue, const int& hightOrWidth) :observer() {
	m_startValue = startValue;
	m_endValue = endValue;
	m_hightOrWidth = hightOrWidth;
}
concreteObserver2LaneHoriPos::~concreteObserver2LaneHoriPos() noexcept {}
void concreteObserver2LaneHoriPos::notify(const int& param1, const int& param2){
	if ((m_hightOrWidth == param2) && (m_startValue < param1) && (param1 <= m_endValue)) {
		m_position.first = param1 - m_startValue;
		m_position.second = 2;
	}
	if (((m_hightOrWidth + 10) == param2) && (m_startValue < param1) && (param1 <= m_endValue)) {
		m_position.first = param1 - m_startValue;
		m_position.second = 1;
	}
}

concreteObserver2LaneVertiNeg::concreteObserver2LaneVertiNeg(const int& startValue, const int& endValue, const int& hightOrWidth) :observer() {
	m_startValue = startValue;
	m_endValue = endValue;
	m_hightOrWidth = hightOrWidth;
}
concreteObserver2LaneVertiNeg::~concreteObserver2LaneVertiNeg() {	}
void concreteObserver2LaneVertiNeg::notify(const int& param1, const int& param2){
	if (((m_hightOrWidth + 10) == param1) && (m_startValue > param2) && (param2 >= m_endValue)) {
		m_position.first = param2 - m_endValue;
		m_position.second = 1;
	}
	if ((m_hightOrWidth == param1) && (m_startValue > param2) && (param2 >= m_endValue)) {
		m_position.first = param2 - m_endValue;
		m_position.second = 2;
	}
}

concreteObserver2LaneVertiPos::concreteObserver2LaneVertiPos(const int& startValue, const int& endValue, const int& hightOrWidth) :observer() {
	m_startValue = startValue;
	m_endValue = endValue;
	m_hightOrWidth = hightOrWidth;
}
concreteObserver2LaneVertiPos::~concreteObserver2LaneVertiPos() noexcept {	}
void concreteObserver2LaneVertiPos::notify(const int& param1, const int& param2){
	if ((m_hightOrWidth == param1) && (m_startValue < param2) && (param2 <= m_endValue)) {
		m_position.first = param2 - m_startValue + 10;
		m_position.second = 1;
	}
	if (((m_hightOrWidth + 10) == param1) && (m_startValue < param2) && (param2 <= m_endValue)) {
		m_position.first = param2 - m_startValue + 10;
		m_position.second = 2;
	}
}