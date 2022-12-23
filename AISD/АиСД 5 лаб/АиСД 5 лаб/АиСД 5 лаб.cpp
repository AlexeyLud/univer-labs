/*#include <cstdlib>
#include <iostream>
#include <Windows.h>
using namespace std;

struct Node {//описание структуры очереди
	float number; //информационное поле
	Node* last; //указатель на первый элемент
	Node* next; //указатель на следующий элемент
};

int main() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Node* head = NULL;
	Node* tail = NULL;
	Node* ptrLast = NULL;
	short action = -1;
	while (1) {
		cout << "1. Добавить Элемент\n";
		cout << "2. Просмотр Очереди\n";
		cout << "3. Удалить Элемент\n";
		cout << "4. Поиск Элемента\n";
		cout << "0. Выход\n\n";
		cout << "Ваш Выбор: ";
		cin >> action;
		if (action == 0) break;
		if (action == 1) {       //добавление элемента в начало очереди
			int num = -1;
			cout << "Введите Число: ";
			cin >> num;
			Node* ptr = new (Node);
			ptr->number = num;
			ptr->next = NULL;
			tail = ptr;
			if (head == NULL) {
				head = ptr;
				ptrLast = ptr;
				ptr->last = NULL;
				continue;
			}
			ptr->last = ptrLast;
			ptrLast->next = ptr;
			ptrLast = ptr;
			continue;
		}
		if (action == 2) {     //просмотр очереди
			Node* ptr = NULL;
			if (head == NULL) {
				cout << "\t ОЧЕРЕДЬ ПУСТА \n\n";
				continue;
			}
			cout << " ---------ОЧЕРЕДЬ--------- \n\n";
			ptr = tail;
			while (1) {
				cout << ptr->number << " ";
				if (ptr->last == 0)
					break;
				ptr = ptr->last;
			}
			cout << "\n\n";
			continue;
		}
		if (action == 3) {         //удаление элемента из хвоста очереди
			Node* pt = NULL;
			if (head == NULL) {
				cout << "\t ОЧЕРЕДЬ ПУСТА \n\n";
				continue;
			}
			if (head->next == NULL) {
				head = NULL;
				tail = NULL;
				delete (tail);
				continue;
			}
			pt = head;
			head = pt->next;
			head->last = NULL;
			delete (pt);
			continue;
		}
		if (action == 4) {          //поиск элемента в очереди
			Node* ptr = NULL;
			int key = -1;
			if (head == NULL) {
				cout << "\t!!! СПИСОК ПУСТ !!!\n\n";
				continue;
			}
			cout << "Введите элемент для поиска: ";
			cin >> key;
			ptr = head;
			while (1) {
				if (key == ptr->number) {
					cout << "\n\t ЭЛЕМЕНТ НАЙДЕН \n";
					break;
				}
				if (ptr->next == NULL) {
					cout << "\n\t ЭЛЕМЕНТ НЕ НАЙДЕН \n";
					break;
				}
				ptr = ptr->next;
			}
			continue;
		}
		if (action > 4) {
			cout << "\t НЕВЕРНЫЙ ВЫБОР. ПОВТОРИТЕ ВВОД \n\n";
			continue;
		}
	}
}*/



#include <iostream>
#include <Windows.h>
using namespace std;

struct Node { //описание узла списка
	float data; //информационное поле
	Node* next; //указатель на следующий элемент
};

struct Queue { //описание очереди
	int size; //счетчик размера очереди
	Node* first; //указатель на начало очереди
	Node* last; //указатель на конец очереди
};

bool isEmpty(Queue* arr) { //проверка очереди на пустоту
	if (arr->first == arr->last) return true;
	else return false;
}

int FirstElement(Queue* arr) { //вывод начального элемента
	return arr->first->data;
}

void View(Queue* arr){ //вывод очереди со сдвигом
	Queue* temp = new Queue;
	temp->first = arr->first;
	while (temp->first != NULL){
		cout << "|" << temp->first->data << "|";
		temp->first = temp->first->next;
	}
}

void Add(Queue*& arr, const int f) { //добавление элемента
	const int n = 10;
    float a[n];
	int j = 0;
	for (int i = 0; i < n; i++) {
		cout << "Введите " << i << " элемент: ";
		cin >> a[i];
		Node* temp = new Node;;
		temp->data = a[i];
		if (arr->first == NULL){
			arr->first = temp; arr->first->next = NULL;
			arr->last = temp; arr->last->next = NULL;
		}
		else{
			if (temp->data < arr->first->data){
				arr->last->next = temp;
				arr->last = temp;
				arr->last->next = NULL;
			}
			else{
				temp->next = arr->first;
				arr->first = temp;
			}
		}
		arr->size++;
	}
	cout << endl << "Очередь: " << endl;
	View(arr);
	cout << endl;
}

int Size(Queue* arr) { //размер очереди
	return arr->size;
}

int main() { //главная функция
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Queue* arr = new Queue;
	arr->first = NULL;
	arr->last = NULL;
	arr->size = 0;
	const int n = 10;
	char number;
	do
	{
		cout << "1. Введите элементы очереди" << endl;
		cout << "2. Узнать верхний элемент" << endl;
		cout << "3. Вывести размер очереди" << endl;
		cout << "0. Выйти" << endl;
		cout << "Номер команды > "; cin >> number;
		switch (number){
		case '1':
			Add(arr, n);
			break;
		case '2':
			if (isEmpty(arr)) cout << endl << "Очередь пуста" << endl;
			else  cout << "\nНачальный элемент: " << FirstElement(arr) << endl;
			break;
		case '3':
			if (isEmpty(arr)) cout << endl << "Очередь пуста" << endl;
			else cout << "\nРазмер очереди: " << Size(arr) << endl;
			break;
		case '0': break;
		default: cout << endl << "Команда не определена" << endl;
			break;
		}
	} while (number != '0');
	system("pause");
	return 0;
}