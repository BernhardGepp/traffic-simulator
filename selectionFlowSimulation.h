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
	callBackLinks* m_CBLptr = nullptr;
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
		vehicleSetPtr = std::make_unique<flowSimulation1NegStraight>(gsl::not_null<callBackLinks*>(m_CBLptr), m_maxVelocity, m_maxVelocity_Density);
	}
	void selectionFlowSimulation::setStrategy(PrintPatternLine1LaneHoriPos& ppt) override {
		vehicleSetPtr = std::make_unique<flowSimulation1PosStraight>(gsl::not_null<callBackLinks*>(m_CBLptr), m_maxVelocity, m_maxVelocity_Density);
	}
	void selectionFlowSimulation::setStrategy(PrintPatternLine1LaneVertiNeg& ppt) override{
		vehicleSetPtr = std::make_unique<flowSimulation1NegStraight>(gsl::not_null<callBackLinks*>(m_CBLptr), m_maxVelocity, m_maxVelocity_Density);
	}
	void selectionFlowSimulation::setStrategy(PrintPatternLine1LaneVertiPos& ppt) override{
		vehicleSetPtr = std::make_unique<flowSimulation1PosStraight>(gsl::not_null<callBackLinks*>(m_CBLptr), m_maxVelocity, m_maxVelocity_Density);
	}
	void selectionFlowSimulation::setStrategy(PrintPatternLine2LaneHoriNeg& ppt) override {
		vehicleSetPtr = std::make_unique<flowSimulation2NegStraight>(gsl::not_null<callBackLinks*>(m_CBLptr), m_maxVelocity, m_maxVelocity_Density);
	}
	void selectionFlowSimulation::setStrategy(PrintPatternLine2LaneHoriPos& ppt)override {
		vehicleSetPtr = std::make_unique<flowSimulation2PosStraightA>(gsl::not_null<callBackLinks*>(m_CBLptr), m_maxVelocity, m_maxVelocity_Density);
	}
	void selectionFlowSimulation::setStrategy(PrintPatternLine2LaneVertiNeg& ppt) override {
		vehicleSetPtr = std::make_unique<flowSimulation2NegStraight>(gsl::not_null<callBackLinks*>(m_CBLptr),  m_maxVelocity, m_maxVelocity_Density);
	}
	void selectionFlowSimulation::setStrategy(PrintPatternLine2LaneVertiPos& ppt) override {
		vehicleSetPtr = std::make_unique<flowSimulation2PosStraightA>(gsl::not_null<callBackLinks*>(m_CBLptr), m_maxVelocity, m_maxVelocity_Density);
	}
};

class PrintPattern {
public:
	bool m_verticalOrHorizontal = false;
	bool m_risingOrDescention = false;
	bool m_startVertexShort = false;
	bool m_endVertexShort = false;
	std::unique_ptr<observer> m_observer;
	callBackLinks* m_CBLptr=nullptr;
	PrintPattern::PrintPattern() {

	}
	PrintPattern::PrintPattern(const PrintPattern& other)  {
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
	}
	PrintPattern::PrintPattern(const PrintPattern&& other) {
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
	}
	PrintPattern& operator=(const PrintPattern& other) {
		if (&other == this) {
			return *this;
		}
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		return *this;
	}
	PrintPattern& operator=(const PrintPattern&& other) {
		if (&other == this) {
			return *this;
		}
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		return *this;
	}

	virtual void accept(selectionFlowSimulation& v) = 0;
	virtual void paintBoxPP() = 0;
	virtual void paintWhiteLinePP() = 0;
	virtual observer* createObserver() = 0;
	virtual void paintStartVertex11() = 0;
	virtual void paintEndVertex11() = 0;
	virtual void setStartVertexShort(const bool& setOrRelease) = 0;
	virtual void setEndVertexShort(const bool& setOrRelease) = 0;
};
class PrintPatternLine1LaneHoriNeg :public PrintPattern {
private:
	
	int m_p1x = 0;
	int m_p2x = 0;
	int m_p12y = 0;
	
public:

