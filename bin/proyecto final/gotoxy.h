#include <windows.h>
#include <stdio.h>
using namespace std;


///Edwin Adony Montejo Martínez 9491-21-3898
void gotoxy (int x, int y){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon,dwPos);
}
