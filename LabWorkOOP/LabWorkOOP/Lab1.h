#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <Windows.h>
using namespace std;

enum ConsoleColor {
	Black = 0, Blue = 1, Green = 2, Cyan = 3, Red = 4, Magenta = 5,
	Brown = 6, LightGray = 7, DarkGray = 8, LightBlue = 9, LightGreen = 10,
	LightCyan = 11, LightRed = 12, LightMagenta = 13, Yellow = 14, White = 15
};

void textcolor(ConsoleColor text, ConsoleColor background = Black) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void clrscr() {
	HWND hwn = GetConsoleWindow();
	HDC hdc = GetDC(hwn);
	HPEN pen = CreatePen(PS_DASHDOT, 2, RGB(0, 0, 0));
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);
	Rectangle(hdc, 0, 0, 10000, 10000);
}

// 2. �������� ����� �� ����� Rational ��� ���������� ��������������
// �������� � �������. �������� ��������� �������� ��� ������ ������.
class Rational
{
private: int numerator;				// ��������� (a)
		 int denominator;			// ����������� (b)
public:
	Rational(int a = 1, int b = 1);
	bool input();
	void showFraction();
	void showDecimal();
	friend Rational add(Rational firstArg, Rational secondArg);
	friend Rational sub(Rational firstArg, Rational secondArg);
	friend Rational mult(Rational firstArg, Rational secondArg);
	friend Rational div(Rational firstArg, Rational secondArg);
};

Rational::Rational(int a, int b) {
	numerator = a;
	denominator = b;
}

bool Rational::input()      		// �������� ������� input
{
	textcolor(Yellow);
	clrscr();
	cout << "������� ������������� ��������� � ����������� �����:\n";
	cout << "(����������� �� ����� ����) \n";
	textcolor(White);
	cin >> numerator >> denominator;
	if (denominator == 0 || denominator < 0 || numerator < 0) {
		textcolor(LightRed);
		cout << "������ �����" << endl;
		textcolor(White);
		return false;
	}
	else return true;
}

void Rational::showFraction()       				// �������� ������� sered
{
	textcolor(LightCyan);
	cout << numerator << " / " << denominator << endl;
	textcolor(White);
}

void Rational::showDecimal()      				// �������� ������� show
{
	textcolor(LightCyan);
	cout.precision(2);
	cout << fixed << (float)numerator / (float)denominator << endl;
	cout.precision(0);
	textcolor(White);
}

Rational add(Rational firstArg, Rational secondArg)
{
	if (firstArg.denominator == secondArg.denominator) {
		return Rational(firstArg.numerator + secondArg.numerator, firstArg.denominator);
	}
	else {
		firstArg.numerator *= secondArg.denominator;
		secondArg.numerator *= firstArg.denominator;
		firstArg.denominator *= secondArg.denominator;
		return Rational(firstArg.numerator + secondArg.numerator, firstArg.denominator);
	}
}

Rational sub(Rational firstArg, Rational secondArg)
{
	if (firstArg.denominator == secondArg.denominator) {
		return Rational(firstArg.numerator - secondArg.numerator, firstArg.denominator);
	}
	else {
		firstArg.numerator *= secondArg.denominator;
		secondArg.numerator *= firstArg.denominator;
		firstArg.denominator *= secondArg.denominator;
		return Rational(firstArg.numerator - secondArg.numerator, firstArg.denominator);
	}
}

Rational mult(Rational firstArg, Rational secondArg)
{
	return Rational(firstArg.numerator * secondArg.numerator, firstArg.denominator * secondArg.denominator);
}

Rational div(Rational firstArg, Rational secondArg)
{
	return Rational(firstArg.numerator * secondArg.denominator, firstArg.denominator * secondArg.numerator);
}

void lab1_2()
{
	clrscr();
	system("cls");
	Rational a, b, c;
	char ch;
	if (a.input() && b.input()) {
		textcolor(LightMagenta);
		cout << "������ �����:\n";
		textcolor(White);
		cout << "������ � ����� a / b:\n";
		a.showFraction();
		cout << "������ � ����� � ��������� ������:\n";
		a.showDecimal();

		textcolor(LightMagenta);
		cout << "������ �����:\n";
		textcolor(White);
		cout << "������ � ����� a / b:\n";
		b.showFraction();
		cout << "������ � ����� � ��������� ������:\n";
		b.showDecimal();

		cout << "�������� �������� ��� �������\n";
		cout << "=> 1: A+B; 2: A-B; 3: A*B; 4: A/B; 0: EXIT <=\n";
		ch = _getch();
		switch (ch)
		{
		case '0': break;
		case '1': { c = add(a, b); break; }
		case '2': { c = sub(a, b); break; }
		case '3': { c = mult(a, b); break; }
		case '4': { c = div(a, b); break; }
		}
		textcolor(LightMagenta);
		cout << "����� ����������:\n";
		textcolor(White);
		cout << "������ � ����� a / b:\n";
		c.showFraction();
		cout << "������ � ����� � ��������� ������:\n";
		c.showDecimal();
	}
	_getch();
}