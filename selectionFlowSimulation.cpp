#include "PrecompiledHeadersEdges.h"
#include "selectionFlowSimulation.h"

/*void selectionFlowSimulation::setEndingPoints(const int& p1x, const int& p1y, const int& p2x, const int& p2y, const int& maxVelocity, const int& maxVelocity_Density) {
	
	m_maxVelocity = maxVelocity;
	m_maxVelocity_Density = maxVelocity_Density;

}*/

//********************************************
void selectionFlowSimulation::setStrategy(PrintPatternLine1LaneHoriNeg& ppt) {
	vehicleSetPtr = std::make_unique<flowSimulation1NegStraight>(gsl::not_null<callBackLinks*>(m_CBLptr), m_maxVelocity, m_maxVelocity_Density);
}
void selectionFlowSimulation::setStrategy(PrintPatternLine1LaneHoriPos& ppt) {
	vehicleSetPtr = std::make_unique<flowSimulation1PosStraight>(gsl::not_null<callBackLinks*>(m_CBLptr), m_maxVelocity, m_maxVelocity_Density);
}
void selectionFlowSimulation::setStrategy(PrintPatternLine1LaneVertiNeg& ppt) {
	vehicleSetPtr = std::make_unique<flowSimulation1NegStraight>(gsl::not_null<callBackLinks*>(m_CBLptr), m_maxVelocity, m_maxVelocity_Density);
}
void selectionFlowSimulation::setStrategy(PrintPatternLine1LaneVertiPos& ppt) {
	vehicleSetPtr = std::make_unique<flowSimulation1PosStraight>(gsl::not_null<callBackLinks*>(m_CBLptr), m_maxVelocity, m_maxVelocity_Density);
}
void selectionFlowSimulation::setStrategy(PrintPatternLine2LaneHoriNeg& ppt) {
	vehicleSetPtr = std::make_unique<flowSimulation2NegStraight>(gsl::not_null<callBackLinks*>(m_CBLptr), m_maxVelocity, m_maxVelocity_Density);
}
void selectionFlowSimulation::setStrategy(PrintPatternLine2LaneHoriPos& ppt) {
	vehicleSetPtr = std::make_unique<flowSimulation2PosStraightA>(gsl::not_null<callBackLinks*>(m_CBLptr), m_maxVelocity, m_maxVelocity_Density);
}
void selectionFlowSimulation::setStrategy(PrintPatternLine2LaneVertiNeg& ppt) {
	vehicleSetPtr = std::make_unique<flowSimulation2NegStraight>(gsl::not_null<callBackLinks*>(m_CBLptr), m_maxVelocity, m_maxVelocity_Density);
}
void selectionFlowSimulation::setStrategy(PrintPatternLine2LaneVertiPos& ppt) {
	vehicleSetPtr = std::make_unique<flowSimulation2PosStraightA>(gsl::not_null<callBackLinks*>(m_CBLptr), m_maxVelocity, m_maxVelocity_Density);
}

PrintPattern::PrintPattern() noexcept{}

PrintPatternLine1LaneHoriNeg::PrintPatternLine1LaneHoriNeg(const int& p1x, const int& p1y, const int& p2x, const int& p2y, callBackLinks* CBLptr)noexcept
	: PrintPattern(), m_p1x(p1x), m_p12y(p1y), m_p2x(p2x) {
	m_length = m_p1x - m_p2x;
	m_startVertexShort = false;
	m_endVertexShort = false;
	m_verticalOrHorizontal = false;
	m_risingOrDescention = false;
	m_CBLptr = CBLptr;
	
}

void PrintPatternLine1LaneHoriNeg::accept(selectionFlowSimulation& v){
	v.setStrategy(*this);
}

void PrintPatternLine1LaneHoriNeg::paintBoxPP(){
	if ((m_startVertexShort == false) && (m_endVertexShort == true)) {
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p2x + 20, m_p12y, m_p1x - m_p2x - 20, 10,false);
	}
	if ((m_startVertexShort == false) && (m_endVertexShort == false)) {
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p2x + 10, m_p12y, m_p1x - m_p2x - 10, 10,false);
	}
	if ((m_startVertexShort == true) && (m_endVertexShort == false)) {
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p2x + 10, m_p12y, m_p1x - m_p2x - 10, 10,false);
	}
	if ((m_startVertexShort == true) && (m_endVertexShort == true)) {
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p2x + 10, m_p12y, m_p1x - m_p2x - 10, 10,false);
	}
}

