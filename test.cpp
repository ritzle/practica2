#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <tuple>
#include <string>
#include <random>

using namespace std;

bool theoremFerma(int number, int degree, int mod);
unsigned long long logPowMod(int number, int degree, int mod);
int coprimeTest(int number_1, int number_2); // проверяет взаимно простые ли числа
int extendedAlgEuclid(int a, int b);         // c^-1 modm = d;

unsigned long int fastPowMod(int number, int degree, int mod);

void printVector(const vector<int> &vec);
bool checkPrimeNumber(int &number);
void toBinary(int degree, vector<int> &binaryNum);
void CipherHughes();
vector<int> encrypt(const string &plain_text, unsigned long int openAlisaKey, unsigned long int secretAlisaKey, int mod);
string decrypt(vector<int> &ciphertext, unsigned long int secretBobKey, int mod);

unsigned long int modInverse(unsigned long int a, int m)
{
    a = a % m;
    for (int x = 1; x < m; x++)
    {
        if ((a * x) % m == 1)
        {
            return x;
        }
    }
    return 1; // Возвращаем 1, если обратное число не найдено
}

int main()
{
    CipherHughes();
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

int coprimeTest(int number_1, int number_2)
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

int extendedAlgEuclid(int c, int m)
{

    // cz modm = 1 или m(-k) + cz = d(m,c)
    // тогда на и не нужно значение 2-го элемента

    int a = c;
    int b = m;
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

void CipherHughes()
{
    std::ofstream fileAlisa("Alisa.txt", std::ios::trunc); // Открыть файл для записи и очистить его содержимое
    fileAlisa.close();

    std::ofstream fileBob("Bob.txt", std::ios::trunc); // Открыть файл для записи и очистить его содержимое
    fileBob.close();

    int base; // основание
    cout << "enter general base: ";
    cin >> base;

    int mod; // большое простое число
    cout << "enter prime number: ";
    cin >> mod;

    int alisaDegree;
    cout << "Alisa enter degree: ";
    cin >> alisaDegree;
    unsigned long int openAlisaKey = fastPowMod(base, alisaDegree, mod);

    int bobDegree;
    cout << "Bob enter degree: ";
    cin >> bobDegree;
    unsigned long int openBobKey = fastPowMod(base, bobDegree, mod);

    unsigned long int secretAlisaKey = fastPowMod(openBobKey, alisaDegree, mod);
    unsigned long int secretBobKey = fastPowMod(openAlisaKey, bobDegree, mod);

    cout << secretAlisaKey << " " << secretBobKey;
    cout << endl;

    cout << "Enter text: ";
    string text;
    cin.ignore();
    getline(std::cin, text);

    vector<int> chiperText = encrypt(text, openAlisaKey, secretAlisaKey, mod);

    string detext = decrypt(chiperText, secretBobKey, mod);

    cout << detext;
}

// для шифровки
vector<int> encrypt(const string &plain_text, unsigned long int openAlisaKey, unsigned long int secretAlisaKey, int mod)
{
    int c1 = openAlisaKey;
    vector<int> c2;

    int c3 = secretAlisaKey;
    for (char ch : plain_text)
    {
        int m = static_cast<int>(ch); // ASCII
        int c2_val = (m * c3) % mod;
        c2.push_back(c2_val);
    }

    return c2;
}

// для дешифровки
string decrypt(vector<int> &ciphertext, unsigned long int secretBobKey, int mod)
{
    const vector<int> &c2 = ciphertext;
    string decrypted_text = "";

    int s_inverse = modInverse(secretBobKey, mod);

    for (int enc_char : c2)
    {
        int m = (enc_char * s_inverse) % mod;
        decrypted_text.push_back(static_cast<char>(m));
    }

    return decrypted_text;
}
