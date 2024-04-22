#include <iostream>
#include <vector>
#include "mainH.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "RUS");
    system("chcp 65001");

    cout << "enter baseFirst, enter degreeFirst, enter modFirst\n";

    int baseFirst, degreeFirst, modFirst;

    cin >> baseFirst;
    cin >> degreeFirst;
    cin >> modFirst;

    // Проверка на простоту модуля p
    if (!checkPrimeNumber(modFirst))
    {
        cout << "Модуль p должен быть простым числом." << endl;
        return 0;
    }

    cout << "enter baseSecond, enter degreeSecond, enter modSecond\n";

    int baseSecond, degreeSecond, modSecond;

    cin >> baseSecond;
    cin >> degreeSecond;
    cin >> modSecond;

    // Проверка на простоту модуля p
    if (!checkPrimeNumber(modSecond))
    {
        cout << "Модуль p должен быть простым числом." << endl;
        return 0;
    }

    // Проверка на теорему Ферма First
    if (theoremFerma(baseFirst, degreeFirst, modFirst))
    {
        cout << "Теорема Ферма выполняется для первого числа." << endl;
    }
    else
    {
        cout << "Теорема Ферма не выполняется для первого числа." << endl;
    }

    // Проверка на теорему Ферма Second
    if (theoremFerma(baseFirst, degreeFirst, modFirst))
    {
        cout << "Теорема Ферма выполняется для второго числа." << endl;
    }
    else
    {
        cout << "Теорема Ферма не выполняется для второго числа." << endl;
    }

    int resulFirstNumber = logPowMod(baseFirst, degreeFirst, modFirst);
    int resulSecondNumber = logPowMod(baseSecond, degreeSecond, modSecond);

    // Выводим результаты и сравниваем их по модулю p
    cout << "Результат вычисления a^x mod p: " << resulFirstNumber << endl;
    cout << "Результат вычисления b^y mod p: " << resulSecondNumber << endl;
    if (resulFirstNumber == resulSecondNumber)
        cout << "Оба результата совпадают по модулю p." << endl;
    else
        cout << "Результаты по модулю p не совпадают." << endl;

    return 0;
}