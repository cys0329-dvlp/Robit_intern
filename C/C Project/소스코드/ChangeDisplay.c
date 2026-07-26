#include "MousePoint.h"
#include "reset_console.h"
#include "difficulty.h"
#include <stdio.h>
#include <windows.h>
#include <conio.h>

int ChangeDifficulty();

int ChangeDisplay()
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;

    // 현재 콘솔 모드 가져오기
    GetConsoleMode(hInput, &mode);

    // Quick Edit 끄기
    mode &= ~ENABLE_QUICK_EDIT_MODE;

    // 마우스 입력 활성화
    mode |= ENABLE_MOUSE_INPUT;

    // 확장 플래그 활성화(Quick Edit 설정 적용을 위해 필요)
    mode |= ENABLE_EXTENDED_FLAGS;

    SetConsoleMode(hInput, mode);
    INPUT_RECORD rec;
    DWORD read;

    while (1)
    {
        ReadConsoleInput(hInput, &rec, 1, &read);

        if (rec.EventType == MOUSE_EVENT)
        {
            MOUSE_EVENT_RECORD mouse = rec.Event.MouseEvent;

            if (mouse.dwEventFlags == 0 &&
                (mouse.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED))
            {
                //난이도 선택
                if ((20 <= mouse.dwMousePosition.X && mouse.dwMousePosition.X <= 30) && (19 <= mouse.dwMousePosition.Y && mouse.dwMousePosition.Y <= 21))
                {
                    reset_console();
                    difficulty(); 
                    ChangeDifficulty();
                }
                //기록
                else if ((54 <= mouse.dwMousePosition.X && mouse.dwMousePosition.X <= 64) && (19 <= mouse.dwMousePosition.Y && mouse.dwMousePosition.Y <= 21))
                {
                    reset_console();
                }
            }
        }
        else if (rec.EventType == KEY_EVENT)
        {
            KEY_EVENT_RECORD key = rec.Event.KeyEvent;

            if (key.bKeyDown && key.wVirtualKeyCode == VK_ESCAPE)
            {
                break;
            }
        }
    }

    return 0;
}
