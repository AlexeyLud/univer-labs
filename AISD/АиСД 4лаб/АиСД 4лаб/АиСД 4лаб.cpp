#include <iostream>
#include <ctime>
using namespace std;
struct massiv{ 
	int m; 
              };
void BubbleSort(massiv* arr, int n) {// сортировка пузырька
	int tmp;
	for (int i = 0; i < n - 1; ++i) // i - номер прохода
	{
		for (int j = 0; j < n - 1; ++j) // внутренний цикл прохода
		{
			if (arr[j + 1].m < arr[j].m)
			{
				tmp = arr[j].m;
				arr[j].m = arr[j + 1].m;
				arr[j + 1].m = tmp;
			}
		}
	}
}
int main()
{
	setlocale(LC_ALL, "rus");
	srand(time_t(NULL));
	int n = 0;
	int k = 0;
	cout << "Введите количество элементов массива : ";
	cin >> n;
	massiv* arr = new massiv[n];
	cout << " Массив:" << endl;
	cout << "arr[";
	for (int i = 0; i < n; i++)
	{
		arr[i].m = rand() % 40;
		cout << arr[i].m << ",";
	}
	cout << "]";
	BubbleSort(arr, n);
	cout << "\nОтсортированный массив:" << endl;
	cout << "SortArr[";
	for (int i = 0; i < n; i++) 
	{
		cout  << arr[i].m << ",";
	}
	cout << "]";
	cout << "\nВсе элементы, которые встречаютя один раз => ";
	cout << " [ ";
	for (int i = 0; i < n; i++)
	{
		if (arr[i].m != arr[i - 1].m && arr[i].m != arr[i + 1].m) 
		{
			++k;
			cout  << arr[i].m << ",";
		}
	}
	    cout << "]";
		cout << "\nКоличество элементов, которые повторяются один раз => " << k << endl;
		delete[] arr;
		system("pause");
		return 0;	
}

