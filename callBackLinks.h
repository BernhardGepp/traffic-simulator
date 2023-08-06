#pragma once
#include "PrecompiledHeadersEdges.h"

class callBackLinks {
private:
public:
	void(*m_f1PaintBoxLB)(HDC hdc)=nullptr;
	void(*m_f2PaintBoxRB)(HDC hdc)=nullptr;
	void(*m_f3PaintFrame)(HDC hdc)=nullptr;
	void(*m_f5PaintLane)(HDC hdc, const int& iPosXLk, const int& iPosYLk, const int& iPosXRk, const int& iPosYRk, const bool& HorV, const int& numberOfLanesa, const std::vector<std::tuple<int, int, int>>& PointsToBePrinted)=nullptr;
	void(*m_f7PrintVertexNumber)(HDC hdc, const int& iPosX, const int& iPosY, const int& iVertexID)=nullptr;
	void(*m_f10PaintBox)(HDC hdc, const int &param1, const int &param2, const int &param3, const int &param4, const bool &param5)=nullptr;
	void(*m_f11PaintWhiteLine)(HDC hdc, const int &param1, const int &param2, const int &param3, const int &param4, const int &param5)=nullptr;
	void(*m_f12PaintBoxStart)(HDC hdc, const int& x, const int& y)=nullptr;
	void(*m_f13PaintBoxEnd)(HDC hdc, const int& x, const int& y)=nullptr; 
	void(*m_f14PaintBoxFlex11)(HDC hdc, const int& x, const int& y) = nullptr;
	void(*m_f15PaintBoxFlex12)(HDC hdc, const int& x, const int& y) = nullptr;
	void(*m_f16PaintBoxFlex21)(HDC hdc, const int& x, const int& y) = nullptr;
	void(*m_f17PaintBoxFlex22)(HDC hdc, const int& x, const int& y) = nullptr;
	int(*m_callback_getRandomNumber)() = nullptr;
	HDC m_hdc=0;

