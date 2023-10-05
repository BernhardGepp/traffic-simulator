#pragma once
#include "PrecompiledHeadersEdges.h"
#include "callBackFunctions.h"
using namespace Gdiplus;

VOID PaintBoxLB(HDC hdc, const int& iPosXLK, const int& iPosYLK, const int& iPosXRK,const int& iPosYRK) {
	Graphics graphics1(hdc);
	Pen	pen2(Color(255, 255, 0, 255), 10.0F);
	TextOutW(hdc, iPosXLK + 10, iPosYLK + 10, L"P1", wcslen(L"P1 "));
	graphics1.DrawLine(&pen2, iPosXLK, iPosYLK + 5, iPosXLK + 10, iPosYLK + 5);
}
VOID PaintBoxRB(HDC hdc, const int& iPosXLK, const int& iPosYLK, const int& iPosXRK, const int& iPosYRK) {
	Graphics graphics3(hdc);
	Pen	pen3(Gdiplus::Color(255, 255, 0, 255), 10.0F);
	TextOutW(hdc, iPosXRK + 10, iPosYRK + 10, L"P2", wcslen(L"P2 "));
	graphics3.DrawLine(&pen3, iPosXRK, iPosYRK + 5, iPosXRK + 10,iPosYRK + 5);
}
VOID PaintFrame(HDC hdc, const int& height, const int& width) {
	Graphics graphicsFR(hdc);
	Pen	penFR(Gdiplus::Color(255, 0, 0, 255), 2);
	graphicsFR.DrawLine(&penFR, 0, 0, 0, height - 100);
	graphicsFR.DrawLine(&penFR, 0, 0, width - 100, 0);
	graphicsFR.DrawLine(&penFR, 0, height - 100, width - 100, height - 100);
	graphicsFR.DrawLine(&penFR, width - 100, 0, width - 100, height - 100);
}
VOID PrintVertexNumber(HDC hdc, const int& iPosX, const int& iPosY, const int& iVertexID) {
	wchar_t buffer1[256];
	wsprintfW(buffer1, L"%d", iVertexID);
	TextOutW(hdc,
		iPosX + 25,
		iPosY + 25,
		buffer1,
		wcslen(buffer1));
	Graphics graphics3(hdc);
	Pen	pen3(Gdiplus::Color(255, 255, 0, 255), 10.0F);
	graphics3.DrawLine(&pen3, iPosX, iPosY + 5, iPosX + 10, iPosY + 5);
}
VOID PaintBoxStart(HDC hdc,const int& x, const int& y) {
	Graphics graphics3(hdc);
	Pen	pen3(Gdiplus::Color(245, 0, 125, 125), 10.0F);//greenBox
	graphics3.DrawLine(&pen3, x, y + 5, x + 10, y + 5);
}
VOID PaintBoxEnd(HDC hdc, const int& x, const int& y) {//redBox
	Graphics graphics3(hdc);
	Pen	pen3(Gdiplus::Color(255, 255, 0, 0), 10.0F);
	graphics3.DrawLine(&pen3, x, y + 5, x + 10, y + 5);
}
VOID PaintBoxFex11(HDC hdc, const int& x, const int& y) {//small_pinkBox
	Graphics graphics3(hdc);
	Pen	pen3(Gdiplus::Color(255, 255, 0, 255), 10.0F);
	graphics3.DrawLine(&pen3, x, y + 5, x + 10, y + 5);
}
VOID PaintBoxFex12(HDC hdc, const int& x, const int& y) {//half_pinkBox
	Graphics graphics3(hdc);
	Pen	pen3(Gdiplus::Color(255, 255, 0, 255), 10.0F);
	graphics3.DrawLine(&pen3, x, y + 5, x + 20, y + 5);
}
VOID PaintBoxFex21(HDC hdc, const int& x, const int& y) {//half_pinkBox
	Graphics graphics3(hdc);
	Pen	pen3(Gdiplus::Color(255, 255, 0, 255), 20.0F);
	graphics3.DrawLine(&pen3, x, y+10 , x + 10, y +10);
}
VOID PaintBoxFex22(HDC hdc, const int& x, const int& y) {//big_prinkBox
	Graphics graphics3(hdc);
	Pen	pen3(Gdiplus::Color(255, 255, 0, 255), 20.0F);
	graphics3.DrawLine(&pen3, x, y + 10, x + 20, y + 10);
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
VOID PaintWhiteClearLane(HDC hdc, const int &iPosXLk, const int &iPosYLk, const int &iPosXRk, const int &iPosYRk, const bool &HorV) {
	Graphics graphics3(hdc);
	Pen pen7(Gdiplus::Color(245, 245, 245, 255), 4);
	graphics3.DrawLine(&pen7, iPosXLk, iPosYLk + 5, iPosXRk, iPosYLk + 5);
}