void PrintPatternLine1LaneHoriNeg::paintWhiteLinePP(){

	if (m_endVertexShort) {
		m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p1x, m_p12y + 5, m_p2x + 20, m_p12y + 5, 6);
		m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p2x, m_p12y + 5, m_p2x - 32, m_p12y + 5, 6);
	}
	else {
		m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p1x, m_p12y + 5, m_p2x + 10, m_p12y + 5, 6);
		m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p2x, m_p12y + 5, m_p2x - 35, m_p12y + 5, 6);
	}
}
observer* PrintPatternLine1LaneHoriNeg::createObserver(){
	m_observer = std::make_unique<concreteObserver1LaneHoriNeg>(m_p1x, m_p2x, m_p12y);
	return m_observer.get();
}
void PrintPatternLine1LaneHoriNeg::paintStartVertex11(){

}
void PrintPatternLine1LaneHoriNeg::paintEndVertex11(){

}
void PrintPatternLine1LaneHoriNeg::setStartVertexShort(const bool& setOrRelease){
	m_startVertexShort = setOrRelease;
}
void PrintPatternLine1LaneHoriNeg::setEndVertexShort(const bool& setOrRelease){
	m_endVertexShort = setOrRelease;
}
void PrintPatternLine1LaneHoriNeg::printContentOfSection(const int& lane, const int& position, const int& destination){
	m_P1LN.addPrintContent(m_p1x, m_p12y, m_p2x, m_p12y, lane, position, destination);
}

PrintPatternLine1LaneHoriPos::PrintPatternLine1LaneHoriPos(const int& p1x, const int& p1y, const int& p2x, const int& p2y, callBackLinks* CBLptr)noexcept
	: PrintPattern(), m_p1x(p1x), m_p12y(p1y), m_p2x(p2x) {
	m_length = m_p2x - m_p1x;
	m_startVertexShort = false;
	m_endVertexShort = false;
	m_verticalOrHorizontal = false;
	m_risingOrDescention = true;
	m_CBLptr = CBLptr;

}
void PrintPatternLine1LaneHoriPos::accept(selectionFlowSimulation& v){
	v.setStrategy(*this);
}
void PrintPatternLine1LaneHoriPos::paintBoxPP(){
	if ((m_startVertexShort == false) && (m_endVertexShort == false))
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p1x + 10, m_p12y, m_p2x - m_p1x - 10, 10,true);
	if ((m_startVertexShort == false) && (m_endVertexShort == true))
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p1x + 10, m_p12y, m_p2x - m_p1x - 10, 10,true);
	if ((m_startVertexShort == true) && (m_endVertexShort == false))
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p1x + 20, m_p12y, m_p2x - m_p1x - 20, 10,true);
	if ((m_startVertexShort == true) && (m_endVertexShort == true))
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p1x + 20, m_p12y, m_p2x - m_p1x - 20, 10,true);
}
void PrintPatternLine1LaneHoriPos::paintWhiteLinePP(){
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
observer* PrintPatternLine1LaneHoriPos::createObserver(){
	m_observer = std::make_unique<concreteObserver1LaneHoriPos>(m_p1x, m_p2x, m_p12y);
	return m_observer.get();
}
void PrintPatternLine1LaneHoriPos::paintStartVertex11(){}
void PrintPatternLine1LaneHoriPos::paintEndVertex11(){}
void PrintPatternLine1LaneHoriPos::setStartVertexShort(const bool& setOrRelease){
	m_startVertexShort = setOrRelease;
}
void PrintPatternLine1LaneHoriPos::setEndVertexShort(const bool& setOrRelease){
	m_endVertexShort = setOrRelease;
}
void PrintPatternLine1LaneHoriPos::printContentOfSection(const int& lane, const int& position, const int& destination) {
	m_P1LP.addPrintContent(m_p1x, m_p12y, m_p2x, m_p12y, lane, position, destination);
}

PrintPatternLine1LaneVertiNeg::PrintPatternLine1LaneVertiNeg(const int& p1x, const int& p1y, const int& p2x, const int& p2y, callBackLinks* CBLptr)noexcept
	: PrintPattern(), m_p12x(p1x), m_p1y(p1y), m_p2y(p2y) {
	m_length = m_p1y - m_p2y;
	m_startVertexShort = false;
	m_endVertexShort = false;
	m_verticalOrHorizontal = true;
	m_risingOrDescention = false;
	m_CBLptr = CBLptr;

}
void PrintPatternLine1LaneVertiNeg::accept(selectionFlowSimulation& v){
	v.setStrategy(*this);
}
void PrintPatternLine1LaneVertiNeg::paintBoxPP(){
	if ((m_startVertexShort == false) && (m_endVertexShort == false)) {
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p2y + 10, 10, m_p1y - m_p2y - 10,false);
	}
	if ((m_startVertexShort == true) && (m_endVertexShort == false)) {
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p2y + 10, 10, m_p1y - m_p2y - 10,false);
	}
	if ((m_startVertexShort == false) && (m_endVertexShort == true)) {
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p2y + 20, 10, m_p1y - m_p2y - 20,false);
	}
	if ((m_startVertexShort == true) && (m_endVertexShort == true)) {
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p2y + 10, 10, m_p1y - m_p2y - 10,false);
	}
}
void PrintPatternLine1LaneVertiNeg::paintWhiteLinePP(){
	if (m_endVertexShort) {
		m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 5, m_p1y, m_p12x + 5, m_p2y + 20, 6);
		m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 5, m_p2y, m_p12x + 5, m_p2y - 22, 6);
	}
	else {
		m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 5, m_p1y, m_p12x + 5, m_p2y + 10, 6);
		m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 5, m_p2y, m_p12x + 5, m_p2y - 22, 6);
	}
}
observer* PrintPatternLine1LaneVertiNeg::createObserver(){
	m_observer = std::make_unique<concreteObserver1LaneVertiNeg>(m_p1y, m_p2y, m_p12x);
	return m_observer.get();
}
void PrintPatternLine1LaneVertiNeg::paintStartVertex11(){}
void PrintPatternLine1LaneVertiNeg::paintEndVertex11(){}
void PrintPatternLine1LaneVertiNeg::setStartVertexShort(const bool& setOrRelease){
	m_startVertexShort = setOrRelease;
}
void PrintPatternLine1LaneVertiNeg::setEndVertexShort(const bool& setOrRelease){
	m_endVertexShort = setOrRelease;
}
void PrintPatternLine1LaneVertiNeg::printContentOfSection(const int& lane, const int& position, const int& destination) {
	m_P1LN.addPrintContent(m_p12x, m_p1y, m_p12x, m_p2y, lane, position, destination);
}

