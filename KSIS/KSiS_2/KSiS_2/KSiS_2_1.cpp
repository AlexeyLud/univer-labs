#include <iostream>
#include <ctime>
#include <string.h>
using namespace std;

int function()
{
	char str[100];
	cout << "Введите строку: ";
	cin >> str;
	int len = strlen(str);
	cout << "Результат: ";
	__asm
	{
		lea esi, str
		mov eax, len
		mov bl, 2
		div bl
		mov ecx, eax
		looope :
		inc esi
			mov al, [esi]
			xchg al, [esi - 1]
			mov[esi], al
			inc esi
			loop looope

	}
	cout << str;
	return 0;
}

int main()
{
	setlocale(LC_ALL, "rus");
	clock_t start = clock();
	function();
	clock_t finish = clock();
	cout << endl;
	cout << "Время:" << finish - start << endl;
	return 0;
}