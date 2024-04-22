#include <iostream>
#include <vector>
#include "mainH.h"

using namespace std;

int main()
{
    cout << "Видите число: ";
    int number;
    cin >> number;

    cout << "Видите mod: ";
    int mod;
    cin >> mod;

    int modInverse = extendedAlgEuclid(number, mod);
    cout << "Обратное число к числу " << number << " по mod " << mod << " = " << modInverse << endl;
    return 0;
}