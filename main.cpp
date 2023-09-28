#pragma once
#include "PrecompiledHeadersEdges.h"
#include "simpleWindowUserInterface.h"
#include "callBackLinks.h"
#include "trafficSimulator.h"
#include "trafficSimulatorWithSimpleUserInterface.h"
#include "callBackFunctions.h"

#define MY_BUTTON_ID 38
#define MY_RKLICK_ID 37
#define START_SIMULATION 41
#define MY_BUTTON_1 42
#define MY_BUTTON_2 43
#define MY_BUTTON_3 44
#define ESTVertexOfGraph 45
#define MY_BUTTON_YES 46
#define MY_BUTTON_NO 47
#define createSecondWindow 101
#define INT int

static HDC hdc;
trafficSimulatorWithSimpleUserInterface ts(hdc);

enum numberOFLanes { one = 1, two = 2 };

const int width = 1200;
const int height = 700;
bool window1closed = false;
bool window2closed = false;
bool StartSimulation = false;
using namespace Gdiplus;
LRESULT CALLBACK WindowProc(HWND g_windowHandle, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WindowProc2(HWND g_windowHandle2, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WindowProc3(HWND g_windowHandle3, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WindowProc4(HWND g_windowHandle3, UINT message, WPARAM wParam, LPARAM lParam);
LPCWSTR Questiontext1 = L"Wie viele Fahrstreifen                                ";
LPCWSTR Questiontext2 = L"soll diese Fahrbahn haben?                            ";
LPCWSTR Questiontext3 = L"1 oder 2?                                             ";
LPCWSTR Questiontext4 = L"Soll der Verkehr über alle oder über die              ";
LPCWSTR Questiontext5 = L"schnellsten Routen zwischen den Start- und End-       ";
LPCWSTR Questiontext6 = L"punkten erzeugt werden?                               ";
LPCWSTR Questiontext7 = L"Soll die Simulation fortgesetzt werden?                                      ";
HINSTANCE g_hInstance = nullptr;
WNDCLASSEX subWindowClass;
WNDCLASSEX thirdWindowClass;
WNDCLASSEX fourthWindowClass;
HWND  g_windowHandle = nullptr;
HWND g_windowHandle2 = nullptr;
HWND g_windowHandle3 = nullptr;
HWND g_windowHandle4 = nullptr;
HWND hDlg = nullptr;
RECT Rechteck = { (long)0, (long)0, (long)width, (long)height };


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	MSG msg;
	bool mainProgramLoopFlag = true;
	PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE);
	
	WNDCLASSEX windowClass;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	g_hInstance = hInstance;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.hInstance = hInstance;
	windowClass.hCursor = LoadCursor(NULL, IDC_CROSS);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = (LPCSTR)L"WindowClass";


	RegisterClassEx(&windowClass);	//Übergabes des Styles

	if (g_windowHandle == nullptr) {
		DWORD errVal = GetLastError();
	}

	HWND g_windowHandle = CreateWindowEx(
		NULL,
		(LPCSTR)L"WindowClass",//muss gleich sein mit windowClass.lpszClassName = (LPCSTR)L"WindowClass";	
		(LPCSTR)L"Simulationsfeld.h",
		WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_SYSMENU,
		10,
		10,
		width,
		height,
		NULL,
		NULL,
		hInstance,
		NULL);
	//^^^^^^^^^^^^Das ist das Hauptfenster!!!*************************************************
	
	ZeroMemory(&subWindowClass, sizeof(WNDCLASSEX));
	subWindowClass.cbClsExtra = NULL;
	subWindowClass.cbSize = sizeof(WNDCLASSEX);
	subWindowClass.cbWndExtra = NULL;
	subWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	subWindowClass.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	subWindowClass.lpfnWndProc = (WNDPROC)WindowProc2;
	subWindowClass.hInstance = hInstance;			
	subWindowClass.hIcon = NULL;
	subWindowClass.hIconSm = NULL;
	subWindowClass.lpszMenuName = NULL;
	subWindowClass.lpszClassName = (LPCSTR)L"SubWindowClass";

	RegisterClassEx(&subWindowClass);

	ZeroMemory(&thirdWindowClass, sizeof(WNDCLASSEX));
	thirdWindowClass.cbClsExtra = NULL;
	thirdWindowClass.cbSize = sizeof(WNDCLASSEX);
	thirdWindowClass.cbWndExtra = NULL;
	thirdWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	thirdWindowClass.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	thirdWindowClass.lpfnWndProc = (WNDPROC)WindowProc3;
	thirdWindowClass.hInstance = hInstance;
	thirdWindowClass.hIcon = NULL;
	thirdWindowClass.hIconSm = NULL;
	thirdWindowClass.lpszMenuName = NULL;
	thirdWindowClass.lpszClassName = (LPCSTR)L"ThirdWindowClass";

	RegisterClassEx(&thirdWindowClass);

	ZeroMemory(&fourthWindowClass, sizeof(WNDCLASSEX));
	fourthWindowClass.cbClsExtra = NULL;
	fourthWindowClass.cbSize = sizeof(WNDCLASSEX);
	fourthWindowClass.cbWndExtra = NULL;
	fourthWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	fourthWindowClass.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	fourthWindowClass.lpfnWndProc = (WNDPROC)WindowProc4;
	fourthWindowClass.hInstance = hInstance;
	fourthWindowClass.hIcon = NULL;
	fourthWindowClass.hIconSm = NULL;
	fourthWindowClass.lpszMenuName = NULL;
	fourthWindowClass.lpszClassName = (LPCSTR)L"FourthWindowClass";

	RegisterClassEx(&fourthWindowClass);

	CreateWindowExW(NULL, L"BUTTON", L"Start", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		width - 100,
		height - 100,
		100,
		50, g_windowHandle,
		(HMENU)MY_BUTTON_ID,
		(HINSTANCE)GetWindowLong(g_windowHandle, GWL_HINSTANCE),
		NULL);


	ts.n->m_CBLptr->m_hdc = hdc;
	ts.width = width;
	ts.height = height;
	//***************************************************************
	//"Program surfaces loop" respectively  "Program interfaces loop" 
	while (mainProgramLoopFlag) {
	
		PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE);

		TranslateMessage(&msg);
		DispatchMessage(&msg);
		
		switch (ts.mainInterfaceFunction()) {
		case 0:
			break;
		case 1:
			ts.n->m_CBLptr->m_f3PaintFrame(hdc, height, width);
			break;
		
		case 2:
		{
			ts.m_programStatus = false;
			PAINTSTRUCT ps_s;
			HDC hdc_s = BeginPaint(g_windowHandle4, &ps_s);
			g_windowHandle4 = CreateWindowEx(
				NULL,
				(LPCSTR)L"FourthWindowClass",
				(LPCSTR)L"Bestimmung ",
				WS_VISIBLE | WS_CHILDWINDOW | WS_SYSMENU | WS_CHILD,
				10,
				150,
				1200,
				550,
				g_windowHandle,
				(HMENU)createSecondWindow,
				(HINSTANCE)GetWindowLong(g_windowHandle, GWL_HINSTANCE),
				NULL);
			CreateWindowExW(NULL, L"BUTTON", L"JA", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
				80,
				160,
				35,
				35, g_windowHandle4,
				(HMENU)MY_BUTTON_YES,
				(HINSTANCE)GetWindowLong(g_windowHandle4, GWL_HINSTANCE),
				NULL);
			CreateWindowExW(NULL, L"BUTTON", L"Nein", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
				120,
				160,
				35,
				35, g_windowHandle4,
				(HMENU)MY_BUTTON_NO,
				(HINSTANCE)GetWindowLong(g_windowHandle4, GWL_HINSTANCE),
				NULL);
			break;
		}
		case 3:
			window1closed = true;
			break;
		}
		if (window1closed) {
			mainProgramLoopFlag=false;
			ts.n->m_networkDataStructure.appliedGraph.clear();
			ts.n->destroy();
			ts.n = nullptr;
		}
	}
	//***************************************************************
	GdiplusShutdown(gdiplusToken);
	return msg.wParam;
}
LRESULT CALLBACK WindowProc(HWND g_windowHandle, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	
	switch (uMsg) {
	case WM_CHAR:
		if (wParam == 0x31) {// Code for CHAR digit 1
			numberOFLanes::one;
			ts.m_determinationVariableOfNumberOfLanes = 1;
			SendMessage(g_windowHandle2, WM_CLOSE, NULL, NULL);
		}
		if (wParam == 0x32) {// Code for CHAR digit 2
			numberOFLanes::two;
			ts.m_determinationVariableOfNumberOfLanes = 2;
			SendMessage(g_windowHandle2, WM_CLOSE, NULL, NULL);
		}
		break;
	case WM_LBUTTONDOWN:
	{
		int param1 = LOWORD(lParam);
		int param2 = HIWORD(lParam);
		while (true) {
			if ((param1 % 10) == 0)
				break;
			param1--;
		}
		while (true) {
			if ((param2 % 10) == 0)
				break;
			param2--;
		}
		ts.leftClick(param1,param2);
		if (ts.m_programStatus == false) {
			InvalidateRect(g_windowHandle, &Rechteck, TRUE); // Set square!
			SendMessage(g_windowHandle, WM_PAINT, wParam, lParam);
		}
		break;
	}
	case WM_RBUTTONDOWN:
	{
		int param1 = LOWORD(lParam);
		int param2 = HIWORD(lParam);
		while (true) {
			if ((param1 % 10) == 0)
				break;
			param1--;
		}
		while (true) {
			if ((param2 % 10) == 0)
				break;
			param2--;
		}
		ts.rightClick(param1, param2);
		InvalidateRect(g_windowHandle, &Rechteck, TRUE);//Set square!
		SendMessage(g_windowHandle, WM_PAINT, wParam, lParam);
		break;
	}
	case WM_COMMAND:
		InvalidateRect(g_windowHandle, &Rechteck, TRUE);
		SendMessage(g_windowHandle, WM_PAINT, wParam, 0);
		break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		switch (wParam) {
		
		case MK_LBUTTON:
			hdc = BeginPaint(g_windowHandle, &ps);
			ts.n->m_CBLptr->m_hdc = hdc;
			if (ts.queryOnTheSelectedNumberOfLanes()) {
				numberOFLanes::one;
				ts.m_determinationVariableOfNumberOfLanes = 1;
				SendMessage(g_windowHandle, WM_CREATE, 0, 0);
			}
			else {
				SendMessage(g_windowHandle2, WM_CLOSE, NULL, NULL);
			}
			for (auto& i : ts.n->m_networkCreationFunctions.networkLaneVector) {
				//ts.n->m_CBLptr->m_f18PrintLaneIF(hdc, std::get<0>(i).first, std::get<0>(i).second, std::get<1>(i).first, std::get<1>(i).second);
				PrintLaneIF(hdc, std::get<0>(i).first, std::get<0>(i).second, std::get<1>(i).first, std::get<1>(i).second);
			}
			ts.n->m_CBLptr->m_hdc = hdc;
			//ts.n->m_CBLptr->m_f2PaintBoxRB(hdc, ts.n->iPosXLK, ts.n->iPosYLK, ts.n->iPosXRK, ts.n->iPosYRK);
			//ts.n->m_CBLptr->m_f1PaintBoxLB(hdc, ts.n->iPosXLK, ts.n->iPosYLK, ts.n->iPosXRK, ts.n->iPosYRK);
			PaintBoxRB(hdc, ts.n->iPosXLK, ts.n->iPosYLK, ts.n->iPosXRK, ts.n->iPosYRK);
			PaintBoxLB(hdc, ts.n->iPosXLK, ts.n->iPosYLK, ts.n->iPosXRK, ts.n->iPosYRK);
			PaintFrame(hdc, height, width);
			EndPaint(g_windowHandle, &ps);
			ts.clickPointsResetInTheField();

			break;
		case MK_RBUTTON:
			hdc = BeginPaint(g_windowHandle, &ps);
			ts.n->m_CBLptr->m_hdc = hdc;
			//ts.n->m_CBLptr->m_f2PaintBoxRB(hdc, ts.n->iPosXLK, ts.n->iPosYLK, ts.n->iPosXRK, ts.n->iPosYRK);
			//ts.n->m_CBLptr->m_f1PaintBoxLB(hdc, ts.n->iPosXLK, ts.n->iPosYLK, ts.n->iPosXRK, ts.n->iPosYRK);
			PaintBoxRB(hdc, ts.n->iPosXLK, ts.n->iPosYLK, ts.n->iPosXRK, ts.n->iPosYRK);
			PaintBoxLB(hdc, ts.n->iPosXLK, ts.n->iPosYLK, ts.n->iPosXRK, ts.n->iPosYRK);
			EndPaint(g_windowHandle, &ps);
			break;

		case MY_BUTTON_ID:
			hdc = BeginPaint(g_windowHandle, &ps);
			ts.n->m_CBLptr->m_hdc = hdc;
			if (ts.m_programStatus == false) {
				ts.m_determinationVariableOfNumberOfLanes= 2;
				g_windowHandle3 = CreateWindowEx(
					NULL,
					(LPCSTR)L"ThirdWindowClass",
					(LPCSTR)L"Bestimmung ",
					WS_VISIBLE | WS_CHILDWINDOW | WS_SYSMENU | WS_CHILD,
					150,
					150,
					500,
					350,
					g_windowHandle,
					(HMENU)createSecondWindow,
					(HINSTANCE)GetWindowLong(g_windowHandle, GWL_HINSTANCE),
					NULL);
				CreateWindowExW(NULL, L"BUTTON", L"gleichverteilung über alle Routen", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON | BS_LEFTTEXT,
					80,
					80,
					300,
					20, g_windowHandle3,
					(HMENU)MY_BUTTON_1,
					(HINSTANCE)GetWindowLong(g_windowHandle3, GWL_HINSTANCE),
					NULL);

				CreateWindowExW(NULL, L"BUTTON", L"auf schnelle Routen", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON | BS_LEFTTEXT,
					80,
					110,
					300,
					20, g_windowHandle3,
					(HMENU)MY_BUTTON_2,
					(HINSTANCE)GetWindowLong(g_windowHandle3, GWL_HINSTANCE),
					NULL);
				CreateWindowExW(NULL, L"BUTTON", L"OK", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
					80,
					160,
					30,
					30, g_windowHandle3,
					(HMENU)MY_BUTTON_3,
					(HINSTANCE)GetWindowLong(g_windowHandle3, GWL_HINSTANCE),
					NULL);
				
				ts.clickPointsResetInTheField();
				ts.n->displayNetworkWithSimulationStepResult();
				ts.n->m_networkDataStructure.printLanesAndVehiclesOfAllEdges();
			}

			break;
			
			
		case ESTVertexOfGraph:
			if (ts.n->generationOfTheNetworkGraphsFromNetworkLanes(ts.m_determinationVariableOfNumberOfLanes)) {
				ts.clickPointsResetInTheField();
				ts.n->displayNetworkWithSimulationStepResult();
				ts.n->m_networkDataStructure.printLanesAndVehiclesOfAllEdges();
				ts.m_programStatus = true;
				StartSimulation = false;
			}
		default:
			hdc = BeginPaint(g_windowHandle, &ps);	
			ts.n->m_CBLptr->m_hdc = hdc;
			ts.clickPointsResetInTheField();
			//ts.n->m_CBLptr->m_f2PaintBoxRB(hdc, ts.n->iPosXLK, ts.n->iPosYLK, ts.n->iPosXRK, ts.n->iPosYRK);
			//ts.n->m_CBLptr->m_f1PaintBoxLB(hdc, ts.n->iPosXLK, ts.n->iPosYLK, ts.n->iPosXRK, ts.n->iPosYRK);
			//ts.n->m_CBLptr->m_f3PaintFrame(hdc, height, width);

			PaintBoxRB(hdc, ts.n->iPosXLK, ts.n->iPosYLK, ts.n->iPosXRK, ts.n->iPosYRK);
			PaintBoxLB(hdc, ts.n->iPosXLK, ts.n->iPosYLK, ts.n->iPosXRK, ts.n->iPosYRK);
			PaintFrame(hdc, height, width);
			EndPaint(g_windowHandle, &ps);
			break;
		}
		return 0;
	}
	
	case WM_CREATE:
	{
		
			g_windowHandle2 = CreateWindowEx(
			NULL,
			(LPCSTR)L"SubWindowClass",	
			(LPCSTR)L"Ermittlung der Fahrstreifenanzahl",
			WS_VISIBLE  | WS_CHILDWINDOW/*WS_OVERLAPPEDWINDOW */ | WS_SYSMENU | WS_CHILD,
			150,
			150,
			500,
			320,
			g_windowHandle,
			(HMENU)createSecondWindow,
			(HINSTANCE)GetWindowLong(g_windowHandle, GWL_HINSTANCE),
			NULL);
		CreateWindowExW(NULL, L"BUTTON", L"1", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			80,
			80,
			20,
			20, g_windowHandle2,
			(HMENU)MY_BUTTON_1,
			(HINSTANCE)GetWindowLong(g_windowHandle2, GWL_HINSTANCE),
			NULL);

		CreateWindowExW(NULL, L"BUTTON", L"2", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			110,
			80,
			20,
			20, g_windowHandle2,
			(HMENU)MY_BUTTON_2,
			(HINSTANCE)GetWindowLong(g_windowHandle2, GWL_HINSTANCE),
			NULL);
	}
		break;
	case WM_CLOSE:
		
		PostQuitMessage(0);
		window1closed = true;

		break;
	default:
		if (StartSimulation)
			SendMessage(g_windowHandle,WM_PAINT, ESTVertexOfGraph, NULL);
		break;
	}
	return DefWindowProcW(g_windowHandle, uMsg, wParam, lParam);
}

