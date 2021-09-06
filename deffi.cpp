#include <iostream>
#include "iostream"
#include "math.h"
using namespace std;

int main()
{
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
    setlocale(LC_ALL, "RUS");
    int a;
    int b;
    int p;
    int g;
    cout << "Введите числа g, p " << endl;
    cin >> g >> p;
    cout << "Введите числа a, b " << endl;
    cin >> a >> b;

    int Aa = pow(g, a);
    int A = (int)Aa;
    A = A % p;
    cout << "A= " << A << endl;

    int Bb = pow(g, b);
    int B = (int)Bb;
    B = B % p;

    cout << "B= " << B << endl;

    int Ab = pow(B, a);
    Ab = Ab % p;
    int Ba = pow(A,b);
    Ba = Ba % p;
    cout << Ab << endl;
    cout << Ba << endl;
    system("pause");
}
