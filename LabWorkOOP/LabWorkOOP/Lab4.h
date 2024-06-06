#include <iostream>

// 4.  � ���������� ������� ���� �������� ��� ����� / ����� / ���. 
// ����������� � ������ ���������� �����:
// �) ����������� ����� ����, ��������� ����� ����� ������ (�������� % );
// �) ���������� ����������� ������  ���� � �������� ���� (�������� / ).
// ������ ������ ������� ������� � ������ printf() ��� ������ �������� ����.
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
    // ��������������� ������� ��� �������� ���� � ������ ����
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

    // ��������������� ������� ��� ����������� ����������� ����
    bool isLeapYear() const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
};

void lab4_4() {
    system("cls");
    Date dateS(1, 1, 2024); // 1 ������ 2024
    Date dateE(1, 2, 2024); // 1 ������� 2024

    // ����������� ����� ���� ����� ����� ������
    int daysBetween = dateE % dateS;
    std::cout << "���� �����: " << daysBetween << std::endl;

    // ���������� ����������� ������ ���� � �������� ����
    int ordinalNumber = dateE / Date(1, 1, 2024);
    std::cout << "���������� �����: " << ordinalNumber << std::endl;
    char code = _getch();
}