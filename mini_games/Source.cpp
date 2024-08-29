#include <iostream>
#include <math.h>
#include<Windows.h>
const int mapWIDTH = 80 + 1;			// ������ ����� � ������ ������������ ������� '\0'
const int mapHEIGHT = 25;
void ClearMap(char map[][mapWIDTH])
{
    for (int i = 0; i < mapHEIGHT; i++)
    {
        for (int j = 0; j < mapWIDTH; j++)
        {
            if (j < mapWIDTH - 1)
                map[i][j] = '.'; // ���������� ���������
            else
                map[i][j] = '\0'; // ��������� ������ ������ � ����������� ����
        }
    }
}
void Print(const char map[][mapWIDTH])
{
    for (int i = 0; i < mapHEIGHT; i++)
    {
        std::cout << map[i];  // ������ ������ �����
    }
}
bool isPosInMap(const int& x, const int& y)
{
    return ((x >= 0) && (x < mapWIDTH - 1) && (y >= 0) && (y < mapHEIGHT));
}
struct TObject
{
    double x;
    int y;        // ������� ������� �� �����
    int width, height; // ������ � ������ �������
};
void SetObjectPos(TObject& obj, const double xPos, const int yPos);
void initObject(TObject& obj, const double xPos, const int yPos, const int oWidth, const int oHeight)
{
    SetObjectPos(obj, xPos, yPos);  // ��������� ������� �������
    obj.width = oWidth;             // ��������� ������ �������
    obj.height = oHeight;           // ��������� ������ �������
}
void SetObjectPos(TObject& obj, const double xPos, const int yPos)
{
    obj.x = xPos;		// ��������� ���������� X
    obj.y = yPos;		// ��������� ���������� Y
}
void PutObjectOnMap(TObject& obj, char map[][mapWIDTH])//����������� ���������
{
    int ix = (int)round(obj.x);						// ��������� ���������� X
    int iy = (int)round(obj.y);						// ��������� ���������� Y
    int iWidth = obj.width;				// ��������� ������
    int iHeght = obj.height;			// ��������� ������
    // ��������� ����� ��������� �������
    for (int i = ix; i < (ix + iWidth); i++)
    {
        for (int j = iy; j < (iy + iHeght); j++)
        {
            if (isPosInMap(i, j))					// ���� ������� ������ �����
                map[j][i] = '@';				// ������������� ������ ������
        }
    }
}
void HorizionMoveMap(TObject& obj, double dx,double mx, TObject& mario)
{
    mario.x -= mx;   // ������� �������� ����� � ��������������� �������
    obj.x += dx;     // ����� �������� ������� �� �����
}void setCur(int x, int y)
{
    COORD coord;			// ������� ��������� ��� ������� ������� �������
    coord.X = x;				// ������������� ���������� X
    coord.Y = y;				// ������������� ���������� Y
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);// ������������� ������� �������
}
int main() {
    char map[mapHEIGHT][mapWIDTH];
    TObject mario;
    TObject brick;
    initObject(mario, 39, 10, 3, 3);   // ������������� �����
    initObject(brick, 20, 20, 40, 5);  // ������������� �������
    do
    {
        ClearMap(map);
        if (GetKeyState('A') < 0)
            HorizionMoveMap(brick,1, 0.1, mario);   // �������� �����
        if (GetKeyState('D') < 0)
            HorizionMoveMap(brick,-1, -0.1, mario);  // �������� ������
        PutObjectOnMap(brick, map);
        PutObjectOnMap(mario, map);
        setCur(0, 0);
        Print(map);
        Sleep(1);
    } while (true);
    return 0;
}