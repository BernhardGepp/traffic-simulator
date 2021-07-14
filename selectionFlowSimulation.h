#pragma once
#include "PrecompiledHeadersEdges.h"
#include "flowSimulation1PosStraight.h"
#include "flowSimulation2PosStraight.h"
#include "flowSimulation1NegStraight.h"
#include "flowSimulation2NegStraight.h"
#include "callBackLinks.h"
#include "observer.h"


class selectionFlowSimulation;
class PrintPatternLine1LaneHoriNeg;
class PrintPatternLine1LaneHoriPos;
class PrintPatternLine1LaneVertiNeg;
class PrintPatternLine1LaneVertiPos;
class PrintPatternLine2LaneHoriNeg;
class PrintPatternLine2LaneHoriPos;
class PrintPatternLine2LaneVertiNeg;
class PrintPatternLine2LaneVertiPos;
class sectionVisitor {

public:
	virtual void setStrategy(PrintPatternLine1LaneHoriNeg& ppt) = 0;
	virtual void setStrategy(PrintPatternLine1LaneHoriPos& ppt) = 0;
	virtual void setStrategy(PrintPatternLine1LaneVertiNeg& ppt) = 0;
	virtual void setStrategy(PrintPatternLine1LaneVertiPos& ppt) = 0;
	virtual void setStrategy(PrintPatternLine2LaneHoriNeg& ppt) = 0;
	virtual void setStrategy(PrintPatternLine2LaneHoriPos& ppt) = 0;
	virtual void setStrategy(PrintPatternLine2LaneVertiNeg& ppt) = 0;
	virtual void setStrategy(PrintPatternLine2LaneVertiPos& ppt) = 0;
};

class selectionFlowSimulation:public sectionVisitor {
private:
	int m_p1x = 0;
	int m_p1y = 0;
	int m_p2x = 0;
	int m_p2y = 0;
	int m_maxVelocity = 0;
	int m_maxVelocity_Density = 0;
	
public:
	HDC m_hdc;
	int(*m_callback_getRandomNumber)() = nullptr;
	void(*m_f6PrintLaneInNumbers)(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV) = nullptr;
	selectionFlowSimulation::selectionFlowSimulation() {
		
	}
	
	std::unique_ptr<sectionVehicleSet> vehicleSetPtr;
	void setEndingPoints(const int& p1x, const int& p1y, const int& p2x, const int& p2y, const int& maxVelocity, const int& maxVelocity_Density) {
		m_p1x = p1x;
		m_p1y = p1y;
		m_p2x = p2x;
		m_p2y = p2y;
		m_maxVelocity = maxVelocity;
		m_maxVelocity_Density = maxVelocity_Density;
		
	}
	
