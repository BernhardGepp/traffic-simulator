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

simpleWindowUserInterface* n = nullptr;
simpleWindowUserInterface* simpleWindowUserInterface::instance = 0;


enum numberOFLanes { one = 1, two = 2 };
int simulationIteration =100;
const int width = 1200;
const int height = 700;
int numberOfLanesINT = 1;
bool window1closed = false;
bool window2closed = false;
bool actionQueueBool = false;
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


VOID PaintBoxLB(HDC hdc) {
	Graphics graphics1(hdc);
	Pen	pen2(Gdiplus::Color(255, 255, 0, 255), 10.0F);
	TextOutW(hdc, n->iPosXLK + 10, n->iPosYLK + 10, L"P1", wcslen(L"P1 "));
	graphics1.DrawLine(&pen2, n->iPosXLK, n->iPosYLK + 5, n->iPosXLK + 10, n->iPosYLK + 5);

}
VOID PaintBoxRB(HDC hdc) {
	Graphics graphics3(hdc);
	Pen	pen3(Gdiplus::Color(255, 255, 0, 255), 10.0F);
	TextOutW(hdc, n->iPosXRK + 10, n->iPosYRK + 10, L"P2", wcslen(L"P2 "));
	graphics3.DrawLine(&pen3, n->iPosXRK, n->iPosYRK + 5, n->iPosXRK + 10, n->iPosYRK + 5);
}
/*VOID PaintBoxStart(HDC hdc, const int& x, const int& y) {
	Graphics graphics3(hdc);
	Pen	pen3(Gdiplus::Color(245, 0, 125, 125), 10.0F);//greenBox
	graphics3.DrawLine(&pen3, x, y + 5, x + 10, y + 5);
}*/

VOID PaintFrame(HDC hdc) {
	Graphics graphicsFR(hdc);
	Pen	penFR(Gdiplus::Color(255, 0, 0, 255), 2);
	graphicsFR.DrawLine(&penFR, 0, 0, 0, height - 100);
	graphicsFR.DrawLine(&penFR, 0, 0, width - 100, 0);
	graphicsFR.DrawLine(&penFR, 0, height - 100, width - 100, height - 100);
	graphicsFR.DrawLine(&penFR, width - 100, 0, width - 100, height - 100);
}

VOID PrintVertexNumber(HDC hdc, const int &iPosX, const int &iPosY, const int &iVertexID) {
	wchar_t buffer1[256];
	wsprintfW(buffer1, L"%d", iVertexID);
	TextOutW(hdc,
		iPosX+25,
		iPosY+25,
		buffer1,
		wcslen(buffer1));
	Graphics graphics3(hdc);
	Pen	pen3(Gdiplus::Color(255, 255, 0, 255), 10.0F);
	graphics3.DrawLine(&pen3, n->iPosXRK, n->iPosYRK + 5, n->iPosXRK + 10, n->iPosYRK + 5);
}


