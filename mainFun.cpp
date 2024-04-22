#include "mainH.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

bool theoremFerma(int number, int degree, int mod)
{
    if (checkPrimeNumber(mod) && (number % degree != 0) && degree == mod - 1)
    {
        return true;
    }
    return false;
}

bool checkPrimeNumber(int &n)
{
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return false;
    return true;
}

unsigned long long logPowMod(int number, int degree, int mod)
{

    unsigned long long result = 1;    // a^0 -> a^degree
    unsigned long long mult = number; //(a^1, a^2, a^4 ... a^(2^k))

    vector<int> binaryNumber;
    toBinary(degree, binaryNumber); // 1 шаг - перевод degree в 2сс

    for (int i = binaryNumber.size() - 1; i >= 0; i--) // идем по двоичной записи числа degree и как бы переводим в 10сс, только полученные числа будут степенями для number
    {

        if (binaryNumber[i])
        {
            result = (result * mult) % mod;
        }

        mult = (mult * mult) % mod;
    }
    return result;
}

void toBinary(int degree, vector<int> &binaryNum)
{ // перевод в 2сс

    while (degree > 0)
    {
        binaryNum.push_back(degree % 2); // добавляем остатки от деления на 2
        degree /= 2;                     // и делим число на 2
    }
    reverse(binaryNum.begin(), binaryNum.end()); // после переворачиваем
}

int extendedAlgEuclid(int c, int numberAski)
{

    // cz mod numberAski = 1 или numberAski(-k) + cz = d(numberAski,c)
    // тогда на и не нужно значение 2-го элемента

    int a = c;
    int b = numberAski;
    vector<vector<int>> table;

    // первые две особенные
    vector<int> firstRow = {a, 1, 0, 0};
    vector<int> secondRow = {b, 0, 1, 0};
    table.push_back(firstRow);
    table.push_back(secondRow);

    int r, q, x, y;

    while (true)
    {
        vector<int> prevRow = table[table.size() - 2]; // предпоследняя
        vector<int> currRow = table[table.size() - 1]; // последняя

        r = prevRow[0] % currRow[0]; // остаток от деления  предпоследнего н последнее
        q = prevRow[0] / currRow[0]; // деления  предпоследнего на последнее
        x = prevRow[1] - q * currRow[1];
        y = prevRow[2] - q * currRow[2];

        if (r == 0)
        {
            vector<int> lastRow = {r, x, y, 0};
            table.push_back(lastRow);
            break;
        }

        vector<int> newRow = {r, x, y, q};
        table.push_back(newRow);
    }

    cout << "r\tx\ty\tq" << std::endl;
    for (const vector<int> &row : table)
    {
        cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << std::endl;
    }
    cout << endl;

    vector<int> inverse = table[table.size() - 2];

    return inverse[1] + b;
}

vector<int> encrypt(const string &plain_text, unsigned long int secretAlisaKey, int mod)
{

    vector<int> encryptedCharacters;

    for (char ch : plain_text)
    {
        int numberAski = static_cast<int>(ch); // ASCII
        int c2_val = (numberAski * static_cast<int>(secretAlisaKey)) % mod;
        encryptedCharacters.push_back(c2_val);
    }

    return encryptedCharacters;
}

// для дешифровки
string decrypt(vector<int> &ciphertext, unsigned long int secretBobKey, int mod)
{
    string decrypted_text = "";

    int s_inverse = modInverse(secretBobKey, mod);

    for (int enc_char : ciphertext)
    {
        int numberAski = (enc_char * s_inverse) % mod;
        decrypted_text.push_back(static_cast<char>(numberAski));
    }

    return decrypted_text;
}

unsigned long int modInverse(unsigned long int a, int numberAski)
{
    int m0 = numberAski;
    int y = 0, x = 1;

    if (numberAski == 1)
    {
        return 0;
    }

    while (a > 1)
    {
        int q = a / numberAski;
        int t = numberAski;

        numberAski = a % numberAski, a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0)
    {
        x += m0;
    }

    return x;
}

unsigned long int fastPowMod(int number, int degree, int mod) // при mod = 10 найдем остаток
{                                                             // основан на половине степени
    if (degree == 0)
        return 1;

    unsigned long int result = fastPowMod(number % mod, degree / 2, mod) % mod;

    if (degree % 2 == 0) // если четно a^(2n) = (a^n)^2
        return (result * result) % mod;

    else // a^3n = a * a^2n
        return ((number % mod) * ((result * result) % mod)) % mod;
}