	//********************************************
	void selectionFlowSimulation::setStrategy(PrintPatternLine1LaneHoriNeg& ppt) override {
		vehicleSetPtr = std::make_unique<flowSimulation1NegStraight>(m_callback_getRandomNumber, m_f6PrintLaneInNumbers, m_hdc, m_maxVelocity, m_maxVelocity_Density);
	}
	void selectionFlowSimulation::setStrategy(PrintPatternLine1LaneHoriPos& ppt) override {
		vehicleSetPtr = std::make_unique<flowSimulation1PosStraight>(m_callback_getRandomNumber, m_f6PrintLaneInNumbers, m_hdc, m_maxVelocity, m_maxVelocity_Density);
	}
	void selectionFlowSimulation::setStrategy(PrintPatternLine1LaneVertiNeg& ppt) override{
		vehicleSetPtr = std::make_unique<flowSimulation1NegStraight>(m_callback_getRandomNumber, m_f6PrintLaneInNumbers, m_hdc, m_maxVelocity, m_maxVelocity_Density);
	}
	void selectionFlowSimulation::setStrategy(PrintPatternLine1LaneVertiPos& ppt) override{
		vehicleSetPtr = std::make_unique<flowSimulation1PosStraight>(m_callback_getRandomNumber, m_f6PrintLaneInNumbers, m_hdc, m_maxVelocity, m_maxVelocity_Density);
	}
	void selectionFlowSimulation::setStrategy(PrintPatternLine2LaneHoriNeg& ppt) override {
		vehicleSetPtr = std::make_unique<flowSimulation2NegStraight>(m_callback_getRandomNumber, m_f6PrintLaneInNumbers, m_hdc, m_maxVelocity, m_maxVelocity_Density);
	}
	void selectionFlowSimulation::setStrategy(PrintPatternLine2LaneHoriPos& ppt)override {
		vehicleSetPtr = std::make_unique<flowSimulation2PosStraightA>(m_callback_getRandomNumber, m_f6PrintLaneInNumbers, m_hdc, m_maxVelocity, m_maxVelocity_Density);
	}
	void selectionFlowSimulation::setStrategy(PrintPatternLine2LaneVertiNeg& ppt) override {
		vehicleSetPtr = std::make_unique<flowSimulation2NegStraight>(m_callback_getRandomNumber, m_f6PrintLaneInNumbers, m_hdc, m_maxVelocity, m_maxVelocity_Density);
	}
	void selectionFlowSimulation::setStrategy(PrintPatternLine2LaneVertiPos& ppt) override {
		vehicleSetPtr = std::make_unique<flowSimulation2PosStraightA>(m_callback_getRandomNumber, m_f6PrintLaneInNumbers, m_hdc, m_maxVelocity, m_maxVelocity_Density);
	}
	
	
};
class PrintPattern {
public:
	bool m_verticalOrHorizontal = false;
	bool m_risingOrDescention = false;
	HDC m_hdc;
	void(*m_f10PaintBox)(HDC hdc, const int &param1, const int &param2, const int &param3, const int &param4) = nullptr;
	void(*m_f11PaintWhiteLine)(HDC hdc, const int &param1, const int &param2, const int &param3, const int &param4, const int &param5) = nullptr;
	std::unique_ptr<observer> m_observer;
	callBackLinks m_cbl;
	
	PrintPattern::PrintPattern() {

	}
	explicit PrintPattern::PrintPattern(const PrintPattern& other)  {
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_hdc=other.m_hdc;
		m_f10PaintBox = other.m_f10PaintBox;
		m_f11PaintWhiteLine = other.m_f11PaintWhiteLine;
		m_cbl = other.m_cbl;
	}
	explicit PrintPattern::PrintPattern(PrintPattern&& other) = default;
	PrintPattern& operator=(PrintPattern& other) {
		if (&other == this) {
			return *this;
		}
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_hdc = other.m_hdc;
		m_f10PaintBox = other.m_f10PaintBox;
		m_f11PaintWhiteLine = other.m_f11PaintWhiteLine;
		m_cbl = other.m_cbl;
		return *this;
	}
	PrintPattern& operator=(PrintPattern&& other) = default;

	virtual void accept(selectionFlowSimulation& v) = 0;
	virtual void paintBoxPP() = 0;
	virtual void paintWhiteLinePP() = 0;
	virtual observer* createObserver() = 0;
};
class PrintPatternLine1LaneHoriNeg :public PrintPattern {
private:
	
	int m_p1x = 0;
	int m_p2x = 0;
	int m_p12y = 0;
	
public:

	
	explicit PrintPatternLine1LaneHoriNeg::PrintPatternLine1LaneHoriNeg(const int& p1x, const int& p1y, const int& p2x, const int& p2y) 
		: PrintPattern(),m_p1x(p1x),m_p12y(p1y),m_p2x(p2x) {
		m_verticalOrHorizontal = false;
		m_risingOrDescention = false;

	}
	explicit PrintPatternLine1LaneHoriNeg::PrintPatternLine1LaneHoriNeg(PrintPatternLine1LaneHoriNeg& other) : PrintPattern() {
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
	}
	explicit PrintPatternLine1LaneHoriNeg::PrintPatternLine1LaneHoriNeg(PrintPatternLine1LaneHoriNeg&& other) = default;
		
