#include <iostream>
#include <Windows.h>
#include <iomanip>
using namespace std;

class NumberInput_N {
public:
	double w;

	void random_w() {
		w = 2 * ((rand() % 10) * 0.1) - 1;
	}
	void change_w(double a, double y, double e, double x) {
		w -= a * (y - e) * x;
	}
	void set_w(int w) {
		this->w = w;
	}
	double get_w() {
		return w;
	}
};

class NumberHidden_N {
public:
	double w;
	double summa, znach;

	void random_w() {
		w = 2 * ((rand() % 10) * 0.1) - 1;
	}
	void change_w(double a, double y1, double gamma, double y2) {
		w -= a * gamma * y1 * (1 - y1) * y2;
	}
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	const int N_ob = 30, // obychenie
		N_pr = 15, // prognoz
		input_neuron = 6, // kol vhodov
		hidden_neuron = 2; // elem skritogo sloya
	double a = 0.4,
		   b = 0.4, 
		   c = 0.08,
		   d = 0.4,
	       Emin = 0.00001, // min error
		   V = 0.1, // speed learn
		   Emax; // max error 

	double obechenie_y[N_ob + N_pr], // massiv obych zn
	//	etalon[],
		y, // vihodn zn
		prognoz_y[N_ob + N_pr], // massiv prognoz zn
		Tx[hidden_neuron], // porog skritogo sloya
		Ty = 2 * ((rand() % 10) * 0.1) - 1,  // porog vihodnogo sloya
		E, // error skritogo sloya
		Ei[N_ob - input_neuron]; // error i-togo sloya 

	for (int i = 0; i < N_ob + N_pr + input_neuron; i++) {
		double x = 0.1 * i;
		obechenie_y[i] = a * cos(b * x) + c * sin(d * x);
	}

	NumberInput_N W[hidden_neuron * input_neuron]; // vesovie koaff
	NumberHidden_N Sij[hidden_neuron]; // vzveshen summa

	for (int i = 0; i < input_neuron * hidden_neuron; i++) {
		W[i].random_w();
	}

	for (int i = 0; i < hidden_neuron; i++) {
		Sij[i].random_w();
		Sij[i].summa = 0;
		Tx[i] = 2 * ((rand() % 10) * 0.1) - 1;
	}

	do {
		y = 0;
		Emax = 0;

		for (int k = 0; k < N_ob - input_neuron; k++) {
			y = 0;
			for (int i = 0; i < hidden_neuron; i++) {
				for (int j = 0; j < input_neuron; j++) {
					Sij[i].summa += W[j].w * obechenie_y[k + j];
				}
				Sij[i].summa -= Tx[i];
				Sij[i].znach = (1 / (1 + exp(-Sij[i].summa)));
				Sij[i].summa = 0;
			}

			for (int i = 0; i < hidden_neuron; i++) {
				y += Sij[i].znach * Sij[i].w;
			}
			y -= Ty;

			E = y - obechenie_y[k + input_neuron];
			Ei[k] = E;

			for (int i = 0; i < hidden_neuron; i++) {
				Sij[i].w -= V * Sij[i].znach * E;
			}
			Ty += V * E;

			for (int i = 0; i < hidden_neuron; i++) {
				for (int j = 0; j < input_neuron; j++)
					W[(i * 10) + j].w -= V * obechenie_y[k + j] * (Sij[i].w * E * Sij[i].znach * (1 - Sij[i].znach));
				    Tx[i] += V * (Sij[i].w * E * Sij[i].znach * (1 - Sij[i].znach));
			}
		}

		for (int i = 0; i < N_ob - input_neuron; i++) {
			Emax += (pow(Ei[i], 2.0) * 0.5);
		}
		cout << "Emax= " << Emax << endl;
	} while (Emax > Emin);

	cout << "||Результаты Обучения||" << endl;
	cout << setw(27) << left << "|Эталонные значения|" << setw(29) << left << "|Полученные значения|" << setw(30) << left << "|Отклонение|" << endl;

	for (int k = 0; k < N_ob; k++) {
		y = 0;
		for (int i = 0; i < hidden_neuron; i++) {
			for (int j = 0; j < input_neuron; j++) {
				Sij[i].summa += W[j].w * obechenie_y[N_ob - input_neuron + k + j];
			}
			Sij[i].summa -= Tx[i];
			Sij[i].znach = (1 / (1 + exp(-Sij[i].summa)));
			Sij[i].summa = 0;
		}

		for (int i = 0; i < hidden_neuron; i++) {
			y += Sij[i].znach * Sij[i].w;
		}
		y -= Ty;

		obechenie_y[N_ob + k] = y;
		double x = 0.1 * ((double)k + (double)N_ob);
		cout << "y[" << k << "] = " << setw(25) << left << a * cos(b * x) + c * sin(d * x) << setw(25) << left << obechenie_y[N_ob + k];
		cout << setw(30) << left << a * cos(b * x) + c * sin(d * x) - obechenie_y[N_ob + k] << endl;
	}

	cout << "||Результаты Прогнозирования||" << endl;
	cout << setw(27) << left << "|Эталонные значения|" << setw(29) << left << "|Полученные значения|" << setw(30) << left << "|Отклонение|" << endl;


	for (int k = 0; k < N_pr; k++) {
		y = 0;
		for (int i = 0; i < hidden_neuron; i++) {
			for (int j = 0; j < input_neuron; j++) {
				Sij[i].summa += W[j].w * obechenie_y[N_ob + k + j];
			}
			Sij[i].summa -= Tx[i];
			Sij[i].znach = (1 / (1 + exp(-Sij[i].summa)));
			Sij[i].summa = 0;
		}

		for (int i = 0; i < hidden_neuron; i++) {
			prognoz_y[N_ob + k] += Sij[i].znach * Sij[i].w;
		}
		prognoz_y[N_ob + k] -= Ty;

		obechenie_y[N_pr + k] = prognoz_y[N_ob + k];
		double x = 0.1 * ((double)k + (double)N_ob);
		cout << "y[" << N_ob + k << "] = " << setw(25) << left << a * cos(b * x) + c * sin(d * x) << setw(25) << left << obechenie_y[N_ob + k];
		cout << setw(30) << left << a * cos(b * x) + c * sin(d * x) - obechenie_y[N_ob + k] << endl;
	}

	system("pause");
	return 0;
}
