#include <locale.h>
#include "Lab1.h"
#include "Lab2.h"
#include "Lab3.h"
#include "Lab4.h"
using namespace std;

void select(int position) {
	switch (position) {
	case 0: lab1_2(); system("cls"); break;
	case 1: lab2_2(); system("cls"); break;
	case 2: lab3_2(); system("cls"); break;
	case 3: lab4_4(); system("cls"); break;
	case 4: exit(0);
	}
}

int main()             					// Основная программа
{
	setlocale(LC_CTYPE, "rus");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD active = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	WORD noActive = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	char lines[][20] = { "Лаб-раб 1", "Лаб-раб 2", "Лаб-раб 3", "Лаб-раб 4", "Выход" };
	COORD coordinate;
	int position = 0, lastItemMenu = 5;
	char code;
	while (true) {
		clrscr(); system("cls");
		coordinate.X = 25; coordinate.Y = 3;
		SetConsoleCursorPosition(handle, coordinate);
		cout << "Вариант 5" << endl;
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
		if (code == 13) select(position);
	}
	return 0;
}