#include "Header.h"
#include <time.h>
#include <cstdlib>

int GenerateKoefficient(int p)
{
	int koefficient = 0;
	srand(time(0));
	koefficient = rand() % p - 0;
	return koefficient;
}
int GeneratePrimeNumber() //запускать надо перед GenetareHashFunction!!!
{
	int* arrayPrimeNumber = new int[11, 13, 17, 19, 23, 29, 
									31, 37, 41, 43, 47, 53, 
									59, 61, 67, 71];
	int p = rand() % arrayPrimeNumber[15] - arrayPrimeNumber[0];
	delete[] arrayPrimeNumber;
	return p;
}
/*
	p - простое число
	m - р-р хэш-таблицы
	k - кол-во ключей
*/

int GenetareHashFunction(int m, int k, int p)
{
	int hash = 0;
	hash = ((GenerateKoefficient(p - 1) * k + GenerateKoefficient(p)) % p) % m;
	return hash;
}