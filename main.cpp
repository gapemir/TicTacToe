#include <iostream>
#include <windows.h>
using namespace std;

void cls() {//this function is not my work
    COORD topLeft  = { 0, 0 };
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

void marks_grid_x(int size) {//numbers above grid
    int j=0;
    for (int i = 0; i < size*4 + 3; i++) {
        if (i < 5 || i % 4 != 1)
            cout << ' ';
        else {
            cout << ++j;
        }
    }
    cout << endl;
}

void marks_grid_y(int i) {//letters next to grid
    int j=65;
    if (i < 18 || i % 2 == 0)
        cout << ' ';
    if (i % 2 == 1){
        j=j+i/2;
        cout << (char)j;
    }
    else 
        cout << ' ';
    cout << ' ';
}

void header(int size){ //header of the game
    for(int i=0;i<size;i++)
        cout<<"****";
    cout<<"*****\n\n";
    cout<<" ";
    for(int i=0;i<size-2;i++)
        cout<<"  ";
    cout<<"Tic Tac Toe\n\n";
    for(int i=0;i<size;i++)
        cout<<"****";
    cout<<"*****\n";
}

int brain (char mrezza[10][10], int size){
    int n=0;
    char a='X';
    do{
        for (int i = 0; i < size; i++){//checks horizontal
            for (int j = 0; j < size; j++){
                if(mrezza[i][j]==a)    
                    n++;
            }
            if (n==size)
                return a;
            n=0;
        }
        for (int i = 0; i < size; i++){//checks vertical
            for (int j = 0; j < size; j++){
                if(mrezza[j][i]==a)    
                    n++;
            }
            if (n==size)
                return a;
            n=0;
        }
        for (int i=0;i<size;i++){//checks diagonal/
            if (mrezza[i][i]==a)
                n++;}
        if (n==size)
            return a;
        n=0;
        int j=2;
        for (int i=0;i<size;i++, j--)//checks diagonal\*
            if (mrezza[i][j]==a)
            n++;
        if (n==size)
            return a;
        n=0;
        a-=9;
    }while(a=='O');
return 0;
}

void win(int result, int &size){
    cls();
    for(int i=0;i<size;i++)
        cout<<"****";
    cout<<"*****\n\n";
    cout<<"   ";
    for(int i=0;i<size-2;i++)
        cout<<"  ";
    cout<<(char)result<<"  wins\n\n";
    for(int i=0;i<size;i++)
        cout<<"****";
    cout<<"*****\n";
}

void start(int &size){
    header(3);
    cout<<"Please enter size (max 10)\n";
    cout<<"Size: ";
    cin>>size;
    cls();
}

void print(char grid[10][10],int size,int ms){
    cls();
    header(size);
    marks_grid_x(size);
    for (int i = 0; i < ms; i++) {
        marks_grid_y(i);
        for (int j = 0; j < ms; j++) {
            if (j < 0)
                cout << ' ';
            else if (i == 0 && j == 0)
                cout << (char)201;  //-
            else if (i == 0 && j == ms - 1)
                cout << (char)187;  //¬
            else if (i == ms - 1 && j == 0)
                cout << (char)200;  //L
            else if (i == ms - 1 && j == ms - 1)
                cout << (char)188;  //-
            else if (i == 0 && j % 2 == 0)
                cout << (char)203;  //T
            else if (i == ms - 1 && j % 2 == 0)
                cout << (char)202;  //¦
            else if (i % 2 == 0 && (j == 0 || j == ms - 1)) {
                if (j == 0)
                    cout << (char)204;  //¦
                if (j == ms - 1)
                    cout << (char)185;  //¦
            } else if (i % 2 == 1 && j % 2 == 0)
                cout << (char)186;  //¦
            else if (i % 2 == 0 && j % 2 == 0)
                cout << (char)206;  //╬
            else if (j % 2 == 1) {
                if (i % 2 == 0) 
                    cout << (char)205 << (char)205 << (char)205;  //=
                else 
                    cout<<' '<<grid[(j/2)][(i/2)]<<' ';//tuki pise znake
            }
        }
        cout << endl;
    }
}

int main() {
    int ms, i=0, j=0, x=-1, p=0, result, size;
    char grid[10][10], y=-1, a='A';
    start(size);
    for (int i = 0; i < size; i++)//empties grid
        for (int j = 0; j < size; j++)
            grid[i][j] = ' ';
    ms = size * 2 + 1;
    while(size!=1){
        result=brain(grid, size);
        if (result!=0){
            win(result, size);
            break;
        }
        print(grid,size,ms);
        cout<<"letter, number\n";
        cin>>y>>x;//coordinates for X and O
        x=x-1;
        if(y>='A'&& y<='Z') 
            y=y-65;
        else if (y>='a'&&y<='z')
            y=y-97;
        else{
            cout<<"An error accured\nmake sure you are putting first letter then number"<<endl;
            break;
        }
        if (p==0){
            grid[x][y]='X';
            p=1;
        } else{
            grid[x][y]='O';
            p=0;
        }
        cout<<endl;
        cls();
        cout<<endl;
    }
    cout << endl;
}
