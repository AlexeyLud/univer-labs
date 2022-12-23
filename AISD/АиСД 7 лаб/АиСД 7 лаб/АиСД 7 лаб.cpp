#include <iostream>
#include <Windows.h>
#include <queue> // очередь
#include <stack> // стек
using namespace std;

struct List {
    int start;
    int end;
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    queue<int> Queue;
    stack<List> Stack;
    int num;
    List graph;
    int array[7][7] = { { 0, 1, 1, 0, 0, 0, 1 }, // матрица смежности
                        { 1, 0, 1, 1, 0, 0, 0 },
                        { 1, 1, 0, 0, 0, 0, 0 },
                        { 0, 1, 0, 0, 1, 0, 0 },
                        { 0, 0, 0, 1, 0, 1, 0 },
                        { 0, 0, 0, 0, 1, 0, 1 },
                        { 1, 0, 0, 0, 0, 1, 0 } 
                     };
    int temp[7]; // вершины графа
    for (int i = 0; i < 7; i++) // исходно все вершины равны 0
        temp[i] = 0;
        cout << "N = "; 
        cin >> num;
        num--;
    Queue.push(0); // помещаем в очередь первую вершину
    while (!Queue.empty())
    {
        int Node = Queue.front(); // извлекаем вершину
        Queue.pop();
        temp[Node] = 2; // отмечаем ее как посещенную
        for (int j = 0; j < 7; j++)
        {
            if (array[Node][j] == 1 && temp[j] == 0) // если вершина смежная и не обнаружена
            { 
                Queue.push(j); // добавляем ее в очередь
                temp[j] = 1; // отмечаем вершину как обнаруженную
                graph.start = Node;
                graph.end = j;
                Stack.push(graph);
                if (Node == num) break;
            }
        }
        cout << Node + 1 << endl; // выводим номер вершины
    }
    cout << "Путь до вершины " << num + 1 << endl;
    cout << num + 1;
    while (!Stack.empty()) {
        graph = Stack.top();
        Stack.pop();
        if (graph.end == num) {
            num = graph.start;
            cout << " <- " << num + 1;
        }
    }
    cout << endl;
    system("pause");
    return 0;
}
