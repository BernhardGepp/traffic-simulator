#pragma once
#include "PrecompiledHeadersEdges.h"
#include "network.h"
#include "callBackLinks.h"

#define MY_BUTTON_ID 38
#define MY_RKLICK_ID 37
#define START_SIMULATION 41
#define MY_BUTTON_1 42
#define MY_BUTTON_2 43
#define createSecondWindow 101
#define INT int

network* n = nullptr;
network* network::instance = 0;


enum numberOFLanes { one = 1, two = 2 };
int simulationIteration =1000;
const int width = 1200;
const int height = 700;
int numberOfLanesINT = 1;
bool window1closed = false;
bool window2closed = false;
bool actionQueueBool = false;
bool reStartSimulation = false;
using namespace Gdiplus;
LRESULT CALLBACK WindowProc(HWND g_windowHandle, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WindowProc2(HWND g_windowHandle2, UINT message, WPARAM wParam, LPARAM lParam);
LPCWSTR Fragetext1 = L"Wie viele Fahrstreifen                           ";
LPCWSTR Fragetext2 = L"soll diese Fahrbahn haben?                       ";
LPCWSTR Fragetext3 = L"1 oder 2?                                        ";
HINSTANCE g_hInstance = nullptr;
WNDCLASSEX subWindowClass;
HWND  g_windowHandle = nullptr;
HWND g_windowHandle2 = nullptr;
HWND iter_button = nullptr;
RECT Rechteck = { (long)0, (long)0, (long)width, (long)height };
//bool serviceBool = true;

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
			if (std::get<2>(i) == 0) {
				graphics3.DrawLine(&pen23, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
			}
			if (std::get<2>(i) == 1) {
				graphics3.DrawLine(&pen11, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
			}
			if (std::get<2>(i) == 2) {
				graphics3.DrawLine(&pen11, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
			}
			if (std::get<2>(i) == 3) {
				graphics3.DrawLine(&pen10, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
			}
			if (std::get<2>(i) == 4) {
				graphics3.DrawLine(&pen14, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
			}
			if (std::get<2>(i) == 5) {
				graphics3.DrawLine(&pen11, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
			}
			if (std::get<2>(i) == 6) {
				graphics3.DrawLine(&pen17, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
			}
			if (std::get<2>(i) == 7) {
				graphics3.DrawLine(&pen15, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
			}
			if (std::get<2>(i) == 8) {
				graphics3.DrawLine(&pen20, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
			}
			if (std::get<2>(i) == 9) {
				graphics3.DrawLine(&pen13, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
			}
			if (std::get<2>(i) == 10) {
				graphics3.DrawLine(&pen24, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
			}
			if (std::get<2>(i) == 11) {
				graphics3.DrawLine(&pen19, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
			}
			if (std::get<2>(i) == 12) {
				graphics3.DrawLine(&pen22, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
			}
			if (std::get<2>(i) == 13) {
				graphics3.DrawLine(&pen12, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
			}
			if (std::get<2>(i) == 14) {
				graphics3.DrawLine(&pen25, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
			}
			if (std::get<2>(i) == 15) {
				graphics3.DrawLine(&pen16, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
			}
			if (std::get<2>(i) == 16) {
				graphics3.DrawLine(&pen26, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
			}
			if (std::get<2>(i) == 17) {
				graphics3.DrawLine(&pen18, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
			}
			if (std::get<2>(i) == 18) {
				graphics3.DrawLine(&pen27, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
			}
			if (std::get<2>(i) == 19) {
				graphics3.DrawLine(&pen21, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
			}
			if (std::get<2>(i) == 20) {
				graphics3.DrawLine(&pen28, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
			}
			if (std::get<2>(i) == 21) {
				graphics3.DrawLine(&pen30, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
			}
			if (std::get<2>(i) >= 22) {
				graphics3.DrawLine(&pen29, std::get<0>(i) + 3, std::get<1>(i), std::get<0>(i) + 5, std::get<1>(i));
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
	
	/*n = n->getInstance(width, height, callBackLinks(hdc, PaintBoxLB, PaintBoxRB, PaintFrame, PaintLane, PrintVertexNumber, PaintBox, PaintWhiteLine,
		PaintBoxStart, PaintBoxEnd, PaintBoxFex11, PaintBoxFex12, PaintBoxFex21, PaintBoxFex22));*/
	n = network::getInstance(width, height, callBackLinks(hdc, PaintBoxLB, PaintBoxRB, PaintFrame, PaintLane, PrintVertexNumber, PaintBox, PaintWhiteLine,
		PaintBoxStart, PaintBoxEnd,PaintBoxFex11,PaintBoxFex12,PaintBoxFex21,PaintBoxFex22));
	MSG msg;
	bool endprogram = false;
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
	subWindowClass.hInstance = hInstance;			//Gleiche HInstance wie oben?
	subWindowClass.hIcon = NULL;
	subWindowClass.hIconSm = NULL;
	subWindowClass.lpszMenuName = NULL;
	subWindowClass.lpszClassName = (LPCSTR)L"SubWindowClass";

	RegisterClassEx(&subWindowClass);

	iter_button = CreateWindowExW(NULL, L"BUTTON", L"Start", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		width - 100,
		height - 100,
		100,
		50, g_windowHandle,
		(HMENU)MY_BUTTON_ID,
		(HINSTANCE)GetWindowLong(g_windowHandle, GWL_HINSTANCE),
		NULL);
	
	while (endprogram == false) {
		PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE);

		//Hier die Aktionque verwickrlichen
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (actionQueueBool == true) {
			if (msg.message == WM_LBUTTONDOWN) {
				if (!n->networkLaneVector.empty()) {
					if (!n->networkCreationClass.appliedGraph.empty()) {
						if ((n->iPosXLK < width) && (n->iPosYLK < height)) {
							if (n->checkIfDubbleKlick(n->iPosXLK, n->iPosYLK)) {
								n->m_cObSptr->benachrichtigen(n->iPosXLK, n->iPosYLK);
							}
						}
					}
				}
			}
			else {
				if (simulationIteration > 0) {
					simulationIteration--;
					if (simulationIteration == 0) {
						reStartSimulation = true;
					}
					PaintFrame(hdc);
					SendMessageCallback(g_windowHandle, WM_PAINT, START_SIMULATION, NULL, NULL, NULL);
				}
				else {
					actionQueueBool = false;
				}
			}
		}
		if (window1closed == true) {
			endprogram = true;
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
		if (wParam == 0x31) {// Code für CHAR Ziffer 1
			numberOFLanes::one;
			numberOfLanesINT = 1;
			SendMessage(g_windowHandle2, WM_CLOSE, NULL, NULL);
		}
		if (wParam == 0x32) {// Code für CHAR Ziffer 2
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
			InvalidateRect(g_windowHandle, &Rechteck, TRUE); // Quadrat setzen!
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

		InvalidateRect(g_windowHandle, &Rechteck, TRUE);//Quadrat setzen!
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
			if(numberOfLanesINT==1){
				serviceBool = n->setPoints(hdc, 1);
			}
			
			if (numberOfLanesINT == 2) {
				serviceBool = n->setPoints(hdc, 2);
			}

			if (serviceBool == false) {
				numberOFLanes::one;
				numberOfLanesINT = 1;
				SendMessage(g_windowHandle, WM_CREATE, 0, 0);
			}
			if (serviceBool == true) {
				SendMessage(g_windowHandle2, WM_CLOSE, NULL, NULL);
			}
			for (auto &i : n->m_nCptr->networkLaneVector) {
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
			if ((actionQueueBool == false)&&(reStartSimulation==false)&&(!n->m_nCptr->networkLaneVector.empty())) {
				n->establishVertexOfGraph();
				n->iPosXLK = height;
				n->iPosYLK = width;
				n->printLanesAndVehiclesOfAllEdges();
				actionQueueBool = true;
			}
			break;
		case START_SIMULATION:
			if (n->appliedGraph.size() >= 1) {
				for (auto& i : n->appliedGraph) {
					i->simulation(simulationIteration);
				}
				if (n->appliedGraph[0]->m_vectorOfEdgesPtr.size() <= 6) {
					std::this_thread::sleep_for(std::chrono::milliseconds(250));
				}
				else {
					std::this_thread::sleep_for(std::chrono::milliseconds(260));
				}
				n->printLanesAndVehiclesOfAllEdges();
			}
			break;
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
			450,
			300,
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
		
		n->networkLaneVector.clear();
		PostQuitMessage(0);
		window1closed = true;

		break;
	default:
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
		TextOut(hdc_s, 10, 10, (LPCSTR)Fragetext1, wcslen(Fragetext1));
		TextOut(hdc_s, 10, 30, (LPCSTR)Fragetext2, wcslen(Fragetext2));
		TextOut(hdc_s, 10, 50, (LPCSTR)Fragetext3, wcslen(Fragetext3));
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
			for (auto& i : n->m_nCptr->networkLaneVector) {
				PrintLaneIF(hdc, std::get<0>(i).first, std::get<0>(i).second, std::get<1>(i).first, std::get<1>(i).second);
			}
			break;
		case MY_BUTTON_2:
			numberOFLanes::two;
			numberOfLanesINT = 2;
			SendMessage(g_windowHandle2, WM_CLOSE, NULL, NULL);
			for (auto& i : n->m_nCptr->networkLaneVector) {
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