	explicit PrintPatternLine1LaneHoriNeg::PrintPatternLine1LaneHoriNeg(const int& p1x, const int& p1y, const int& p2x, const int& p2y, callBackLinks* CBLptr) 
		: PrintPattern(),m_p1x(p1x),m_p12y(p1y),m_p2x(p2x) {
		m_startVertexShort = false;
		m_endVertexShort = false;
		m_verticalOrHorizontal = false;
		m_risingOrDescention = false;
		m_CBLptr = CBLptr;
		
	}
	PrintPatternLine1LaneHoriNeg::PrintPatternLine1LaneHoriNeg(const PrintPatternLine1LaneHoriNeg& other) : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
	}
	PrintPatternLine1LaneHoriNeg::PrintPatternLine1LaneHoriNeg(const PrintPatternLine1LaneHoriNeg&& other) : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
		
	}
	PrintPatternLine1LaneHoriNeg& operator=(const PrintPatternLine1LaneHoriNeg& other) {
		if (&other == this) {
			return *this;
		}
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
		return *this;
	}
	PrintPatternLine1LaneHoriNeg& operator=(const PrintPatternLine1LaneHoriNeg&& other) {
		if (&other == this) {
			return *this;
		}
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
		return *this;
	}

	/*virtual*/ void accept(selectionFlowSimulation& v) override
	{
		
		v.setStrategy(*this);
	}
	void paintBoxPP() override{
		if ((m_startVertexShort == false) && (m_endVertexShort==true)) {
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p2x + 20, m_p12y, m_p1x - m_p2x-20 , 10);
		}
		if((m_startVertexShort == false)&&(m_endVertexShort == false)){
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p2x + 10, m_p12y, m_p1x - m_p2x - 10, 10);
		}
		if ((m_startVertexShort == true) && (m_endVertexShort == false)) {
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p2x + 10, m_p12y, m_p1x - m_p2x - 10, 10);
		}
		if ((m_startVertexShort == true) && (m_endVertexShort == true)) {
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p2x + 10, m_p12y, m_p1x - m_p2x - 10, 10);
		}
	}
	void paintWhiteLinePP() override {
		
		if (m_endVertexShort) {
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p1x , m_p12y + 5, m_p2x + 20, m_p12y + 5, 6);
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p2x, m_p12y + 5, m_p2x - 32, m_p12y + 5, 6);
		}
		else {
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p1x , m_p12y + 5, m_p2x + 10, m_p12y + 5, 6);
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p2x, m_p12y + 5, m_p2x - 35, m_p12y + 5, 6);
		}
	}
	observer* createObserver() override {
		m_observer = std::make_unique<concreteObserver1LaneHoriNeg>(m_p1x,m_p2x,m_p12y);
		return m_observer.get();
	}
	void paintStartVertex11() override {
		
	}
	void paintEndVertex11() override {

	}
	void setStartVertexShort(const bool& setOrRelease) override {
		m_startVertexShort = setOrRelease;
	}
	void setEndVertexShort(const bool& setOrRelease) override {
		m_endVertexShort = setOrRelease;
	}
};
class PrintPatternLine1LaneHoriPos :public PrintPattern {
private:
	
	int m_p1x = 0;
	int m_p2x = 0;
	int m_p12y = 0;
	
public:
	
