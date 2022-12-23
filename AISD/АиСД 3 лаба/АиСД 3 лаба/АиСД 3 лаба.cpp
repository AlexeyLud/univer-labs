#include <iostream>
#include <iomanip>
#include <ctime>
#include <clocale>
using namespace std;
void BubbleSort(int* arr, int N) {// сортировка пузырька
	int tmp;
	for (int i = 0; i < N - 1; ++i) // i - номер прохода
	{
		for (int j = 0; j < N - 1; ++j) // внутренний цикл прохода
		{
			if (arr[j + 1] < arr[j])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}
int main()
{
	setlocale(LC_ALL, "rus");
	int time = clock();
	int n;
	cout << "Введите количество элементов массива => ";
	cin >> n;
	cout << "\tВведите элементы массива: "<< endl;
	int* key = new int[n];
	cout << " Массив" << endl;
	for (int i = 0; i < n; i++) {
		cout << "key[" << i << "]=";
		cin >> key[i];
	}
	BubbleSort(key, n);
	cout << "Отсортированный массив" << endl;
	for(int i = 0; i < n;i++){
		cout << "key[" << i << "]=" <<key[i] << " ";
	}
	cout << endl;
	cout << "            |"<<endl;
	cout << "Поиск ключа\\|/" << endl;
	int arg;
	bool naideno;
	do {
		int lev = 0, prav = n - 1, k;
		cout << "Введите аргумент поиска – искомый ключ => ";
		cin >> arg;
		if (arg >= 0) 
		{
			if (arg == key[n - 1]) 
			{
				k = n - 1;
				naideno = true;
			}
			else {
				naideno = false;
				do {
					if (arg > key[n - 1]) {
						naideno = false;
						break;
					}
					k = (int)((lev + prav) / 2);
					if (arg == key[k]) 
					{
						naideno = true; break;
					}
					else
						if (arg > key[k])
							lev = k;
						else
							prav = k;
				  } while (naideno == false || (lev == prav - 1));
			}
			if (naideno == true)
				cout << "Ключ найден, его номер =>" << k << endl;
			else
				cout << "Такого ключа нет"<< endl;
		} 
	} while (arg >= 0);
	cout << "T= " << ((float)time) / (double)CLOCKS_PER_SEC << " секунд" << endl;
	delete[] key;
	system("pause");
	return 0;
}
