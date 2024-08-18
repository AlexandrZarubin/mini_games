#include<iostream>
#include<string>
#include<vector>
#include <ctime>
#include <conio.h>
#include<Windows.h>

using namespace std;

// Функция для инициализации строки
// Заполняем строку символом '#'
void init(string&str,const int width)
{

	str = string(width, '#');
}

// Функция для копирования по вектору и инициализации каждой строки
void initializeVector(vector<string>& vec, const int width) 
{
	for (string& str : vec) 
	{
		init(str, width); // Инициализируем каждую строку вектора
	}
}

// Функция для вставки символов в строки вектора
// Заполняем строки символами: границы символом Symbol, внутренние символом Symbol2
void InsertSymbol(vector<string>& vec,const int width,const string Symbol = " ", const char Symbol2 = ' ')
{
	for (int i = 1; i < vec.size(); ++i)
	{
		vec[i]= Symbol + string(width-2, Symbol2) + Symbol;
	}
}

// Функция для вывода строки на экран
void Print(const string& str)
{
	cout << str;
}

// Функция для вывода всех строк вектора на экран
void PrintAll(const vector<string>& vec)
{
	//for (const string& str : vec)
	for (int i=0;i<vec.size();i++)
	{
		Print(vec[i]);
		
		if (i<vec.size()-1)// Печатаем перевод строки после каждой строки, кроме последней
		{
			cout << endl;
		}
	}
}

// Структура для представления ракетки
struct Tracket
{
	int x;// Позиция X
	int y;// Позиция Y
	int w;// Ширина ракетки
};

// Функция для инициализации ракетки
void inittracket(Tracket& tr,const int width,const int height)
{
	tr.w = 7;				// Устанавливаем ширину ракетки
	tr.x=(width - tr.w) / 2;// Центрируем ракетку по X
	tr.y = height - 1;		// Устанавливаем ракетку в нижнюю часть экрана
}

// Функция для размещения ракетки на экране
void PutRacket(vector<string>& vec,Tracket& tr)
{
	for (int i = tr.x; i < tr.x+tr.w; i++)
	{
		vec[tr.y][i] = '@';// Размещаем символ '@' на позиции ракетки
	}
}

// Функция для перемещения ракетки
void moveRacket(Tracket& tr,int x, const int width)
{
	tr.x = x;
	// Проверка, чтобы ракетка не вышла за границы экрана
	if (tr.x < 1)tr.x=1;
	if (tr.x + tr.w >= width)tr.x = width - 1 - tr.w;
}

// Функция для установки позиции курсора в консоли
void setcur(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int main()
{
	srand(static_cast<unsigned>(time(0)));							// Заполнение границ
	const int width = 65;											// Ширина экрана
	const int height = 25;											// Высота экрана
	vector<string> mas(height, string(width, ' '));					// Инициализация вектора строк
	Tracket trackt;													// Создание структуры для ракетки
	inittracket(trackt, width, height);								// Инициализация ракетки
	init(mas[0], width);											// Инициализация первой строки (границы)
	initializeVector(mas, width);									// Инициализация всех строк
	do
	{
		// Очистка экрана
		//system("cls");
		setcur(0, 0);												// Установка курсора в начало
		InsertSymbol(mas, width, "#", ' ');							// Заполнение границ
		PutRacket(mas, trackt);										// Размещение ракетки
		PrintAll(mas);												// Вывод на экран

		// Управление ракеткой с использованием состояния клавиш
		//c = _getch();
		//if (c == 'a')moveRacket(trackt, trackt.x - 1, width);
		if (GetKeyState('A')>=0)moveRacket(trackt, trackt.x + 1, width);// Перемещение влево
		if (GetKeyState('D')>=0)moveRacket(trackt, trackt.x - 1, width);// Перемещение вправо
		//if (c == 'd')moveRacket(trackt, trackt.x + 1, width);
		
		Sleep(10);
	} while (GetKeyState(VK_ESCAPE) >= 0);
	//int aa = !(GetKeyState(VK_ESCAPE) & 0x8000);
	return 0;
}