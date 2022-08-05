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
	

	void selectionFlowSimulation::setEndingPoints(const int& p1x, const int& p1y, const int& p2x, const int& p2y, const int& maxVelocity, const int& maxVelocity_Density);
	
	//********************************************
	void selectionFlowSimulation::setStrategy(PrintPatternLine1LaneHoriNeg& ppt) override;
	void selectionFlowSimulation::setStrategy(PrintPatternLine1LaneHoriPos& ppt) override;
	void selectionFlowSimulation::setStrategy(PrintPatternLine1LaneVertiNeg& ppt) override;
	void selectionFlowSimulation::setStrategy(PrintPatternLine1LaneVertiPos& ppt) override;
	void selectionFlowSimulation::setStrategy(PrintPatternLine2LaneHoriNeg& ppt) override;
	void selectionFlowSimulation::setStrategy(PrintPatternLine2LaneHoriPos& ppt)override;
	void selectionFlowSimulation::setStrategy(PrintPatternLine2LaneVertiNeg& ppt) override;
	void selectionFlowSimulation::setStrategy(PrintPatternLine2LaneVertiPos& ppt) override;
};

class PrintPattern {
public:
	bool m_verticalOrHorizontal = false;
	bool m_risingOrDescention = false;
	bool m_startVertexShort = false;
	bool m_endVertexShort = false;
	std::unique_ptr<observer> m_observer;
	callBackLinks* m_CBLptr=nullptr;

