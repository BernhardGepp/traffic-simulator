#pragma once

class PrintInGDIplusWin1LP :public PrintInGDIplusWindow {
private:
	int m_p1x = 0;
	int m_p2x = 0;
	int m_p1y = 0;
	int m_p2y = 0;
	int m_position = 0;
public:
	explicit PrintInGDIplusWin1LP();
	~PrintInGDIplusWin1LP() noexcept;
	PrintInGDIplusWin1LP::PrintInGDIplusWin1LP(const PrintInGDIplusWin1LP& other) = delete;
	PrintInGDIplusWin1LP::PrintInGDIplusWin1LP(const PrintInGDIplusWin1LP&& other) = delete;
	PrintInGDIplusWin1LP& operator=(const PrintInGDIplusWin1LP& other) = delete;
	PrintInGDIplusWin1LP& operator=(const PrintInGDIplusWin1LP&& other) = delete;
	
	void addPrintContent(const int&, const int&, const int&, const int&, const int&, const int&, const int&);
};
