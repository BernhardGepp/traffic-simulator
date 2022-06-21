#pragma once
#include "PrecompiledHeadersEdges.h"

class PrintInGDIplusWinEmpty :public PrintInGDIplusWindow {
private:
	void(*m_f5PaintLane)(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV, const int &m_numberOfLanes, const std::vector<std::tuple<int, int, int>> &PointsToBePrinted) = nullptr;
	
public:
	explicit PrintInGDIplusWinEmpty();
	PrintInGDIplusWinEmpty::PrintInGDIplusWinEmpty(const PrintInGDIplusWinEmpty& other) = delete;
	PrintInGDIplusWinEmpty::PrintInGDIplusWinEmpty(const PrintInGDIplusWinEmpty&& other) = delete;
	PrintInGDIplusWinEmpty& operator=(const PrintInGDIplusWinEmpty& other) = delete;
	PrintInGDIplusWinEmpty&& operator=(const PrintInGDIplusWinEmpty&& ohter) = delete;
	~PrintInGDIplusWinEmpty() noexcept;

	void fullemptyPrintContainer(HDC hdc, void(*f5PaintLane)(HDC hdc, const int& iPosXLk, const int& iPosYLk, const int& iPosXRk, const int& iPosYRk, const bool& HorV, const int& numberOfLanes, const std::vector<std::tuple<int, int, int>>& PointsToBePrinted));
};
