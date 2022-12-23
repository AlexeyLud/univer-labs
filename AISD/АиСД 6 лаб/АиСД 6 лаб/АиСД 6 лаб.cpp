#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

struct TreeNode
{
    double key;          //ключ узла
    TreeNode* parent;   //родительский узел
    TreeNode* left;    //левый под-узел
    TreeNode* right;  //правый под-узел

    TreeNode(double _key, TreeNode* _parent)
    {
        key = _key;
        parent = _parent;
        left = NULL;
        right = NULL;
    }

    void print() //метод вывода 
    {
        cout << "(";
        if (left != NULL)  //вывод левого поддерева, если оно есть
        {
            left->print();
            cout << " <- ";
        }
        cout << "|" << key << "|";  //вывод значения узла
        //вывод правого поддерева, если оно есть (отображается слева от этого узла со знаком "->")
        if (right != NULL)
        {
            cout << " -> ";
            right->print();
        }
        cout << ")";
    }

    void add(double newKey)    //метод добавления под-узла
    {
        //если добавляемое значение меньше значения узла - отправить его в левое поддерево
        if (newKey < key)
        {
            //если левый узел уже существует - отправить значение в поддерево левого узла
            if (left != NULL)
            {
                left->add(newKey);
            }
            //иначе - создать левый узел с заданным значением и текущим узлом в качестве родителя
            else
            {
                left = new TreeNode(newKey, this);
            }
        }
        //если значение больше - отправить его в правое поддерево
        else if (newKey > key)
        {
            //если правый узел уже существует - отправить значение в поддерево правого узла
            if (right != NULL)
            {
                right->add(newKey);
            }
            //иначе - создать правый узел с заданным значением и текущим узлом в качестве родителя
            else
            {
                right = new TreeNode(newKey, this);
            }
        }
    }
};

//функция поиска суммы ключей с определенного уровня
int SumLevel(TreeNode* tnode, int firstlevel, int endlevel) {
    if (tnode != NULL) {
        firstlevel++;
        if (firstlevel < endlevel) {
            int sum = 0;
            sum += SumLevel(tnode->left, firstlevel, endlevel);
            sum += SumLevel(tnode->right, firstlevel, endlevel);
            return sum;
        }
        else
            return tnode->key;
    }
    else
        return 0;
}

int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    TreeNode* koren = NULL;  //корень дерева
    int num = 0;           //число узлов дерева
    cout << "Введите количество узлов дерева: ";
    cin >> num;   
    cout << "Введите " << num << " значений:" << endl;
    for (int i = 0; i < num; i++) {
        double value;
        cin >> value;
        if (koren != NULL) {
            koren->add(value);
        } 
        else {
            koren = new TreeNode(value, NULL);
        }
    }
    cout << endl << "Дерево:" << endl; //вывод дерева на экран
    koren->print();
    cout << endl << endl;
    int k = 0;    //запрашиваемый уровень узлов дерева
    cout << endl << "Введите значение уровня дерева (нумерация с 0): ";
    cin >> k;                                           
    int nodeSum = SumLevel(koren, -1, k); //вычисление суммы элементов на указанном уровне
    cout << "Сумма узлов на " << k << "-м уровне равна " << nodeSum;
}