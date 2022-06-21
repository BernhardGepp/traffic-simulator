#pragma once
#include "PrecompiledHeadersEdges.h"
class PrintInGDIplusWin1LN :public PrintInGDIplusWindow {
private:
	
	int m_p2x = 0;
	int m_p1y = 0;
	int m_p2y = 0;
	int m_position = 0;
	
public:
	explicit PrintInGDIplusWin1LN();
	~PrintInGDIplusWin1LN() noexcept;
	PrintInGDIplusWin1LN::PrintInGDIplusWin1LN(const PrintInGDIplusWin1LN& other) = delete;
	PrintInGDIplusWin1LN::PrintInGDIplusWin1LN(const PrintInGDIplusWin1LN&& other) = delete;
	PrintInGDIplusWin1LN& operator=(const PrintInGDIplusWin1LN& other) = delete;
	PrintInGDIplusWin1LN& operator=(const PrintInGDIplusWin1LN&& other) = delete;

	void PrintInGDIplusWin1LN::addPrintContent(const int&, const int&, const int&, const int&, const int&, const int&, const int&);
};
