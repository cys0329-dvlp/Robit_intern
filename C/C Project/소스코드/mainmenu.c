#include <stdio.h>
#include "MousePoint.h"
#include "MainMenu.h"

/* 메인 화면(로고 + 게임 시작/기록/조작법 버튼)을 그린다.
   프로그램 시작 시(main.c)뿐 아니라, 난이도 선택 화면에서 ESC로
   돌아왔을 때도 다시 호출해서 그린다. */
void draw_main_menu(void)
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

    SetMousePoint(20, 20);
    printf("┌─────────┐");
    SetMousePoint(20, 21);
    printf("│게임 시작│");
    SetMousePoint(20, 22);
    printf("└─────────┘");

    SetMousePoint(54, 20);
    printf("┌────┐");
    SetMousePoint(54, 21);
    printf("│기록│");
    SetMousePoint(54, 22);
    printf("└────┘");

    SetMousePoint(80, 20);
    printf("┌──────┐");
    SetMousePoint(80, 21);
    printf("│조작법│");
    SetMousePoint(80, 22);
    printf("└──────┘");
}
