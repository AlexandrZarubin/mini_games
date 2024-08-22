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
	const int mapWIDTH = 80+1;
	const int mapHEIGHT = 25;
	
	struct TObject//персонаж
	{
		double x, y;
		double width, height;//ширина и высота
		double vertSpeed;//вертикальная скорость
		bool isFly;
		char cType;
	};
	void ClearMap(char map[][mapWIDTH])//заполнение карты
	{
		for (int i = 0; i < mapHEIGHT; i++)
		{
			for (int j = 0; j < mapWIDTH; j++)
			{
				if (j < mapWIDTH-1)map[i][j] = ' ';
				else map[i][j] = '\0';
			}
		}
		map[mapHEIGHT - 1][mapWIDTH - 2] = '\0';
	}
	void Print(const char map[][mapWIDTH])//отрисовка карты
	{
		for (int i = 0; i < mapHEIGHT; i++)
		{
			cout << map[i];
		}
	}
	void SetObjectPos(TObject& obj,const double xPos,const double yPos)//задает позицию персонажа
	{
		obj.x = xPos;
		obj.y = yPos;
	}
	void initObject(TObject& obj, const double xPos, const double yPos, const double oWidth, const double oHeight,const char &inType)
	{
		//инициалаизация перснонажа
		SetObjectPos(obj, xPos, yPos);
		obj.width = oWidth;   //задаем ширину персонажа
		obj.height = oHeight;
		obj.vertSpeed = 0;
		obj.cType = inType;
	}
	bool isCollision(TObject& obj1, TObject& obj2);
	void VertMoveOgject(TObject& obj, TObject brick[], const int& brickLenght)
	{
		obj.isFly = true;
		obj.vertSpeed += 0.04;
		SetObjectPos(obj, obj.x, obj.y + obj.vertSpeed);
		for (int i = 0; i <brickLenght; i++)
		{
		if (isCollision(obj, brick[i]))
		{
			obj.y -= obj.vertSpeed;
			obj.vertSpeed = 0;
			obj.isFly = false;
			break;
		}
		}
	}
	bool isPosInMap(const int& x,const int& y)
	{
		return ((x >= 0) && (x < mapWIDTH-1) && (y >= 0) && (y < mapHEIGHT));
	}
	void PutObjectOnMap(TObject& obj,char map[][mapWIDTH])//Перемещение персонажа
	{
		int ix = (int)round(obj.x);
		int iy = (int)round(obj.y);
		int iWidth = (int)round(obj.width);
		int iHeght = (int)round(obj.height);
		for (int i = ix; i <(ix+iWidth) ; i++)
		{
			for (int j = iy; j < (iy+iHeght); j++)
			{
				if(isPosInMap(i, j))
					map[j][i] = obj.cType;
			}
		}
	}
	void setCur(int x, int y)
	{
		COORD coord;
		coord.X=x;
		coord.Y=y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
	}
	void HorizionMoveMap(TObject obj[], double dx,const int& brickLenght, TObject&mario)
	{
		mario.x -= dx;
		for (int i = 0; i < brickLenght; i++)
		{
			if (isCollision(mario,obj[i]))
			{
			mario.x += dx;
			return;
			}
		}
		mario.x += dx;
		for(int i=0;i<brickLenght;i++)
			obj[i].x += dx;
	}
	bool isCollision(TObject& obj1, TObject& obj2)
	{
		return  ((obj1.x + obj1.width) > obj2.x) && (obj1.x < (obj2.x + obj2.width)) &&
				((obj1.y + obj1.height) > obj2.y) && (obj1.y < (obj2.y + obj2.height));
	}
	void CreatLevel(int&brickLenght,TObject&mario,TObject**brick)
	{
		brickLenght = 5;
		initObject(mario, 39, 10, 3, 3,'@');
		*brick = new TObject[brickLenght];
		if (*brick == nullptr)
		{
			std::cerr << "error allocation memory" << endl;
			return ;
		}
		else
		{
			initObject((*brick)[0], 20, 20, 40, 5,'#');
			initObject((*brick)[1], 60, 15, 10, 10, '#');
			initObject((*brick)[2], 80, 20, 20, 5, '#');
			initObject((*brick)[3], 120, 15, 10, 10, '#');
			initObject((*brick)[4], 150, 20, 40, 5, '#');
			
		}

	}
int main()
{
	SetConsoleSize(80,25);
	char map[mapHEIGHT][mapWIDTH];
	TObject mario;
	TObject *brick=nullptr;
	int brickLenght;
	//SetObjectPos(mario, 20, 10);//инициализруем персонаажа
	//initObject(mario, 39, 10, 3, 3);
	//initObject(brick[0], 20, 20, 40, 5);
	CreatLevel(brickLenght, mario, &brick);
	do
	{
		ClearMap(map);
		if ((mario.isFly==false)&&(GetKeyState(VK_SPACE) < 0))mario.vertSpeed = -0.7;
		if (GetKeyState('A') < 0)HorizionMoveMap(brick, 1, brickLenght,mario);
		if (GetKeyState('D') < 0)HorizionMoveMap(brick, -1, brickLenght,mario);
		if (mario.y > mapHEIGHT - 1)
		{
			if (brick != nullptr)
			{
				delete[]brick;
				brick = nullptr;
			}
			CreatLevel(brickLenght, mario, &brick);
		}
		VertMoveOgject(mario,brick, brickLenght);
		for (int i = 0; i < brickLenght; i++)
			PutObjectOnMap(brick[i], map);//помещаем персонажа
		PutObjectOnMap(mario, map);//помещаем персонажа
		setCur(0, 0);

		Print(map);
		Sleep(10);
	} while (GetKeyState(VK_ESCAPE)>=0);
	
	if (brick != nullptr)
	{
		delete[]brick;
		brick = nullptr;
	}
	return 0;
}