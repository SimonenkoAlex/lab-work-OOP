#include <stdio.h>
#include <conio.h>
#include <math.h>
#define PI 3.1415

// 2. ������� �����-�������� ������, ��� ���������� � ����� ��������, ���������� 
// ��������� ������� ���������������� (����������, �������, ���������, �����������, 
// ���������).
class Point // �������� �������
{
protected:
	double x0; // ���������� ����� �� ��� �������
	double y0; // ���������� ����� �� ��� �������
public:
	Point(double xn = 0, double yn = 0) : x0(xn), y0(yn) {}
	double getX() { return x0; }
	double getY() { return y0; }
	void setX(double xn) { x0 = xn; }
	void setY(double yn) { y0 = yn; }
	void paint(void); // ������� ������ ����������
	void clear(void);
};

void Point::paint() {
	HWND hwn = GetConsoleWindow();
	HDC hdc = GetDC(hwn);
	HPEN pen = CreatePen(PS_SOLID, 5, RGB(140, 90, 10));
	HBRUSH BRUSH = CreateSolidBrush(RGB(140, 90, 10));
	RECT rect; GetClientRect(hwn, &rect);
	const int c = rect.right / 2, d = rect.bottom / 2, k = 10;
	SelectObject(hdc, pen); SelectObject(hdc, BRUSH);
	Ellipse(hdc, (c + k * x0) - 1, (d - k * y0) - 1, (c + k * x0) + 1, (d - k * y0) + 1);
	DeleteObject(pen); DeleteObject(BRUSH);
	ReleaseDC(hwn, hdc);
}

void Point::clear() {
	HWND hwn = GetConsoleWindow();
	HDC hdc = GetDC(hwn);
	HPEN pen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	HBRUSH BRUSH = CreateSolidBrush(RGB(0, 0, 0));
	RECT rect; GetClientRect(hwn, &rect);
	const int c = rect.right / 2, d = rect.bottom / 2, k = 10;
	SelectObject(hdc, pen); SelectObject(hdc, BRUSH);
	Ellipse(hdc, (c + k * x0) - 1, (d - k * y0) - 1, (c + k * x0) + 1, (d - k * y0) + 1);
	DeleteObject(pen); DeleteObject(BRUSH);
	ReleaseDC(hwn, hdc);
}

class Line : public Point
{
protected:
	Point _A, _B;	// ����� �������
	double _length;	// ����� �������
public:
	Line(double x0 = 0, double y0 = 0, double x1 = 1, double y1 = 1) : _A(x0, y0), _B(x1, y1) 
	{
		_length = sqrt(pow(_A.getX() - _B.getX(),2) + (_A.getY() - _B.getY(), 2));
	}
	Point getPointStart() { return _A; }
	Point getPointEnd() { return _B; }
	double length() { return _length; }
	void paint(void);
	void clear(void);
	void rotation(float angleDeg);
	void move(int units);
};

void Line::paint() {
	HWND hwn = GetConsoleWindow();
	HDC hdc = GetDC(hwn);
	HPEN pen = CreatePen(PS_SOLID, 3, RGB(113, 47, 38));
	RECT rect; GetClientRect(hwn, &rect);
	const int c = rect.right / 2, d = rect.bottom / 2, k = 10;
	SelectObject(hdc, pen);
	MoveToEx(hdc, c + k * _A.getX(), d - k * _A.getY(), NULL);
	LineTo(hdc, c + k * _B.getX(), d - k * _B.getY());
	DeleteObject(pen);
	ReleaseDC(hwn, hdc);
}

void Line::clear() {
	HWND hwn = GetConsoleWindow();
	HDC hdc = GetDC(hwn);
	HPEN pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	RECT rect; GetClientRect(hwn, &rect);
	const int c = rect.right / 2, d = rect.bottom / 2, k = 10;
	SelectObject(hdc, pen);
	MoveToEx(hdc, c + k * _A.getX(), d - k * _A.getY(), NULL);
	LineTo(hdc, c + k * _B.getX(), d - k * _B.getY());
	DeleteObject(pen);
	ReleaseDC(hwn, hdc);
}

void Line::rotation(float angleDeg = 0) {
	cout << "������� ������� �� " << angleDeg << " ����..." << endl;
	float r = 0.0, a1 = 0.0;
	// ���������� �������� �������
	double sx = (int)((_A.getX() + _B.getX()) / 2);
	double sy = (int)((_A.getY() + _B.getY()) / 2);
	// ������� �� ����. � ���.
	angleDeg *= (PI / 180);
	// ������� ������ ��������� � �����
	a1 = atan2((float)(sy - _B.getY()), (float)(_B.getX() - sx));
	r = sqrt((_B.getX() - sx)*(_B.getX() - sx) + (sy - _B.getY())*(sy - _B.getY()));
	_B.setX((double)(sx + r * cos(a1 + angleDeg)));
	_B.setY((double)(sy - r * sin(a1 + angleDeg)));
	_A.setX((double)(sx - r * cos(a1 + angleDeg)));
	_A.setY((double)(sy + r * sin(a1 + angleDeg)));
}

void Line::move(int units = 0) {
	cout << "�������������� �������..." << endl;
	_B.setX((double)_B.getX() + units);
	_B.setY((double)_B.getY() + units);
	_A.setX((double)_A.getX() + units);
	_A.setY((double)_A.getY() + units);
}

