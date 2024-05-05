#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <string>

bool theoremFerma(int number, int degree, int mod);
bool checkPrimeNumber(int &n);
long int logPowMod(int number, int degree, int mod);
void toBinary(int degree, std::vector<int> &binaryNum);
int extendedAlgEuclid(int a, int b);
std::vector<int> encrypt(const std::string &plain_text, long int secretAlisaKey, int mod);
std::string decrypt(std::vector<int> &ciphertext, long int secretBobKey, int mod);
long int modInverse(long int a, int m);
long int fastPowMod(int number, int degree, int mod);

#endif