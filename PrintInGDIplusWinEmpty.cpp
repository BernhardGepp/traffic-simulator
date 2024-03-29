#include "PrecompiledHeadersEdges.h"
#include "PrintInGDIplusWinEmpty.h"

PrintInGDIplusWinEmpty::PrintInGDIplusWinEmpty() {}
PrintInGDIplusWinEmpty::~PrintInGDIplusWinEmpty() noexcept {}

void PrintInGDIplusWinEmpty::fullemptyPrintContainer(HDC hdc, void(*f5PaintLane)(HDC hdc, const int& iPosXLk, const int& iPosYLk, const int& iPosXRk, const int& iPosYRk, const bool& HorV, const int& numberOfLanes, const std::vector<std::tuple<int, int, int>>& PointsToBePrinted)) {
	//********************************************************************
	//This method is used to empty the data containter "m_pointContainer" of the parent class.
	m_f5PaintLane = f5PaintLane;
	emptyPrintContainer(hdc, f5PaintLane);
}