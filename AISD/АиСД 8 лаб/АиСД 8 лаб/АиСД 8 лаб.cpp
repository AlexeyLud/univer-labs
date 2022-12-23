#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const int n = 6;
    int array[n][n]; // матрица связей
    int length[n]; // минимальное расстояние
    int v[n]; // посещенные вершины
    int temp, min_index, min;
    int start_index = 0;
    for (int i = 0; i < n; i++){  // Инициализация матрицы связей
        array[i][i] = 0;
        for (int j = i + 1; j < n; j++) {
           cout <<"Введите расстояние " << i + 1 << " - " << j + 1 << ": ";
            cin >> temp;
            array[i][j] = temp;
            array[j][i] = temp;
        }
    }
    cout << "Матрица смежности:" << endl;
    for (int i = 0; i < n; i++){ // Вывод матрицы связей
        for (int j = 0; j < n; j++) {
            cout << setw(5) << right << array[i][j] << " ";
        }
        cout << "\n";
    }
    for (int i = 0; i < n; i++){ // Инициализация вершин и расстояний
        length[i] = 10000;
        v[i] = 1;
    }
    length[start_index] = 0;

    do {  // Шаг алгоритма
        min_index = 10000;
        min = 10000;
        for (int i = 0; i < n; i++){ 
            if ((v[i] == 1) && (length[i] < min)){ // Если вершину ещё не обошли и вес меньше min
                min = length[i]; // Переприсваиваем значения
                min_index = i;
            }
        }
        // Добавляем найденный минимальный вес
        // к текущему весу вершины
        // и сравниваем с текущим минимальным весом вершины
        if (min_index != 10000){
            for (int i = 0; i < n; i++){
                if (array[min_index][i] > 0){
                    temp = min + array[min_index][i];
                    if (temp < length[i]){
                        length[i] = temp;
                    }
                }
            }
            v[min_index] = 0;
        }
    } while(min_index < 10000);

    cout << "\nКратчайшие расстояния до вершин:\n";
    for (int i = 0; i < n; i++){
        cout << length[i] << "    ";
    }
    // Восстановление пути
    int arr[n]; // массив посещенных вершин
    int end; // индекс конечной вершины
    cout << "\nВведите индекс конечной вершины для поиска кратчайшего пути => ";
    cin >> end;
    arr[0] = end + 1; // начальный элемент - конечная вершина
    int k = 1; // индекс предыдущей вершины
    int weight = length[end]; // вес конечной вершины
    while (end != start_index) // пока не дошли до начальной вершины
    {
        for (int i = 0; i < n; i++) { // просматриваем все вершины
            if (array[i][end] != 0)   // если связь есть
            {
                int temp = weight - array[i][end]; // определяем вес пути из предыдущей вершины
                if (temp == length[i]) // если вес совпал с рассчитанным
                {                 // значит из этой вершины и был переход
                    weight = temp; // сохраняем новый вес
                    end = i;       // сохраняем предыдущую вершину
                    arr[k] = i + 1; // и записываем ее в массив
                    k++;
                }
            }
        }
    }
    // Вывод пути (начальная вершина оказалась в конце массива из k элементов)
    cout << "\nВывод кратчайшего пути\n";
    for (int i = k - 1; i >= 0; i--) {
        cout << arr[i] << "   ";
    }
    cout << endl;
    system("pause");
    return 0;
}
