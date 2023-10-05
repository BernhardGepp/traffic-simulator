#pragma once

class PrintInGDIplusWin2LP :public PrintInGDIplusWindow {
private:
	int m_p1x = 0;
	int m_p2x = 0;
	int m_p1y = 0;
	int m_p2y = 0;
	int m_position = 0;
public:
	explicit PrintInGDIplusWin2LP();
	PrintInGDIplusWin2LP::PrintInGDIplusWin2LP(const PrintInGDIplusWin2LP& other) = delete;
	PrintInGDIplusWin2LP::PrintInGDIplusWin2LP(const PrintInGDIplusWin2LP&& other) = delete;
	PrintInGDIplusWin2LP& operator=(const PrintInGDIplusWin2LP& other) = delete;
	PrintInGDIplusWin2LP& operator=(const PrintInGDIplusWin2LP&& other) = delete;
	~PrintInGDIplusWin2LP() noexcept;

	void PrintInGDIplusWin2LP::addPrintContent(const int&, const int&, const int&, const int&, const int&, const int&, const int&);
};
