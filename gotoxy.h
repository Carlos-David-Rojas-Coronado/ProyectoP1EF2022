#include <windows.h>
#include <stdio.h>
using namespace std;

void gotoxy (int x, int y){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon,dwPos);
}