static HDC hdc;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	trafficSimulatorWithSimpleUserInterface ts;
	n = simpleWindowUserInterface::getInstance(width, height, callBackLinks(hdc, PaintBoxLB, PaintBoxRB, PaintFrame, PaintLane, PrintVertexNumber, PaintBox, PaintWhiteLine,
		/*PaintBoxStart,*/ PaintBoxEnd, PaintBoxFex11, PaintBoxFex12, PaintBoxFex21, PaintBoxFex22));
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
	
	while (mainProgramLoopFlag) {
		PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE);

		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (actionQueueBool == true) {
			if (msg.message == WM_LBUTTONDOWN) {
				if (!n->m_networkDataStructure.appliedGraph.empty()) {
					if ((n->iPosXLK < width) && (n->iPosYLK < height)) {
						n->waitIfDubbleClick(n->iPosXLK, n->iPosYLK);
						n->m_cObSptr->benachrichtigen(n->iPosXLK, n->iPosYLK);
					}
				}
			}
			else {
				if (simulationIteration > 0) {
					simulationIteration--;
					PaintFrame(hdc);
					SendMessageCallback(g_windowHandle, WM_PAINT, START_SIMULATION, NULL, NULL, NULL);
				}
				else {
					actionQueueBool = false;
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
				}
			}
		}
		if (window1closed == true) {
			mainProgramLoopFlag=false;
			n->m_networkDataStructure.appliedGraph.clear();
			n->destroy();
			n = nullptr;
		}
	}
	GdiplusShutdown(gdiplusToken);
	return msg.wParam;
}
LRESULT CALLBACK WindowProc(HWND g_windowHandle, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	
	switch (uMsg) {
	case WM_CHAR:
		if (wParam == 0x31) {// Code for CHAR digit 1
			numberOFLanes::one;
			numberOfLanesINT = 1;
			SendMessage(g_windowHandle2, WM_CLOSE, NULL, NULL);
		}
		if (wParam == 0x32) {// Code for CHAR digit 2
			numberOFLanes::two;
			numberOfLanesINT = 2;
			SendMessage(g_windowHandle2, WM_CLOSE, NULL, NULL);
		}
		break;
	case WM_LBUTTONDOWN:
	{
		n->iPosXLK = LOWORD(lParam);
		n->iPosYLK = HIWORD(lParam);
		while (true) {
			if ((n->iPosXLK % 10) == 0)
				break;
			n->iPosXLK--;
		}
		if (n->iPosXLK > (width - 100))
			n->iPosXLK = (width - 110);
		while (true) {
			if ((n->iPosYLK % 10) == 0)
				break;
			n->iPosYLK--;
		}
		if (n->iPosYLK > (height - 100))
			n->iPosYLK = (height - 110);

		if (actionQueueBool == false) {
			InvalidateRect(g_windowHandle, &Rechteck, TRUE); // Set square!
			SendMessage(g_windowHandle, WM_PAINT, wParam, lParam);
		}
		break;
	}
	case WM_RBUTTONDOWN:
	{
		n->iPosXRK = LOWORD(lParam);
		n->iPosYRK = HIWORD(lParam);
		while (true) {
			if ((n->iPosXRK % 10) == 0)
				break;
			n->iPosXRK--;
		}
		if (n->iPosXRK > (width - 100))
			n->iPosXRK = (width - 100);
		while (true) {
			if ((n->iPosYRK % 10) == 0)
				break;
			n->iPosYRK--;
		}
		if (n->iPosYRK > (height - 100))
			n->iPosYRK = (height - 110);

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
		{
			
			hdc = BeginPaint(g_windowHandle, &ps);
			n->m_CBLptr->m_hdc = hdc;
			bool serviceBool = false;
			switch (numberOfLanesINT) {
			case 1:
				serviceBool = n->setClickPoints(hdc, 1);
				break;
			case 2:
				serviceBool = n->setClickPoints(hdc, 2);
				break;
			}
			if (serviceBool) {
				SendMessage(g_windowHandle2, WM_CLOSE, NULL, NULL);
			}
			else{
				numberOFLanes::one;
				numberOfLanesINT = 1;
				SendMessage(g_windowHandle, WM_CREATE, 0, 0);
			}
			
			for (auto &i : n->m_networkCreationFunctions.networkLaneVector) {
				PrintLaneIF(hdc, std::get<0>(i).first, std::get<0>(i).second, std::get<1>(i).first, std::get<1>(i).second);
			}
			PaintBoxRB(hdc);
			PaintBoxLB(hdc);
			EndPaint(g_windowHandle, &ps);
			
			n->clickPointsResetInTheField();
			
		}
			break;

		case MK_RBUTTON:
			hdc = BeginPaint(g_windowHandle, &ps);
			n->m_CBLptr->m_hdc = hdc;
			PaintBoxRB(hdc);
			PaintBoxLB(hdc);
			EndPaint(g_windowHandle, &ps);
			break;

		case MY_BUTTON_ID:
			hdc = BeginPaint(g_windowHandle, &ps);
			n->m_CBLptr->m_hdc = hdc;
			if ((actionQueueBool == false)/* && (reStartSimulation == false) * / /* && (!n->m_networkDataStructure.appliedGraph.empty()) */) {
				numberOfLanesINT = 2;
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
				
				n->clickPointsResetInTheField();
				n->displayNetworkWithSimulationStepResult();
				n->m_networkDataStructure.printLanesAndVehiclesOfAllEdges();
				
				//actionQueueBool = true;
			}

			break;
		

		case START_SIMULATION:
			if (n->m_networkDataStructure.appliedGraph.size() >= 1) {
				for (auto& i : n->m_networkDataStructure.appliedGraph) {
					i->simulation(simulationIteration);
				}
				if (n->m_networkDataStructure.appliedGraph[0]->m_vectorOfEdgesPtr.size() <= 6) {
					std::this_thread::sleep_for(std::chrono::milliseconds(250));
				}
				else {
					std::this_thread::sleep_for(std::chrono::milliseconds(260));
				}
				n->displayNetworkWithSimulationStepResult();
				n->m_networkDataStructure.printLanesAndVehiclesOfAllEdges();
			}
			else {
				window1closed = true;
			}
			break;
		case ESTVertexOfGraph:
			if (n->generationOfTheNetworkGraphsFromNetworkLanes(numberOfLanesINT)) {
				n->clickPointsResetInTheField();
				n->displayNetworkWithSimulationStepResult();
				n->m_networkDataStructure.printLanesAndVehiclesOfAllEdges();
				actionQueueBool = true;
				StartSimulation = false;
			}
		default:
			hdc = BeginPaint(g_windowHandle, &ps);	
			n->m_CBLptr->m_hdc = hdc;
			n->clickPointsResetInTheField();
			PaintBoxRB(hdc);
			PaintBoxLB(hdc);
			PaintFrame(hdc);
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
			numberOfLanesINT = 1;
			SendMessage(g_windowHandle2, WM_CLOSE, NULL, NULL);
			for (auto& i : n->m_networkCreationFunctions.networkLaneVector) {
				PrintLaneIF(hdc, std::get<0>(i).first, std::get<0>(i).second, std::get<1>(i).first, std::get<1>(i).second);
			}
			break;
		case MY_BUTTON_2:
			numberOFLanes::two;
			numberOfLanesINT = 2;
			SendMessage(g_windowHandle2, WM_CLOSE, NULL, NULL);
			for (auto& i : n->m_networkCreationFunctions.networkLaneVector) {
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
			numberOfLanesINT = 1;
			SendDlgItemMessage(g_windowHandle3, MY_BUTTON_1, BM_SETCHECK, 1, 0);
			SendDlgItemMessage(g_windowHandle3, MY_BUTTON_2, BM_SETCHECK, 0, 1);
			break;
		case MY_BUTTON_2:
			numberOfLanesINT = 2;
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
		if (simulationIteration == 0) {
			window1closed = true;
		}
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps_s;
		HDC hdc_s = BeginPaint(g_windowHandle4, &ps_s);
		TextOut(hdc_s, 10, 10, (LPCSTR)Questiontext7, wcslen(Questiontext7));
		n->clickPointsResetInTheField();
		EndPaint(g_windowHandle4, &ps_s);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case MY_BUTTON_YES:
			actionQueueBool = true;
			simulationIteration = 1000;
			SendMessage(g_windowHandle4, WM_CLOSE, NULL, NULL);
			break;
		case MY_BUTTON_NO:
			actionQueueBool = false;
			simulationIteration = 0;
			n->m_networkDataStructure.appliedGraph.clear();
			SendMessage(g_windowHandle4, WM_CLOSE, NULL, NULL);
			break;
		
		}
	}
	return DefWindowProcW(g_windowHandle4, message, wParam, lParam);
}