	PrintPatternLine1LaneHoriNeg& operator=(PrintPatternLine1LaneHoriNeg& other) {
		if (&other == this) {
			return *this;
		}
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
		return *this;
	}
	PrintPatternLine1LaneHoriNeg& operator=(PrintPatternLine1LaneHoriNeg&& other) = default;
	
	/*virtual*/ void accept(selectionFlowSimulation& v) override
	{

		v.setStrategy(*this);
	}
	void paintBoxPP() override{
		
		m_cbl.m_f10PaintBox(m_cbl.m_hdc, m_p2x, m_p12y, m_p1x - m_p2x + 10, 10);
	}
	void paintWhiteLinePP() override {
		
		m_cbl.m_f11PaintWhiteLine(m_cbl.m_hdc, m_p1x + 5, m_p12y + 5, m_p2x-10, m_p12y + 5, 6);
	}
	observer* createObserver() override {
		m_observer = std::make_unique<concreteObserver1LaneHoriNeg>(m_p1x,m_p2x,m_p12y);
		return m_observer.get();
	}
};
class PrintPatternLine1LaneHoriPos :public PrintPattern {
private:
	
	int m_p1x = 0;
	int m_p2x = 0;
	int m_p12y = 0;
	
	
public:
	
	explicit PrintPatternLine1LaneHoriPos::PrintPatternLine1LaneHoriPos(const int& p1x, const int& p1y, const int& p2x, const int& p2y)
		: PrintPattern(), m_p1x(p1x), m_p12y(p1y), m_p2x(p2x) {
		m_verticalOrHorizontal = false;
		m_risingOrDescention = true;
	}
	PrintPatternLine1LaneHoriPos::PrintPatternLine1LaneHoriPos(PrintPatternLine1LaneHoriPos& other) : PrintPattern() {
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
	}
	explicit PrintPatternLine1LaneHoriPos::PrintPatternLine1LaneHoriPos(PrintPatternLine1LaneHoriPos&& other)  = default;
		
	PrintPatternLine1LaneHoriPos& operator=(PrintPatternLine1LaneHoriPos& other) {
		if (&other == this) {
			return *this;
		}
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
		return *this;
	}
	PrintPatternLine1LaneHoriPos& operator=(PrintPatternLine1LaneHoriPos&& other) = default;
	
	/*virtual*/ void accept(selectionFlowSimulation& v) override
	{
		v.setStrategy(*this);
	}
	void paintBoxPP() override {
		
		m_cbl.m_f10PaintBox(m_cbl.m_hdc, m_p1x, m_p12y, m_p2x - m_p1x + 10, 10);
	}
	void paintWhiteLinePP() override {
		m_cbl.m_f11PaintWhiteLine(m_cbl.m_hdc, m_p1x -5, m_p12y + 5, m_p2x + 10, m_p12y + 5, 6);
	}
	observer* createObserver() override {
		m_observer = std::make_unique<concreteObserver1LaneHoriPos>(m_p1x,m_p2x,m_p12y);
		return m_observer.get();
	}
};
class PrintPatternLine1LaneVertiNeg :public PrintPattern {
private:
	
	int m_p12x = 0;
	int m_p1y = 0;
	int m_p2y = 0;
	
	
public:
	
	explicit PrintPatternLine1LaneVertiNeg::PrintPatternLine1LaneVertiNeg(const int& p1x, const int& p1y, const int& p2x, const int& p2y)
		: PrintPattern(),m_p12x(p1x),m_p1y(p1y),m_p2y(p2y) {
		m_verticalOrHorizontal = true;
		m_risingOrDescention = false;
	}
	explicit PrintPatternLine1LaneVertiNeg::PrintPatternLine1LaneVertiNeg(PrintPatternLine1LaneVertiNeg& other) : PrintPattern() {
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p12x = other.m_p12x;
		m_p1y = other.m_p1y;
		m_p2y = other.m_p2y;
	}
	explicit PrintPatternLine1LaneVertiNeg::PrintPatternLine1LaneVertiNeg(PrintPatternLine1LaneVertiNeg&& other) = default;
		
