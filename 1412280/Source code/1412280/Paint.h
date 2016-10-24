#include "stdafx.h"
#include <vector>
#include <fstream>
#include "PaintDLL.h"
using namespace std;
using namespace PaintDLL;


class Paint {
	HWND hwnd;
	vector<Shape*>data;
	int style;
public:
	int GetStyle();
	void SetStyle(int sty);
	void AddData(int x1, int y1, int x2, int y2, int style);
	void DrawShape(HWND hWnd, int isDrawing, int curX, int curY, int lastX, int lastY);
	void WriteData(PWSTR pathSaveFile);
	void ReadData(PWSTR pathFile);
	void ClearScreen();
};
extern Paint paint;
extern PWSTR pathFile;
extern PWSTR pathSaveFile;