PrintPatternLine1LaneVertiPos::PrintPatternLine1LaneVertiPos(const int& p1x, const int& p1y, const int& p2x, const int& p2y, callBackLinks* CBLptr)noexcept
	: PrintPattern(), m_p12x(p1x), m_p1y(p1y), m_p2y(p2y) {
	m_length = m_p2y - m_p1y;
	m_startVertexShort = false;
	m_endVertexShort = false;
	m_verticalOrHorizontal = true;
	m_risingOrDescention = true;
	m_CBLptr = CBLptr;

}
void PrintPatternLine1LaneVertiPos::accept(selectionFlowSimulation& v){
	v.setStrategy(*this);
}
void PrintPatternLine1LaneVertiPos::paintBoxPP(){
	if ((m_startVertexShort == false) && (m_endVertexShort == false)) {
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p1y + 10, 10, m_p2y - 10 - m_p1y,true);
	}
	if ((m_startVertexShort == false) && (m_endVertexShort == true)) {
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p1y + 10, 10, m_p2y - 10 - m_p1y,true);
	}
	if ((m_startVertexShort == true) && (m_endVertexShort == false)) {
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p1y + 20, 10, m_p2y - 20 - m_p1y,true);
	}
	if ((m_startVertexShort == true) && (m_endVertexShort == true)) {
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p1y + 20, 10, m_p2y - 20 - m_p1y,true);
	}
}
void PrintPatternLine1LaneVertiPos::paintWhiteLinePP(){

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
observer* PrintPatternLine1LaneVertiPos::createObserver(){
	m_observer = std::make_unique<concreteObserver1LaneVertiPos>(m_p1y, m_p2y, m_p12x);
	return m_observer.get();
}
void PrintPatternLine1LaneVertiPos::paintStartVertex11(){}
void PrintPatternLine1LaneVertiPos::paintEndVertex11(){}
void PrintPatternLine1LaneVertiPos::setStartVertexShort(const bool& setOrRelease){
	m_startVertexShort = setOrRelease;
}
void PrintPatternLine1LaneVertiPos::setEndVertexShort(const bool& setOrRelease){
	m_endVertexShort = setOrRelease;
}
void PrintPatternLine1LaneVertiPos::printContentOfSection(const int& lane, const int& position, const int& destination) {
	m_P1LP.addPrintContent(m_p12x, m_p1y, m_p12x, m_p2y, lane, position, destination);
}
PrintPatternLine2LaneHoriNeg::PrintPatternLine2LaneHoriNeg(const int& p1x, const int& p1y, const int& p2x, const int& p2y, callBackLinks* CBLptr)noexcept
	: PrintPattern(), m_p1x(p1x), m_p12y(p1y), m_p2x(p2x) {
	m_length = m_p1x - m_p2x;
	m_startVertexShort = false;
	m_endVertexShort = false;
	m_verticalOrHorizontal = false;
	m_risingOrDescention = false;
	m_CBLptr = CBLptr;
}
void PrintPatternLine2LaneHoriNeg::accept(selectionFlowSimulation& v){
	v.setStrategy(*this);
}
void PrintPatternLine2LaneHoriNeg::paintBoxPP(){
	if ((m_startVertexShort == false) && (m_endVertexShort == true)) {
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p2x + 20, m_p12y, m_p1x - m_p2x - 20, 20,false);
	}
	if ((m_startVertexShort == false) && (m_endVertexShort == false)) {
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p2x + 10, m_p12y, m_p1x - m_p2x - 10, 20,false);
	}
	if ((m_startVertexShort == true) && (m_endVertexShort == false)) {
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p2x + 10, m_p12y, m_p1x - m_p2x - 10, 20,false);
	}
	if ((m_startVertexShort == true) && (m_endVertexShort == true)) {
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p2x + 10, m_p12y, m_p1x - m_p2x - 10, 20,false);
	}
}
void PrintPatternLine2LaneHoriNeg::paintWhiteLinePP(){

	if (m_endVertexShort) {
		m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p1x - 1, m_p12y + 12, m_p2x + 20, m_p12y + 12, 17);
		m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p2x, m_p12y + 12, m_p2x - 32, m_p12y + 12, 17);
	}
	else {
		m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p1x - 1, m_p12y + 12, m_p2x + 10, m_p12y + 12, 17);
		m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p2x, m_p12y + 12, m_p2x - 35, m_p12y + 12, 17);
	}
}
observer* PrintPatternLine2LaneHoriNeg::createObserver(){
	m_observer = std::make_unique<concreteObserver2LaneHoriNeg>(m_p1x, m_p2x, m_p12y);
	return m_observer.get();
}
void PrintPatternLine2LaneHoriNeg::paintStartVertex11(){
	m_CBLptr->topLevelFunctionPTR_f16PaintBoxFlex21(m_p1x, m_p12y);
}
void PrintPatternLine2LaneHoriNeg::paintEndVertex11(){
	m_CBLptr->topLevelFunctionPTR_f16PaintBoxFlex21(m_p2x, m_p12y);
}
void PrintPatternLine2LaneHoriNeg::setStartVertexShort(const bool& setOrRelease){
	m_startVertexShort = setOrRelease;
}
void PrintPatternLine2LaneHoriNeg::setEndVertexShort(const bool& setOrRelease){
	m_endVertexShort = setOrRelease;
}
void PrintPatternLine2LaneHoriNeg::printContentOfSection(const int& lane, const int& position, const int& destination) {
	m_P2LN.addPrintContent(m_p1x, m_p12y, m_p2x, m_p12y, lane, position, destination);
}
PrintPatternLine2LaneHoriPos::PrintPatternLine2LaneHoriPos(const int& p1x, const int& p1y, const int& p2x, const int& p2y, callBackLinks* CBLptr)noexcept
	: PrintPattern(), m_p1x(p1x), m_p12y(p1y), m_p2x(p2x) {
	m_length = m_p2x - m_p1x;
	m_startVertexShort = false;
	m_endVertexShort = false;
	m_verticalOrHorizontal = false;
	m_risingOrDescention = true;
	m_CBLptr = CBLptr;
}


