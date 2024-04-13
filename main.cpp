#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <tuple>

using namespace std;

bool theoremFerma(int number, int degree, int mod);
unsigned long long logPowMod(int number, int degree, int mod);
int algEuclid(int number_1, int number_2);
tuple<int, int, int> extendedAlgEuclid(int a, int b); // вернет НОД x y

unsigned long int fastPowMod(int number, int degree, int mod);

void printVector(const vector<int> &vec);
bool checkPrimeNumber(int &number);
void toBinary(int degree, vector<int> &binaryNum);

int main()
{
    cout << logPowMod(3, 100, 7) << " - " << fastPowMod(3, 100, 7);
}

bool theoremFerma(int number, int degree, int mod)
{
    if (checkPrimeNumber(mod) && (number % degree != 0) && degree == mod - 1)
    {
        cout << number << "^" << degree << " mod" << mod << " = "
             << "1 mod" << mod << endl;
        return true;
    }
    return false;
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
    cout << endl;
    return result;
}

int algEuclid(int number_1, int number_2)
{
    while (number_1 != 0 && number_2 != 0)
    {
        if (number_1 > number_2)
        {
            number_1 %= number_2;
        }
        else
        {
            number_2 %= number_1;
        }
    }

    return number_1 + number_2;
}

tuple<int, int, int> extendedAlgEuclid(int a, int b)
{

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

    return make_tuple(table[table.size() - 2][0], x, y);
}

unsigned long int fastPowMod(int number, int degree, int mod) // при mod = 10 найдем остаток
{                                                             // основан на полове степени
    if (degree == 0)
        return 1;

    unsigned long int result = fastPowMod(number % mod, degree / 2, mod) % mod;

    if (degree % 2 == 0) // если четно a^(2n) = (a^n)^2
        return (result * result) % mod;

    else // a^3n = a * a^2n
        return ((number % mod) * ((result * result) % mod)) % mod;
}

void printVector(const vector<int> &vec)
{

    for (auto i : vec)
    {
        std::cout << i << " ";
    }
}

bool checkPrimeNumber(int &n)
{
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return false;
    return true;
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