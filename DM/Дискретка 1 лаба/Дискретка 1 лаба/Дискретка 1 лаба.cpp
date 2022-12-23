#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;

const int N = 5;

void Print(int A[], int n) // булеан мн А
{
    int i = 0;
    cout << "{ ";
    while(n)
    {
        if (n & 1)
        {
            cout << A[i] << " ";
        }
        i++;
        n >>= 1;
    }
    cout << "}" << endl;
}

void Sort_Merge(int first, int last, int* arr, int N) { // сортировка слиянием
    if (last == first) {
        return;
    }
    if (last - first == 1) {
        if (arr[last] < arr[first]) {
            swap(arr[last], arr[first]);
        }
        return;
    }
    int middle = (last + first) / 2;
    Sort_Merge(first, middle, arr, N);
    Sort_Merge(middle + 1, last, arr, N);

    int* ar = new int[N],
    xf = first,
    x = middle + 1,
    c = 0;
    while (last - first + 1 != c)
    {
        if (xf > middle) {
            ar[c++] = arr[x++];
        }
        else if (x > last) {
            ar[c++] = arr[xf++];
        }
        else if (arr[xf] > arr[x]) {
            ar[c++] = arr[x++];
        }
        else ar[c++] = arr[xf++];
    }
    for (int i = 0; i < c; i++) {
        arr[i + first] = ar[i];
    }
    delete[] ar;
}

