#include<iostream>
#include<math.h>
#include<Windows.h>
using std::cout;
using std::endl;
void SetConsoleSize(int width, int height)
{
	// Получаем дескриптор консоли для вывода
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Создаем структуру для задания размера буфера экрана консоли
	COORD bufferSize;
	bufferSize.X = width;  // Задаем ширину буфера
	bufferSize.Y = height; // Задаем высоту буфера
	// Устанавливаем размер буфера экрана консоли
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	// Создаем структуру для задания размера окна консоли
	SMALL_RECT windowSize;
	windowSize.Left = 0;            // Левая граница окна консоли (начинается с 0)
	windowSize.Top = 0;             // Верхняя граница окна консоли (начинается с 0)
	windowSize.Right = width - 1;   // Правая граница окна консоли (отсчет от 0, поэтому -1)
	windowSize.Bottom = height - 1; // Нижняя граница окна консоли (отсчет от 0, поэтому -1)
	// Устанавливаем размер окна консоли
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

}
	const int mapWIDTH = 80+1;			// Ширина карты с учетом завершающего символа '\0'
	const int mapHEIGHT = 25;			// Высота карты
	// Структура для описания объектов на карте (например, персонажей)
	struct TObject
	{
		double x, y;			// Позиция объекта на карте
		double width, height;	//ширина и высота
		double vertSpeed;		//вертикальная скорость
		bool isFly;				// Флаг, указывающий, находится ли объект в полете
		char cType;				// Символ, представляющий объект на карте
	};
	// Функция для очистки карты (заполнение пробелами)
	void ClearMap(char map[][mapWIDTH])				
	{
		for (int i = 0; i < mapHEIGHT; i++)
		{
			for (int j = 0; j < mapWIDTH; j++)
			{
				if (j < mapWIDTH-1)map[i][j] = ' '; // Заполнение пробелами
				else map[i][j] = '\0';				// Последний символ строки — завершающий нуль
			}
		}
		map[mapHEIGHT - 1][mapWIDTH - 2] = '\0';	// Завершающий нуль для последней строки
	}
	// Функция для вывода карты на экран
	void Print(const char map[][mapWIDTH])//отрисовка карты
	{
		for (int i = 0; i < mapHEIGHT; i++)
		{
			cout << map[i];// Печать строки карты
		}
	}
	// Функция для задания позиции объекта на карте
	void SetObjectPos(TObject& obj,const double xPos,const double yPos)
	{
		obj.x = xPos;		// Установка координаты X
		obj.y = yPos;		// Установка координаты Y
	}
	// Функция для инициализации объекта (персонажа)
	void initObject(TObject& obj, const double xPos, const double yPos, const double oWidth, const double oHeight,const char &inType)
	{
		SetObjectPos(obj, xPos, yPos);	// Установка позиции объекта
		obj.width = oWidth;				// Установка ширины объекта
		obj.height = oHeight;			// Установка высоты объекта
		obj.vertSpeed = 0;				// Изначально вертикальная скорость равна 0
		obj.cType = inType;				// Задание типа (символа) объекта
	}
	// Функция для проверки столкновения двух объектов
	bool isCollision(TObject& obj1, TObject& obj2);
	// Функция для вертикального перемещения объекта (например, гравитация)
	void VertMoveOgject(TObject& obj, TObject brick[], const int& brickLenght)
	{
		obj.isFly = true;									// Предполагаем, что объект в полете
		obj.vertSpeed += 0.04;								// Увеличиваем вертикальную скорость (гравитация)
		SetObjectPos(obj, obj.x, obj.y + obj.vertSpeed);	// Перемещаем объект вниз
		for (int i = 0; i <brickLenght; i++)				// Проверяем столкновение с кирпичами (brick
		{
			if (isCollision(obj, brick[i]))
			{
				obj.y -= obj.vertSpeed;						// Если есть столкновение, отменяем перемещение
				obj.vertSpeed = 0;							// Сбрасываем вертикальную скорость
				obj.isFly = false;							// Объект больше не в полете
				break;
			}
		}
	}
	// Функция для проверки, находится ли координата внутри карты
	bool isPosInMap(const int& x,const int& y)
	{
		return ((x >= 0) && (x < mapWIDTH-1) && (y >= 0) && (y < mapHEIGHT));
	}
	// Функция для отображения объекта на карте
	void PutObjectOnMap(TObject& obj,char map[][mapWIDTH])//Перемещение персонажа
	{
		int ix = (int)round(obj.x);						// Округляем координату X
		int iy = (int)round(obj.y);						// Округляем координату Y
		int iWidth = (int)round(obj.width);				// Округляем ширину
		int iHeght = (int)round(obj.height);			// Округляем высоту
		// Заполняем карту символами объекта
		for (int i = ix; i <(ix+iWidth) ; i++)
		{
			for (int j = iy; j < (iy+iHeght); j++)
			{
				if(isPosInMap(i, j))					// Если позиция внутри карты
					map[j][i] = obj.cType;				// Устанавливаем символ объект
			}
		}
	}
	// Функция для установки позиции курсора консоли
	void setCur(int x, int y)
	{
		COORD coord;			// Создаем структуру для задания позиции курсора
		coord.X=x;				// Устанавливаем координату X
		coord.Y=y;				// Устанавливаем координату Y
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);// Устанавливаем позицию курсора
	}
	// Функция для горизонтального перемещения карты (и объектов на ней)
	void HorizionMoveMap(TObject obj[], double dx,const int& brickLenght, TObject&mario)
	{
		mario.x -= dx;		// Перемещаем игрока (Марио) в противоположную сторону от перемещения карты
		for (int i = 0; i < brickLenght; i++)	// Проверяем, не столкнулся ли Марио с каким-либо объектом
		{
			if (isCollision(mario,obj[i]))
			{
			mario.x += dx;		 // Если есть столкновение, возвращаем Марио обратно
			return;				 // Завершаем функцию
			}
		}
		mario.x += dx;			 // Если столкновения нет, возвращаем Марио на прежнее место
		for(int i=0;i<brickLenght;i++)
			obj[i].x += dx;		 // Перемещаем все объекты (кирпичи) на карте
	}
	// Функция для проверки столкновения двух объектов
	bool isCollision(TObject& obj1, TObject& obj2)
	{
		return  ((obj1.x + obj1.width) > obj2.x) && (obj1.x < (obj2.x + obj2.width)) &&
				((obj1.y + obj1.height) > obj2.y) && (obj1.y < (obj2.y + obj2.height));
	}
	// Функция для создания уровня (инициализации объектов)
	void CreatLevel(int&brickLenght,TObject&mario,TObject**brick)
	{
		brickLenght = 5;						// Задаем количество кирпичей на уровне
		initObject(mario, 39, 10, 3, 3,'@');	// Инициализируем Марио
		*brick = new TObject[brickLenght];		// Выделяем память под массив объектов (кирпичей)
		if (*brick == nullptr)					// Проверяем успешность выделения памяти
		{
			std::cerr << "error allocation memory" << endl;
			return ;
		}
		else
		{	// Инициализируем каждый кирпич на карте
			initObject((*brick)[0], 20, 20, 40, 5,'#');
			initObject((*brick)[1], 60, 15, 10, 10, '#');
			initObject((*brick)[2], 80, 20, 20, 5, '#');
			initObject((*brick)[3], 120, 15, 10, 10, '#');
			initObject((*brick)[4], 150, 20, 40, 5, '#');
			
		}

	}
