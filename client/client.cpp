// client.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <conio.h>
#include <Windows.h>

int main()
{
	setlocale(0, "rus");
	while (true) {
		system("cls");

		HANDLE hMutex;

		hMutex = OpenMutex(SYNCHRONIZE, FALSE, L"printer_mutex");
		if (hMutex == NULL) {
			system("cls");
			std::cout << "Принтер выключен" << std::endl;
			_getch();
		}
		else {
			std::cout << "Нажмите чтобы начать печать либо поменять приоритет (a, b, c)..." << std::endl;

			switch (_getch()) {
				case 'a': {
					SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS);
					std::cout << "Задан фоновый приоритет" << std::endl;
				}
				break;
				case 'b': {
					SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
					std::cout << "Задан нормальный приоритет" << std::endl;
				}
				break;
				case 'c': {
					SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
					std::cout << "Задан высокий приоритет" << std::endl;
				}
				break;
				default: {

					if (WaitForSingleObject(hMutex, 0) == WAIT_TIMEOUT) {
						system("cls");
						std::cout << "Мьютекс занят" << std::endl;
					}
					else {
						system("cls");
						std::cout << "Задание отправлено на печать" << std::endl;
						Sleep(1000);
						ReleaseMutex(hMutex);
						Sleep(1000);

						WaitForSingleObject(hMutex, INFINITE);
						system("cls");
						std::cout << "Печать завершена" << std::endl;
						ReleaseMutex(hMutex);
					}
				}
			}
			CloseHandle(hMutex);
			Sleep(1000);
		}
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