	PrintPatternLine1LaneVertiNeg& operator=(PrintPatternLine1LaneVertiNeg& other) {
		if (&other == this) {
			return *this;
		}
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p12x = other.m_p12x;
		m_p1y = other.m_p1y;
		m_p2y = other.m_p2y;
		return *this;
	}
	PrintPatternLine1LaneVertiNeg& operator=(PrintPatternLine1LaneVertiNeg&& other) = default;
	
	/*virtual*/ void accept(selectionFlowSimulation& v) override
	{
		v.setStrategy(*this);
	}
	void paintBoxPP() override {
			
		m_cbl.m_f10PaintBox(m_cbl.m_hdc, m_p12x, m_p2y, 10, m_p1y - m_p2y + 10);
	}
	void paintWhiteLinePP() override {
		m_cbl.m_f11PaintWhiteLine(m_cbl.m_hdc, m_p12x + 5, m_p1y, m_p12x + 5, m_p2y, 6);
	}
	observer* createObserver() override {
		m_observer = std::make_unique<concreteObserver1LaneVertiNeg>(m_p1y,m_p2y,m_p12x);
		return m_observer.get();
	}
};
class PrintPatternLine1LaneVertiPos :public PrintPattern {
private:
	
	int m_p12x = 0;
	int m_p1y = 0;
	int m_p2y = 0;
	
	
public:
	
	explicit PrintPatternLine1LaneVertiPos::PrintPatternLine1LaneVertiPos(const int& p1x, const int& p1y, const int& p2x, const int& p2y)
		: PrintPattern(), m_p12x(p1x), m_p1y(p1y), m_p2y(p2y) {
		m_verticalOrHorizontal = true;
		m_risingOrDescention = true;
	}
	explicit PrintPatternLine1LaneVertiPos::PrintPatternLine1LaneVertiPos(PrintPatternLine1LaneVertiPos& other) : PrintPattern() {
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p12x = other.m_p12x;
		m_p1y = other.m_p1y;
		m_p2y = other.m_p2y;
	}
	explicit PrintPatternLine1LaneVertiPos::PrintPatternLine1LaneVertiPos(PrintPatternLine1LaneVertiPos&& other) = default;
		
	PrintPatternLine1LaneVertiPos& operator=(PrintPatternLine1LaneVertiPos& other) {
		if (&other == this) {
			return *this;
		}
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p12x = other.m_p12x;
		m_p1y = other.m_p1y;
		m_p2y = other.m_p2y;
		return *this;
	}
	PrintPatternLine1LaneVertiPos& operator=(PrintPatternLine1LaneVertiPos&& other) = default;
	
	/*virtual*/ void accept(selectionFlowSimulation& v) override
	{
		v.setStrategy(*this);
	}
	void paintBoxPP() override {
		
		m_cbl.m_f10PaintBox(m_cbl.m_hdc, m_p12x, m_p1y, 10, m_p2y + 10 - m_p1y);
	}
	void paintWhiteLinePP() override {
		m_cbl.m_f11PaintWhiteLine(m_cbl.m_hdc, m_p12x + 5, m_p1y , m_p12x + 5, m_p2y , 6);
	}
	observer* createObserver() override {
		m_observer = std::make_unique<concreteObserver1LaneVertiPos>(m_p1y,m_p2y,m_p12x);
		return m_observer.get();
	}
};
class PrintPatternLine2LaneHoriNeg :public PrintPattern {
private:
	
	int m_p1x = 0;
	int m_p2x = 0;
	int m_p12y = 0;
	
	
public:
	