void PrintPatternLine2LaneHoriPos::accept(selectionFlowSimulation& v){
	v.setStrategy(*this);
}
void PrintPatternLine2LaneHoriPos::paintBoxPP(){
	//m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p1x + 10, m_p12y, m_p2x - m_p1x - 10, 20);
	if ((m_startVertexShort == false) && (m_endVertexShort == false))
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p1x + 10, m_p12y, m_p2x - m_p1x - 10, 20,true);
	if ((m_startVertexShort == false) && (m_endVertexShort == true))
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p1x + 10, m_p12y, m_p2x - m_p1x - 10, 20,true);
	if ((m_startVertexShort == true) && (m_endVertexShort == false))
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p1x + 20, m_p12y, m_p2x - m_p1x - 20, 20,true);
	if ((m_startVertexShort == true) && (m_endVertexShort == true))
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p1x + 20, m_p12y, m_p2x - m_p1x - 20, 20,true);
}
void PrintPatternLine2LaneHoriPos::paintWhiteLinePP(){
	if ((m_startVertexShort == false) && (m_endVertexShort == false)) {
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
observer* PrintPatternLine2LaneHoriPos::createObserver(){
	m_observer = std::make_unique<concreteObserver2LaneHoriPos>(m_p1x, m_p2x, m_p12y);
	return m_observer.get();
}
void PrintPatternLine2LaneHoriPos::paintStartVertex11(){
	m_CBLptr->topLevelFunctionPTR_f16PaintBoxFlex21(m_p1x, m_p12y);
}
void PrintPatternLine2LaneHoriPos::paintEndVertex11(){
	m_CBLptr->topLevelFunctionPTR_f16PaintBoxFlex21(m_p2x, m_p12y);
}
void PrintPatternLine2LaneHoriPos::setStartVertexShort(const bool& setOrRelease){
	m_startVertexShort = setOrRelease;
}
void PrintPatternLine2LaneHoriPos::setEndVertexShort(const bool& setOrRelease){
	m_endVertexShort = setOrRelease;
}
void PrintPatternLine2LaneHoriPos::printContentOfSection(const int& lane, const int& position, const int& destination) {
	m_P2LP.addPrintContent(m_p1x, m_p12y, m_p2x, m_p12y, lane, position, destination);
}

PrintPatternLine2LaneVertiNeg::PrintPatternLine2LaneVertiNeg(const int& p1x, const int& p1y, const int& p2x, const int& p2y, callBackLinks* CBLptr)noexcept
	: PrintPattern(), m_p12x(p1x), m_p1y(p1y), m_p2y(p2y) {
	m_length = m_p1y - m_p2y;
	m_startVertexShort = false;
	m_endVertexShort = false;
	m_verticalOrHorizontal = true;
	m_risingOrDescention = false;
	m_CBLptr = CBLptr;
}
void PrintPatternLine2LaneVertiNeg::accept(selectionFlowSimulation& v){
	v.setStrategy(*this);
}
void PrintPatternLine2LaneVertiNeg::paintBoxPP(){
	if ((m_startVertexShort == false) && (m_endVertexShort == false)) {
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p2y + 10, 20, m_p1y - m_p2y - 10,false);
	}
	if ((m_startVertexShort == true) && (m_endVertexShort == false)) {
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p2y + 10, 20, m_p1y - m_p2y - 10,false);
	}
	if ((m_startVertexShort == false) && (m_endVertexShort == true)) {
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p2y + 20, 20, m_p1y - m_p2y - 20,false);
	}
	if ((m_startVertexShort == true) && (m_endVertexShort == true)) {
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p2y + 10, 20, m_p1y - m_p2y - 10,false);
	}

}
void PrintPatternLine2LaneVertiNeg::paintWhiteLinePP(){
	if (m_endVertexShort) {
		m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 8, m_p1y, m_p12x + 8, m_p2y + 20, 16);
		m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 8, m_p2y, m_p12x + 8, m_p2y - 32, 16);
	}
	else {
		m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 8, m_p1y, m_p12x + 8, m_p2y + 10, 16);
		m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 8, m_p2y, m_p12x + 8, m_p2y - 32, 16);
	}

}
observer* PrintPatternLine2LaneVertiNeg::createObserver(){
	m_observer = std::make_unique<concreteObserver2LaneVertiNeg>(m_p1y, m_p2y, m_p12x);
	return m_observer.get();
}
void PrintPatternLine2LaneVertiNeg::paintStartVertex11(){
	m_CBLptr->topLevelFunctionPTR_f15PaintBoxFlex12(m_p12x, m_p1y);
}
void PrintPatternLine2LaneVertiNeg::paintEndVertex11(){
	m_CBLptr->topLevelFunctionPTR_f15PaintBoxFlex12(m_p12x, m_p2y);
}
void PrintPatternLine2LaneVertiNeg::setStartVertexShort(const bool& setOrRelease){
	m_startVertexShort = setOrRelease;
}
void PrintPatternLine2LaneVertiNeg::setEndVertexShort(const bool& setOrRelease){
	m_endVertexShort = setOrRelease;
}
void PrintPatternLine2LaneVertiNeg::printContentOfSection(const int& lane, const int& position, const int& destination) {
	m_P2LN.addPrintContent(m_p12x, m_p1y, m_p12x, m_p2y, lane, position, destination);
}

