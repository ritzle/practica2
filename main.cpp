#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void printVector(const vector<int> &vec);
bool checkPrimeNumber(int number);

int main()
{
}

// реализация на основе алгоритма "Решето Эратосфена"
bool checkPrimeNumber(int number)
{
    vector<int> SieveEratosthenes(sqrt(number) + 1, 1); // инициализация вектора на кол.чисел = корень из number + 1

    // предполагаем что изначально все числа простые
    for (int i = 2; i < SieveEratosthenes.size(); i++) // можно заменить SieveEratosthenes.size() на number
    {
        if (SieveEratosthenes[i]) // проверка что число простое
        {
            if (number % i == 0) // если есть простое число которое делит number -> number не простое
            {
                return false;
            }

            // по алгоритму Решето Эратосфена убираем все числа у которых есть делитель в виде нашего числа
            for (int j = i * i; j < SieveEratosthenes.size(); j += i) // j=i*i что бы не считать само число
            {
                SieveEratosthenes[j] = 0;
            }
        }
    }

    return true;
}

void printVector(const vector<int> &vec)
{

    for (auto i : vec)
    {
        std::cout << i << " ";
    }
}