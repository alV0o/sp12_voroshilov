// sp12_voroshilov.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <random>
#include <conio.h>

DWORD WINAPI Printer() {
	std::cout << "Печать..." << std::endl;

	std::random_device rd;   // non-deterministic generator
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(5, 15);

	int sleeptime = dist(gen) * 1000;
	Sleep(sleeptime);
	return 0;
}

int main()
{
	setlocale(0, "rus");

	HANDLE hMutex;
	hMutex = CreateMutex(NULL, FALSE, L"printer_mutex");
	if (hMutex == NULL) {
		return GetLastError();
	}
	int timeLife = 0;
	while (timeLife <= 600) {
		std::cout << "Ждет..." << std::endl;

		if (WaitForSingleObject(hMutex, 0) == WAIT_TIMEOUT) {
			timeLife = 0;
			system("cls");

			HANDLE hThread;
			DWORD IDThread;

			WaitForSingleObject(hMutex, INFINITE);

			hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Printer, NULL, NULL, &IDThread);
			if (hThread == NULL)
				return GetLastError();

			if (WaitForSingleObject(hThread, 10000) == WAIT_OBJECT_0) {
				system("cls");
				std::cout << "Готово" << std::endl;
			}
			else {
				system("cls");
				std::cout << "Ошибка печати" << std::endl;
			}
			CloseHandle(hThread);

		}
		else {
			timeLife++;
		}
		ReleaseMutex(hMutex);
		Sleep(1000);
		system("cls");
	}
	CloseHandle(hMutex);
	std::cout << "Принтер отключился" << std::endl;
	_getch();
}
