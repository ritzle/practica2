#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "mainH.h"

using namespace std;
void dataInput(int &base, int &mod, int &alisaDegree, int &bobDegree);
vector<int> fromStringToVector(string input);
void encryptTheMessage(unsigned long int openAlisaKey, unsigned long int secretAlisaKey, int mod);
void decryptTheMessage(unsigned long int openAlisaKey, unsigned long int secretBobKey, int mod);

// Алиса отправляет сообщение бобу
int main()
{

    int base, mod, alisaDegree, bobDegree;
    dataInput(base, mod, alisaDegree, bobDegree);

    unsigned long int openAlisaKey = fastPowMod(base, alisaDegree, mod);
    unsigned long int openBobKey = fastPowMod(base, bobDegree, mod); // нужен будет только если боб отправляет сообщение

    unsigned long int secretAlisaKey = fastPowMod(openBobKey, alisaDegree, mod);
    unsigned long int secretBobKey = fastPowMod(openAlisaKey, bobDegree, mod);

    encryptTheMessage(openAlisaKey, secretAlisaKey, mod);
    decryptTheMessage(openAlisaKey, secretBobKey, mod);
}

void dataInput(int &base, int &mod, int &alisaDegree, int &bobDegree)
{
    cout << "enter general base: ";
    cin >> base;

    cout << "enter prime number: ";
    cin >> mod;

    if (!checkPrimeNumber(mod))
    {
        cout << "простое число должно быть простым числом." << endl;
        return;
    }

    cout << "Alisa enter degree: ";
    cin >> alisaDegree;

    cout << "Bob enter degree: ";
    cin >> bobDegree;
}

vector<int> fromStringToVector(string input)
{
    istringstream iss(input); // Создаем поток ввода из строки
    int number;
    vector<int> numbers;

    while (iss >> number)
    {
        numbers.push_back(number); // Добавляем числа в вектор
    }

    return numbers;
}

void encryptTheMessage(unsigned long int openAlisaKey, unsigned long int secretAlisaKey, int mod)
{
    std::ifstream fileMessage("messages.txt");                            // Открываем файл для чтения
    std::ofstream fileEncrypted("encryptedMessage.txt", std::ios::trunc); // Открываем файл для записи
    if (fileMessage.is_open())
    { // Проверяем, удалось ли открыть файл
        string message;

        // Считываем сообщения построчно из файла
        while (getline(fileMessage, message))
        {
            vector<int> chiperText = encrypt(message, openAlisaKey, secretAlisaKey, mod);

            if (fileEncrypted.is_open())
            { // Проверяем, удалось ли открыть файл
                for (size_t i = 0; i < chiperText.size(); ++i)
                {
                    fileEncrypted << chiperText[i] << " "; // Записываем элементы массива в файл
                }
                // fileEncrypted << "\n"; если добавить то в расшифровке лишнии пустые строки будут
                //  std::cout << "Массив успешно записан в файл." << std::endl;
            }
            else
            {
                std::cerr << "Не удалось открыть файл для записи." << std::endl; // Выводим сообщение об ошибке, если файл не удалось открыть
            }
        }

        fileMessage.clear(); // Сброс состояния потока

        fileMessage.close();   // Закрываем файл после чтения
        fileEncrypted.close(); // Закрываем файл после записи
    }
    else
    {
        std::cerr << "Unable to open file" << std::endl; // Выводим сообщение об ошибке, если файл не удалось открыть
        fileMessage.close();                             // Закрываем файл после чтения
        fileEncrypted.close();
    }
}

void decryptTheMessage(unsigned long int openAlisaKey, unsigned long int secretBobKey, int mod)
{

    std::ifstream fileEncrypted("encryptedMessage.txt");                  // Открываем файл для чтения
    std::ofstream fileDecrypted("decryptedMessage.txt", std::ios::trunc); // Открываем файл для записи

    if (fileEncrypted.is_open())
    { // Проверяем, удалось ли открыть файл
        string line;

        // Считываем сообщения построчно из файла
        while (getline(fileEncrypted, line))
        {
            vector<int> vecMessage = fromStringToVector(line);

            string decryptedText = decrypt(vecMessage, secretBobKey, mod);

            if (fileDecrypted.is_open())
            {                                          // Проверяем, удалось ли открыть файл
                fileDecrypted << decryptedText << " "; // Записываем элементы массива в файл
                fileDecrypted << "\n";
            }
            else
            {
                std::cerr << "Не удалось открыть файл для записи." << std::endl; // Выводим сообщение об ошибке, если файл не удалось открыть
            }
        }
        fileEncrypted.close(); // Закрываем файл после чтения
        fileDecrypted.close(); // Закрываем файл после записи
    }
    else
    {
        std::cerr << "Unable to open file" << std::endl; // Выводим сообщение об ошибке, если файл не удалось открыть
    }
}