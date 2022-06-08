#pragma once
#include "PrintInGDIplusWindow.h"
#include "PrecompiledHeadersEdges.h"

class PrintInGDIplusWin2LP :public PrintInGDIplusWindow {
private:
	int m_p1x = 0;
	int m_p2x = 0;
	int m_p1y = 0;
	int m_p2y = 0;
	int m_position = 0;
public:
	explicit PrintInGDIplusWin2LP::PrintInGDIplusWin2LP() {

	}
	PrintInGDIplusWin2LP::PrintInGDIplusWin2LP(const PrintInGDIplusWin2LP& other) = delete;
	PrintInGDIplusWin2LP::PrintInGDIplusWin2LP(const PrintInGDIplusWin2LP&& other) = delete;
	PrintInGDIplusWin2LP& operator=(const PrintInGDIplusWin2LP& other) = delete;
	PrintInGDIplusWin2LP& operator=(const PrintInGDIplusWin2LP&& other) = delete;
	PrintInGDIplusWin2LP::~PrintInGDIplusWin2LP() noexcept {	}

	void PrintInGDIplusWin2LP::addPrintContent(const int& p1x, const int& p1y,
		const int& p2x, const int& p2y,
		const int& lane, const int& position, const int& lastRouteVertex) {
		m_p1x = p1x;
		m_p2x = p2x;
		m_p1y = p1y;
		m_p2y = p2y;
		m_position = position;
		if ((p1y == p2y) && ((m_p2x - m_p1x)>m_position) && (lane == 1)) {
			fillPrintContainer((m_p1x + m_position), (m_p1y + 13), lastRouteVertex);
		}
		if ((p1y == p2y) && ((m_p2x - m_p1x)>m_position)&&(lane==2)) {
			fillPrintContainer((m_p1x + m_position), (m_p1y + 5), lastRouteVertex);
		}
		if ((p1x == p2x) && ((m_p2y - m_p1y)>m_position) && (lane == 1)) {
			fillPrintContainer(m_p1x, (m_p1y + m_position), lastRouteVertex);
		}
		if ((p1x == p2x) && ((m_p2y - m_p1y)>m_position) && (lane == 2)) {
			fillPrintContainer((m_p1x+10), (m_p1y + m_position), lastRouteVertex);
		}
	}
};
