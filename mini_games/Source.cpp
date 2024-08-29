#include <iostream>
#include <math.h>
#include<Windows.h>
const int mapWIDTH = 80 + 1;			// Ширина карты с учетом завершающего символа '\0'
const int mapHEIGHT = 25;
void ClearMap(char map[][mapWIDTH])
{
    for (int i = 0; i < mapHEIGHT; i++)
    {
        for (int j = 0; j < mapWIDTH; j++)
        {
            if (j < mapWIDTH - 1)
                map[i][j] = '.'; // Заполнение пробелами
            else
                map[i][j] = '\0'; // Последний символ строки — завершающий нуль
        }
    }
}
void Print(const char map[][mapWIDTH])
{
    for (int i = 0; i < mapHEIGHT; i++)
    {
        std::cout << map[i];  // Печать строки карты
    }
}
bool isPosInMap(const int& x, const int& y)
{
    return ((x >= 0) && (x < mapWIDTH - 1) && (y >= 0) && (y < mapHEIGHT));
}
struct TObject
{
    double x;
    int y;        // Позиция объекта на карте
    int width, height; // Ширина и высота объекта
};
void SetObjectPos(TObject& obj, const double xPos, const int yPos);
void initObject(TObject& obj, const double xPos, const int yPos, const int oWidth, const int oHeight)
{
    SetObjectPos(obj, xPos, yPos);  // Установка позиции объекта
    obj.width = oWidth;             // Установка ширины объекта
    obj.height = oHeight;           // Установка высоты объекта
}
void SetObjectPos(TObject& obj, const double xPos, const int yPos)
{
    obj.x = xPos;		// Установка координаты X
    obj.y = yPos;		// Установка координаты Y
}
void PutObjectOnMap(TObject& obj, char map[][mapWIDTH])//Перемещение персонажа
{
    int ix = (int)round(obj.x);						// Округляем координату X
    int iy = (int)round(obj.y);						// Округляем координату Y
    int iWidth = obj.width;				// Округляем ширину
    int iHeght = obj.height;			// Округляем высоту
    // Заполняем карту символами объекта
    for (int i = ix; i < (ix + iWidth); i++)
    {
        for (int j = iy; j < (iy + iHeght); j++)
        {
            if (isPosInMap(i, j))					// Если позиция внутри карты
                map[j][i] = '@';				// Устанавливаем символ объект
        }
    }
}
void HorizionMoveMap(TObject& obj, double dx,double mx, TObject& mario)
{
    mario.x -= mx;   // Сначала сдвигаем Марио в противоположную сторону
    obj.x += dx;     // Затем сдвигаем объекты на карте
}void setCur(int x, int y)
{
    COORD coord;			// Создаем структуру для задания позиции курсора
    coord.X = x;				// Устанавливаем координату X
    coord.Y = y;				// Устанавливаем координату Y
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);// Устанавливаем позицию курсора
}
int main() {
    char map[mapHEIGHT][mapWIDTH];
    TObject mario;
    TObject brick;
    initObject(mario, 39, 10, 3, 3);   // Инициализация Марио
    initObject(brick, 20, 20, 40, 5);  // Инициализация кирпича
    do
    {
        ClearMap(map);
        if (GetKeyState('A') < 0)
            HorizionMoveMap(brick,1, 0.1, mario);   // Движение влево
        if (GetKeyState('D') < 0)
            HorizionMoveMap(brick,-1, -0.1, mario);  // Движение вправо
        PutObjectOnMap(brick, map);
        PutObjectOnMap(mario, map);
        setCur(0, 0);
        Print(map);
        Sleep(1);
    } while (true);
    return 0;
}