PrintPatternLine2LaneVertiPos::PrintPatternLine2LaneVertiPos(const int& p1x, const int& p1y, const int& p2x, const int& p2y, callBackLinks* CBLptr)noexcept
	: PrintPattern(), m_p12x(p1x), m_p1y(p1y), m_p2y(p2y) {
	m_length = m_p2y - m_p1y;
	m_startVertexShort = false;
	m_endVertexShort = false;
	m_verticalOrHorizontal = true;
	m_risingOrDescention = true;
	m_CBLptr = CBLptr;
}
void PrintPatternLine2LaneVertiPos::accept(selectionFlowSimulation& v){
	v.setStrategy(*this);
}
void PrintPatternLine2LaneVertiPos::paintBoxPP(){


	if ((m_startVertexShort == false) && (m_endVertexShort == false)) {
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p1y + 10, 20, m_p2y - 10 - m_p1y,true);
	}
	if ((m_startVertexShort == false) && (m_endVertexShort == true)) {
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p1y + 10, 20, m_p2y - 10 - m_p1y,true);
	}
	if ((m_startVertexShort == true) && (m_endVertexShort == false)) {
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p1y + 20, 20, m_p2y - 20 - m_p1y,true);
	}
	if ((m_startVertexShort == true) && (m_endVertexShort == true)) {
		m_CBLptr->topLevelFunctionPTR_f10PaintBox(m_p12x, m_p1y + 20, 20, m_p2y - 20 - m_p1y,true);
	}
}
void PrintPatternLine2LaneVertiPos::paintWhiteLinePP(){
	if ((m_startVertexShort == false) && (m_endVertexShort == false)) {
		m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 10, m_p1y + 10, m_p12x + 10, m_p2y - 1, 16);
		m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 10, m_p2y + 10, m_p12x + 10, m_p2y + 30, 16);
	}
	if ((m_startVertexShort == false) && (m_endVertexShort == true)) {
		m_CBLptr->topLevelFunctionPTR_f11PaintWhiteLine(m_p12x + 10, m_p1y + 10, m_p12x + 10, m_p2y - 1, 16);
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
observer* PrintPatternLine2LaneVertiPos::createObserver(){
	m_observer = std::make_unique<concreteObserver2LaneVertiPos>(m_p1y, m_p2y, m_p12x);
	return m_observer.get();
}
void PrintPatternLine2LaneVertiPos::paintStartVertex11(){
	m_CBLptr->topLevelFunctionPTR_f15PaintBoxFlex12(m_p12x, m_p1y);
}
void PrintPatternLine2LaneVertiPos::paintEndVertex11(){
	m_CBLptr->topLevelFunctionPTR_f15PaintBoxFlex12(m_p12x, m_p2y);
}
void PrintPatternLine2LaneVertiPos::setStartVertexShort(const bool& setOrRelease){
	m_startVertexShort = setOrRelease;
}
void PrintPatternLine2LaneVertiPos::setEndVertexShort(const bool& setOrRelease){
	m_endVertexShort = setOrRelease;
}
void PrintPatternLine2LaneVertiPos::printContentOfSection(const int& lane, const int& position, const int& destination) {
	m_P2LP.addPrintContent(m_p12x, m_p1y, m_p12x, m_p2y, lane, position, destination);
}