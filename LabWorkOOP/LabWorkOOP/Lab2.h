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

// 2. Определите класс t_end_d, которому при его создании передается текущее
// системное время и дата в виде параметров конструктора. Этот класс должен
// включать функцию-член, выводящую время и дату на экран. (Для нахождения
// и вывода на экран этих данных воспользуйтесь стандартной библиотечной функцией.)
class t_end_d
{
private:
	string date;
	string tim;
public:
	t_end_d();	// конструктор
	~t_end_d(); // деструктор
	void show();
};

t_end_d::t_end_d()		// определение конструктора
{
	// получить количество секунд, прошедших с эпохи, как std::time_t значение
	time_t t = time(nullptr);
	// преобразовать его в объект, содержащий календарную дату и время, разбитые на составляющие
	struct tm now;	localtime_s(&now, &t);
	date = to_string(now.tm_mday) + "-" + to_string(now.tm_mon + 1) + "-" + to_string(now.tm_year + 1900);
	tim = to_string(now.tm_hour) + ":" + to_string(now.tm_min);
}

t_end_d::~t_end_d()		// определение деструктора
{
	cout << "Удаление...\n";
}

void t_end_d::show()	// определение функции вывода
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
	gotoxy(25, 8); textcolor(Yellow); cout << "Системное время: ";
	t_end_d datetime;
	datetime.show();
	char code = _getch();
}