#include "stdafx.h"
#include "Paint.h"

//get style is rectangle or ellipse or line
int Paint::GetStyle() {
	return style;
}

//set style is rectangle or ellipse or line
void Paint::SetStyle(int sty) {
	style = sty;
}

//add coordinates
void Paint::AddData(int x1, int y1, int x2, int y2, int style) {
	if (style == 1)
	{
		Line *tmp = new Line(x1, y1, x2, y2, -1);
		data.push_back(tmp);
	}
	else if (style == 2) {
		Rectang *tmp = new Rectang(x1, y1, x2, y2, -2);
		data.push_back(tmp);
	}

	else if (style == 3) {
		Ellip *tmp = new Ellip(x1, y1, x2, y2, -3);
		data.push_back(tmp);
	}
}

//reDraw shape rectangle or line or ellipse 
void Paint::DrawShape(HWND hWnd, int isDrawing, int curX, int curY, int lastX, int lastY) {
	hwnd = hWnd;
	PAINTSTRUCT ps;
	HDC virDc;
	HBITMAP hBitmap;

	RECT client;
	::GetClientRect(hWnd, &client);
	HDC hdc = BeginPaint(hWnd, &ps);
	virDc = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, client.right, client.bottom - 147);

	SelectObject(virDc, hBitmap);
	::FillRect(virDc, &client, (HBRUSH)::GetStockObject(WHITE_BRUSH));


	for (int i = 0; i < data.size(); i++) {
		data[i]->Draw(virDc);
	}
	if (isDrawing) {
		if (style == 1) {
			MoveToEx(virDc, curX, curY, NULL);
			LineTo(virDc, lastX, lastY);
		}
		else if (style == 2) {
			Rectangle(virDc, curX, curY, lastX, lastY);
		}
		else if (style == 3) {
			Ellipse(virDc, curX, curY, lastX, lastY);
		}
	}

	BitBlt(hdc, 0, 147, client.right, client.bottom, virDc, 0, 0, SRCCOPY);

	DeleteDC(virDc);
	DeleteObject(hBitmap);
	EndPaint(hWnd, &ps);
}

//write on database
void Paint::WriteData(PWSTR pathSaveFile) {
	if (pathSaveFile == NULL)
		return;
	fstream output(pathSaveFile, ios::binary | ios::out);
	if (!output.is_open())
		return;
	for (int i = 0; i<data.size(); i++)
		output.write((char*)data[i], sizeof(Line));
	output.close();
}

//read database , set vector data
void Paint::ReadData(PWSTR pathFile) {
	if (pathFile == NULL)
		return;
	fstream input(pathFile, ios::binary | ios::in);
	if (!input.is_open())
		return;
	ClearScreen();
	while (!input.eof()) {
		Line  *tmp = new Line();
		input.read((char*)tmp, sizeof(Line));
		if (tmp->GetType() == -1) {
			Line *tmpLine = new Line(tmp->GetX1(), tmp->GetY1(), tmp->GetX2(), tmp->GetY2(), -1);
			data.push_back(tmpLine);
		}
		if (tmp->GetType() == -2) {
			Rectang *tmpRec = new Rectang(tmp->GetX1(), tmp->GetY1(), tmp->GetX2(), tmp->GetY2(), -2);
			data.push_back(tmpRec);
		}
		if (tmp->GetType() == -3) {
			Ellip *tmpEllip = new Ellip(tmp->GetX1(), tmp->GetY1(), tmp->GetX2(), tmp->GetY2(), -3);
			data.push_back(tmpEllip);
		}
	}
	input.close();

}

//clear vector data
void Paint::ClearScreen() {
	data.clear();
	InvalidateRect(hwnd, 0, TRUE);
}