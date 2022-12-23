
/*#include <iostream>
#include <ctime>
#include <string.h>
using namespace std;

int function(char* str, int len)
{
	char temp;
	for (int i = 0; i < len; i = i + 2) {
		temp = str[i];
		str[i] = str[i + 1];
		str[i + 1] = temp;
	}
	cout << str;
	return 0;
}

int main()
{
	setlocale(LC_ALL, "rus");
	char str[100];
	cout << "Введите строку: ";
	cin >> str;
	int len = strlen(str);
	cout << "Результат: ";
	clock_t start = clock();
	function(str, len);
	clock_t finish = clock();
	cout << endl;
	cout << "Время:" << finish - start << endl;
	return 0;
} */
