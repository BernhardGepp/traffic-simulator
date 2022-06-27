#include "PrecompiledHeadersEdges.h"
#include "PrintInGDIplusWin1LN.h"

PrintInGDIplusWin1LN::PrintInGDIplusWin1LN() {}
PrintInGDIplusWin1LN::~PrintInGDIplusWin1LN() noexcept {}

void PrintInGDIplusWin1LN::addPrintContent(const int& p1x, const int& p1y, const int& p2x, const int& p2y,
	const int& numberOfLanes, const int& position, const int& lastRouteVertex) {
	//********************************************************************
	//The aim of this method is to display the results of the simulation correctly. 
	//It depends on the position of the link in the traffic graph. 
	//Specifically, this method is chosen for links with one lane in negativ direction.
	//The caller of this method passes the simulation results, 
	//which are slightly manipulated here and later filled into the data container "m_pointContainer" 
	//by method "fillPrintContainer" of the parent class. 
	m_p2x = p2x;
	m_p1y = p1y;
	m_p2y = p2y;
	m_position = position;
	if ((m_p1y == m_p2y) && (p1x > (m_p2x + m_position))) {
		fillPrintContainer((m_p2x + m_position), (m_p1y + 5), lastRouteVertex);
	}
	if ((p1x == m_p2x) && (m_p1y > (m_p2y + m_position))) {
		fillPrintContainer(p1x, (m_p2y + m_position), lastRouteVertex);
	}
}