	//callBackLinks::callBackLinks() {}
	callBackLinks::callBackLinks(const HDC& hdc,
		void(*f1PaintBoxLB)(HDC hdc),
		void(*f2PaintBoxRB)(HDC hdc), 
		void(*f3PaintFrame)(HDC hdc),
		void(*f5PaintLane)(HDC hdc, const int& iPosXLk, const int& iPosYLk, const int& iPosXRk, const int& iPosYRk, const bool& HorV, const int& numberOfLanes, const std::vector<std::tuple<int, int, int>>& PointsToBePrinted),
		void(*f7PrintVertexNumber)(HDC hdc, const int& iPosX, const int& iPosY, const int& iVertexID),
		void(*f10PaintBox)(HDC hdc, const int& param1, const int& param2, const int& param3, const int& param4, const bool& param5),
		void(*f11PaintWhiteLine)(HDC hdc, const int& param1, const int& param2, const int& param3, const int& param4, const int& param5),
		//void(*f12PaintBoxStart)(HDC hdc, const int& x, const int& y),
		void(*f13PaintBoxEnd)(HDC hdc, const int& x, const int& y),
		void(*f14PaintBoxFlex11)(HDC hdc, const int& x, const int& y),
		void(*f15PaintBoxFlex12)(HDC hdc, const int& x, const int& y),
		void(*f16PaintBoxFlex21)(HDC hdc, const int& x, const int& y),
		void(*f17PaintBoxFlex22)(HDC hdc, const int& x, const int& y)
	) noexcept :m_hdc(hdc), m_f1PaintBoxLB(f1PaintBoxLB), m_f2PaintBoxRB(f2PaintBoxRB), m_f3PaintFrame(f3PaintFrame), m_f5PaintLane(f5PaintLane),
		m_f7PrintVertexNumber(f7PrintVertexNumber), m_f10PaintBox(f10PaintBox), m_f11PaintWhiteLine(f11PaintWhiteLine)/*, m_f12PaintBoxStart(f12PaintBoxStart)*/, m_f13PaintBoxEnd(f13PaintBoxEnd),
		m_f14PaintBoxFlex11(f14PaintBoxFlex11),m_f15PaintBoxFlex12(f15PaintBoxFlex12),m_f16PaintBoxFlex21(f16PaintBoxFlex21),m_f17PaintBoxFlex22(f17PaintBoxFlex22)
	{

	}
	callBackLinks::callBackLinks(const callBackLinks& other)noexcept {
		m_f1PaintBoxLB = other.m_f1PaintBoxLB;
		m_f2PaintBoxRB = other.m_f2PaintBoxRB;
		m_f3PaintFrame = other.m_f3PaintFrame;
		m_f5PaintLane = other.m_f5PaintLane;
		m_f7PrintVertexNumber = other.m_f7PrintVertexNumber;
		m_f10PaintBox = other.m_f10PaintBox;
		m_f11PaintWhiteLine = other.m_f11PaintWhiteLine;
		//m_f12PaintBoxStart = other.m_f12PaintBoxStart;
		m_f13PaintBoxEnd = other.m_f13PaintBoxEnd;
		m_f14PaintBoxFlex11 = other.m_f14PaintBoxFlex11;
		m_f15PaintBoxFlex12 = other.m_f15PaintBoxFlex12;
		m_f16PaintBoxFlex21 = other.m_f16PaintBoxFlex21;
		m_f17PaintBoxFlex22 = other.m_f17PaintBoxFlex22;
		m_callback_getRandomNumber = other.m_callback_getRandomNumber;
		m_hdc = other.m_hdc;
	}
	callBackLinks::callBackLinks(const callBackLinks&& other) noexcept {
		m_f1PaintBoxLB = other.m_f1PaintBoxLB;
		m_f2PaintBoxRB = other.m_f2PaintBoxRB;
		m_f3PaintFrame = other.m_f3PaintFrame;
		m_f5PaintLane = other.m_f5PaintLane;
		m_f7PrintVertexNumber = other.m_f7PrintVertexNumber;
		m_f10PaintBox = other.m_f10PaintBox;
		m_f11PaintWhiteLine = other.m_f11PaintWhiteLine;
		//m_f12PaintBoxStart = other.m_f12PaintBoxStart;
		m_f13PaintBoxEnd = other.m_f13PaintBoxEnd;
		m_f14PaintBoxFlex11 = other.m_f14PaintBoxFlex11;
		m_f15PaintBoxFlex12 = other.m_f15PaintBoxFlex12;
		m_f16PaintBoxFlex21 = other.m_f16PaintBoxFlex21;
		m_f17PaintBoxFlex22 = other.m_f17PaintBoxFlex22;
		m_callback_getRandomNumber = other.m_callback_getRandomNumber;
		m_hdc = other.m_hdc;
	}
	callBackLinks& operator=(const callBackLinks& other)noexcept {
		if (&other == this) {
			return *this;
		}
		m_f1PaintBoxLB = other.m_f1PaintBoxLB;
		m_f2PaintBoxRB = other.m_f2PaintBoxRB;
		m_f3PaintFrame = other.m_f3PaintFrame;
		m_f5PaintLane = other.m_f5PaintLane;
		m_f7PrintVertexNumber = other.m_f7PrintVertexNumber;
		m_f10PaintBox = other.m_f10PaintBox;
		m_f11PaintWhiteLine = other.m_f11PaintWhiteLine;
		//m_f12PaintBoxStart = other.m_f12PaintBoxStart;
		m_f13PaintBoxEnd = other.m_f13PaintBoxEnd;
		m_f14PaintBoxFlex11 = other.m_f14PaintBoxFlex11;
		m_f15PaintBoxFlex12 = other.m_f15PaintBoxFlex12;
		m_f16PaintBoxFlex21 = other.m_f16PaintBoxFlex21;
		m_f17PaintBoxFlex22 = other.m_f17PaintBoxFlex22;
		m_callback_getRandomNumber = other.m_callback_getRandomNumber;
		m_hdc = other.m_hdc;
		return *this;
	}
	callBackLinks& operator=(const callBackLinks&& other) noexcept {
		if (&other == this) {
			return *this;
		}
		m_f1PaintBoxLB = other.m_f1PaintBoxLB;
		m_f2PaintBoxRB = other.m_f2PaintBoxRB;
		m_f3PaintFrame = other.m_f3PaintFrame;
		m_f5PaintLane = other.m_f5PaintLane;
		m_f7PrintVertexNumber = other.m_f7PrintVertexNumber;
		m_f10PaintBox = other.m_f10PaintBox;
		m_f11PaintWhiteLine = other.m_f11PaintWhiteLine;
		//m_f12PaintBoxStart = other.m_f12PaintBoxStart;
		m_f13PaintBoxEnd = other.m_f13PaintBoxEnd;
		m_f14PaintBoxFlex11 = other.m_f14PaintBoxFlex11;
		m_f15PaintBoxFlex12 = other.m_f15PaintBoxFlex12;
		m_f16PaintBoxFlex21 = other.m_f16PaintBoxFlex21;
		m_f17PaintBoxFlex22 = other.m_f17PaintBoxFlex22;
		m_callback_getRandomNumber = other.m_callback_getRandomNumber;
		m_hdc = other.m_hdc;
		return *this;
	}
	callBackLinks::~callBackLinks() noexcept {	}

