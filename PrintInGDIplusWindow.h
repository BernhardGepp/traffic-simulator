#pragma once
#include "PrecompiledHeadersEdges.h"

class PrintInGDIplusWindow {
private:

public:
	explicit PrintInGDIplusWindow::PrintInGDIplusWindow() {

	}
	PrintInGDIplusWindow::PrintInGDIplusWindow(const PrintInGDIplusWindow& other) = delete;
	PrintInGDIplusWindow::PrintInGDIplusWindow(const PrintInGDIplusWindow&& other) = delete;
	PrintInGDIplusWindow& operator=(const PrintInGDIplusWindow& other) = delete;
	PrintInGDIplusWindow& operator=(const PrintInGDIplusWindow&& other) = delete;
	PrintInGDIplusWindow::~PrintInGDIplusWindow() noexcept {}

	static std::vector<std::tuple<int, int, int>> m_pointContainer;
	static bool m_helper;
	
	static bool fillPrintContainer(const int& a,const int& b,const int& c);
	static bool emptyPrintContainer(HDC hdc,void(*f5PaintLane)(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV, const int &numberOfLanes, const std::vector<std::tuple<int, int, int>> &PointsToBePrinted));
};

std::vector<std::tuple<int,int,int>> PrintInGDIplusWindow::m_pointContainer;

bool PrintInGDIplusWindow::fillPrintContainer(const int& a, const int& b, const int& c) {
	m_pointContainer.push_back(std::make_tuple(a,b,c));
	return true;
}

bool PrintInGDIplusWindow::emptyPrintContainer(HDC hdc,void(*f5PaintLane)(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV, const int &numberOfLanes, const std::vector<std::tuple<int, int, int>> &PointsToBePrinted)) {
	f5PaintLane(hdc, 0, 0, 0, 0, true, 1, m_pointContainer);
	m_pointContainer.clear();
	return true;
}
bool PrintInGDIplusWindow::m_helper = fillPrintContainer;