class Quadrilateral : public Line
{
	Line _lineAB, _lineBC, _lineCD, _lineAD;
public:
	Quadrilateral(double xA, double yA, double xB, double yB,
		double xC, double yC, double xD, double yD) : _lineAB(xA, yA, xB, yB), 
		_lineBC(xB, yB, xC, yC), _lineCD(xC, yC, xD, yD), _lineAD(xA, yA, xD, yD) {}
	Line getLineAB() { return _lineAB; }
	Line getLineBC() { return _lineBC; }
	Line getLineCD() { return _lineCD; }
	Line getLineAD() { return _lineAD; }
	void paint(void);
	void clear(void);
};

void Quadrilateral::paint() {
	// ������� AB
	_lineAB.paint();
	// ������� BC
	_lineBC.paint();
	// ������� CD
	_lineCD.paint();
	// ������� CD
	_lineAD.paint();
}

void Quadrilateral::clear() {
	_lineAB.clear();
	_lineBC.clear();
	_lineCD.clear();
	_lineAD.clear();
}

Line lineAB(13, 9, 1, 4); // ������������

void selectFigure(int position)
{
	char code;
	switch (position) {
	case 0: {
		cout << "��������� �����..." << endl;	// ��������� �����
		lineAB.getPointStart().paint();
		lineAB.getPointEnd().paint();
		code = _getch();
		cout << "�������� �����..." << endl;	// �������� �����
		lineAB.getPointStart().clear();
		lineAB.getPointEnd().clear();
		code = _getch();
	} break;
	case 1: {
		cout << "��������� �������..." << endl;	// ��������� �������
		lineAB.paint();
		code = _getch();
		cout << "�������� �������..." << endl;	// �������� �������
		lineAB.clear();
		code = _getch();
	} break;
	case 2: {
		cout << "������� ������ �� 30 ����..." << endl;	// ������� ������ �� 30 ����.
		lineAB.rotation(30.0);
		lineAB.paint();
		code = _getch();
	} break;
	case 3: {
		cout << "�������� �� 2 ��. ����..." << endl;	// �������� �� 2 ��. ����
		lineAB.clear();
		lineAB.move(-2);
		lineAB.paint();
		code = _getch();
	} break;
	case 4: {
		cout << "�������� �� 3 ��. �����..." << endl;	// �������� �� 3 ��. �����
		lineAB.clear();
		lineAB.move(3);
		lineAB.paint();
		code = _getch();
	} break;
	case 5: {
		Quadrilateral figure(1, 2, 5, 4, 5, 13, 3, 10);
		cout << "��������� �������������� � ������������";
		cout << " A(" << figure.getLineAB().getPointStart().getX() << ", " << figure.getLineAB().getPointStart().getY() << ")";
		cout << " B(" << figure.getLineAB().getPointEnd().getX() << ", " << figure.getLineAB().getPointEnd().getY() << ")";
		cout << " �(" << figure.getLineCD().getPointStart().getX() << ", " << figure.getLineCD().getPointStart().getY() << ")";
		cout << " D(" << figure.getLineCD().getPointEnd().getX() << ", " << figure.getLineCD().getPointEnd().getY() << ")" << endl;
		figure.paint();
		code = _getch();
		figure.clear();
		cout << "����� ������� AB = " << figure.getLineAB().length() << endl;
		cout << "����� ������� BC = " << figure.getLineBC().length() << endl;
		cout << "����� ������� CD = " << figure.getLineCD().length() << endl;
		cout << "����� ������� AD = " << figure.getLineAD().length() << endl;
		code = _getch();
	} break;
	case 6: exit(0);
	}
}

void lab3_2() {
	clrscr();
	system("cls");
	textcolor(White);
	
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD active = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	WORD noActive = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	char lines[][50] = { "��������� �����", "��������� �������",  
		"������� ������ �� 30 ����.", "�������� �� 2 ��. ����", 
		"�������� �� 3 ��. �����", "��������� ��������������", "�����" };
	COORD coordinate;
	int position = 0, lastItemMenu = 7;
	char code;
	while (true) {
		clrscr(); system("cls");
		cout << "����� ������� AB ������ = " << lineAB.length() << " � ������������";
		cout << " A(" << lineAB.getPointStart().getX() << ", " << lineAB.getPointStart().getY() << ")";
		cout << " B(" << lineAB.getPointEnd().getX() << ", " << lineAB.getPointEnd().getY() << ")" << endl;
		coordinate.X = 25; coordinate.Y = 3;
		SetConsoleCursorPosition(handle, coordinate);
		cout << "������� 5" << endl;
		for (int i = 0; i < lastItemMenu; i++) {
			if (position == i)
				SetConsoleTextAttribute(handle, active);
			else
				SetConsoleTextAttribute(handle, noActive);
			coordinate.X = 25; coordinate.Y = 5 + i * 2;
			SetConsoleCursorPosition(handle, coordinate);
			cout << i + 1 << ") " << lines[i] << endl;
		}
		code = _getch();
		if (code == 72) {
			if (position == 0) position = lastItemMenu - 1;
			else position--;
		}
		if (code == 80) {
			if (position == lastItemMenu - 1) position = 0;
			else position++;
		}
		if (code == 13) selectFigure(position);
	}
}