	explicit PrintPatternLine1LaneHoriPos::PrintPatternLine1LaneHoriPos(const int& p1x, const int& p1y, const int& p2x, const int& p2y, callBackLinks* CBLptr)
		: PrintPattern(), m_p1x(p1x), m_p12y(p1y), m_p2x(p2x) {
		m_startVertexShort = false;
		m_endVertexShort = false;
		m_verticalOrHorizontal = false;
		m_risingOrDescention = true;
		m_CBLptr = CBLptr;
		
	}
	PrintPatternLine1LaneHoriPos::PrintPatternLine1LaneHoriPos(const PrintPatternLine1LaneHoriPos& other) : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
	}
	PrintPatternLine1LaneHoriPos::PrintPatternLine1LaneHoriPos(const PrintPatternLine1LaneHoriPos&& other) : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
	}
	PrintPatternLine1LaneHoriPos& operator=(const PrintPatternLine1LaneHoriPos& other) {
		if (&other == this) {
			return *this;
		}
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
		return *this;
	}
	PrintPatternLine1LaneHoriPos& operator=(const PrintPatternLine1LaneHoriPos&& other) {
		if (&other == this) {
			return *this;
		}
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
		return *this;
	}

	/*virtual*/ void accept(selectionFlowSimulation& v) override
	{
		v.setStrategy(*this);
	}
	void paintBoxPP() override {
		if ((m_startVertexShort == false) && (m_endVertexShort == false))
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p1x+10, m_p12y, m_p2x - m_p1x -10, 10);
		if ((m_startVertexShort == false) && (m_endVertexShort == true))
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p1x + 10, m_p12y, m_p2x - m_p1x-10 , 10);
		if ((m_startVertexShort == true) && (m_endVertexShort == false))
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p1x + 20, m_p12y, m_p2x - m_p1x - 20, 10);
		if ((m_startVertexShort == true) && (m_endVertexShort == true))
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p1x + 20, m_p12y, m_p2x - m_p1x-20, 10);
	}
	void paintWhiteLinePP() override {
		if ((m_startVertexShort == false) && (m_endVertexShort == false)) {
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p1x + 10, m_p12y + 5, m_p2x - 1, m_p12y + 5, 6);
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p2x + 10, m_p12y + 5, m_p2x + 22, m_p12y + 5, 6);
		}
		if ((m_startVertexShort == false) && (m_endVertexShort == true)) {
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p1x + 10, m_p12y + 5, m_p2x - 1, m_p12y + 5, 6);
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p2x + 20, m_p12y + 5, m_p2x + 32, m_p12y + 5, 6);
		}
		if ((m_startVertexShort == true) && (m_endVertexShort == false)) {
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p1x + 20, m_p12y + 5, m_p2x - 1, m_p12y + 5, 6);
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p2x + 10, m_p12y + 5, m_p2x + 22, m_p12y + 5, 6);
		}
		if ((m_startVertexShort == true) && (m_endVertexShort == true)) {
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p1x + 20, m_p12y + 5, m_p2x - 1, m_p12y + 5, 6);
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p2x + 20, m_p12y + 5, m_p2x + 32, m_p12y + 5, 6);
		}
	}
	observer* createObserver() override {
		m_observer = std::make_unique<concreteObserver1LaneHoriPos>(m_p1x,m_p2x,m_p12y);
		return m_observer.get();
	}
	void paintStartVertex11() override {

	}
	void paintEndVertex11() override {

	}
	void setStartVertexShort(const bool& setOrRelease) override {
		m_startVertexShort = setOrRelease;
	}
	void setEndVertexShort(const bool& setOrRelease) override {
		m_endVertexShort = setOrRelease;
	}
};
class PrintPatternLine1LaneVertiNeg :public PrintPattern {
private:
	
	int m_p12x = 0;
	int m_p1y = 0;
	int m_p2y = 0;
	
public:
	
	explicit PrintPatternLine1LaneVertiNeg::PrintPatternLine1LaneVertiNeg(const int& p1x, const int& p1y, const int& p2x, const int& p2y, callBackLinks* CBLptr)
		: PrintPattern(),m_p12x(p1x),m_p1y(p1y),m_p2y(p2y) {
		m_startVertexShort = false;
		m_endVertexShort = false;
		m_verticalOrHorizontal = true;
		m_risingOrDescention = false;
		m_CBLptr = CBLptr;
		
	}
	PrintPatternLine1LaneVertiNeg::PrintPatternLine1LaneVertiNeg(const PrintPatternLine1LaneVertiNeg& other) : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p12x = other.m_p12x;
		m_p1y = other.m_p1y;
		m_p2y = other.m_p2y;
	}
	PrintPatternLine1LaneVertiNeg::PrintPatternLine1LaneVertiNeg(const PrintPatternLine1LaneVertiNeg&& other) : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p12x = other.m_p12x;
		m_p1y = other.m_p1y;
		m_p2y = other.m_p2y;
	}
		
	PrintPatternLine1LaneVertiNeg& operator=(const PrintPatternLine1LaneVertiNeg& other) {
		if (&other == this) {
			return *this;
		}
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p12x = other.m_p12x;
		m_p1y = other.m_p1y;
		m_p2y = other.m_p2y;
		return *this;
	}
	PrintPatternLine1LaneVertiNeg& operator=(const PrintPatternLine1LaneVertiNeg&& other) {
		if (&other == this) {
			return *this;
		}
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p12x = other.m_p12x;
		m_p1y = other.m_p1y;
		m_p2y = other.m_p2y;
		return *this;
	}

	/*virtual*/ void accept(selectionFlowSimulation& v) override
	{
		v.setStrategy(*this);
	}
	void paintBoxPP() override {	
		if((m_startVertexShort == false) && (m_endVertexShort == false)) {
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p2y + 10, 10, m_p1y - m_p2y - 10);
		}
		if ((m_startVertexShort == true) && (m_endVertexShort == false)) {
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p2y + 10, 10, m_p1y - m_p2y - 10);
		}
		if ((m_startVertexShort == false) && (m_endVertexShort == true)) {
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p2y + 20, 10, m_p1y - m_p2y -20);
		}
		if ((m_startVertexShort == true) && (m_endVertexShort == true)) {
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p2y + 10, 10, m_p1y - m_p2y - 10);
		}
	}
	void paintWhiteLinePP() override {
		if(m_endVertexShort){
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 5, m_p1y, m_p12x + 5, m_p2y+20, 6);
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 5, m_p2y, m_p12x + 5, m_p2y-22, 6);
		}
		else {
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 5, m_p1y, m_p12x + 5, m_p2y + 10, 6);
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 5, m_p2y, m_p12x + 5, m_p2y - 22, 6);
		}

	}
	observer* createObserver() override {
		m_observer = std::make_unique<concreteObserver1LaneVertiNeg>(m_p1y,m_p2y,m_p12x);
		return m_observer.get();
	}
	void paintStartVertex11() override {

	}
	void paintEndVertex11() override {

	}
	void setStartVertexShort(const bool& setOrRelease) override {
		m_startVertexShort = setOrRelease;
	}
	void setEndVertexShort(const bool& setOrRelease) override {
		m_endVertexShort = setOrRelease;
	}
};
class PrintPatternLine1LaneVertiPos :public PrintPattern {
private:
	
