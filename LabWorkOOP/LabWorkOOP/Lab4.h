#include <iostream>

// 4.  В британском формате дата задается как число / месяц / год. 
// Реализовать с учетом високосных годов:
// а) определение числа дней, прошедших между двумя датами (операция % );
// б) нахождение порядкового номера  даты в заданном году (операция / ).
// Членом класса сделать функцию с именем printf() для вывода конечной даты.
class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    int operator%(const Date& other) const {
        int days1 = countDays();
        int days2 = other.countDays();
        return abs(days1 - days2);
    }

    int operator/(const Date& other) const {
        return countDays() - other.countDays() + 1;
    }

    void printf() const {
        std::cout << day << "/" << month << "/" << year << std::endl;
    }

private:
    // Вспомогательная функция для подсчета дней с начала года
    int countDays() const {
        int days = day;
        switch (month - 1) {
        case 11:
            days += 30;
        case 10:
            days += 31;
        case 9:
            days += 30;
        case 8:
            days += 31;
        case 7:
            days += 31;
        case 6:
            days += 30;
        case 5:
            days += 31;
        case 4:
            days += 30;
        case 3:
            days += 31;
        case 2:
            days += isLeapYear() ? 29 : 28;
        case 1:
            days += 31;
        }
        return days;
    }

    // Вспомогательная функция для определения высокосного года
    bool isLeapYear() const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
};

void lab4_4() {
    system("cls");
    Date dateS(1, 1, 2024); // 1 января 2024
    Date dateE(1, 2, 2024); // 1 феврфля 2024

    // Определение числа дней между двумя датами
    int daysBetween = dateE % dateS;
    std::cout << "Дней между: " << daysBetween << std::endl;

    // Нахождение порядкового номера даты в заданном году
    int ordinalNumber = dateE / Date(1, 1, 2024);
    std::cout << "Порядковый номер: " << ordinalNumber << std::endl;
    char code = _getch();
}