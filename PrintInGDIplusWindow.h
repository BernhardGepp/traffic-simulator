#pragma once

class PrintInGDIplusWindow {
private:

public:
	explicit PrintInGDIplusWindow();
	PrintInGDIplusWindow::PrintInGDIplusWindow(const PrintInGDIplusWindow& other) = delete;
	PrintInGDIplusWindow::PrintInGDIplusWindow(const PrintInGDIplusWindow&& other) = delete;
	PrintInGDIplusWindow& operator=(const PrintInGDIplusWindow& other) = delete;
	PrintInGDIplusWindow& operator=(const PrintInGDIplusWindow&& other) = delete;
	~PrintInGDIplusWindow() noexcept;

	static std::vector<std::tuple<int, int, int>> m_pointContainer;
	static bool m_helper;
	
	static bool fillPrintContainer(const int& ,const int& ,const int& );
	static bool emptyPrintContainer(HDC hdc ,void(*f5PaintLane)(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV, const int &numberOfLanes, const std::vector<std::tuple<int, int, int>> &PointsToBePrinted));
};