LRESULT CALLBACK WindowProc2(HWND g_windowHandle2, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps_s;
		HDC hdc_s = BeginPaint(g_windowHandle2, &ps_s);
		TextOut(hdc_s, 10, 10, (LPCSTR)Questiontext1, wcslen(Questiontext1));
		TextOut(hdc_s, 10, 30, (LPCSTR)Questiontext2, wcslen(Questiontext2));
		TextOut(hdc_s, 10, 50, (LPCSTR)Questiontext3, wcslen(Questiontext3));
		numberOFLanes::one;
		EndPaint(g_windowHandle2, &ps_s);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case MY_BUTTON_1:
			numberOFLanes::one;
			ts.m_determinationVariableOfNumberOfLanes = 1;
			SendMessage(g_windowHandle2, WM_CLOSE, NULL, NULL);
			for (auto& i : ts.n->m_networkCreationFunctions.networkLaneVector) {
				//ts.n->m_CBLptr->m_f18PrintLaneIF(hdc, std::get<0>(i).first, std::get<0>(i).second, std::get<1>(i).first, std::get<1>(i).second);
				PrintLaneIF(hdc, std::get<0>(i).first, std::get<0>(i).second, std::get<1>(i).first, std::get<1>(i).second);
				//ts.n->m_CBLptr->m_f5PaintLane(hdc, std::get<0>(i).first, std::get<0>(i).second, std::get<1>(i).first, std::get<1>(i).second);
			}
			break;
		case MY_BUTTON_2:
			numberOFLanes::two;
			ts.m_determinationVariableOfNumberOfLanes = 2;
			SendMessage(g_windowHandle2, WM_CLOSE, NULL, NULL);
			for (auto& i : ts.n->m_networkCreationFunctions.networkLaneVector) {
				//ts.n->m_CBLptr->m_f18PrintLaneIF(hdc, std::get<0>(i).first, std::get<0>(i).second, std::get<1>(i).first, std::get<1>(i).second);
				PrintLaneIF(hdc, std::get<0>(i).first, std::get<0>(i).second, std::get<1>(i).first, std::get<1>(i).second);
			}
			break;
		default:
			break;
		}
	
	default:
		numberOFLanes::one;
		break;
	}
	return DefWindowProcW(g_windowHandle2, message, wParam, lParam);
}

