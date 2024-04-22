#include <iostream>
#include "mainH.h"

using namespace std;
int main()
{
    cout << "base: ";
    int base;
    cin >> base;

    cout << "degree: ";
    int degree;
    cin >> degree;

    cout << "degree degree: ";
    int degreeDegree;
    cin >> degreeDegree;

    cout << "\n";

    //
    /*на примере (3^7) ^ 8
        сначала n =  3^7mod 10
        потом считаем n^8 mod m
    */

    int lastDigitNumber = fastPowMod(base, fastPowMod(degree, degreeDegree, 10), 10); // на десять для последнего числа
    cout << "последнее число: " << lastDigitNumber;

    cout << "\n";
    return 0;
}