	int m_p12x = 0;
	int m_p1y = 0;
	int m_p2y = 0;
	
public:
	
	explicit PrintPatternLine1LaneVertiPos::PrintPatternLine1LaneVertiPos(const int& p1x, const int& p1y, const int& p2x, const int& p2y, callBackLinks* CBLptr)
		: PrintPattern(), m_p12x(p1x), m_p1y(p1y), m_p2y(p2y) {
		m_startVertexShort = false;
		m_endVertexShort = false;
		m_verticalOrHorizontal = true;
		m_risingOrDescention = true;
		m_CBLptr = CBLptr;
		
	}
	PrintPatternLine1LaneVertiPos::PrintPatternLine1LaneVertiPos(const PrintPatternLine1LaneVertiPos& other) : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p12x = other.m_p12x;
		m_p1y = other.m_p1y;
		m_p2y = other.m_p2y;
	}
	PrintPatternLine1LaneVertiPos::PrintPatternLine1LaneVertiPos(const PrintPatternLine1LaneVertiPos&& other) : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p12x = other.m_p12x;
		m_p1y = other.m_p1y;
		m_p2y = other.m_p2y;
	}
	PrintPatternLine1LaneVertiPos& operator=(const PrintPatternLine1LaneVertiPos& other) {
		if (&other == this) {
			return *this;
		}
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p12x = other.m_p12x;
		m_p1y = other.m_p1y;
		m_p2y = other.m_p2y;
		return *this;
	}
	PrintPatternLine1LaneVertiPos& operator=(const PrintPatternLine1LaneVertiPos&& other) {
		if (&other == this) {
			return *this;
		}
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p12x = other.m_p12x;
		m_p1y = other.m_p1y;
		m_p2y = other.m_p2y;
		return *this;
	}

	/*virtual*/ void accept(selectionFlowSimulation& v) override
	{
		v.setStrategy(*this);
	}
	void paintBoxPP() override {
		if ((m_startVertexShort == false) && (m_endVertexShort == false)) {
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p1y + 10, 10, m_p2y - 10 - m_p1y);
		}
		if ((m_startVertexShort == false) && (m_endVertexShort == true)) {
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p1y + 10, 10, m_p2y -10- m_p1y);
		}
		if ((m_startVertexShort == true) && (m_endVertexShort == false)) {
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p1y + 20, 10, m_p2y - 20 - m_p1y);
		}
		if ((m_startVertexShort == true) && (m_endVertexShort == true)) {
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p1y + 20, 10, m_p2y - 20 - m_p1y);
		}
	}
	void paintWhiteLinePP() override {
		
		if ((m_startVertexShort == false) && (m_endVertexShort == false)) {
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 5, m_p1y + 10, m_p12x + 5, m_p2y - 1, 6);
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 5, m_p2y + 10, m_p12x + 5, m_p2y + 30, 6);
		}
		if ((m_startVertexShort == false) && (m_endVertexShort == true)) {
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 5, m_p1y + 10, m_p12x + 5, m_p2y - 1, 6);
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 5, m_p2y + 20, m_p12x + 5, m_p2y + 40, 6);
		}
		if ((m_startVertexShort == true) && (m_endVertexShort == false)) {
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 5, m_p1y + 20, m_p12x + 5, m_p2y - 1, 6);
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 5, m_p2y + 10, m_p12x + 5, m_p2y + 30, 6);
		}
		if ((m_startVertexShort == true) && (m_endVertexShort == true)) {
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 5, m_p1y + 20, m_p12x + 5, m_p2y - 1, 6);
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 5, m_p2y + 20, m_p12x + 5, m_p2y + 40, 6);
		}
	}
	observer* createObserver() override {
		m_observer = std::make_unique<concreteObserver1LaneVertiPos>(m_p1y,m_p2y,m_p12x);
		return m_observer.get();
	}
	void paintStartVertex11() override {

	}
	void paintEndVertex11() override {

	}
	void setStartVertexShort(const bool& setOrRelease) override {
		m_startVertexShort = setOrRelease;
	}
	void setEndVertexShort(const bool& setOrRelease) override {
		m_endVertexShort = setOrRelease;
	}
};
class PrintPatternLine2LaneHoriNeg :public PrintPattern {
private:
	
