#pragma once
#include "PrecompiledHeadersEdges.h"
#include "simpleWindowUserInterface.h"
#include "callBackLinks.h"

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
VOID PaintBoxStart(HDC hdc,const int& x, const int& y) {
	Graphics graphics3(hdc);
	Pen	pen3(Gdiplus::Color(245, 0, 125, 125), 10.0F);//Grün
	graphics3.DrawLine(&pen3, x, y + 5, x + 10, y + 5);
}
VOID PaintBoxEnd(HDC hdc, const int& x, const int& y) {
	Graphics graphics3(hdc);
	Pen	pen3(Gdiplus::Color(255, 255, 0, 0), 10.0F);
	graphics3.DrawLine(&pen3, x, y + 5, x + 10, y + 5);
}
VOID PaintBoxFex11(HDC hdc, const int& x, const int& y) {
	Graphics graphics3(hdc);
	Pen	pen3(Gdiplus::Color(255, 255, 0, 255), 10.0F);
	graphics3.DrawLine(&pen3, x, y + 5, x + 10, y + 5);
}
VOID PaintBoxFex12(HDC hdc, const int& x, const int& y) {
	Graphics graphics3(hdc);
	Pen	pen3(Gdiplus::Color(255, 255, 0, 255), 10.0F);
	graphics3.DrawLine(&pen3, x, y + 5, x + 20, y + 5);
}
VOID PaintBoxFex21(HDC hdc, const int& x, const int& y) {
	Graphics graphics3(hdc);
	Pen	pen3(Gdiplus::Color(255, 255, 0, 255), 20.0F);
	graphics3.DrawLine(&pen3, x, y+10 , x + 10, y +10);
}
VOID PaintBoxFex22(HDC hdc, const int& x, const int& y) {
	Graphics graphics3(hdc);
	Pen	pen3(Gdiplus::Color(255, 255, 0, 255), 20.0F);
	graphics3.DrawLine(&pen3, x, y + 10, x + 20, y + 10);
}
VOID PaintFrame(HDC hdc) {
	Graphics graphicsFR(hdc);
	Pen	penFR(Gdiplus::Color(255, 0, 0, 255), 2);
	graphicsFR.DrawLine(&penFR, 0, 0, 0, height - 100);
	graphicsFR.DrawLine(&penFR, 0, 0, width - 100, 0);
	graphicsFR.DrawLine(&penFR, 0, height - 100, width - 100, height - 100);
	graphicsFR.DrawLine(&penFR, width - 100, 0, width - 100, height - 100);
}
VOID PaintBox(HDC hdc, const int &param1, const int &param2, const int &param3, const int &param4, const bool &param5) {
	Graphics graphics5(hdc);
	Pen	pen1(Gdiplus::Color(255, 0, 0, 255), 2);
	Pen	pen2(Gdiplus::Color(255, 255, 0, 0), 2);
	//***************************************************
	Rect rectH(param1, param2, param3, param4);	//Rectangle definition
	if(param5)
		graphics5.DrawRectangle(&pen1, rectH);		//Draw rectangle / color option 1
	else
		graphics5.DrawRectangle(&pen2, rectH);		//Draw rectangle / color option 2
}
VOID PaintWhiteLine(HDC hdc, const int &param1, const int &param2, const int &param3, const int &param4, const int &param5) {
	Graphics graphics3(hdc);
	Pen pen7(Gdiplus::Color(255, 255, 255, 255), param5);
	graphics3.DrawLine(&pen7, param1, param2, param3, param4);//weiße Linie!
}
VOID PrintLaneIF(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk) {
	Graphics graphics5(hdc);
	Pen	pen5(Gdiplus::Color(255, 255, 0, 255), 2);
	if (iPosYLk == iPosYRk) {
		if (iPosXLk <= iPosXRk) {
			Rect rectH(iPosXLk, iPosYLk, iPosXRk - iPosXLk + 10, 10);
			graphics5.DrawRectangle(&pen5, rectH);
		}
		else {
			Rect rectH(iPosXRk, iPosYRk, iPosXLk - iPosXRk + 10, 10);
			graphics5.DrawRectangle(&pen5, rectH);
		}
	}
	if (iPosXLk == iPosXRk) {
		if (iPosYLk <= iPosYRk) {
			Rect rectH(iPosXLk, iPosYLk, 10, (iPosYRk + 10) - iPosYLk);
			graphics5.DrawRectangle(&pen5, rectH);
		}
		else {
			Rect rectH(iPosXRk, iPosYRk, 10, iPosYLk - iPosYRk + 10);
			graphics5.DrawRectangle(&pen5, rectH);
		}
	}
}
VOID PaintLane(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV, const int &numberOFLanesa, const std::vector<std::tuple<int, int,int>> &PointsToBePrinted) {
	
	//***************************************************
	Graphics graphics3(hdc);
	
	Pen pen7(Gdiplus::Color(245, 245, 245, 255), 6);
	Pen pen8(Gdiplus::Color(245, 245, 245, 255), 16);
	Pen	pen10(Gdiplus::Color(255, 0, 0, 255), 2.0F);//Blau
	Pen	pen11(Gdiplus::Color(125, 0, 0, 255), 2.0F);//Licht Blau
	Pen	pen12(Gdiplus::Color(245, 0, 0, 125), 2.0F);//Schwarz
	Pen	pen13(Gdiplus::Color(245, 0, 125, 125), 2.0F);//Grün
	Pen	pen14(Gdiplus::Color(255, 0, 0, 255), 2.0F);//Blau
	Pen	pen15(Gdiplus::Color(255, 221, 102, 204), 2.0F);//Lila
	Pen	pen16(Gdiplus::Color(255, 153, 68, 0), 2.0F);//Braun
	Pen	pen17(Gdiplus::Color(175, 255, 0, 175), 2.0F);
	Pen	pen18(Gdiplus::Color(200, 25, 75, 175), 2.0F);
	Pen	pen19(Gdiplus::Color(225, 100, 75, 86), 2.0F);
	Pen	pen20(Gdiplus::Color(100, 255, 0, 100), 2.0F);
	Pen	pen21(Gdiplus::Color(255, 51, 68, 0), 2.0F);
	Pen	pen22(Gdiplus::Color(255, 161, 207, 47), 2.0F);
	Pen	pen23(Gdiplus::Color(255, 255, 0, 0), 2.0F);//Rot
	Pen	pen24(Gdiplus::Color(255, 100,255, 100), 2.0F);//Gelb
	Pen	pen25(Gdiplus::Color(255, 156, 247, 7), 2.0F);
	Pen	pen26(Gdiplus::Color(255, 191, 191, 63), 2.0F);
	Pen	pen27(Gdiplus::Color(255, 61, 243, 11), 2.0F);
	Pen	pen28(Gdiplus::Color(255, 205, 64, 49), 2.0F);
	Pen	pen29(Gdiplus::Color(255, 231, 226, 28), 2.0F);
	Pen	pen30(Gdiplus::Color(255, 47, 15, 239), 2.0F);
	

	if (!PointsToBePrinted.empty()) {//Hier werden die Punkte gezeichnet!
		for (auto &i : PointsToBePrinted) {
			switch (std::get<2>(i)){
				case 0:
				graphics3.DrawLine(&pen23, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
				break;
				case 1:
				graphics3.DrawLine(&pen11, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
				break;
				case 2:
				graphics3.DrawLine(&pen11, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
				break;
				case 3:
				graphics3.DrawLine(&pen10, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
				break;
				case 4:
				graphics3.DrawLine(&pen14, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
				break;
				case 5:
				graphics3.DrawLine(&pen11, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
				break;
				case 6:
				graphics3.DrawLine(&pen17, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
				break;
				case 7:
				graphics3.DrawLine(&pen15, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
				break;
				case 8:
				graphics3.DrawLine(&pen20, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
				break;
				case 9:
				graphics3.DrawLine(&pen13, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
				break;
				case 10:
				graphics3.DrawLine(&pen24, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
				break;
				case 11:
				graphics3.DrawLine(&pen19, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
				break;
				case 12:
				graphics3.DrawLine(&pen22, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
				break;
				case 13:
				graphics3.DrawLine(&pen12, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
				break;
				case 14:
				graphics3.DrawLine(&pen25, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
				break;
				case 15:
				graphics3.DrawLine(&pen16, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
				break;
				case 16:
				graphics3.DrawLine(&pen26, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
				break;
				case 17:
				graphics3.DrawLine(&pen18, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
				break;
				case 18:
				graphics3.DrawLine(&pen27, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
				break;
				case 19:
				graphics3.DrawLine(&pen21, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
				break;
				case 20:
				graphics3.DrawLine(&pen28, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
				break;
				case 21:
				graphics3.DrawLine(&pen30, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
				break;
				default:
				graphics3.DrawLine(&pen29, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
				break;
			}
		}
	}
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
VOID PaintWhiteClearLane(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV) {
	Graphics graphics3(hdc);
	Pen pen7(Gdiplus::Color(245, 245, 245, 255), 4);
	graphics3.DrawLine(&pen7, iPosXLk, iPosYLk + 5, iPosXRk, iPosYLk + 5);
}

static HDC hdc;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	n = simpleWindowUserInterface::getInstance(width, height, callBackLinks(hdc, PaintBoxLB, PaintBoxRB, PaintFrame, PaintLane, PrintVertexNumber, PaintBox, PaintWhiteLine,
		PaintBoxStart, PaintBoxEnd,PaintBoxFex11,PaintBoxFex12,PaintBoxFex21,PaintBoxFex22));
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
					CreateWindowExW(NULL, L"BUTTON", L"Yes", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
						80,
						160,
						35,
						35, g_windowHandle4,
						(HMENU)MY_BUTTON_YES,
						(HINSTANCE)GetWindowLong(g_windowHandle4, GWL_HINSTANCE),
						NULL);
					CreateWindowExW(NULL, L"BUTTON", L"No", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
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
				serviceBool = n->setPoints(hdc, 1);
				break;
			case 2:
				serviceBool = n->setPoints(hdc, 2);
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
			
			n->iPosXLK = height;
			n->iPosYLK = width;
			
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
				
				n->iPosXLK = height;
				n->iPosYLK = width;
				n->printLanesAndVehiclesOfAllEdges();
				
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
				n->printLanesAndVehiclesOfAllEdges();
			}
			break;
		case ESTVertexOfGraph:
			if (n->establishVertexOfGraph(numberOfLanesINT)) {
				n->iPosXLK = height;
				n->iPosYLK = width;
				n->printLanesAndVehiclesOfAllEdges();
				actionQueueBool = true;
				StartSimulation = false;
			}
		default:
			hdc = BeginPaint(g_windowHandle, &ps);	
			n->m_CBLptr->m_hdc = hdc;
			n->fieldRecalibarte();
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
		n->iPosXLK = height;
		n->iPosYLK = width;
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