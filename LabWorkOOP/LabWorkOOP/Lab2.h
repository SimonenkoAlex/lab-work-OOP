#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <ctime>
using namespace std;

void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 2. ���������� ����� t_end_d, �������� ��� ��� �������� ���������� �������
// ��������� ����� � ���� � ���� ���������� ������������. ���� ����� ������
// �������� �������-����, ��������� ����� � ���� �� �����. (��� ����������
// � ������ �� ����� ���� ������ �������������� ����������� ������������ ��������.)
class t_end_d
{
private:
	string date;
	string tim;
public:
	t_end_d();	// �����������
	~t_end_d(); // ����������
	void show();
};

t_end_d::t_end_d()		// ����������� ������������
{
	// �������� ���������� ������, ��������� � �����, ��� std::time_t ��������
	time_t t = time(nullptr);
	// ������������� ��� � ������, ���������� ����������� ���� � �����, �������� �� ������������
	struct tm now;	localtime_s(&now, &t);
	date = to_string(now.tm_mday) + "-" + to_string(now.tm_mon + 1) + "-" + to_string(now.tm_year + 1900);
	tim = to_string(now.tm_hour) + ":" + to_string(now.tm_min);
}

t_end_d::~t_end_d()		// ����������� �����������
{
	cout << "��������...\n";
}

void t_end_d::show()	// ����������� ������� ������
{
	gotoxy(25, 10);
	textcolor(LightGreen);
	cout << date << " ";
	textcolor(LightBlue);
	cout << tim;
}

void lab2_2()
{
	clrscr();
	system("cls");
	gotoxy(25, 8); textcolor(Yellow); cout << "��������� �����: ";
	t_end_d datetime;
	datetime.show();
	char code = _getch();
}