	int m_p1x = 0;
	int m_p2x = 0;
	int m_p12y = 0;
	
public:
	
	explicit PrintPatternLine2LaneHoriNeg::PrintPatternLine2LaneHoriNeg(const int& p1x, const int& p1y, const int& p2x, const int& p2y, callBackLinks* CBLptr)
		: PrintPattern(), m_p1x(p1x), m_p12y(p1y), m_p2x(p2x) {
		m_startVertexShort = false;
		m_endVertexShort = false;
		m_verticalOrHorizontal = false;
		m_risingOrDescention = false;
		m_CBLptr = CBLptr;
	}
	PrintPatternLine2LaneHoriNeg::PrintPatternLine2LaneHoriNeg(const PrintPatternLine2LaneHoriNeg& other) : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
	}
	PrintPatternLine2LaneHoriNeg::PrintPatternLine2LaneHoriNeg(const PrintPatternLine2LaneHoriNeg&& other) : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
	}
	PrintPatternLine2LaneHoriNeg& operator=(const PrintPatternLine2LaneHoriNeg& other) {
		if (&other == this) {
			return *this;
		}
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
		return *this;
	}
	PrintPatternLine2LaneHoriNeg& operator=(const PrintPatternLine2LaneHoriNeg&& other) {
		if (&other == this) {
			return *this;
		}
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
		return *this;
	}
	/*virtual*/ void accept(selectionFlowSimulation& v) override
	{
		v.setStrategy(*this);
		
	}
	void paintBoxPP() override {
		if ((m_startVertexShort == false) && (m_endVertexShort == true)) {
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p2x + 20, m_p12y, m_p1x - m_p2x - 20, 20);
		}
		if ((m_startVertexShort == false) && (m_endVertexShort == false)) {
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p2x + 10, m_p12y, m_p1x - m_p2x - 10, 20);
		}
		if ((m_startVertexShort == true) && (m_endVertexShort == false)) {
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p2x + 10, m_p12y, m_p1x - m_p2x - 10, 20);
		}
		if ((m_startVertexShort == true) && (m_endVertexShort == true)) {
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p2x + 10, m_p12y, m_p1x - m_p2x - 10, 20);
		}
	}
	void paintWhiteLinePP() override {
		
		if (m_endVertexShort) {
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p1x-1, m_p12y + 12, m_p2x +20 , m_p12y + 12, 17);
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p2x, m_p12y + 12, m_p2x - 32, m_p12y + 12, 17);
		}
		else {
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p1x-1, m_p12y + 12, m_p2x + 10, m_p12y + 12, 17);
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p2x, m_p12y + 12, m_p2x - 35, m_p12y + 12, 17);
		}
	}
	observer* createObserver() override {
		m_observer = std::make_unique<concreteObserver2LaneHoriNeg>(m_p1x,m_p2x,m_p12y);
		return m_observer.get();
	}
	void paintStartVertex11() override {
		m_CBLptr->topLevelFunctionPTR_f16PaintBoxFlex21(m_p1x, m_p12y);
	}
	void paintEndVertex11() override {
		
		m_CBLptr->topLevelFunctionPTR_f16PaintBoxFlex21(m_p2x, m_p12y);
		
		
	}
	void setStartVertexShort(const bool& setOrRelease) override {
		m_startVertexShort = setOrRelease;
	}
	void setEndVertexShort(const bool& setOrRelease) override {
		m_endVertexShort = setOrRelease;
	}
};
class PrintPatternLine2LaneHoriPos : public PrintPattern {
private:
	
