#include "MousePoint.h"
#include "reset_console.h"
#include "INGAME.h"
#include <stdio.h>
#include <windows.h>
#include <conio.h>


int ChangeDifficulty() //AI 사용. 일단 다음 단계 진행 후 다시 직접 짜기
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
                //EASY (level 1: 단서 50개)
                if ((30 <= mouse.dwMousePosition.X && mouse.dwMousePosition.X <= 40) && (20 <= mouse.dwMousePosition.Y && mouse.dwMousePosition.Y <= 22))
                {
                    reset_console();
                    INGAME_EASY(1);
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