LRESULT CALLBACK WindowProc3(HWND g_windowHandle3, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CLOSE:
		StartSimulation = true;
		PostQuitMessage(0);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps_s;
		HDC hdc_s = BeginPaint(g_windowHandle3, &ps_s);
		TextOut(hdc_s, 10, 10, (LPCSTR)Questiontext4, wcslen(Questiontext4));
		TextOut(hdc_s, 10, 30, (LPCSTR)Questiontext5, wcslen(Questiontext5));
		TextOut(hdc_s, 10, 50, (LPCSTR)Questiontext6, wcslen(Questiontext6));
		numberOFLanes::one;
		EndPaint(g_windowHandle3, &ps_s);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case MY_BUTTON_1:
			ts.m_determinationVariableOfNumberOfLanes = 1;
			SendDlgItemMessage(g_windowHandle3, MY_BUTTON_1, BM_SETCHECK, 1, 0);
			SendDlgItemMessage(g_windowHandle3, MY_BUTTON_2, BM_SETCHECK, 0, 1);
			break;
		case MY_BUTTON_2:
			ts.m_determinationVariableOfNumberOfLanes = 2;
			SendDlgItemMessage(g_windowHandle3, MY_BUTTON_2, BM_SETCHECK, 1, 0);
			SendDlgItemMessage(g_windowHandle3, MY_BUTTON_1, BM_SETCHECK, 0, 1);
			break;
		case MY_BUTTON_3:
			SendMessage(g_windowHandle3, WM_CLOSE, NULL, NULL);
			break;
		}
	}
	return DefWindowProcW(g_windowHandle3, message, wParam, lParam);
}
LRESULT CALLBACK WindowProc4(HWND g_windowHandle4, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CLOSE:
		
		PostQuitMessage(0);
		if (ts.m_currentSimulationStep == 0) {
			window1closed = true;
		}
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps_s;
		HDC hdc_s = BeginPaint(g_windowHandle4, &ps_s);
		TextOut(hdc_s, 10, 10, (LPCSTR)Questiontext7, wcslen(Questiontext7));
		ts.clickPointsResetInTheField();
		EndPaint(g_windowHandle4, &ps_s);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case MY_BUTTON_YES:
			ts.m_programStatus = true;
			ts.m_currentSimulationStep = 1000;
			SendMessage(g_windowHandle4, WM_CLOSE, NULL, NULL);
			break;
		case MY_BUTTON_NO:
			ts.m_programStatus = false;
			ts.m_currentSimulationStep = 0;
			ts.n->m_networkDataStructure.appliedGraph.clear();
			SendMessage(g_windowHandle4, WM_CLOSE, NULL, NULL);
			break;
		
		}
	}
	return DefWindowProcW(g_windowHandle4, message, wParam, lParam);
}