	int m_p1x = 0;
	int m_p2x = 0;
	int m_p12y = 0;
	
public:
	
	explicit PrintPatternLine2LaneHoriPos::PrintPatternLine2LaneHoriPos(const int& p1x, const int& p1y, const int& p2x, const int& p2y, callBackLinks* CBLptr)
		: PrintPattern(), m_p1x(p1x), m_p12y(p1y), m_p2x(p2x) {
		m_startVertexShort = false;
		m_endVertexShort = false;
		m_verticalOrHorizontal = false;
		m_risingOrDescention = true;
		m_CBLptr = CBLptr;
	}
	PrintPatternLine2LaneHoriPos::PrintPatternLine2LaneHoriPos(const PrintPatternLine2LaneHoriPos& other) : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
	}
	PrintPatternLine2LaneHoriPos::PrintPatternLine2LaneHoriPos(const PrintPatternLine2LaneHoriPos&& other) : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
	}
	PrintPatternLine2LaneHoriPos& operator=(const PrintPatternLine2LaneHoriPos& other) {
		if (&other == this) {
			return *this;
		}
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
		return *this;
	}
	PrintPatternLine2LaneHoriPos& operator=(const PrintPatternLine2LaneHoriPos&& other) {
		if (&other == this) {
			return *this;
		}
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
		return *this;
	}
	
	/*virtual*/ void accept(selectionFlowSimulation& v) override
	{
		v.setStrategy(*this);
	}
	void paintBoxPP() override {
		//m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p1x + 10, m_p12y, m_p2x - m_p1x - 10, 20);
		if ((m_startVertexShort == false) && (m_endVertexShort == false))
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p1x + 10, m_p12y, m_p2x - m_p1x - 10, 20);
		if ((m_startVertexShort == false) && (m_endVertexShort == true))
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p1x + 10, m_p12y, m_p2x - m_p1x-10, 20);
		if ((m_startVertexShort == true) && (m_endVertexShort == false))
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p1x + 20, m_p12y, m_p2x - m_p1x - 20, 20);
		if ((m_startVertexShort == true) && (m_endVertexShort == true))
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p1x + 20, m_p12y, m_p2x - m_p1x - 20, 20);
	}
	void paintWhiteLinePP() override {
		if ((m_startVertexShort==false)&&(m_endVertexShort==false)) {
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p1x + 10, m_p12y + 10, m_p2x - 1, m_p12y + 10, 16);
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p2x + 10, m_p12y + 10, m_p2x + 22, m_p12y + 10, 16);
		}
		if ((m_startVertexShort == false) && (m_endVertexShort == true)) {
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p1x + 10, m_p12y + 10, m_p2x - 1, m_p12y + 10, 16);
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p2x + 20, m_p12y + 10, m_p2x + 42, m_p12y + 10, 16);
		}
		if ((m_startVertexShort == true) && (m_endVertexShort == false)) {
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p1x + 20, m_p12y + 10, m_p2x - 1, m_p12y + 10, 16);
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p2x + 10, m_p12y + 10, m_p2x + 22, m_p12y + 10, 16);
		}
		if ((m_startVertexShort == true) && (m_endVertexShort == true)) {
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p1x + 20, m_p12y + 10, m_p2x - 1, m_p12y + 10, 16);
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p2x + 20, m_p12y + 10, m_p2x + 42, m_p12y + 10, 16);
		}
	}
	observer* createObserver() override {
		m_observer = std::make_unique<concreteObserver2LaneHoriPos>(m_p1x,m_p2x,m_p12y);
		return m_observer.get();
	}
	void paintStartVertex11() override {
		m_CBLptr->topLevelFunctionPTR_f16PaintBoxFlex21(m_p1x, m_p12y);
	}
	void paintEndVertex11() override {
		
		m_CBLptr->topLevelFunctionPTR_f16PaintBoxFlex21(m_p2x, m_p12y);
		
	}
	void setStartVertexShort(const bool& setOrRelease) override {
		m_startVertexShort = setOrRelease;
	}
	void setEndVertexShort(const bool& setOrRelease) override {
		m_endVertexShort = setOrRelease;
	}
};
class PrintPatternLine2LaneVertiNeg :public PrintPattern {
private:
	