	explicit PrintPatternLine2LaneHoriNeg::PrintPatternLine2LaneHoriNeg(const int& p1x, const int& p1y, const int& p2x, const int& p2y)
		: PrintPattern(), m_p1x(p1x), m_p12y(p1y), m_p2x(p2x) {
		m_verticalOrHorizontal = false;
		m_risingOrDescention = false;
	}
	explicit PrintPatternLine2LaneHoriNeg::PrintPatternLine2LaneHoriNeg(PrintPatternLine2LaneHoriNeg& other) : PrintPattern() {
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
	}
	explicit PrintPatternLine2LaneHoriNeg::PrintPatternLine2LaneHoriNeg(PrintPatternLine2LaneHoriNeg&& other) = default;
	
	PrintPatternLine2LaneHoriNeg& operator=(PrintPatternLine2LaneHoriNeg& other) {
		if (&other == this) {
			return *this;
		}
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
		return *this;
	}
	PrintPatternLine2LaneHoriNeg& operator=(PrintPatternLine2LaneHoriNeg&& other) = default;
	
	/*virtual*/ void accept(selectionFlowSimulation& v) override
	{
		v.setStrategy(*this);
	}
	void paintBoxPP() override {
		
		m_cbl.m_f10PaintBox(m_cbl.m_hdc, m_p2x, m_p12y, m_p1x - m_p2x + 10, 20);
	}
	void paintWhiteLinePP() override {
		m_cbl.m_f11PaintWhiteLine(m_cbl.m_hdc, m_p1x + 10, m_p12y + 12, m_p2x - 35, m_p12y + 12, 17);
	}
	observer* createObserver() override {
		m_observer = std::make_unique<concreteObserver2LaneHoriNeg>(m_p1x,m_p2x,m_p12y);
		return m_observer.get();
	}
};
class PrintPatternLine2LaneHoriPos : public PrintPattern {
private:
	
	int m_p1x = 0;
	int m_p2x = 0;
	int m_p12y = 0;
	
	
public:
	
	explicit PrintPatternLine2LaneHoriPos::PrintPatternLine2LaneHoriPos(const int& p1x, const int& p1y, const int& p2x, const int& p2y)
		: PrintPattern(), m_p1x(p1x), m_p12y(p1y), m_p2x(p2x) {
		m_verticalOrHorizontal = false;
		m_risingOrDescention = true;
	}
	explicit PrintPatternLine2LaneHoriPos::PrintPatternLine2LaneHoriPos(PrintPatternLine2LaneHoriPos& other) : PrintPattern() {
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
	}
	explicit PrintPatternLine2LaneHoriPos::PrintPatternLine2LaneHoriPos(PrintPatternLine2LaneHoriPos&& other) = default;
		
	PrintPatternLine2LaneHoriPos& operator=(PrintPatternLine2LaneHoriPos& other) {
		if (&other == this) {
			return *this;
		}
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
		return *this;
	}
	PrintPatternLine2LaneHoriPos& operator=(PrintPatternLine2LaneHoriPos&& other) = default;
	
	/*virtual*/ void accept(selectionFlowSimulation& v) override
	{
		v.setStrategy(*this);
	}
	void paintBoxPP() override {
		
		m_cbl.m_f10PaintBox(m_cbl.m_hdc, m_p1x, m_p12y, m_p2x - m_p1x + 10, 20);
	}
	void paintWhiteLinePP() override {
		m_cbl.m_f11PaintWhiteLine(m_cbl.m_hdc, m_p1x - 5, m_p12y + 10, m_p2x + 10, m_p12y + 10, 16);
	}
	observer* createObserver() override {
		m_observer = std::make_unique<concreteObserver2LaneHoriPos>(m_p1x,m_p2x,m_p12y);
		return m_observer.get();
	}
};
class PrintPatternLine2LaneVertiNeg :public PrintPattern {
private:
	
	int m_p12x = 0;
	int m_p1y = 0;
	int m_p2y = 0;
	
	
public:
	
