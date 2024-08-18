#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <conio.h> // ��� ������������� _getch()

using namespace std;

int main() {
    const int rows = 10;
    const int cols = 20;
    vector<string> mas(rows, string(cols, ' ')); // ���������� ������ ����� ������ �������
    int x = 10, y = 5;
    char key;
    int ox, oy;
    int ax = 5, ay = 3;
    int count = 0;
    srand(static_cast<unsigned>(time(0)));

    do {
        // ��������� ������� � ������ �������
        mas[0] = string(cols, '#');
        mas[9] = string(cols, '#');

        // ��������� ��������� ������ ���������
        for (int i = 1; i < 9; ++i) {
            mas[i] = "#" + string(cols - 2, ' ') + "#";
        }

        mas[y][x] = '@'; // �����
        mas[ay][ax] = '*'; // ����

        system("cls"); // ������� ������

        //// ������� ������� ����
        //for (const auto& row : mas) {
        //    cout << row << endl;
        //}
        // ������� ������� ���� � �������������� �������� ����� for
        for (int i = 0; i < rows; ++i) {
            cout << mas[i] << endl;
        }

        cout <<"eat apple: "<< count;

        key = _getch(); // ��������� ������� �������
        ox = x;
        oy = y;

        // ��������� ����������
        if (key == 'w') y--;
        if (key == 's') y++;
        if (key == 'a') x--;
        if (key == 'd') x++;

        // �������� �� ������������ �� ������
        if (mas[y][x] == '#') {
            x = ox;
            y = oy;
        }

        // �������� �� ������������ � �����
        if (x == ax && y == ay) {
            ax = rand() % (cols - 2) + 1;
            ay = rand() % (rows - 2) + 1;
            count++;
        }

        mas[y][x] = ' '; // ������� ���������� ��������� ������
    } while (key != 'e'); // ����� �� ������� 'e'

    return 0;
}
