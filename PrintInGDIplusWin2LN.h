#pragma once
#include "PrecompiledHeadersEdges.h"

class PrintInGDIplusWin2LN :public PrintInGDIplusWindow {
private:
	int m_p1x = 0;
	int m_p2x = 0;
	int m_p1y = 0;
	int m_p2y = 0;
	int m_position = 0;
public:
	explicit PrintInGDIplusWin2LN();
	PrintInGDIplusWin2LN::PrintInGDIplusWin2LN(const PrintInGDIplusWin2LN& other) = delete;
	PrintInGDIplusWin2LN::PrintInGDIplusWin2LN(const PrintInGDIplusWin2LN&& other) = delete;
	PrintInGDIplusWin2LN& operator=(const PrintInGDIplusWin2LN& other) = delete;
	PrintInGDIplusWin2LN& operator=(const PrintInGDIplusWin2LN&& other) = delete;
	~PrintInGDIplusWin2LN() noexcept; 

	void addPrintContent(const int& , const int& , const int& , const int& ,
		const int& , const int& , const int& );
	
};