	explicit PrintPatternLine2LaneVertiNeg::PrintPatternLine2LaneVertiNeg(const int& p1x, const int& p1y, const int& p2x, const int& p2y) 
		: PrintPattern(), m_p12x(p1x), m_p1y(p1y), m_p2y(p2y) {
		m_verticalOrHorizontal = true;
		m_risingOrDescention = false;
	}
	explicit PrintPatternLine2LaneVertiNeg::PrintPatternLine2LaneVertiNeg(PrintPatternLine2LaneVertiNeg& other) : PrintPattern() {
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1y = other.m_p1y;
		m_p12x = other.m_p12x;
		m_p2y = other.m_p2y;
	}
	explicit PrintPatternLine2LaneVertiNeg::PrintPatternLine2LaneVertiNeg(PrintPatternLine2LaneVertiNeg&& other) = default;
	
	PrintPatternLine2LaneVertiNeg& operator=(PrintPatternLine2LaneVertiNeg& other) {
		if (&other == this) {
			return *this;
		}
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1y = other.m_p1y;
		m_p12x = other.m_p12x;
		m_p2y = other.m_p2y;
		return *this;
	}
	PrintPatternLine2LaneVertiNeg& operator=(PrintPatternLine2LaneVertiNeg&& other) = default;
	
	/*virtual*/ void accept(selectionFlowSimulation& v) override
	{
		v.setStrategy(*this);
	}
	void paintBoxPP() override {
		
		m_cbl.m_f10PaintBox(m_cbl.m_hdc, m_p12x, m_p2y, 20, m_p1y - m_p2y + 10);
	}
	void paintWhiteLinePP() override {
		m_cbl.m_f11PaintWhiteLine(m_cbl.m_hdc, m_p12x + 8, m_p1y, m_p12x + 8, m_p2y-35, 16);
	}
	observer* createObserver() override {
		m_observer = std::make_unique<concreteObserver2LaneVertiNeg>(m_p1y,m_p2y,m_p12x);
		return m_observer.get();
	}
};
class PrintPatternLine2LaneVertiPos : public PrintPattern {
private:
	
	int m_p12x = 0;
	int m_p1y = 0;
	int m_p2y = 0;
	
	
public:
	
	explicit PrintPatternLine2LaneVertiPos::PrintPatternLine2LaneVertiPos(const int& p1x,const int& p1y,const int& p2x, const int& p2y)
		: PrintPattern(), m_p12x(p1x), m_p1y(p1y), m_p2y(p2y) {
		m_verticalOrHorizontal = true;
		m_risingOrDescention = true;
	}
	explicit PrintPatternLine2LaneVertiPos::PrintPatternLine2LaneVertiPos(PrintPatternLine2LaneVertiPos& other) : PrintPattern() {
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1y = other.m_p1y;
		m_p12x = other.m_p12x;
		m_p2y = other.m_p2y;
	}
	explicit PrintPatternLine2LaneVertiPos::PrintPatternLine2LaneVertiPos(PrintPatternLine2LaneVertiPos&& other) = default;
		
	PrintPatternLine2LaneVertiPos& operator=(PrintPatternLine2LaneVertiPos& other) {
		if (&other == this) {
			return *this;
		}
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1y = other.m_p1y;
		m_p12x = other.m_p12x;
		m_p2y = other.m_p2y;
		return *this;
	}
	PrintPatternLine2LaneVertiPos& operator=(PrintPatternLine2LaneVertiPos&& other) = default;
	/*virtual*/ void accept(selectionFlowSimulation& v) override
	{
		v.setStrategy(*this);
	}
	void paintBoxPP() override {
		
		m_cbl.m_f10PaintBox(m_cbl.m_hdc, m_p12x, m_p1y, 20, m_p2y - m_p1y + 10);
	}
	void paintWhiteLinePP() override {
		m_cbl.m_f11PaintWhiteLine(m_cbl.m_hdc, m_p12x + 10, m_p1y, m_p12x + 10, m_p2y, 16);
	}
	observer* createObserver() override {
		m_observer = std::make_unique<concreteObserver2LaneVertiPos>(m_p1y,m_p2y,m_p12x);
		return m_observer.get();
	}
};