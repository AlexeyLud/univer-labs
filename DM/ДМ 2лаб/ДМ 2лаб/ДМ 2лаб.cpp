#include <iostream>
#include <Windows.h>
using namespace std;

// funkcii zadanie 1
void Function() 
{
	int sum = 0,
		B[4] = { 1,2,3,4 },
		nB = 4,
		C[4] = { 5,6,7,8 },
		nC = 4,
		S[4][2] = { {1,5},{2,5},{3,6},{4,8} },
		matrica[4][4];
	bool p1 = true, p2 = true;
	cout << "Отношение (1,5),(2,5),(3,6),(4,8)" << endl;
	for (int i = 0, k = 0; i < nB; i++) {
		for (int j = 0; j < nC; j++) {
			if (B[i] == S[k][0] && C[j] == S[k][1]) {
				matrica[i][j] = 1;
				k++;
			}
			else matrica[i][j] = 0;
			cout << matrica[i][j] << " ";
		}cout << endl;
	}
	for (int i = 0; i < nB; i++) {
		for (int j = 0; j < nC; j++) {
			sum += matrica[i][j];
		}
	}
	if (sum == nB) {
		cout << "Данное отношение является функцией. ";
		sum = 0;
		for (int i = 0; i < nC; i++) {
			for (int j = 0; j < nB; j++) {
				sum += matrica[j][i];
			}

			if ((sum > 1) && (p1 == true)) {
				p1 = false;
			}
			if ((sum == 0) && (p2 == true)) {
				p2 = false;
			}
			sum = 0;
		}
		if (p2 == true && p1 == true) {
			cout << "Биективна ";
		}
		else
			if (p2 == true) {
				cout << "Сюръективна и ";
				cout << "Не инъективна";
			}
			else {
				cout << "Не сюръективна и ";
				if (p1 == true) {
					cout << "Инъективна ";
				}
				else {
					cout << "Не инъективна ";
				}
			}
	}
	else {
		cout << "Данное отношение НЕ является функцией" << endl;
	}
	cout << endl;
}

void MatricaOtnosheniy(int a[], int b[], int num) {
	cout << "Матрица R1" << endl;
	int** matrica1 = new int* [num];
	for (int i = 0; i < num; i++) {
		matrica1[i] = new int[num];
	}
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (a[i] < b[j] || a[i] == b[j]) {
				matrica1[i][j] = 1;
			}
			else {
				matrica1[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			cout << matrica1[i][j] << " ";
		} cout << endl;
	} cout << endl;

	cout << "Матрица R2" << endl;
	int** matrica2 = new int* [num];
	for (int i = 0; i < num; i++) {
		matrica2[i] = new int[num];
	}
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (a[i] == 3 * b[j]) {
				matrica2[i][j] = 1;
			}
			else {
				matrica2[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			cout << matrica2[i][j] << " ";
		} cout << endl;
	} cout << endl;
	system("pause");
	system("cls");

	// obratnoe otnoshenie
	cout << "-----------------" << endl;
	cout << "|Задание 2|" << endl;
	cout << "-----------------" << endl;
	cout << "Обратное отношение и дополнение отношений" << endl;
	cout << "Обратное R1" << endl;
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			cout << matrica1[j][i] << " ";
		} cout << endl;
	} cout << endl;

	cout << "Обратное R2" << endl;
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			cout << matrica2[j][i] << " ";
		} cout << endl;
	} cout << endl;
	system("pause");
	system("cls");

	// dopolnenie otnosheniy
	cout << "Дополнение R1" << endl;
	int** convert1 = new int* [num];
	for (int i = 0; i < num; i++) {
		convert1[i] = new int[num];
	}
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (matrica1[i][j] == 1) {
				convert1[i][j] = 0;
			}
			else {
				convert1[i][j] = 1;
			}
		}
	}
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			cout << convert1[i][j] << " ";
		} cout << endl;
	} cout << endl;

	cout << "Дополнение R2" << endl;
	int** convert2 = new int* [num];
	for (int i = 0; i < num; i++) {
		convert2[i] = new int[num];
	}
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (matrica2[i][j] == 1) {
				convert2[i][j] = 0;
			}
			else {
				convert2[i][j] = 1;
			}
		}
	}
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			cout << convert2[i][j] << " ";
		} cout << endl;
	} cout << endl;
	system("pause");
	system("cls");

	// floid-yorsholl
	cout << "-----------------" << endl;
	cout << "|Задание 4|" << endl;
	cout << "-----------------" << endl;
	cout << "Алгоритм Флойда-Уоршолла" << endl;
	cout << "Транзитивное замыкание" << endl;
	for (int k = 0; k < num; k++) {
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < num; j++) {
				matrica2[i][j] = matrica2[i][j] || matrica2[i][k] && matrica2[k][j];
			}
		}
	} cout << endl;
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			cout << matrica2[i][j] << " ";
		} cout << endl;
	} cout << endl;
	system("pause");
	system("cls");
}
	
void Compozitciya(int a[], int b[], int num)
{
     int** matrica1 = new int* [num];
	 for (int i = 0; i < num; i++) {
		 matrica1[i] = new int[num];
	 }
	 for (int i = 0; i < num; i++) {
		 for (int j = 0; j < num; j++) {
			 if (a[i] < b[j] || a[i] == b[j]) {
				 matrica1[i][j] = 1;
			 }
			 else {
				 matrica1[i][j] = 0;
			 }
		 }
	 } cout << endl;

	int** matrica2 = new int* [num];
	for (int i = 0; i < num; i++) {
		matrica2[i] = new int[num];
	}
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (a[i] == 3 * b[j]) {
				matrica2[i][j] = 1;
			}
			else {
				matrica2[i][j] = 0;
			}
		}
	}
	int** R = new int* [num];
	for (int i = 0; i < num; i++) {
		R[i] = new int[num];
	}
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			R[i][j] = 0;
		}
	}
						
	cout << " Композиция R1R2 " << endl;
    for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			for (int k = 0; k < num; k++) {
				R[i][j] |= matrica1[i][k] & matrica2[k][j];
		    }
		}
	}
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			cout << R[i][j] << " ";
		} cout << endl;
	} cout << endl;

	cout << " Композиция R2R1 " << endl;
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			for (int k = 0; k < num; k++) {
				R[i][j] |= matrica2[i][k] & matrica1[k][j];
			}
		}
	}
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			cout << R[i][j] << " ";
		} cout << endl;
	} 
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

	int a[] = { 1,2,3,4,5,6,7,8,9,10 };
	int b[] = { 1,2,3,4,5,6,7,8,9,10 };
	int num = 10;
	int** matrica1 = new int* [num];
	int** matrica2 = new int* [num];

	cout << "-----------------" << endl;
	cout << "|Задание 1|" << endl;
	cout << "-----------------" << endl;
	cout << "Матрицы отношений R1 и R2" << endl;
	MatricaOtnosheniy(a, b, num); // 1
	system("pause");
	system("cls");

	cout << "-----------------" << endl;
	cout << "|Задание 5|" << endl;
	cout << "-----------------" << endl;
	cout << "Композиция R1oR2 и R2oR1 " << endl;
	Compozitciya(a, b, num); // 5
	system("pause");
	system("cls");

	cout << "-----------------" << endl;
	cout << "|Задание 1|" << endl;
	cout << "-----------------" << endl;
	cout << "Функция(тип)" << endl;
	Function(); // function
    system("pause");
    system("cls");
    return 0;
}