	int m_p12x = 0;
	int m_p1y = 0;
	int m_p2y = 0;
	
public:
	
	explicit PrintPatternLine2LaneVertiNeg::PrintPatternLine2LaneVertiNeg(const int& p1x, const int& p1y, const int& p2x, const int& p2y, callBackLinks* CBLptr)
		: PrintPattern(), m_p12x(p1x), m_p1y(p1y), m_p2y(p2y) {
		m_startVertexShort = false;
		m_endVertexShort = false;
		m_verticalOrHorizontal = true;
		m_risingOrDescention = false;
		m_CBLptr = CBLptr;
	}
	PrintPatternLine2LaneVertiNeg::PrintPatternLine2LaneVertiNeg(const PrintPatternLine2LaneVertiNeg& other) : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1y = other.m_p1y;
		m_p12x = other.m_p12x;
		m_p2y = other.m_p2y;
	}
	PrintPatternLine2LaneVertiNeg::PrintPatternLine2LaneVertiNeg(const PrintPatternLine2LaneVertiNeg&& other) : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1y = other.m_p1y;
		m_p12x = other.m_p12x;
		m_p2y = other.m_p2y;
	}
	PrintPatternLine2LaneVertiNeg& operator=(const PrintPatternLine2LaneVertiNeg& other) {
		if (&other == this) {
			return *this;
		}
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1y = other.m_p1y;
		m_p12x = other.m_p12x;
		m_p2y = other.m_p2y;
		return *this;
	}
	PrintPatternLine2LaneVertiNeg& operator=(const PrintPatternLine2LaneVertiNeg&& other) {
		if (&other == this) {
			return *this;
		}
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1y = other.m_p1y;
		m_p12x = other.m_p12x;
		m_p2y = other.m_p2y;
		return *this;
	}
	
	/*virtual*/ void accept(selectionFlowSimulation& v) override
	{
		v.setStrategy(*this);
	}
	void paintBoxPP() override {
		if ((m_startVertexShort == false) && (m_endVertexShort == false)) {
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p2y + 10, 20, m_p1y - m_p2y - 10);
		}
		if ((m_startVertexShort == true) && (m_endVertexShort == false)) {
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p2y + 10, 20, m_p1y - m_p2y - 10);
		}
		if ((m_startVertexShort == false) && (m_endVertexShort == true)) {
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p2y + 20, 20, m_p1y - m_p2y - 20);
		}
		if ((m_startVertexShort == true) && (m_endVertexShort == true)) {
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p2y + 10, 20, m_p1y - m_p2y - 10);
		}
	
	}
	void paintWhiteLinePP() override {
		if (m_endVertexShort) {
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 8, m_p1y, m_p12x + 8, m_p2y+20 , 16);
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 8, m_p2y, m_p12x + 8, m_p2y - 32, 16);
		}
		else {
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 8, m_p1y, m_p12x + 8, m_p2y+10, 16);
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 8, m_p2y, m_p12x + 8, m_p2y - 32, 16);
		}
		
	}
	observer* createObserver() override {
		m_observer = std::make_unique<concreteObserver2LaneVertiNeg>(m_p1y,m_p2y,m_p12x);
		return m_observer.get();
	}
	void paintStartVertex11() override {
		m_CBLptr->topLevelFunctionPTR_f15PaintBoxFlex12(m_p12x, m_p1y);
	}
	void paintEndVertex11() override {
		m_CBLptr->topLevelFunctionPTR_f15PaintBoxFlex12(m_p12x, m_p2y);
	}
	void setStartVertexShort(const bool& setOrRelease) override {
		m_startVertexShort = setOrRelease;
	}
	void setEndVertexShort(const bool& setOrRelease) override {
		m_endVertexShort = setOrRelease;
	}
};
class PrintPatternLine2LaneVertiPos : public PrintPattern {
private:
	
