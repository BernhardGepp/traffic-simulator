using namespace Gdiplus;
VOID PaintBoxEnd(HDC hdc, const int& x, const int& y);
VOID PaintBoxFex11(HDC hdc, const int& x, const int& y);
VOID PaintBoxFex12(HDC hdc, const int& x, const int& y);
VOID PaintBoxFex21(HDC hdc, const int& x, const int& y);
VOID PaintBoxFex22(HDC hdc, const int& x, const int& y);
VOID PaintBox(HDC hdc, const int& param1, const int& param2, const int& param3, const int& param4, const bool& param5);
VOID PaintWhiteLine(HDC hdc, const int& param1, const int& param2, const int& param3, const int& param4, const int& param5);
VOID PrintLaneIF(HDC hdc, const int& iPosXLk, const int& iPosYLk, const int& iPosXRk, const int& iPosYRk);
VOID PaintLane(HDC hdc, const int& iPosXLk, const int& iPosYLk, const int& iPosXRk, const int& iPosYRk, const bool& HorV, const int& numberOFLanesa, const std::vector<std::tuple<int, int, int>>& PointsToBePrinted);
VOID PaintWhiteClearLane(HDC hdc, const int& iPosXLk, const int& iPosYLk, const int& iPosXRk, const int& iPosYRk, const bool& HorV);
VOID PaintBoxStart(HDC hdc, const int& x, const int& y);

VOID PaintBoxLB(HDC hdc, const int& iPosXLK, const int& iPosYLK, const int& iPosXRK, const int& iPosYRK);
VOID PaintBoxRB(HDC hdc, const int& iPosXLK, const int& iPosYLK, const int& iPosXRK, const int& iPosYRK);


VOID PaintFrame(HDC hdc, const int& height, const int& width);

VOID PrintVertexNumber(HDC hdc, const int& iPosX, const int& iPosY, const int& iVertexID);