	auto topLevelFunctionPTR_f1PaintBoxLB() {
		return m_f1PaintBoxLB(m_hdc);
	}
	auto topLevelFunctionPTR_f2PaintBoxRB() {
		return m_f2PaintBoxRB(m_hdc);
	}
	auto topLevelFunctionPTR_f3PaintFrame() {
		return m_f3PaintFrame(m_hdc);
	}
	auto topLevelFunctionPTR_f5PaintLane(const int& iPosXLk, const int& iPosYLk, const int& iPosXRk, const int& iPosYRk, const bool& HorV, const int& numberOfLanesa, const std::vector<std::tuple<int, int, int>>& PointsToBePrinted) {
		return m_f5PaintLane(m_hdc, iPosXLk, iPosYLk, iPosXRk, iPosYRk, HorV, numberOfLanesa, PointsToBePrinted);
	}
	auto topLevelFunctionPTR_f7PrintVertexNumber(const int& iPosX, const int& iPosY, const int& iVertexID) {
		return m_f7PrintVertexNumber(m_hdc, iPosX, iPosY, iVertexID);
	}
	auto topLevelFunctionPTR_f10PaintBox(int param1, int param2, int param3, int param4, bool param5) {
		return m_f10PaintBox(m_hdc, param1, param2, param3, param4, param5);
	}
	auto topLevelFunctionPTR_f11PaintWhiteLine(const int& param1, const int& param2, const int& param3, const int& param4, const int& param5) {
		return m_f11PaintWhiteLine(m_hdc, param1, param2, param3, param4, param5);
	}
	auto topLevelFunctionPTR_f12PaintBoxStart(const int& x, const int& y) {
		return m_f12PaintBoxStart(m_hdc, x,y);
	}
	auto topLevelFunctionPTR_f13PaintBoxEnd(const int& x, const int& y) {
		return m_f13PaintBoxEnd(m_hdc, x, y);
	}
	auto topLevelFunctionPTR_f14PaintBoxFlex11(const int& x, const int& y) {
		return m_f14PaintBoxFlex11(m_hdc, x, y);
	}
	auto topLevelFunctionPTR_f15PaintBoxFlex12(const int& x, const int& y) {
		return m_f15PaintBoxFlex12(m_hdc, x, y);
	}
	auto topLevelFunctionPTR_f16PaintBoxFlex21(const int& x, const int& y) {
		return m_f16PaintBoxFlex21(m_hdc, x, y);
	}
	auto topLevelFunctionPTR_f17PaintBoxFlex22(const int& x, const int& y) {
		return m_f17PaintBoxFlex22(m_hdc, x, y);
	}
};