void Obedinenie(int A[], int nA, int B[], int nB) { // объединение множеств слиянием
    cout << "-----------------" << endl;
    cout << "|Задание 2|" << endl;
    cout << "-----------------" << endl;
    cout << "Сортировка слиянием" << endl;
    int* arr = new int[nA + nB];
    for (int i = 0; i < nA; i++) {
        arr[i] = A[i];
    }
    for (int i = nA; i < nA + nB; i++) {
        arr[i] = B[i - nA];
    }
    cout << "Неотсортированный массив" << endl;
    for (int i = 0; i < nA + nB; i++) {
        cout << arr[i] << " ";
    }
    Sort_Merge(0, nA + nB - 1, arr, nA + nB);
    cout << endl << "Oтсортированный массив:" << endl;
    for (int i = 0; i < nA + nB; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    delete[]arr;
}

void Peresechenie(int A[], int B[], int U[], int nU, int nA, int nB) { // пересечение мн с маской
    cout << "-----------------" << endl;
    cout << "|Задание 3|" << endl;
    cout << "-----------------" << endl;
    cout << "Пересечение множеств AnB с помощью маски." << endl;
    int** Maska = new int* [N];
    for (int i = 0; i < N; i++) {
        Maska[i] = new int[nU];
    }
    for (int i = 0, j = 0, k = 0; i < nU; i++) 
    {
        if (U[i] == A[i - j]) {
            Maska[0][i] = 1;
        }
        else { Maska[0][i] = 0; j++; }

        if (U[i] == B[i - k]) {
            Maska[1][i] = 1;
        }
        else {  Maska[1][i] = 0; k++; }
    }
    cout << "A = {";
    for (int i = 0; i < nA; i++) {
        cout << A[i] << " ";
    } cout << "}" << endl;

    cout << "B = {";
    for (int i = 0; i < nB; i++) {
        cout << B[i] << " ";
    } cout << "}" << endl;

    cout << "Пересечение AnB = {";
    for (int i = 0; i < nU; i++) {
        if (Maska[0][i] & Maska[1][i]) {
            cout << U[i] << ", ";
        }
    }
    cout << '\b' << '\b' << "}" << endl;
    for (int i = 0; i < 2; i++) {
        delete[] Maska[i];
    }
    delete[] Maska;
}

void Proizvedenie(int A[], int B[], int nA, int nB) { // прямое произведение мн.
    cout << "-----------------" << endl;
    cout << "|Задание 4|" << endl;
    cout << "-----------------" << endl;
    cout << "Произведение множеств AxB" << endl;
    int power_proizvedeniy = nA * nB;
    for (int i = 0; i < nA; i++) {
        for (int j = 0; j < nB; j++) {
            cout << "(" << A[i] << ", " << B[j] << "); ";
        }
        cout << endl;
    }
    cout << endl << "Мощность данного произведения |AxB| = " << power_proizvedeniy << endl;
}

void Vichislenie(int A[], int B[], int C[], int U[], int nU, int nA, int nB, int nC) { // вычисление выражения
    cout << "-----------------" << endl;
    cout << "|Задание 5|" << endl;
    cout << "-----------------" << endl;
    cout << "Вычисление выражения" << endl;
    int** Maska = new int* [N];
    for (int i = 0; i < N; i++) {
        Maska[i] = new int[nU];
    }
    for (int i = 0, j = 0, k = 0, z = 0; i < nU; i++)
    {
        if (U[i] == A[i - j]) {
            Maska[0][i] = 1;
        }
        else { Maska[0][i] = 0; j++; }

        if (U[i] == B[i - k]) {
            Maska[1][i] = 1;
        }
        else { Maska[1][i] = 0; k++; }

        if (U[i] == C[i - z]) {
            Maska[2][i] = 1;
        }
        else { Maska[2][i] = 0; z++; }
    }

    cout << "_" << endl;
    cout << "A \\ (B u C) = ";
    cout << "{";
    for (int i = 0; i < nU; i++) {
        if ( ( (!Maska[0][i]) != (Maska[1][i] | Maska[2][i]) ) && Maska[0][i] == 0){
            cout << U[i] << ", ";
        }
    }
    cout << '\b' << '\b' << "}" << endl;
    for (int i = 0; i < 3; i++) {
        delete[] Maska[i];
    }
    delete[] Maska;
} 

struct list { // список
    int data;
    list* next;
};

void Add_list(list*& head, int data) { //добавление записи в список
    list* new_node = new list;
    new_node->data = data;
    new_node->next = NULL;

    if (head == NULL) {
        head = new_node;
    }
    else {
        list* q = head;
        while (q->next) {
            q = q->next;
        }
        q->next = new_node;
    }
}
void Print(list* head) { //вывод спискa 
    for (int i = 0; head; i++) {
        cout << head->data;
        if (head->next != NULL) {
            cout << ", ";
        }
        head = head->next;
    }
}

void Razbienie(int arr[], int N) { // разбиение множеств
   list** elements = new list * [pow(2, N)]; // указатель на элементы списка
    for (int i = 0; i < pow(2, N); i++) {
        list* head = NULL;
        for (int j = 0, num = i; num > 0; j++) {
            if (num % 2 == 1) {
                Add_list(head, arr[j]);
            }num /= 2;
        }
        elements[i] = head;
    }
    cout << "{ ";
    for (int i = 0; i < N; i++) {
        cout << "{";
        cout << arr[i];
        cout << "}";
        cout << ", ";
    }
    cout << "\b }" << endl;
    for (int i = 1, j = pow(2, N) - 2; i < pow(2, N) / 2; i++, j--) {
        cout << "{ {";
        Print(elements[i]);
        cout << "}, {";
        Print(elements[j]);
        cout << "} }" << endl;
    } cout << "{ {";
    Print(elements[int(pow(2, N) - 1)]);
    cout << "} }" << endl;
    delete[] elements;

}

void Kod_Grey(int A[], int nA) { // бинарный код Грея
    cout << "-----------------" << endl;
    cout << "|Задание 8|" << endl;
    cout << "-----------------" << endl;
    cout << "Построить бинарный код Грея для множества А = { 1,2,3,4,5 }" << endl;
    int* kod_grey = new int[N];
    for (int i = 0; i < nA; i++) {
        cout << A[i] << '\t';
        A[i] = A[i] ^ (A[i] >> 1);  // бинарный сдвиг
        cout << "(" << A[i] << ")";
        for (int j = 3; j >= 0; j--) {
            kod_grey[j] = A[i] % 2;
            A[i] /= 2;
        }
        for (int j = 0; j < 4; j++) {
            cout << kod_grey[j];
        }
        cout << endl;
    }
    delete[] kod_grey;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int len,
        i,
        elem,
        U[] = { 1,2,3,4,5,6,7,8,9,10,11 },
        nU = 11,
        nA,
        nB,
        nC;
    len = 1 << N;
    cout << "Введите количество элементов множества А: ";
    cin >> nA;
    int* A = new int[nA];
    for (int i = 0; i < nA; i++) {
        cout << "Введите " << i << " элемент: ";
        cin >> elem; A[i] = elem;
    } cout << endl;

    cout << "Введите количество элементов множества В: ";
    cin >> nB;
    int* B = new int[nB];
    for (int i = 0; i < nB; i++) {
        cout << "Введите " << i << " элемент: ";
        cin >> elem; B[i] = elem;
    } cout << endl;

    cout << "Введите количество элементов множества C: ";
    cin >> nC;
    int* C = new int[nC];
    for (int i = 0; i < nC; i++) {
        cout << "Введите " << i << " элемент: ";
        cin >> elem; C[i] = elem;
    } cout << endl;

    cout << "Множество A = { ";
    for (int i = 0; i < nA; i++) {
        cout << A[i] << " ";
    } cout << "}" << endl;

    cout << "Множество B = { ";
    for (int i = 0; i < nB; i++) {
        cout << B[i] << " ";
    } cout << "}" << endl;

    cout << "Множество C = { ";
    for (int i = 0; i < nC; i++) {
        cout << C[i] << " ";
    } cout << "}" << endl;
    system("pause");
    system("cls");

    cout << "-----------------" << endl;
    cout << "|Задание 1|" << endl;
    cout << "-----------------" << endl;
    cout << "Булеан множества А" << endl;
    for (i = 0; i < len; i++){
        Print(A, i);
    }
    cout << "Мощность данного булеана |A| = " << pow(2, N) << endl;
    system("pause");
    system("cls");

    Obedinenie(A, nA, B, nB);
    system("pause");
    system("cls");

    Peresechenie(A, B, U, nU, nA, nB);
    system("pause");
    system("cls");

    Proizvedenie(A, B, nA, nB);
    system("pause");
    system("cls");

    Vichislenie(A, B, C, U, nU, nA, nB, nC);
    system("pause");
    system("cls");

    cout << "-----------------" << endl;
    cout << "|Задание 7|" << endl;
    cout << "-----------------" << endl;
    cout << "Разбиение множества А" << endl;
    Razbienie(A, nA); cout << endl;
    system("pause");
    system("cls");

    Kod_Grey(A, nA);
    system("pause");
    system("cls");

    return 0;
}
