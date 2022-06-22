#include "PrecompiledHeadersEdges.h"
#include "PrintInGDIplusWin2LN.h"

PrintInGDIplusWin2LN::PrintInGDIplusWin2LN() {}
PrintInGDIplusWin2LN::~PrintInGDIplusWin2LN() noexcept {}

void PrintInGDIplusWin2LN::addPrintContent(const int& p1x, const int& p1y, const int& p2x, const int& p2y,
	const int& lane, const int& position, const int& lastRouteVertex) {
	m_p1x = p1x;
	m_p2x = p2x;
	m_p1y = p1y;
	m_p2y = p2y;
	m_position = position;
	if ((m_p1y == m_p2y) && (p1x > (m_p2x + m_position)) && (lane == 1)) {
		fillPrintContainer((m_p2x + m_position), (m_p1y + 5), lastRouteVertex);
	}
	if ((m_p1y == m_p2y) && (p1x > (m_p2x + m_position)) && (lane == 2)) {
		fillPrintContainer((m_p2x + m_position), (m_p1y + 13), lastRouteVertex);
	}
	if ((m_p1x == m_p2x) && (m_p1y > (m_p2y + m_position)) && (lane == 1)) {
		fillPrintContainer((m_p1x + 10), (m_p2y + m_position), lastRouteVertex);
	}
	if ((m_p1x == m_p2x) && (m_p1y > (m_p2y + m_position)) && (lane == 2)) {
		fillPrintContainer(m_p1x, (m_p2y + m_position), lastRouteVertex);
	}
}