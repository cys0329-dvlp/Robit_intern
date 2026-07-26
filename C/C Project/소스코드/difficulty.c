#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "MousePoint.h"
#include "difficulty.h"

void difficulty()
{
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

    SetMousePoint(30, 20);
    printf("┌────────┐");
    SetMousePoint(30, 21);
    printf("│  EASY  │");
    SetMousePoint(30, 22);
    printf("└────────┘");

   

}
