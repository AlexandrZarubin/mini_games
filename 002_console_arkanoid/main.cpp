#include<iostream>
#include<string>
#include<vector>
#include <ctime>
#include <conio.h>
#include<Windows.h>

using namespace std;

// Функция для инициализации строки
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
void InsertSymbol(vector<string>& vec,const int width,const string Symbol = " ", const char Symbol2 = ' ')
{
	for (int i = 1; i < vec.size(); ++i)
	{
		vec[i]= Symbol + string(width-2, Symbol2) + Symbol;
	}
}
void Print(const string& str)
{
	cout << str;
}
void PrintAll(const vector<string>& vec)
{
	//for (const string& str : vec)
	for (int i=0;i<vec.size();i++)
	{
		Print(vec[i]);
		
		if (i<vec.size()-1)
		{
			cout << endl;
		}
	}
}
struct Tracket
{
	int x;
	int y;
	int w;
};
void inittracket(Tracket& tr,const int width,const int height)
{
	tr.w = 7;
	tr.x=(width - tr.w) / 2;
	tr.y = height - 1;
}
void PutRacket(vector<string>& vec,Tracket& tr)
{
	for (int i = tr.x; i < tr.x+tr.w; i++)
	{
		vec[tr.y][i] = '@';
	}
}
void moveRacket(Tracket& tr,int x, const int width)
{
	tr.x = x;
	if (tr.x < 1)tr.x=1;
	if (tr.x + tr.w >= width)tr.x = width - 1 - tr.w;
}
void setcur(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int main()
{
	srand(static_cast<unsigned>(time(0)));
	const int width = 65;
	const int height = 25;
	char c;
	vector<string> mas(height, string(width, ' '));
	Tracket trackt;
	inittracket(trackt, width, height);
	init(mas[0], width);
	initializeVector(mas, width);
	do
	{
		//system("cls");
		setcur(0, 0);
		InsertSymbol(mas, width, "#", ' ');
		PutRacket(mas, trackt);
		PrintAll(mas);
		//c = _getch();
		//if (c == 'a')moveRacket(trackt, trackt.x - 1, width);
		if (GetKeyState('A')>=0)moveRacket(trackt, trackt.x + 1, width);
		if (GetKeyState('D')>=0)moveRacket(trackt, trackt.x - 1, width);
		//if (c == 'd')moveRacket(trackt, trackt.x + 1, width);
		
		Sleep(10);
	} while (GetKeyState(VK_ESCAPE) >= 0);
	//int aa = !(GetKeyState(VK_ESCAPE) & 0x8000);
	return 0;
}