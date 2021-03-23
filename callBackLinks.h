#pragma once
#include "PrecompiledHeadersEdges.h"

class callBackLinks {
private:
	
public:
	void(*m_f10PaintBox)(HDC hdc, const int &param1, const int &param2, const int &param3, const int &param4)=nullptr;
	void(*m_f11PaintWhiteLine)(HDC hdc, const int &param1, const int &param2, const int &param3, const int &param4, const int &param5)=nullptr;
	HDC m_hdc;
	callBackLinks::callBackLinks() {

	}
	
	callBackLinks::~callBackLinks() {

	}	
};
