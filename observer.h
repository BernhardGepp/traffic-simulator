#pragma once
#include "PrecompiledHeadersEdges.h"
class observer {
public:
	int m_startValue = 0;
	int m_endValue = 0;
	int m_hightOrWidth = 0;
	virtual void notify(const int& param1, const int& param2) = 0;
	std::pair<int,int> m_position = std::make_pair(0,0);
	observer::observer() = default;
	observer::observer(const observer& other) = delete;
	observer& operator= (const observer& other) = delete;
	observer::observer(observer&& other) = default;
	observer& operator= (observer&& other) = default;
	observer::~observer()noexcept {}
};

class concreteObserver1LaneHoriNeg : public observer {
public:
	explicit concreteObserver1LaneHoriNeg(const int& startValue, const int& endValue, const int& hightOrWidth);
	concreteObserver1LaneHoriNeg::concreteObserver1LaneHoriNeg(const concreteObserver1LaneHoriNeg& other) = delete;
	concreteObserver1LaneHoriNeg::concreteObserver1LaneHoriNeg(concreteObserver1LaneHoriNeg&& other) = default;
	concreteObserver1LaneHoriNeg& operator= (const concreteObserver1LaneHoriNeg& other) = delete;
	concreteObserver1LaneHoriNeg& operator= (concreteObserver1LaneHoriNeg&& other) = default;
	~concreteObserver1LaneHoriNeg()noexcept;

	void notify(const int& param1, const int& param2) override;
};

class concreteObserver1LaneHoriPos : public observer {
public:
	explicit concreteObserver1LaneHoriPos(const int& startValue, const int& endValue, const int& hightOrWidth);
	concreteObserver1LaneHoriPos::concreteObserver1LaneHoriPos(const concreteObserver1LaneHoriPos& other) = delete;
	concreteObserver1LaneHoriPos::concreteObserver1LaneHoriPos(concreteObserver1LaneHoriPos&& other) = default;
	concreteObserver1LaneHoriPos& operator= (const concreteObserver1LaneHoriPos& other) = delete;
	concreteObserver1LaneHoriPos& operator= (concreteObserver1LaneHoriPos&& other) = default;
	~concreteObserver1LaneHoriPos()noexcept;

	void notify(const int& param1, const int& param2) override;
};

class concreteObserver1LaneVertiNeg : public observer {
public:
	explicit concreteObserver1LaneVertiNeg(const int& startValue, const int& endValue, const int& hightOrWidth);
	concreteObserver1LaneVertiNeg::concreteObserver1LaneVertiNeg(const concreteObserver1LaneVertiNeg& other) = delete;
	concreteObserver1LaneVertiNeg::concreteObserver1LaneVertiNeg(concreteObserver1LaneVertiNeg&& other) = default;
	concreteObserver1LaneVertiNeg& operator=(const concreteObserver1LaneVertiNeg& other) = delete;
	concreteObserver1LaneVertiNeg& operator=(concreteObserver1LaneVertiNeg&& other) = default;
	~concreteObserver1LaneVertiNeg() noexcept;

	void notify(const int& param1, const int& param2) override;
};

class concreteObserver1LaneVertiPos:public observer {
public:
	explicit concreteObserver1LaneVertiPos(const int& startValue, const int& endValue, const int& hightOrWidth);
	concreteObserver1LaneVertiPos::concreteObserver1LaneVertiPos(const concreteObserver1LaneVertiPos& other) = delete;
	concreteObserver1LaneVertiPos::concreteObserver1LaneVertiPos(concreteObserver1LaneVertiPos&& other) = default;
	concreteObserver1LaneVertiPos& operator= (const concreteObserver1LaneVertiPos& other) = delete;
	concreteObserver1LaneVertiPos& operator= (concreteObserver1LaneVertiPos&& other) = default;
	~concreteObserver1LaneVertiPos() noexcept;

	void notify(const int& param1, const int& param2) override;
};

class concreteObserver2LaneHoriNeg :public observer {
public:
	explicit concreteObserver2LaneHoriNeg(const int& startValue, const int& endValue, const int& hightOrWidth);
	concreteObserver2LaneHoriNeg::concreteObserver2LaneHoriNeg(const concreteObserver2LaneHoriNeg& other) = delete;
	concreteObserver2LaneHoriNeg::concreteObserver2LaneHoriNeg(concreteObserver2LaneHoriNeg&& other) = default;
	concreteObserver2LaneHoriNeg& operator= (const concreteObserver2LaneHoriNeg& other) = delete;
	concreteObserver2LaneHoriNeg& operator= (concreteObserver2LaneHoriNeg&& other) = default;
	~concreteObserver2LaneHoriNeg() noexcept;

	void notify(const int& param1, const int& param2) override;
};

class concreteObserver2LaneHoriPos :public observer {
public:
	explicit concreteObserver2LaneHoriPos(const int& startValue, const int& endValue, const int& hightOrWidth);
	concreteObserver2LaneHoriPos::concreteObserver2LaneHoriPos(const concreteObserver2LaneHoriPos& other) = delete;
	concreteObserver2LaneHoriPos::concreteObserver2LaneHoriPos(concreteObserver2LaneHoriPos&& other) = default;
	concreteObserver2LaneHoriPos& operator= (const concreteObserver2LaneHoriPos& other) = delete;
	concreteObserver2LaneHoriPos& operator= (concreteObserver2LaneHoriPos&& other) = default;
	~concreteObserver2LaneHoriPos() noexcept;

	void notify(const int& param1, const int& param2) override;
};

class concreteObserver2LaneVertiNeg :public observer {
public:
	explicit concreteObserver2LaneVertiNeg(const int& startValue, const int& endValue, const int& hightOrWidth);
	concreteObserver2LaneVertiNeg::concreteObserver2LaneVertiNeg(const concreteObserver2LaneVertiNeg& other) = delete;
	concreteObserver2LaneVertiNeg::concreteObserver2LaneVertiNeg(concreteObserver2LaneVertiNeg&& other) = default;
	concreteObserver2LaneVertiNeg& operator= (const concreteObserver2LaneVertiNeg& other) = delete;
	concreteObserver2LaneVertiNeg& operator= (concreteObserver2LaneVertiNeg&& other) = default;
	~concreteObserver2LaneVertiNeg()noexcept;

	void notify(const int& param1, const int& param2) override;
};

class concreteObserver2LaneVertiPos :public observer {
public:
	explicit concreteObserver2LaneVertiPos(const int& startValue, const int& endValue, const int& hightOrWidth);
	concreteObserver2LaneVertiPos::concreteObserver2LaneVertiPos(const concreteObserver2LaneVertiPos& other) = delete;
	concreteObserver2LaneVertiPos::concreteObserver2LaneVertiPos(concreteObserver2LaneVertiPos&& other) = default;
	concreteObserver2LaneVertiPos& operator= (const concreteObserver2LaneVertiPos& other) = delete;
	concreteObserver2LaneVertiPos& operator= (concreteObserver2LaneVertiPos&& other) = default;
	~concreteObserver2LaneVertiPos() noexcept;

	void notify(const int& param1, const int& param2) override;
};