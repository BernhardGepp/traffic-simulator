#pragma once
#include "PrintInGDIplusWindow.h"
#include "PrecompiledHeadersEdges.h"
class PrintInGDIplusWin1LN :public PrintInGDIplusWindow {
private:
	
	int m_p2x = 0;
	int m_p1y = 0;
	int m_p2y = 0;
	int m_position = 0;
	
public:
	explicit PrintInGDIplusWin1LN::PrintInGDIplusWin1LN() {

	}
	PrintInGDIplusWin1LN::~PrintInGDIplusWin1LN() noexcept {

	}
	PrintInGDIplusWin1LN::PrintInGDIplusWin1LN(const PrintInGDIplusWin1LN& other) = delete;
	PrintInGDIplusWin1LN::PrintInGDIplusWin1LN(const PrintInGDIplusWin1LN&& other) = delete;
	PrintInGDIplusWin1LN& operator=(const PrintInGDIplusWin1LN& other) = delete;
	PrintInGDIplusWin1LN& operator=(const PrintInGDIplusWin1LN&& other) = delete;

	void PrintInGDIplusWin1LN::addPrintContent(const int& p1x, const int& p1y,
		const int& p2x, const int& p2y,
		const int& numberOfLanes, const int& position, const int& lastRouteVertex) {
		m_p2x = p2x;
		m_p1y = p1y;
		m_p2y = p2y;
		m_position = position;
		if ((m_p1y == m_p2y) && (p1x>(m_p2x+m_position))) {
			fillPrintContainer((m_p2x + m_position), (m_p1y + 5), lastRouteVertex);
		}
		if ((p1x==m_p2x)&&(m_p1y>(m_p2y+m_position))) {
			fillPrintContainer(p1x, (m_p2y + m_position), lastRouteVertex);
		}
	}
};
