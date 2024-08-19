#define _USE_MATH_DEFINES // Позволяет использовать математические константы из <cmath>
#include <iostream>       // Для работы с вводом и выводом
#include <string>         // Для работы со строками
#include <vector>         // Для работы с динамическими массивами (векторами)
#include <ctime>          // Для работы с временем (инициализация генератора случайных чисел)
#include <conio.h>        // Для работы с функциями консольного ввода/вывода
#include <Windows.h>      // Для работы с функциями Windows API (например, управление курсором)
#include <cmath>          // Для работы с математическими функциями и константами
using namespace std;

// Функция для инициализации строки
void init(string&str,const int width)
{

	str = string(width, '#');// Заполняем строку символом '#'
}

// Функция для копирования по вектору и инициализации каждой строки
void initializeVector(vector<string>& vec, const int width) 
{
	for (string& str : vec) // Проходим по каждой строке вектора
	{
		init(str, width);	// Инициализируем каждую строку вектора
	}
}

// Функция для вставки символов в строки вектора
void InsertSymbol(vector<string>& vec,const int width,const string Symbol = " ", const char Symbol2 = ' ')
{
	for (int i = 1; i < vec.size(); ++i)// Проходим по всем строкам вектора, кроме первой
	{
		// Заполняем строки символами: границы символом Symbol, внутренние символом Symbol2
		vec[i]= Symbol + string(width-2, Symbol2) + Symbol;
	}
}
void Print(const string& str)// Функция для вывода строки на экран
{
	cout << str;// Выводим строку на экран
}
void PrintAll(const vector<string>& vec,const int& hitCnt,const int& maxHitCnt)// Функция для вывода всех строк вектора на экран и отображения счётчиков
{
	//for (const string& str : vec)
	for (int i=0;i<vec.size();i++)	// Проходим по всем строкам вектора
	{
		Print(vec[i]);				// Выводим строку на экран
		if (i == 3)					// Отображаем текущее количество ударов на третьей строке
			cout << "\t" << hitCnt;
		if (i == 4)					// Отображаем максимальное количество ударов на четвёртой строке
			cout << "\t" << maxHitCnt;
		if (i<vec.size()-1)// Добавляем перевод строки после каждой строки, кроме последней
		{
			cout << endl;
		}
	}
}
struct Tracket// Структура для представления ракетки
{
	int x;// Позиция X
	int y;// Позиция Y
	int w;// Ширина ракетки
};
void inittracket(Tracket& tr,const int width,const int height)// Функция для инициализации ракетки
{
	tr.w = 7;				// Устанавливаем ширину ракетки
	tr.x=(width - tr.w) / 2;// Центрируем ракетку по X
	tr.y = height - 1;		// Устанавливаем ракетку в нижнюю часть экрана
}
void PutRacket(vector<string>& vec,Tracket& tr)// Функция для размещения ракетки на экране
{
	// Проходим по всем символам, которые занимает ракетка
	for (int i = tr.x; i < tr.x+tr.w; i++)
	{
		vec[tr.y][i] = '@';		// Размещаем символ '@' на позиции ракетки
	}
}
void moveRacket(Tracket& tr,int x, const int width)// Функция для перемещения ракетки
{
	tr.x = x;										 // Устанавливаем новую позицию X
	
	// Проверка, чтобы ракетка не вышла за границы экрана
	if (tr.x < 1)tr.x=1;							 // Проверяем, чтобы ракетка не вышла за левую границу
	if (tr.x + tr.w >= width)tr.x = width - 1 - tr.w;// Проверяем, чтобы ракетка не вышла за правую границу
}
void setcur(int x, int y)// Функция для установки позиции курсора в консоли
{
	COORD coord;		// Структура для хранения координат
	coord.X = x;		// Устанавливаем X координату
	coord.Y = y;		// Устанавливаем Y координату
	
	// Перемещаем курсор
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
struct TBall// Структура для представления шарика
{
	double x;			// Позиция X шарика
	double y;			// Позиция Y шарика
	int ix;				// Целая позиция X шарика
	int iy;				// Целая позиция Y шарика
	double alfa;		// Угол направления движения шарика
	double speed;		// Скорость шарика
};
void moveBall(TBall& tb, double x, double y);// Функция для перемещения шарика
void initBall(TBall&tb)// Функция для инициализации шарика
{
	moveBall(tb, 2, 2);	// Устанавливаем начальную позицию шарика
	tb.alfa = -1;		// Устанавливаем начальный угол движения шарика
	tb.speed = 0.5;		// Устанавливаем скорость шарика
}
void putBall(TBall&tb, vector<string>& vec)// Функция для отображения шарика на экране
{
	vec[tb.iy][tb.ix] = '*';// Помещаем шарик на экран, заменяя символ на '*'
}
void moveBall(TBall& tb, double x, double y)// Функция для перемещения шарика
{
	tb.x = x;				// Устанавливаем новую позицию X
	tb.y = y;				// Устанавливаем новую позицию Y
	tb.ix = (int)tb.x;		// Обновляем целочисленное значение X
	tb.iy = (int)tb.y;		// Обновляем целочисленное значение Y
}
void autoMoveBall(TBall& tb, vector<string>& vec,int&hitCnt)// Функция для автоматического перемещения шарика
{
	if (tb.alfa < 0)tb.alfa += M_PI * 2;											// Корректируем угол, если он меньше 0
	if (tb.alfa > M_PI * 2)tb.alfa -= M_PI * 2;										// Корректируем угол, если он больше 2π
	TBall Temptb = tb;																// Сохраняем текущее состояние шарика
	moveBall(tb, tb.x + cos(tb.alfa) * tb.speed, tb.y + sin(tb.alfa) * tb.speed);	// Перемещаем шарик в новую позицию
	if ((vec[tb.iy][tb.ix] == '#') || (vec[tb.iy][tb.ix] == '@'))					// Проверяем столкновение с границами или ракеткой
	{
		if (vec[tb.iy][tb.ix] == '@')												// Увеличиваем счётчик ударов, если шарик попал в ракетку				
			hitCnt++;
		if ((tb.ix != Temptb.ix) && (tb.iy != Temptb.iy))							// Если столкновение произошло в углу
		{
			if (vec[Temptb.iy][tb.ix] == vec[tb.iy][Temptb.ix])
				Temptb.alfa = Temptb.alfa + M_PI;									// Отражаем угол на 180 градусов
			else
			{
				if (vec[Temptb.iy][tb.ix] == '#')
					Temptb.alfa = (2*M_PI-Temptb.alfa) + M_PI;						// Отражаем угол по горизонтали и вертикали
				else
					Temptb.alfa = (2 * M_PI - Temptb.alfa);							// Отражаем угол по горизонтали
			}
		}
		else if (tb.iy==Temptb.iy)
		{
			Temptb.alfa = (2 * M_PI - Temptb.alfa) + M_PI;							// Отражаем угол по горизонтали
		}
		else
		{
			Temptb.alfa = (2 * M_PI - Temptb.alfa);									// Отражаем угол по вертикали
		}
		tb = Temptb;																// Обновляем состояние шарика
		autoMoveBall(tb, vec, hitCnt);												// Рекурсивный вызов для проверки нового направления
	}
}
int main()
{
	srand(static_cast<unsigned>(time(0)));							// Заполнение границ
	const int width = 65;											// Ширина экрана
	const int height = 25;											// Высота экрана
	int hitCnt = 0;
	int maxHitCnt = 0;
	vector<string> mas(height, string(width, ' '));					// Инициализация вектора строк
	Tracket trackt;													// Создание структуры для ракетки
	TBall tball;													// Создаём объект шарика
	inittracket(trackt, width, height);								// Инициализация ракетки
	initBall(tball);												// Инициализируем шарик
	init(mas[0], width);											// Инициализация первой строки (границы)
	initializeVector(mas, width);									// Инициализация всех строк
	bool run = false;
	do																// Главный цикл игры
	{
		// Очистка экрана
		//system("cls");
		setcur(0, 0);												// Устанавливаем курсор в начало экрана
		if (tball.iy >= height-1)
		{
			run = false;
			if (hitCnt > maxHitCnt)
				maxHitCnt = hitCnt;
			hitCnt = 0;
		}															
		if (run)autoMoveBall(tball,mas,hitCnt);						// Автоматически перемещаем шарик
		
		InsertSymbol(mas, width, "#", ' ');							// Заполнение границ
		PutRacket(mas, trackt);										// Размещение ракетки
		putBall(tball, mas);										// Размещаем шарик на экране
		PrintAll(mas,hitCnt,maxHitCnt);								// Вывод на экран

		// Управление ракеткой с использованием состояния клавиш
		//c = _getch();
		//if (c == 'a')moveRacket(trackt, trackt.x - 1, width);
		if (GetKeyState('A')>=0)moveRacket(trackt, trackt.x + 1, width);// Перемещение влево
		if (GetKeyState('D')>=0)moveRacket(trackt, trackt.x - 1, width);// Перемещение вправо
		if (GetKeyState('W')< 0)run = true;

		if(!run) moveBall(tball,trackt.x + trackt.w / 2, trackt.y - 1);
		//if (c == 'd')moveRacket(trackt, trackt.x + 1, width);
		Sleep(10);
	} while (GetKeyState(VK_ESCAPE) >= 0);
	
	return 0;
}