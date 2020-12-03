#pragma once
#include "PrecompiledHeadersEdges.h"
class observer {
public:
	int m_startValue = 0;
	int m_endValue = 0;
	int m_hightOrWidth = 0;
	virtual void notify(const int& param1, const int& param2) = 0;
	std::pair<int,int> m_position = std::make_pair(0,0);
	observer::observer() {

	}
	explicit observer::observer(observer& other) = delete;
	observer& operator= (observer& other) = delete;
	explicit observer::observer(observer&& other) = default;
	observer& operator= (observer&& other) = default;
};

class concreteObserver1LaneHoriNeg : public observer {
public:
	explicit concreteObserver1LaneHoriNeg::concreteObserver1LaneHoriNeg(const int& startValue, const int& endValue, const int& hightOrWidth) {
		m_startValue = startValue;
		m_endValue = endValue;
		m_hightOrWidth = hightOrWidth;
	}
	explicit concreteObserver1LaneHoriNeg::concreteObserver1LaneHoriNeg(concreteObserver1LaneHoriNeg& other) = delete;
	explicit concreteObserver1LaneHoriNeg::concreteObserver1LaneHoriNeg(concreteObserver1LaneHoriNeg&& other) = default;
	concreteObserver1LaneHoriNeg& operator= (concreteObserver1LaneHoriNeg& other) = delete;
	concreteObserver1LaneHoriNeg& operator= (concreteObserver1LaneHoriNeg&& other) = default;
	void notify(const int& param1, const int& param2) override {
		if ((m_hightOrWidth == param2) && (m_startValue>param1) && (param1 >= m_endValue)) {
			m_position.first = param1-m_endValue;
			m_position.second = 1;
		}
	}
};
class concreteObserver1LaneHoriPos : public observer {
public:
	explicit concreteObserver1LaneHoriPos::concreteObserver1LaneHoriPos(const int& startValue, const int& endValue, const int& hightOrWidth) {
		m_startValue = startValue;
		m_endValue = endValue;
		m_hightOrWidth = hightOrWidth;
	}
	explicit concreteObserver1LaneHoriPos::concreteObserver1LaneHoriPos(concreteObserver1LaneHoriPos& other) = delete;
	explicit concreteObserver1LaneHoriPos::concreteObserver1LaneHoriPos(concreteObserver1LaneHoriPos&& other) = default;
	concreteObserver1LaneHoriPos& operator= (concreteObserver1LaneHoriPos& other) = delete;
	concreteObserver1LaneHoriPos& operator= (concreteObserver1LaneHoriPos&& other) = default;
	void notify(const int& param1, const int& param2) override {
		if ((m_hightOrWidth == param2) && (m_startValue<param1) && (param1 <= m_endValue)) {
			m_position.first = param1- m_startValue;
			m_position.second = 1;
		}
	}
};
class concreteObserver1LaneVertiNeg : public observer {
public:
	explicit concreteObserver1LaneVertiNeg::concreteObserver1LaneVertiNeg(const int& startValue, const int& endValue, const int& hightOrWidth) {
		m_startValue = startValue;
		m_endValue = endValue;
		m_hightOrWidth = hightOrWidth;
	}
	explicit concreteObserver1LaneVertiNeg::concreteObserver1LaneVertiNeg(concreteObserver1LaneVertiNeg& other) = delete;
	explicit concreteObserver1LaneVertiNeg::concreteObserver1LaneVertiNeg(concreteObserver1LaneVertiNeg&& other) = default;
	concreteObserver1LaneVertiNeg& operator= (concreteObserver1LaneVertiNeg& other) = delete;
	concreteObserver1LaneVertiNeg& operator= (concreteObserver1LaneVertiNeg&& other) = default;
	void notify(const int& param1, const int& param2) override {
		if ((m_hightOrWidth == param1) && (m_startValue>param2) && (param2 >= m_endValue)) {
			m_position.first = param2-m_endValue;
			m_position.second = 1;
		}
	}
};
class concreteObserver1LaneVertiPos:public observer {
public:
	explicit concreteObserver1LaneVertiPos::concreteObserver1LaneVertiPos(const int& startValue, const int& endValue, const int& hightOrWidth){
		m_startValue = startValue;
		m_endValue = endValue;
		m_hightOrWidth = hightOrWidth;
	}
	explicit concreteObserver1LaneVertiPos::concreteObserver1LaneVertiPos(concreteObserver1LaneVertiPos& other) = delete;
	explicit concreteObserver1LaneVertiPos::concreteObserver1LaneVertiPos(concreteObserver1LaneVertiPos&& other) = default;
	concreteObserver1LaneVertiPos& operator= (concreteObserver1LaneVertiPos& other) = delete;
	concreteObserver1LaneVertiPos& operator= (concreteObserver1LaneVertiPos&& other) = default;
	void notify(const int& param1, const int& param2) override {
		if ((m_hightOrWidth == param1) && (m_startValue<param2) && (param2 <= m_endValue)) {
			m_position.first = param2-m_startValue+10;
			m_position.second = 1;
		}
	}
};
class concreteObserver2LaneHoriNeg :public observer {
public:
	explicit concreteObserver2LaneHoriNeg::concreteObserver2LaneHoriNeg(const int& startValue, const int& endValue,const int& hightOrWidth) {
		m_startValue = startValue;
		m_endValue = endValue;
		m_hightOrWidth = hightOrWidth;
	}
	explicit concreteObserver2LaneHoriNeg::concreteObserver2LaneHoriNeg(concreteObserver2LaneHoriNeg& other) = delete;
	explicit concreteObserver2LaneHoriNeg::concreteObserver2LaneHoriNeg(concreteObserver2LaneHoriNeg&& other) = default;
	concreteObserver2LaneHoriNeg& operator= (concreteObserver2LaneHoriNeg& other) = delete;
	concreteObserver2LaneHoriNeg& operator= (concreteObserver2LaneHoriNeg&& other) = default;
	void notify(const int& param1, const int& param2) override {
		if ((m_hightOrWidth == param2) && (m_startValue>param1) && (param1 >= m_endValue)) {
			m_position.first = param1 - m_endValue;
			m_position.second = 1;
		}
		if (((m_hightOrWidth+10) == param2) && (m_startValue>param1) && (param1 >= m_endValue)) {
			m_position.first = param1 - m_endValue;
			m_position.second = 2;
		}
	}
};
class concreteObserver2LaneHoriPos :public observer {
public:
	explicit concreteObserver2LaneHoriPos::concreteObserver2LaneHoriPos(const int& startValue, const int& endValue, const int& hightOrWidth){
		m_startValue = startValue;
		m_endValue = endValue;
		m_hightOrWidth = hightOrWidth;
	}
	explicit concreteObserver2LaneHoriPos::concreteObserver2LaneHoriPos(concreteObserver2LaneHoriPos& other) = delete;
	explicit concreteObserver2LaneHoriPos::concreteObserver2LaneHoriPos(concreteObserver2LaneHoriPos&& other) = default;
	concreteObserver2LaneHoriPos& operator= (concreteObserver2LaneHoriPos& other) = delete;
	concreteObserver2LaneHoriPos& operator= (concreteObserver2LaneHoriPos&& other) = default;
	void notify(const int& param1, const int& param2) override {
		if ((m_hightOrWidth == param2) && (m_startValue<param1) && (param1 <= m_endValue)) {
			m_position.first = param1 - m_startValue;
			m_position.second = 2;
		}
		if (((m_hightOrWidth+10) == param2) && (m_startValue<param1) && (param1 <= m_endValue)) {
			m_position.first = param1 - m_startValue;
			m_position.second = 1;
		}
	}
};
class concreteObserver2LaneVertiNeg :public observer {
public:
	explicit concreteObserver2LaneVertiNeg::concreteObserver2LaneVertiNeg(const int& startValue, const int& endValue, const int& hightOrWidth)  {
		m_startValue = startValue;
		m_endValue = endValue;
		m_hightOrWidth = hightOrWidth;
	}
	explicit concreteObserver2LaneVertiNeg::concreteObserver2LaneVertiNeg(concreteObserver2LaneVertiNeg& other) = delete;
	explicit concreteObserver2LaneVertiNeg::concreteObserver2LaneVertiNeg(concreteObserver2LaneVertiNeg&& other) = default;
	concreteObserver2LaneVertiNeg& operator= (concreteObserver2LaneVertiNeg& other) = delete;
	concreteObserver2LaneVertiNeg& operator= (concreteObserver2LaneVertiNeg&& other) = default;
	void notify(const int& param1, const int& param2) override {
		if (((m_hightOrWidth+10) == param1) && (m_startValue>param2) && (param2 >= m_endValue)) {
			m_position.first = param2 - m_endValue;
			m_position.second = 1;
		}
		if ((m_hightOrWidth == param1 ) && (m_startValue>param2) && (param2 >= m_endValue)) {
			m_position.first = param2 - m_endValue;
			m_position.second = 2;
		}
	}
};
class concreteObserver2LaneVertiPos :public observer {
public:
	explicit concreteObserver2LaneVertiPos::concreteObserver2LaneVertiPos(const int& startValue, const int& endValue, const int& hightOrWidth) {
		m_startValue = startValue;
		m_endValue = endValue;
		m_hightOrWidth = hightOrWidth;
	}
	explicit concreteObserver2LaneVertiPos::concreteObserver2LaneVertiPos(concreteObserver2LaneVertiPos& other) = delete;
	explicit concreteObserver2LaneVertiPos::concreteObserver2LaneVertiPos(concreteObserver2LaneVertiPos&& other) = default;
	concreteObserver2LaneVertiPos& operator= (concreteObserver2LaneVertiPos& other) = delete;
	concreteObserver2LaneVertiPos& operator= (concreteObserver2LaneVertiPos&& other) = default;
	void notify(const int& param1, const int& param2) override {
		if ((m_hightOrWidth == param1) && (m_startValue<param2) && (param2 <= m_endValue)) {
			m_position.first = param2 - m_startValue + 10;
			m_position.second = 1;
		}
		if (((m_hightOrWidth+10) == param1) && (m_startValue<param2) && (param2 <= m_endValue)) {
			m_position.first = param2 - m_startValue + 10;
			m_position.second = 2;
		}
	}
};