int main()
{
	SetConsoleSize(80,25);			// Устанавливаем размер окна консоли
	char map[mapHEIGHT][mapWIDTH];	// Создаем карту
	TObject mario;					// Создаем объект Марио
	TObject *brick=nullptr;			// Создаем указатель на массив объектов (кирпичей)
	int brickLenght;				// Переменная для хранения количества кирпичей
	CreatLevel(brickLenght, mario, &brick);// Создаем уровень
	do
	{
		ClearMap(map);				// Очищаем карту перед обновлением
		if ((mario.isFly==false)&&(GetKeyState(VK_SPACE) < 0))mario.vertSpeed = -0.7;	// Прыжок
		if (GetKeyState('A') < 0)HorizionMoveMap(brick, 1, brickLenght,mario);			// Движение влево
		if (GetKeyState('D') < 0)HorizionMoveMap(brick, -1, brickLenght,mario);			// Движение вправо
		if (mario.y > mapHEIGHT - 1)	 // Если Марио упал ниже нижней границы карты
		{
			if (brick != nullptr)
			{
				delete[]brick;
				brick = nullptr;
			}
			CreatLevel(brickLenght, mario, &brick);	// Пересоздаем урове
		}
		VertMoveOgject(mario,brick, brickLenght);	// Обновляем вертикальное движение Марио
		for (int i = 0; i < brickLenght; i++)		// Обновляем позицию кирпичей на карте	
			PutObjectOnMap(brick[i], map);			//помещаем персонажа
		PutObjectOnMap(mario, map);					// Обновляем позицию Марио на карте
		setCur(0, 0);								// Устанавливаем курсор в начало консоли для перерисовки карты

		Print(map);									// Печатаем карту
		Sleep(10);									// Задержка для сглаживания анимации
	} while (GetKeyState(VK_ESCAPE)>=0);			// Цикл продолжается, пока не нажата клавиша ESC

	
	if (brick != nullptr)							// Удаляем массив кирпичей после завершения работы
	{
		delete[]brick;
		brick = nullptr;
	}
	return 0;
}