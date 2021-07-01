#include <iostream>
#include <math.h>

using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	cout << "������ ��������� RSA" << endl << endl;
	int p, q, n, fe, e1, d1;
	int len_e = 0, len_d = 0;
	int* e = new int[len_e];
	int* d = new int[5];
	cout << "������� 'p': ";
	cin >> p;
	cout << "������� 'q': ";
	cin >> q;
	n = q * p;
	cout << "n = " << n << endl;
	fe = (p - 1) * (q - 1);
	cout << "fe = " << fe << endl;
	int error = 0;
	for (int i = 2; i < fe; i++) {
		error = 0;
		if (fe % i != 0) {
			for (int j = 2; j < i; j++) {
				if (i % j == 0) {
					error = 1;
					break;
				}
			}
			if (error == 1) {
				continue;
			}
			int* new_e = new int[len_e + 1];
			for (int j = 0; j < len_e; j++) {
				new_e[j] = e[j];
			}
			len_e++;
			delete[] e;
			e = new int[len_e];
			for (int j = 0; j < len_e; j++) {
				if (j == len_e - 1) {
					e[j] = i;
					break;
				}
				e[j] = new_e[j];
			}
			delete[] new_e;
		}
	}
	cout << "����� ��������� � '�': " << len_e << endl;
	cout << "�������� 'e': " << endl;
	for (int i = 0; i < len_e; i++) {
		cout << e[i] << endl;
	}
	error = 1;
	while (error == 1) {
		cout << "�������� ����� �������� �� �����������������: ";
		cin >> e1;
		for (int i = 0; i < len_e; i++) {
			if (e1 == e[i]) {
				error = 0;
				break;
			}
		}
	}
	for (int i = 1; len_d < 5; i++) {
		if ((i * e1) % fe == 1) {
			d[len_d] = i;
			len_d++;
		}
	}
	cout << "5 �������� d:" << endl;
	for (int i = 0; i < 5; i++) {
		cout << d[i] << endl;
	}
	cout << "\n����������\n\n";
	int P, E_sh, E_desh;
	error = 1;
	while (error == 1) {
		cout << "������� ���� P (�������� �� ����� ���� ������ " << n << "): ";
		cin >> P;
		if (P < n) {
			error = 0;
		}
	}
	E_sh = pow(P, e1);
	E_sh = E_sh % n;
	cout << "������������� E: " << E_sh << endl;
	cout << "\n������������\n\n";
	error = 1;
	while (error == 1) {
		cout << "�������� ���� d �� �����������������: ";
		cin >> d1;
		for (int i = 0; i < len_d; i++) {
			if (d1 == d[i]) {
				error = 0;
				break;
			}
		}
	}
	E_desh = pow(E_sh, d1);
	E_desh = E_desh % n;
	cout << "������������� ���������: " << E_desh << endl;
	return 0;
}