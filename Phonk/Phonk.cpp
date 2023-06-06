#include <iostream>
#include <string>
#include <conio.h>
#include "_Long.h"
#include "Node.h"

typedef unsigned int UInt;
typedef unsigned char UChar;

using namespace std;

template<typename T>
void Print(const T& value, const bool hasEndl = false);

template<typename T>
void Input(T& value, const string message);

void PrintInterface();
void PrintLists(const _Long& list, const _Long& list2);
void Compare(const _Long& list, const _Long& list2);


int main()
{
    setlocale(LC_ALL, "ru");
    string str1, str2;

    /*Input(str1, "Введите первое двоичное число: ");
    Input(str2, "Введите второе двоичное число: ");
    */
    _Long list("11110");
    _Long list2("110");

    char action;
    while (true) {
        PrintInterface();
        action = _getch();

        if (action == 43) {
            Print("\nСложение", true);
            _Long* summedList = list.Sum(list2);
            Print("Сумма(2)  = " + summedList->GetFull(), true);
        }
        if (action == 42) {
            Print("\nУмножение", true);
            _Long* multipledList = list.Multiply(list2);
            Print("Произведение(2)  = " + multipledList->GetFull(), true);
        }
        if (action == 45) {
            Print("\nВычитание", true);
            _Long* diffedList = list.Diff(list2);
            Print("Разница(2)  = " + diffedList->GetFull(), true);
        }
        if (action == 47) {
            Print("\nДеление", true);
            _Long* dividedList = list.Division(list2);
            Print("Частное(2)  = " + dividedList->GetFull(), true);
        }
        if (action == 61) {
            Print("\nСравнение (true, false)", true);
            cout << list.GetFull() << " == " << list2.GetFull() << " is " << (list == list2) << endl;
            cout << list.GetFull() << " != " << list2.GetFull() << " is " << (list != list2) << endl;
            cout << list.GetFull() << " >= " << list2.GetFull() << " is " << (list >= list2) << endl;
            cout << list.GetFull() << " <= " << list2.GetFull() << " is " << (list <= list2) << endl;
            cout << list.GetFull() << " > " << list2.GetFull() << " is " << (list > list2) << endl;
            cout << list.GetFull() << " < " << list2.GetFull() << " is " << (list < list2) << endl;
        }
        if (action == 50) {
            short listNumber;
            UInt pos;

            Print("\nУдаление", true);
            PrintLists(list, list2);
            Input(listNumber, "Выберите список");
            if (listNumber > 2 || listNumber < 1) {
                cout << "1 или 2" << endl;
                continue;
            }
            Input(pos, "Введите номер элемента");

            if (listNumber == 1) {
                Print("До: " + list.GetFull(), true);
                list.Remove(pos);
                Print("После: " + list.GetFull(), true);
            }
            if (listNumber == 2) {
                Print("До: " + list2.GetFull(), true);
                list2.Remove(pos);
                Print("После: " + list2.GetFull(), true);
            }


        }
        if (action == 49) {
            short listNumber;
            UInt pos;
            UChar value;


            Print("\nДобавление", true);
            PrintLists(list, list2);
            Input(listNumber, "Выберите список");
            if (listNumber > 2 || listNumber < 1) {
                cout << "1 или 2" << endl;
                continue;
            }
            Input(pos, "Введите позицию для вставки");
            Input(value, "Введите цифру для вставки");

            if (listNumber == 1) {
                Print("До: " + list.GetFull(), true);
                list.InsertByPos(pos, value);
                Print("После: " + list.GetFull(), true);
            }
            if (listNumber == 2) {
                Print("До: " + list2.GetFull(), true);
                list2.InsertByPos(pos, value);
                Print("После: " + list2.GetFull(), true);
            }

        }
        if (action == 9) {
            Print("\nСписки:", true);
            PrintLists(list, list2);

        }
        if (action == 27) {
            break;
        }


    }
    system("pause");
    return 0;
}

template<typename T>
void Print(const T& value, const bool hasEndl) {
    if (hasEndl) cout << value << endl;
    else cout << value;
}

template<typename T>
void Input(T& value, const string message) {
    cout << message << endl;
    cin >> value;
}


void Compare(const _Long& list, const _Long& list2) {
    Print(list == list2, true);
    Print(list != list2, true);
    Print(list >= list2, true);
    Print(list <= list2, true);
    Print(list < list2, true);
    Print(list > list2, true);
}

void PrintInterface() {
    Print("\n\033[32;40mВведите\033[0m", true);
    Print("+ чтобы сложить числа", true);
    Print("* чтобы умножить числа", true);
    Print("- чтобы узнать разницу чисел", true);
    Print("/ чтобы разделить числа", true);
    Print("= чтобы сравнить числа", true);
    Print("1 чтобы добавить элемент в список", true);
    Print("2 чтобы удалить элемент из списка", true);
    Print("TAB чтобы посмотреть списки", true);

}

void PrintLists(const _Long& list, const _Long& list2) {
    Print("1) " + list.GetFull() + "\t| " + to_string(list.GetDecimal()), true);
    Print("2) " + list2.GetFull() + "\t| " + to_string(list2.GetDecimal()), true);
}