#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include<iostream>
#include<string>
#include<algorithm>
#include<Windows.h>
#include<conio.h>
using namespace std;
struct Book
{
	string Capture;
	string FIO;
	string Izd;
	int Year;
	int Kol;
	int Kod;
	void ReadFile();
	void PrintFile();
};

void Book::ReadFile()
{
	setlocale(LC_ALL, "Russian");
	cout << "Введите название книги" << endl;
	string temp;
	getline(cin, temp);
	if (temp == "")
		getline(cin, Capture);
	else
		Capture = temp;
	cout << "Введите фамилию автора" << endl;
	getline(cin, FIO);
	cout << "Введите издательство" << endl;
	getline(cin, Izd);
	cout << "Введите год издание" << endl;
	cin >> Year;
	cout << "Введите количество тиража" << endl;
	cin >> Kol;
	cout << "Введите код книги" << endl;
	cin >> Kod;
}

void Book::PrintFile()
{
	setlocale(LC_ALL, "Russian");
	cout << Kod << ' ';
	cout << Capture << ' ';
	cout << FIO << ' ';
	cout << Izd << ' ';
	cout << Year << ' ';
	cout << Kol << '\n';
}

bool operator<(const Book& x, const Book& y)
{
	return x.Year < y.Year;
}

vector<Book> MassBook;

void Print()
{
	system("cls");
	sort(MassBook.begin(), MassBook.end());
	setlocale(LC_ALL, "Russian");
	for (int i = 0; i < MassBook.size(); ++i)
	{
		MassBook[i].PrintFile();
	}
}

void Read()
{
	setlocale(LC_ALL, "Russian");
	cout << "Введите количество книг" << endl;
	int kol;
	cin >> kol;
	int oldkol = MassBook.size();
	MassBook.resize(oldkol + kol);
	for (int i = oldkol; i < MassBook.size(); ++i)
	{
		MassBook[i].ReadFile();
	}
}

void Delete(int nom)
{
	if (nom > MassBook.size()) return;
	for (int k = 0; k < MassBook.size(); k++)
		if (nom == MassBook[k].Kod)
			MassBook.erase(MassBook.begin() + nom - 1);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	MassBook.clear();
	int i;
	string vvod;
	Read();
	Print();
	metka:
	cout << "Введите add / delete / all" << endl;
	cin >> vvod;
	if (vvod == "add")
	{
		system("cls");
		Read();
		Print();
		goto metka;
	}
	if (vvod == "delete")
	{
		system("cls");
		cout << "Введите код книги, которую необходимо удалить : " << endl;
		cin >> i;
		Delete(i);
		system("cls");
		Print();
		goto metka;
	}
	if (vvod == "all")
	{
		Print();
		goto metka;
	}
	return 0;
}