	PrintPattern()noexcept;
	PrintPattern::PrintPattern(const PrintPattern& other) noexcept {
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
	}
	PrintPattern::PrintPattern(const PrintPattern&& other) noexcept{
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
	}
	PrintPattern& operator=(const PrintPattern& other)noexcept {
		if (&other == this) {
			return *this;
		}
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		return *this;
	}
	PrintPattern& operator=(const PrintPattern&& other) noexcept {
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

	explicit PrintPatternLine1LaneHoriNeg(const int& p1x, const int& p1y, const int& p2x, const int& p2y, callBackLinks* CBLptr) noexcept;

	PrintPatternLine1LaneHoriNeg::PrintPatternLine1LaneHoriNeg(const PrintPatternLine1LaneHoriNeg& other)noexcept : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
	}
	PrintPatternLine1LaneHoriNeg::PrintPatternLine1LaneHoriNeg(const PrintPatternLine1LaneHoriNeg&& other) noexcept : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
		
	}
	PrintPatternLine1LaneHoriNeg& operator=(const PrintPatternLine1LaneHoriNeg& other) noexcept {
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
	PrintPatternLine1LaneHoriNeg& operator=(const PrintPatternLine1LaneHoriNeg&& other) noexcept {
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

	void accept(selectionFlowSimulation& v) override;
	void paintBoxPP() override;
	void paintWhiteLinePP() override;
	observer* createObserver() override;
	void paintStartVertex11() override;
	void paintEndVertex11() override;
	void setStartVertexShort(const bool& setOrRelease) override;
	void setEndVertexShort(const bool& setOrRelease) override;
};
class PrintPatternLine1LaneHoriPos :public PrintPattern {
private:
	
	int m_p1x = 0;
	int m_p2x = 0;
	int m_p12y = 0;
	
public:
	
	explicit PrintPatternLine1LaneHoriPos(const int& p1x, const int& p1y, const int& p2x, const int& p2y, callBackLinks* CBLptr) noexcept;
	PrintPatternLine1LaneHoriPos::PrintPatternLine1LaneHoriPos(const PrintPatternLine1LaneHoriPos& other) noexcept : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
	}
	PrintPatternLine1LaneHoriPos::PrintPatternLine1LaneHoriPos(const PrintPatternLine1LaneHoriPos&& other)noexcept : PrintPattern()  {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
	}
	PrintPatternLine1LaneHoriPos& operator=(const PrintPatternLine1LaneHoriPos& other) noexcept {
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
	PrintPatternLine1LaneHoriPos& operator=(const PrintPatternLine1LaneHoriPos&& other) noexcept {
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

	void accept(selectionFlowSimulation& v) override;
	void paintBoxPP() override;
	void paintWhiteLinePP() override;
	observer* createObserver() override;
	void paintStartVertex11() override;
	void paintEndVertex11() override;
	void setStartVertexShort(const bool& setOrRelease) override;
	void setEndVertexShort(const bool& setOrRelease) override;
};
class PrintPatternLine1LaneVertiNeg :public PrintPattern {
private:
	
	int m_p12x = 0;
	int m_p1y = 0;
	int m_p2y = 0;
	
public:
	
	explicit PrintPatternLine1LaneVertiNeg(const int& p1x, const int& p1y, const int& p2x, const int& p2y, callBackLinks* CBLptr) noexcept;
	PrintPatternLine1LaneVertiNeg::PrintPatternLine1LaneVertiNeg(const PrintPatternLine1LaneVertiNeg& other) noexcept : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p12x = other.m_p12x;
		m_p1y = other.m_p1y;
		m_p2y = other.m_p2y;
	}
	PrintPatternLine1LaneVertiNeg::PrintPatternLine1LaneVertiNeg(const PrintPatternLine1LaneVertiNeg&& other)noexcept : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p12x = other.m_p12x;
		m_p1y = other.m_p1y;
		m_p2y = other.m_p2y;
	}
		
	PrintPatternLine1LaneVertiNeg& operator=(const PrintPatternLine1LaneVertiNeg& other) noexcept {
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
	PrintPatternLine1LaneVertiNeg& operator=(const PrintPatternLine1LaneVertiNeg&& other)noexcept {
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

	void accept(selectionFlowSimulation& v) override;
	void paintBoxPP() override;
	void paintWhiteLinePP() override;
	observer* createObserver() override;
	void paintStartVertex11() override;
	void paintEndVertex11() override;
	void setStartVertexShort(const bool& setOrRelease) override;
	void setEndVertexShort(const bool& setOrRelease) override;
};
class PrintPatternLine1LaneVertiPos :public PrintPattern {
private:
	
	int m_p12x = 0;
	int m_p1y = 0;
	int m_p2y = 0;
	
public:
	
	explicit PrintPatternLine1LaneVertiPos(const int& p1x, const int& p1y, const int& p2x, const int& p2y, callBackLinks* CBLptr)noexcept;
	PrintPatternLine1LaneVertiPos::PrintPatternLine1LaneVertiPos(const PrintPatternLine1LaneVertiPos& other) noexcept : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p12x = other.m_p12x;
		m_p1y = other.m_p1y;
		m_p2y = other.m_p2y;
	}
	PrintPatternLine1LaneVertiPos::PrintPatternLine1LaneVertiPos(const PrintPatternLine1LaneVertiPos&& other)noexcept : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p12x = other.m_p12x;
		m_p1y = other.m_p1y;
		m_p2y = other.m_p2y;
	}
	PrintPatternLine1LaneVertiPos& operator=(const PrintPatternLine1LaneVertiPos& other) noexcept {
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
	PrintPatternLine1LaneVertiPos& operator=(const PrintPatternLine1LaneVertiPos&& other)noexcept {
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

	void accept(selectionFlowSimulation& v) override;
	void paintBoxPP() override;
	void paintWhiteLinePP() override;
	observer* createObserver() override;
	void paintStartVertex11() override;
	void paintEndVertex11() override;
	void setStartVertexShort(const bool& setOrRelease) override;
	void setEndVertexShort(const bool& setOrRelease) override;
};
class PrintPatternLine2LaneHoriNeg :public PrintPattern {
private:
	
	int m_p1x = 0;
	int m_p2x = 0;
	int m_p12y = 0;
	
public:
	
	explicit PrintPatternLine2LaneHoriNeg(const int& p1x, const int& p1y, const int& p2x, const int& p2y, callBackLinks* CBLptr)noexcept;
	PrintPatternLine2LaneHoriNeg::PrintPatternLine2LaneHoriNeg(const PrintPatternLine2LaneHoriNeg& other) noexcept : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
	}
	PrintPatternLine2LaneHoriNeg::PrintPatternLine2LaneHoriNeg(const PrintPatternLine2LaneHoriNeg&& other) noexcept : PrintPattern()  {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
	}
	PrintPatternLine2LaneHoriNeg& operator=(const PrintPatternLine2LaneHoriNeg& other) noexcept {
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
	PrintPatternLine2LaneHoriNeg& operator=(const PrintPatternLine2LaneHoriNeg&& other)noexcept {
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
	void accept(selectionFlowSimulation& v) override;
	void paintBoxPP() override;
	void paintWhiteLinePP() override;
	observer* createObserver() override;
	void paintStartVertex11() override;
	void paintEndVertex11() override;
	void setStartVertexShort(const bool& setOrRelease) override;
	void setEndVertexShort(const bool& setOrRelease) override;
};
class PrintPatternLine2LaneHoriPos : public PrintPattern {
private:
	
	int m_p1x = 0;
	int m_p2x = 0;
	int m_p12y = 0;
	
public:
	
	explicit PrintPatternLine2LaneHoriPos(const int& p1x, const int& p1y, const int& p2x, const int& p2y, callBackLinks* CBLptr)noexcept;
	PrintPatternLine2LaneHoriPos::PrintPatternLine2LaneHoriPos(const PrintPatternLine2LaneHoriPos& other)noexcept : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
	}
	PrintPatternLine2LaneHoriPos::PrintPatternLine2LaneHoriPos(const PrintPatternLine2LaneHoriPos&& other)noexcept : PrintPattern()  {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1x = other.m_p1x;
		m_p12y = other.m_p12y;
		m_p2x = other.m_p2x;
	}
	PrintPatternLine2LaneHoriPos& operator=(const PrintPatternLine2LaneHoriPos& other) noexcept {
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
	PrintPatternLine2LaneHoriPos& operator=(const PrintPatternLine2LaneHoriPos&& other) noexcept {
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
	
	void accept(selectionFlowSimulation& v) override;
	void paintBoxPP() override;
	void paintWhiteLinePP() override;
	observer* createObserver() override;
	void paintStartVertex11() override;
	void paintEndVertex11() override;
	void setStartVertexShort(const bool& setOrRelease) override;
	void setEndVertexShort(const bool& setOrRelease) override;
};
class PrintPatternLine2LaneVertiNeg :public PrintPattern {
private:
	
	int m_p12x = 0;
	int m_p1y = 0;
	int m_p2y = 0;
	
public:
	
	explicit PrintPatternLine2LaneVertiNeg(const int& p1x, const int& p1y, const int& p2x, const int& p2y, callBackLinks* CBLptr)noexcept;
	PrintPatternLine2LaneVertiNeg::PrintPatternLine2LaneVertiNeg(const PrintPatternLine2LaneVertiNeg& other)noexcept : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1y = other.m_p1y;
		m_p12x = other.m_p12x;
		m_p2y = other.m_p2y;
	}
	PrintPatternLine2LaneVertiNeg::PrintPatternLine2LaneVertiNeg(const PrintPatternLine2LaneVertiNeg&& other) noexcept : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1y = other.m_p1y;
		m_p12x = other.m_p12x;
		m_p2y = other.m_p2y;
	}
	PrintPatternLine2LaneVertiNeg& operator=(const PrintPatternLine2LaneVertiNeg& other) noexcept {
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
	PrintPatternLine2LaneVertiNeg& operator=(const PrintPatternLine2LaneVertiNeg&& other)noexcept {
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
	
	void accept(selectionFlowSimulation& v) override;
	void paintBoxPP() override;
	void paintWhiteLinePP() override;
	observer* createObserver() override;
	void paintStartVertex11() override;
	void paintEndVertex11() override;
	void setStartVertexShort(const bool& setOrRelease) override;
	void setEndVertexShort(const bool& setOrRelease) override;
};
class PrintPatternLine2LaneVertiPos : public PrintPattern {
private:
	
	int m_p12x = 0;
	int m_p1y = 0;
	int m_p2y = 0;
	
public:
	
	explicit PrintPatternLine2LaneVertiPos(const int& p1x, const int& p1y, const int& p2x, const int& p2y, callBackLinks* CBLptr)noexcept;
	PrintPatternLine2LaneVertiPos::PrintPatternLine2LaneVertiPos(const PrintPatternLine2LaneVertiPos& other)noexcept : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1y = other.m_p1y;
		m_p12x = other.m_p12x;
		m_p2y = other.m_p2y;
	}
	PrintPatternLine2LaneVertiPos::PrintPatternLine2LaneVertiPos(const PrintPatternLine2LaneVertiPos&& other) noexcept : PrintPattern() {
		m_startVertexShort = other.m_startVertexShort;
		m_endVertexShort = other.m_endVertexShort;
		m_verticalOrHorizontal = other.m_verticalOrHorizontal;
		m_risingOrDescention = other.m_risingOrDescention;
		m_p1y = other.m_p1y;
		m_p12x = other.m_p12x;
		m_p2y = other.m_p2y;
	}
	PrintPatternLine2LaneVertiPos& operator=(const PrintPatternLine2LaneVertiPos& other) noexcept {
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
	PrintPatternLine2LaneVertiPos& operator=(const PrintPatternLine2LaneVertiPos&& other) noexcept {
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

	void accept(selectionFlowSimulation& v) override;
	void paintBoxPP() override;
	void paintWhiteLinePP() override;
	observer* createObserver() override;
	void paintStartVertex11() override;
	void paintEndVertex11() override;
	void setStartVertexShort(const bool& setOrRelease) override;
	void setEndVertexShort(const bool& setOrRelease) override;
};