#include<iostream>
#include<string>
#include<windows.h>
using namespace std;

void init(char arr[][81],const int rows)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < 81; j++)
		{
			if (j < 80)arr[i][j] = ' ';
			else arr[i][j] = '\0';
		}
	}
}
void Print(char arr[][81], const int rows)
{
	arr[rows - 1][80 - 1] = '\0';
	for (int i = 0; i < rows; i++)
	{
		cout << arr[i];
	}
}
void newSnow(char arr[][81], const int rows)
{
	for (int i = 0; i < 80; i++)
	{
		if (rand() % 12 == 1)
			arr[0][i] = '*';
	}
}
void moveSnow(char arr[][81],const int rows)
{
	int dx;
	for (int i = rows-1; i >=0; i--)
	{
		for (int j = 0; j < 81; j++)
		{
			if (arr[i][j] == '*')
			{
				arr[i][j] = ' ';
				dx = 0;
				if (rand() % 10 < 1)dx++;
				if (rand() % 10 < 1)dx--;
				dx += j;
				if ((dx >= 0) && (dx < 80) && (i + 1 < rows))
				{
					arr[i + 1][dx] = '*';
				}

			}
		}
	}
}
void setcur(int x, int y)// Функция для установки позиции курсора в консоли
{
	COORD coord;		// Структура для хранения координат
	coord.X = x;		// Устанавливаем X координату
	coord.Y = y;		// Устанавливаем Y координату

	// Перемещаем курсор
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int main()
{
	setlocale(LC_ALL, "rus");
	//srand(static_cast<unsigned>(time(0)));
	const int h = 25;
	const int w = 80;
	char mas[h][w + 1];
	init(mas, h);
	
	do
	{
		setcur(0, 0);
		newSnow(mas, h);
		moveSnow(mas, h);
		Print(mas, h);
		Sleep(100);
	} while (GetKeyState(VK_ESCAPE)>=0);
	
	

	return 0;
}