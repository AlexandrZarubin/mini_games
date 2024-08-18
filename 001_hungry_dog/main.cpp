#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <conio.h> // Для использования _getch()

using namespace std;

int main() {
    const int rows = 10;
    const int cols = 20;
    vector<string> mas(rows, string(cols, ' ')); // Используем вектор строк вместо массива
    int x = 10, y = 5;
    char key;
    int ox, oy;
    int ax = 5, ay = 3;
    int count = 0;
    srand(static_cast<unsigned>(time(0)));

    do {
        // Заполняем верхнюю и нижнюю границы
        mas[0] = string(cols, '#');
        mas[9] = string(cols, '#');

        // Заполняем остальные строки границами
        for (int i = 1; i < 9; ++i) {
            mas[i] = "#" + string(cols - 2, ' ') + "#";
        }

        mas[y][x] = '@'; // Игрок
        mas[ay][ax] = '*'; // Цель

        system("cls"); // Очистка экрана

        //// Выводим игровое поле
        //for (const auto& row : mas) {
        //    cout << row << endl;
        //}
        // Выводим игровое поле с использованием обычного цикла for
        for (int i = 0; i < rows; ++i) {
            cout << mas[i] << endl;
        }

        cout <<"eat apple: "<< count;

        key = _getch(); // Считываем нажатие клавиши
        ox = x;
        oy = y;

        // Обработка управления
        if (key == 'w') y--;
        if (key == 's') y++;
        if (key == 'a') x--;
        if (key == 'd') x++;

        // Проверка на столкновение со стеной
        if (mas[y][x] == '#') {
            x = ox;
            y = oy;
        }

        // Проверка на столкновение с целью
        if (x == ax && y == ay) {
            ax = rand() % (cols - 2) + 1;
            ay = rand() % (rows - 2) + 1;
            count++;
        }

        mas[y][x] = ' '; // Очищаем предыдущее положение игрока
    } while (key != 'e'); // Выход по нажатию 'e'

    return 0;
}
