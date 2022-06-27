#include "PrintInGDIplusWindow.h"
#include "PrecompiledHeadersEdges.H"
PrintInGDIplusWindow::PrintInGDIplusWindow() {}
PrintInGDIplusWindow::~PrintInGDIplusWindow() noexcept {}
std::vector<std::tuple<int, int, int>> PrintInGDIplusWindow::m_pointContainer;

bool PrintInGDIplusWindow::fillPrintContainer(const int& a, const int& b, const int& c) {
	//********************************************************************
	//This method is used to fill the data containter "m_pointContainer" of that class.
	m_pointContainer.push_back(std::make_tuple(a, b, c));
	return true;
}

bool PrintInGDIplusWindow::emptyPrintContainer(HDC hdc, void(*f5PaintLane)(HDC hdc, const int& iPosXLk, const int& iPosYLk, const int& iPosXRk, const int& iPosYRk, const bool& HorV, const int& numberOfLanes, const std::vector<std::tuple<int, int, int>>& PointsToBePrinted)) {
	f5PaintLane(hdc, 0, 0, 0, 0, true, 1, m_pointContainer);
	//********************************************************************
	//This method is used to empty the data containter "m_pointContainer" of that class.
	m_pointContainer.clear();
	return true;
}
bool PrintInGDIplusWindow::m_helper = fillPrintContainer;