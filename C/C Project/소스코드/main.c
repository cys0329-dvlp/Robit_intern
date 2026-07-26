#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

void reset_console();
void SetMousePoint(int x, int y);
int ChangeDisplay();

int main()
{
    // 스도쿠 생성에 쓰는 rand()의 시드는 프로그램 시작 시 딱 한 번만 초기화.
    // (INGAME 안에서 매번 srand를 부르면 같은 초에 여러 번 호출될 때
    //  똑같은 퍼즐이 반복해서 나올 수 있음)
    srand((unsigned int)time(NULL));

    //SUDOKU 출력 AI 사용
    SetMousePoint(30, 10);
    printf(" ███████╗██╗   ██╗██████╗  ██████╗ ██╗  ██╗██╗   ██╗");
    SetMousePoint(30, 11);
    printf(" ██╔════╝██║   ██║██╔══██╗██╔═══██╗██║ ██╔╝██║   ██║");
    SetMousePoint(30, 12);
    printf(" ███████╗██║   ██║██║  ██║██║   ██║█████╔╝ ██║   ██║");
    SetMousePoint(30, 13);
    printf(" ╚════██║██║   ██║██║  ██║██║   ██║██╔═██╗ ██║   ██║");
    SetMousePoint(30, 14);
    printf(" ███████║╚██████╔╝██████╔╝╚██████╔╝██║  ██╗╚██████╔╝");
    SetMousePoint(30, 15);
    printf(" ╚══════╝ ╚═════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═╝ ╚═════╝");

    SetMousePoint(20, 20);
    printf("┌─────────┐");
    SetMousePoint(20, 21);
    printf("│게임 시작│");
    SetMousePoint(20, 22);
    printf("└─────────┘");


    ChangeDisplay();

    return 0;
}
