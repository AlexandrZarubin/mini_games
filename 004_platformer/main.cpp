#include<iostream>
#include<math.h>
#include<Windows.h>
#include <cstdlib>
#include<string>
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
		float horizonSpeed;
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
	void initObject(TObject* obj, const double xPos, const double yPos, const double oWidth, const double oHeight,const char &inType)
	{
		SetObjectPos(*obj, xPos, yPos);	// Установка позиции объекта
		obj->width = oWidth;				// Установка ширины объекта
		obj->height = oHeight;			// Установка высоты объекта
		obj->vertSpeed = 0;				// Изначально вертикальная скорость равна 0
		obj->cType = inType;				// Задание типа (символа) объекта
		obj->horizonSpeed = 0.2;
	}
	// Функция для проверки столкновения двух объектов
	bool isCollision(TObject& obj1, TObject& obj2);
	void CreatLevel(int& brickLenght, TObject& mario, TObject*& brick, int&lvl, int& movingLength, TObject*& moving, int& Score);
	TObject* GetNewNrick(int& brickLenght, TObject*& brick);
	// Функция для вертикального перемещения объекта (например, гравитация)
	void VertMoveOgject(TObject& obj, TObject*& brick,  int& brickLenght,int&lvl, int& movingLength, TObject*& moving,TObject& mario, int& Score)
	{
		obj.isFly = true;									// Предполагаем, что объект в полете
		obj.vertSpeed += 0.04;								// Увеличиваем вертикальную скорость (гравитация)
		SetObjectPos(obj, obj.x, obj.y + obj.vertSpeed);	// Перемещаем объект вниз
		for (int i = 0; i <brickLenght; i++)				// Проверяем столкновение с кирпичами (brick
		{
			if (isCollision(obj, brick[i]))
			{
				if(obj.vertSpeed>0)
					obj.isFly = false;							// Объект больше не в полете
				if (brick[i].cType == '?' && (obj.vertSpeed < 0)&&(&obj==&mario))
				{
					brick[i].cType = '-';
					initObject(GetNewNrick(movingLength, moving), brick[i].x, brick[i].y-3, 3, 3, '$');
					moving[movingLength - 1].vertSpeed = -0.7;
				}
				obj.y -= obj.vertSpeed;						// Если есть столкновение, отменяем перемещение
				obj.vertSpeed = 0;							// Сбрасываем вертикальную скорость
				if (brick[i].cType == '+')
				{
					
					lvl++;
					if (lvl > 3)lvl = 1;
					CreatLevel(brickLenght,obj,brick, lvl,movingLength,moving,Score);
					Sleep(10);
					
				}
				break;
			}
		}
	}
	void DeleteMoving(int i, int& movingLength, TObject*& moving)
	{
		moving[i] = moving[movingLength-1];
		movingLength--;
		TObject* newMoving = new TObject[movingLength];
		for (int j = 0; j < movingLength; j++)
		{
			newMoving[j] = moving[j];
		}
		delete[]moving;
		moving = newMoving;
		
	}
	void MarrioCollision(TObject& obj, TObject*& brick, int& brickLenght, int& lvl, int& movingLength, TObject*& moving, int& Score)
	{
		for (int i = 0; i < movingLength; i++)
		{
			if (isCollision(obj, moving[i]))
			{
				if (moving[i].cType =='o')
				{
					if ((obj.isFly == true) && (obj.vertSpeed > 0) && (obj.y + obj.height < moving[i].y + moving[i].height * 0.5))
					{
						Score += 50;
						DeleteMoving(i, movingLength, moving);
						i--;
						continue;
					}
					else
						CreatLevel(brickLenght, obj, brick, lvl, movingLength, moving,Score);
				}
				if (moving[i].cType == '$')
				{
					Score += 100;
					DeleteMoving(i, movingLength, moving);
					i--;
					continue;
				}
			}
		}
	}
	void HorizonMoveObject(TObject& obj, int& brickLenght, TObject*& brick, int& lvl, int& movingLength, TObject*& moving,TObject&mario, int& Score)
	{
		obj.x += obj.horizonSpeed;
		for (int i = 0; i < brickLenght; i++)
		{
			if (isCollision(obj, brick[i]))
			{
				obj.x -= obj.horizonSpeed;
				obj.horizonSpeed = -obj.horizonSpeed;
				return;
			}
		}
		if (obj.cType == 'o')
		{
			TObject tmp = obj;
			VertMoveOgject(tmp, brick, brickLenght, lvl, movingLength, moving, mario,Score);
			if (tmp.isFly == true)
			{
				obj.x -= obj.horizonSpeed;
				obj.horizonSpeed = -obj.horizonSpeed;
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
	void HorizionMoveMap(TObject*& obj, double dx,const int& brickLenght, TObject&mario, int& movingLength, TObject*& moving)
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
		for (int i = 0; i < movingLength; i++)
			moving[i].x += dx;
	}
	// Функция для проверки столкновения двух объектов
	bool isCollision(TObject& obj1, TObject& obj2)
	{
		return  ((obj1.x + obj1.width) > obj2.x) && (obj1.x < (obj2.x + obj2.width)) &&
				((obj1.y + obj1.height) > obj2.y) && (obj1.y < (obj2.y + obj2.height));
	}
	
	TObject* GetNewNrick(int& brickLenght, TObject*& brick )
	{
		brickLenght++;
		TObject* newBrick = new TObject[brickLenght];
		for (int j = 0; j < brickLenght-1; j++)
		{
			newBrick[j] = brick[j];
		}
		delete[]brick;
		brick = newBrick;
		return &brick[brickLenght-1];
	}
	TObject* GetNewMoving(int& movingLength, TObject*& moving)
	{
		movingLength++;
		TObject* newMoving = new TObject[movingLength];
		for (int j = 0; j < movingLength - 1; j++)
		{
			newMoving[j] = moving[j];
		}
		delete[]moving;
		moving = newMoving;
		return &moving[movingLength - 1];
	}
	void PutScoreOnMap(char map[][mapWIDTH],int&Score)
	{
		char c[30];
		char scoreSTR[10];
		_itoa_s(Score, scoreSTR, 10);
		strcpy_s(c, "Score: ");// Добавляем текст перед значением Score
		strcat_s(c, scoreSTR);// Конкатенируем строку с числом
		int len = strlen(c);
		for (int i = 0; i < len; i++)
		{
			map[1][i + 5] = c[i];
		}
	}
	// Функция для создания уровня (инициализации объектов)
	void CreatLevel(int& brickLenght, TObject& mario, TObject*& brick, int& lvl,int &movingLength,TObject*&moving,int&Score) {
		// Удаляем старый массив кирпичей, если он уже существует
		if (brick != nullptr) {
			delete[] brick;
			brick = nullptr;
		}
		if (moving != nullptr)
		{
			delete[]moving;
			moving = nullptr;
		}
		Score = 0;
			brickLenght = 0; // Количество кирпичей на уровне 1
			movingLength = 0;
		// Выделяем память под новый массив кирпичей
		//brick = new TObject[brickLenght];
		//moving = new TObject[movingLength];
		/*if (brick == nullptr) {
			std::cerr << "Error allocating memory" << endl;
			return;
		}*/

		// Инициализируем Марио
		initObject(&mario, 39, 10, 3, 3, '@');

		// Инициализируем кирпичи в зависимости от уровня
		if (lvl == 1)
		{
			initObject(GetNewNrick(brickLenght, brick), 20, 20, 40, 5, '#');
				initObject(GetNewNrick(brickLenght, brick), 30, 10, 5, 3, '?');
				initObject(GetNewNrick(brickLenght, brick), 50,	10, 5, 3, '?');	
				initObject(GetNewNrick(brickLenght, brick), 60, 5, 10, 3, '-');
				initObject(GetNewNrick(brickLenght, brick), 70, 5, 5, 3, '?');
				initObject(GetNewNrick(brickLenght, brick), 75, 5, 5, 3, '-');
				initObject(GetNewNrick(brickLenght, brick), 80, 5, 5, 3, '?');
				initObject(GetNewNrick(brickLenght, brick), 85, 5, 10, 3, '-');
			initObject(GetNewNrick(brickLenght, brick), 60, 15, 40, 10, '#');
			initObject(GetNewNrick(brickLenght, brick), 100, 20, 20, 5, '#');
			initObject(GetNewNrick(brickLenght, brick), 120, 15, 10, 10, '#');
			initObject(GetNewNrick(brickLenght, brick), 150, 20, 40, 5, '#');
			initObject(GetNewNrick(brickLenght, brick), 210, 15, 10, 10, '+');
			
			initObject(GetNewMoving(movingLength, moving), 25, 10, 3, 2, 'o');
			initObject(GetNewMoving(movingLength, moving), 80, 10, 3, 2, 'o');

		}
		else if (lvl == 2) 
		{
			initObject(GetNewNrick(brickLenght,brick), 20, 20, 40, 5, '#');
			initObject(GetNewNrick(brickLenght, brick), 60, 15, 10, 10, '#');
			initObject(GetNewNrick(brickLenght, brick), 80, 20, 20, 5, '#');
			initObject(GetNewNrick(brickLenght, brick), 120, 15, 10, 10, '#');
			initObject(GetNewNrick(brickLenght, brick), 150, 20, 40, 5, '#');
			initObject(GetNewNrick(brickLenght, brick), 210, 15, 10, 10, '+');
			initObject(GetNewMoving(movingLength,moving), 25, 10, 3, 2, 'o');
			initObject(GetNewMoving(movingLength,moving), 80, 10, 3, 2, 'o');
			initObject(GetNewMoving(movingLength,moving), 65, 10, 3, 2, 'o');
			initObject(GetNewMoving(movingLength,moving), 120, 10, 3, 2, 'o');
			initObject(GetNewMoving(movingLength,moving), 160, 10, 3, 2, 'o');
			initObject(GetNewMoving(movingLength,moving), 175, 10, 3, 2, 'o');

		}
		else if (lvl == 3) 
		{
			initObject(GetNewNrick(brickLenght, brick), 20, 20, 40, 5, '#');
			initObject(GetNewNrick(brickLenght, brick), 80, 20, 15, 5, '#');
			initObject(GetNewNrick(brickLenght, brick), 110, 15, 15, 10, '#');
			initObject(GetNewNrick(brickLenght, brick), 130, 10, 15, 15, '+');
			
			initObject(GetNewMoving(movingLength, moving), 25, 10, 3, 2, 'o');
			initObject(GetNewMoving(movingLength, moving), 50, 10, 3, 2, 'o');
			initObject(GetNewMoving(movingLength, moving), 80, 10, 3, 2, 'o');
			initObject(GetNewMoving(movingLength, moving), 90, 10, 3, 2, 'o');
			initObject(GetNewMoving(movingLength, moving), 120, 10, 3, 2, 'o');
		}
	}

int main()
{
	SetConsoleSize(80,25);			// Устанавливаем размер окна консоли
	char map[mapHEIGHT][mapWIDTH];	// Создаем карту
	TObject mario;					// Создаем объект Марио
	TObject *brick=nullptr;			// Создаем указатель на массив объектов (кирпичей)
	TObject* moving = nullptr;
	int movingLenght;
	int brickLenght;				// Переменная для хранения количества кирпичей
	int lvl=1;
	int Score;
	CreatLevel(brickLenght, mario, brick,lvl,movingLenght,moving,Score);// Создаем уровень
	do
	{
		ClearMap(map);				// Очищаем карту перед обновлением
		if ((mario.isFly==false)&&(GetKeyState(VK_SPACE) < 0))mario.vertSpeed = -0.7;	// Прыжок
		if (GetKeyState('A') < 0)HorizionMoveMap(brick, 1, brickLenght,mario, movingLenght,moving);			// Движение влево
		if (GetKeyState('D') < 0)HorizionMoveMap(brick, -1, brickLenght,mario, movingLenght,moving);			// Движение вправоif ((mario.isFly==false)&&(GetKeyState(VK_SPACE) < 0))mario.vertSpeed = -0.7;	// Прыжок
		//if (GetKeyState('A') < 0)HorizionMoveMap(brick, 1, brickLenght,mario);			// Движение влево
		//if (GetKeyState('D') < 0)HorizionMoveMap(brick, -1, brickLenght,mario);			// Движение вправо
		if (mario.y > mapHEIGHT - 1)	 // Если Марио упал ниже нижней границы карты
		{
			CreatLevel(brickLenght, mario, brick, lvl, movingLenght, moving,Score);	// Пересоздаем урове
		}
		VertMoveOgject(mario,brick, brickLenght,lvl, movingLenght,moving,mario,Score);	// Обновляем вертикальное движение Марио
		MarrioCollision(mario, brick, brickLenght, lvl, movingLenght, moving,Score);
		for (int i = 0; i < brickLenght; i++)		// Обновляем позицию кирпичей на карте	
			PutObjectOnMap(brick[i], map);			//помещаем персонажа
		for (int i = 0; i < movingLenght; i++)		// Обновляем позицию кирпичей на карте	
		{
			if(moving[i].y>mapHEIGHT)
			{
				DeleteMoving(i, movingLenght, moving);
				i--;
				continue;
			}
			VertMoveOgject(moving[i], brick, brickLenght, lvl, movingLenght, moving,mario,Score);
			HorizonMoveObject(moving[i], brickLenght, brick, lvl, movingLenght, moving,mario,Score);
			PutObjectOnMap(moving[i], map);
		}
		PutObjectOnMap(mario, map);					// Обновляем позицию Марио на карте
		PutScoreOnMap(map, Score);
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