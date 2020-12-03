#pragma once
#include "PrintInGDIplusWindow.h"
#include "PrecompiledHeadersEdges.h"
//#pragma comment(lib, "gdiplus.lib")
//#pragma comment(lib,"user32.lib")
class PrintInGDIplusWin1LP :public PrintInGDIplusWindow {
private:
	int m_p1x = 0;
	int m_p2x = 0;
	int m_p1y = 0;
	int m_p2y = 0;
	int m_position = 0;
public:
	explicit PrintInGDIplusWin1LP::PrintInGDIplusWin1LP() {

	}
	PrintInGDIplusWin1LP::~PrintInGDIplusWin1LP() {

	}
	PrintInGDIplusWin1LP::PrintInGDIplusWin1LP(PrintInGDIplusWin1LP& other) = delete;
	PrintInGDIplusWin1LP::PrintInGDIplusWin1LP(PrintInGDIplusWin1LP&& other) = delete;
	PrintInGDIplusWin1LP& operator=(const PrintInGDIplusWin1LP& other) = delete;
	PrintInGDIplusWin1LP& operator=(const PrintInGDIplusWin1LP&& other) = delete;
	
	
	void PrintInGDIplusWin1LP::addPrintContent(const int& p1x, const int& p1y,
		const int& p2x, const int& p2y,
		const int& lane, const int& position, const int& lastRouteVertex) {
		m_p1x = p1x;
		m_p2x = p2x;
		m_p1y = p1y;
		m_p2y = p2y;
		m_position = position;
		if ((p1y == p2y)&&((m_p2x-m_p1x)>m_position)) {
			fillPrintContainer((m_p1x + m_position), (m_p1y + 5), lastRouteVertex);
		}
		if ((p1x==p2x)&&((m_p2y-m_p1y)>m_position)) {
			fillPrintContainer(m_p1x, (m_p1y + m_position), lastRouteVertex);
		}
		
		
	}
		
};