	int m_p12x = 0;
	int m_p1y = 0;
	int m_p2y = 0;
	
public:
	
	explicit PrintPatternLine2LaneVertiPos::PrintPatternLine2LaneVertiPos(const int& p1x,const int& p1y,const int& p2x, const int& p2y, callBackLinks* CBLptr)
		: PrintPattern(), m_p12x(p1x), m_p1y(p1y), m_p2y(p2y) {
		m_startVertexShort = false;
		m_endVertexShort = false;
		m_verticalOrHorizontal = true;
		m_risingOrDescention = true;
		m_CBLptr = CBLptr;
	}
	PrintPatternLine2LaneVertiPos::PrintPatternLine2LaneVertiPos(const PrintPatternLine2LaneVertiPos& other) : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1y = other.m_p1y;
		m_p12x = other.m_p12x;
		m_p2y = other.m_p2y;
	}
	PrintPatternLine2LaneVertiPos::PrintPatternLine2LaneVertiPos(const PrintPatternLine2LaneVertiPos&& other) : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1y = other.m_p1y;
		m_p12x = other.m_p12x;
		m_p2y = other.m_p2y;
	}
	PrintPatternLine2LaneVertiPos& operator=(const PrintPatternLine2LaneVertiPos& other) {
		if (&other == this) {
			return *this;
		}
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1y = other.m_p1y;
		m_p12x = other.m_p12x;
		m_p2y = other.m_p2y;
		return *this;
	}
	PrintPatternLine2LaneVertiPos& operator=(const PrintPatternLine2LaneVertiPos&& other) {
		if (&other == this) {
			return *this;
		}
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1y = other.m_p1y;
		m_p12x = other.m_p12x;
		m_p2y = other.m_p2y;
		return *this;
	}

	/*virtual*/ void accept(selectionFlowSimulation& v) override
	{
		v.setStrategy(*this);
	}
	void paintBoxPP() override {
		
		
		if ((m_startVertexShort == false) && (m_endVertexShort == false)) {
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p1y + 10, 20, m_p2y - 10 - m_p1y);
		}
		if ((m_startVertexShort == false) && (m_endVertexShort == true)) {
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p1y + 10, 20, m_p2y - 10 - m_p1y);
		}
		if ((m_startVertexShort == true) && (m_endVertexShort == false)) {
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p1y + 20, 20, m_p2y - 20 - m_p1y);
		}
		if ((m_startVertexShort == true) && (m_endVertexShort == true)) {
			m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p1y + 20, 20, m_p2y - 20 - m_p1y);
		}
	}
	void paintWhiteLinePP() override {
		if ((m_startVertexShort == false) && (m_endVertexShort == false)){
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 10, m_p1y+10, m_p12x + 10, m_p2y - 1, 16);
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 10, m_p2y + 10, m_p12x + 10, m_p2y + 30, 16);
		}
		if ((m_startVertexShort == false) && (m_endVertexShort == true)) {
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 10, m_p1y+10, m_p12x + 10, m_p2y - 1, 16);
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 10, m_p2y + 20, m_p12x + 10, m_p2y + 40, 16);
		}
		if ((m_startVertexShort == true) && (m_endVertexShort == false)) {
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 10, m_p1y + 20, m_p12x + 10, m_p2y - 1, 16);
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 10, m_p2y + 10, m_p12x + 10, m_p2y + 30, 16);
		}
		if ((m_startVertexShort == true) && (m_endVertexShort == true)) {
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 10, m_p1y + 20, m_p12x + 10, m_p2y - 1, 16);
			m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 10, m_p2y + 20, m_p12x + 10, m_p2y + 40, 16);
		}
	}
	observer* createObserver() override {
		m_observer = std::make_unique<concreteObserver2LaneVertiPos>(m_p1y,m_p2y,m_p12x);
		return m_observer.get();
	}
	void paintStartVertex11() override {
		m_CBLptr->topLevelFunctionPTR_f15PaintBoxFlex12(m_p12x, m_p1y);
	}
	void paintEndVertex11() override {
		m_CBLptr->topLevelFunctionPTR_f15PaintBoxFlex12(m_p12x, m_p2y);
	}
	void setStartVertexShort(const bool& setOrRelease) override {
		m_startVertexShort = setOrRelease;
	}
	void setEndVertexShort(const bool& setOrRelease) override {
		m_endVertexShort = setOrRelease;
	}
};