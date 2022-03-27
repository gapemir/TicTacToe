#include <iostream>
#include <windows.h>
using namespace std;

void cls() { // this function is not my work, it clears screen
    COORD topLeft = {0, 0};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;
    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    SetConsoleCursorPosition(console, topLeft);
}

void marks_grid_x(int size) { // numbers above grid
    for (int i = 0, j = 0; i < size * 4 + 3; i++) {
        if (i < 5 || i % 4 != 1)
            cout << ' ';
        else {
            cout << ++j;
        }
    }
    cout << endl;
}

void marks_grid_y(int i) { // letters next to grid
    char j = 65;
    cout << ' ';
    if (i % 2 == 0)
        cout << ' ';
    else if (i % 2 == 1) {
        j = j + i / 2;
        cout << j;
    }
    cout << ' ';
}

void header(int size) { // header of the game
    for (int i = 0; i < size; i++)
        cout << "****";
    cout << "*****\n\n ";
    for (int i = 0; i < size - 2; i++)
        cout << "  ";
    cout << "Tic Tac Toe\n\n";
    for (int i = 0; i < size; i++)
        cout << "****";
    cout << "*****\n";
}

int brain(char mrezza[10][10], int size) {//checks for win
    short int h, v, d1, d2;
    char a = 'X';
    do {
        h = 0;
        v = 0;
        d1 = 0;
        d2 = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (mrezza[i][j] == a) // checks horizontal
                    h++;
                if (mrezza[j][i] == a) // checks vertical
                    v++;
                if (mrezza[i][size - 1 - j] == a) // checks diagonal/
                    d2++;
            }
            if (mrezza[i][i] == a) // checks diagonal\*
                d1++;
        }
        if (h == size || v == size || d1 == size || d2 == size)
            return a;
        a -= 9;
    } while (a == 'O');
    return 0;
}

bool win(char grid[10][10], int &size) {
    int winner;
    if (!(winner = brain(grid, size)))
        return 0;//continues main loop
    cls();//displays win 
    for (int i = 0; i < size; i++)
        cout << "****";
    cout << "*****\n\n   ";
    for (int i = 0; i < size - 2; i++)
        cout << "  ";
    cout << (char)winner << "  wins\n\n";
    for (int i = 0; i < size; i++)
        cout << "****";
    cout << "*****\n";
    return 1;//breaks main loop
}

void start(int &size) {
    header(3);
    cout << "Please enter size (max 10)\n";
    cout << "Size: ";
    cin >> size;
    cls();
}

void print(char grid[10][10], int size, int ms) {//prints grid
    cls();
    header(size);
    marks_grid_x(size);
    for (int i = 0; i < ms; i++) {
        marks_grid_y(i);
        for (int j = 0; j < ms; j++) {
            if (i == 0 && j == 0)
                cout << (char)201; //╔
            else if (i == 0 && j == ms - 1)
                cout << (char)187; //╗
            else if (i == ms - 1 && j == 0)
                cout << (char)200; //╚
            else if (i == ms - 1 && j == ms - 1)
                cout << (char)188; //╝
            else if (i == 0 && j % 2 == 0)
                cout << (char)203; //╦
            else if (i == ms - 1 && j % 2 == 0)
                cout << (char)202; //╩
            else if (i % 2 == 0 && j == 0)
                cout << (char)204; //╠
            else if (i % 2 == 0 && j == ms - 1)
                cout << (char)185; //╣
            else if (i % 2 == 1 && j % 2 == 0)
                cout << (char)186; //║
            else if (i % 2 == 0 && j % 2 == 0)
                cout << (char)206; //╬
            else if (j % 2 == 1 && i % 2 == 0)
                cout << (char)205 << (char)205 << (char)205; //═
            else if (j % 2 == 1 && i % 2 == 1)
                cout << ' ' << grid[(j / 2)][(i / 2)] << ' '; //' '
        }
        cout << endl;
    }
}

void input(char &y, int &x, int size) {//if you mess up 2 times second wil count
    cout << "letter, number\n";
    while (!(cin >> y >> x) || !(y >= 'A' || y >= 'a') || !(y <= 'A' + size || y <= 'a' + size) || !(x <= size)) { // coordinates for X and O
        cout << "An error accured\nmake sure you are putting first letter then number" << endl;
        cin.clear();
        y = -1;
        x = -1;
    }
    x = x - 1;
}

int main() {
    int ms, x = -1, p = 0, size;
    char grid[10][10], y = -1;
    start(size);
    for (int i = 0; i < size; i++) // empties grid
        for (int j = 0; j < size; j++)
            grid[i][j] = ' ';
    ms = size * 2 + 1;
    while (!win(grid, size) && size > 1) {
        print(grid, size, ms);
        input(y, x, size);
        if (y >= 'A' && y <= 'Z')
            y = y - 65;
        else if (y >= 'a' && y <= 'z')
            y = y - 97;
        if (p == 0) {
            grid[x][y] = 'X';
            p = 1;
        } else {
            grid[x][y] = 'O';
            p = 0;
        }
        cls();
    }
    cout << endl;
}