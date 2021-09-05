#include <iostream>
#include <math.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

using namespace std;

int len_e = 0, len_d = 0;
int d[5];

int encrypt(int n, int e1)
{
	cout << "\nШифрование\n\n";
		int P, E_sh;
		int error = 1;
		while (error == 1) {
			cout << "Введите ваше P (значение не может быть больше " << n << "): ";
			cin >> P;
			if (P < n) {
				error = 0;
			}
		}
		E_sh = pow(P, e1);
		E_sh = E_sh % n;

		cout << "Зашифрованное E: " << E_sh << endl;
		return E_sh;
}
int decrypt(int E_sh, int n, int e1)
{
	int E_desh,d1;
	cout << "\nДешифрование\n\n";
		int error = 1;
		while (error == 1) {
			cout << "Выберите ваше d из вышеперечисленных: ";
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
	return E_desh;
}


int main() {
	//запуск сокета
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	int program_working_mode;
	struct sockaddr_in serv_addr;

	cout << "Выберите режим работы программы: 0 - сервер, 1 - пользователь";
	cin >> program_working_mode; //реим работы
	switch(program_working_mode)
	{
		case 0://сервер
			serv_addr.sin_family = AF_INET;
			serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
			serv_addr.sin_port = htons(5000);//порт
			bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));//запуск сервера
			listen(sock, 1);//прослушивание порта
			break;
		case 1://пользователь
			serv_addr.sin_family = AF_INET;
			serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
			serv_addr.sin_port = htons(5000);//порт
			connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));//подключение
			break;
		default:
			return 0;
	}
	//конец сокета
	cout << "Запуск программы RSA" << endl << endl;
	int p, q, n, fe, e1, d1;
	int* e = new int[len_e];
	int* d = new int[5];
	cout << "Введите 'p': ";
	cin >> p;
	cout << "Введите 'q': ";
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
	cout << "Всего элементов в 'е': " << len_e << endl;
	cout << "Элементы 'e': " << endl;
	for (int i = 0; i < len_e; i++) {
		cout << e[i] << endl;
	}
	error = 1;
	while (error == 1) {
		cout << "Выберите любое значение из вышеперечисленных: ";
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
	cout << "5 значений d:" << endl;
	for (int i = 0; i < 5; i++) {
		cout << d[i] << endl;
	}
	int E_sh, E_desh;
	while(true)
	{
		E_sh = encrypt(n,e1);
		cout << "Зашифрованное E: " << E_sh << endl;
		E_desh = decrypt(E_sh,n,e1);
		cout << "Дешифрованное сообщение: " << E_desh << endl;
	}
	return 0;
}



