#include "MousePoint.h"
#include <stdio.h>
#include <windows.h>
#include <conio.h>



//https://coding-factory.tistory.com/690 참고 자료

void SetMousePoint(int x, int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //STD_OUTPUT_HANDLE은 출력 화면을 의미한다.
    COORD pos; // 구조체
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
}
