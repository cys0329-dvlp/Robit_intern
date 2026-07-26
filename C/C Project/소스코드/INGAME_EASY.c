#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "MousePoint.h"

#define BOARD_X 2
#define BOARD_Y 2
#define PANEL_X (BOARD_X + 40)
#define PANEL_Y BOARD_Y

int arr[9][9];
int solution_EASY[9][9]; // 정답 배열 (빈칸으로 만들기 전, 완성된 답)
int is_given_EASY[9][9]; // 원래 뚫려있던(=입력 가능한) 칸인지 표시
int is_temp_EASY[9][9];  // 더블클릭으로 넣은 "임시 입력"인지 표시 (틀려도 감점 없음)
int mistake_count_EASY;  // 틀린 횟수 (3번 틀리면 게임 종료)

int define_arr_EASY(int percent);
int is_valid_EASY(int row, int col, int num);
void shuffle_numbers_EASY(int nums[9]);
int fill_board_EASY(int row, int col);
void blind_EASY(int percent);

// ----- 신규: 화면/입력 관련 함수 -----
int cell_content_x_EASY(int col);
int cell_content_y_EASY(int row);
void build_border_EASY(char* buf, int line_index);
void draw_board_EASY(void);
void draw_cell_EASY(int row, int col, int highlight); // highlight: 0=선택안됨, 1=정식입력 선택, 2=임시입력 선택
void draw_panel_EASY(void);
void reveal_solution_EASY(void);

int INGAME_EASY()
{
    define_arr_EASY(40);
    mistake_count_EASY = 0;

    draw_board_EASY();
    draw_panel_EASY();

    // 마우스 클릭 후 숫자 입력 기능 추가 (AI 사용)
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode |= ENABLE_MOUSE_INPUT;
    mode |= ENABLE_EXTENDED_FLAGS;
    SetConsoleMode(hInput, mode);

    INPUT_RECORD rec;
    DWORD read;
    int sel_row = -1, sel_col = -1;
    int sel_temp = 0; // 지금 선택된 칸이 "임시 입력" 모드로 선택된 것인지

    while (1)
    {
        ReadConsoleInput(hInput, &rec, 1, &read);

        if (rec.EventType == MOUSE_EVENT)
        {
            MOUSE_EVENT_RECORD mouse = rec.Event.MouseEvent;

            // 일반 클릭(flags==0) -> 정식 입력 모드로 선택
            // 더블클릭(flags==DOUBLE_CLICK, 지뢰찾기 깃발처럼) -> 임시 입력 모드로 선택
            if ((mouse.dwEventFlags == 0 || mouse.dwEventFlags == DOUBLE_CLICK) &&
                (mouse.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED))
            {
                int is_double = (mouse.dwEventFlags == DOUBLE_CLICK);
                int relX = mouse.dwMousePosition.X - BOARD_X;
                int relY = mouse.dwMousePosition.Y - BOARD_Y;

                // relY가 짝수(0,2,4...)인 줄이 실제 숫자가 있는 줄
                if (relX >= 1 && relY >= 0 && (relY % 2) == 0)
                {
                    int col = (relX - 1) / 4;
                    int row = relY / 2;

                    if (row >= 0 && row <= 8 && col >= 0 && col <= 8)
                    {
                        // 처음부터 채워져 있던 칸(is_given)은 선택 불가
                        if (!is_given_EASY[row][col])
                        {
                            if (sel_row != -1 && sel_col != -1)
                                draw_cell_EASY(sel_row, sel_col, 0); // 이전 선택 강조 해제

                            sel_row = row;
                            sel_col = col;
                            sel_temp = is_double;
                            draw_cell_EASY(sel_row, sel_col, sel_temp ? 2 : 1); // 새 선택 강조
                        }
                    }
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

            if (key.bKeyDown && sel_row != -1 && sel_col != -1)
            {
                // 숫자 1~9 입력 -> 값 채우기
                if (key.wVirtualKeyCode >= '1' && key.wVirtualKeyCode <= '9')
                {
                    arr[sel_row][sel_col] = (char)key.wVirtualKeyCode;

                    if (sel_temp)
                    {
                        // 임시 입력: 틀려도 틀린 횟수에 포함 안 됨
                        is_temp_EASY[sel_row][sel_col] = 1;
                        draw_cell_EASY(sel_row, sel_col, 2);
                        draw_panel_EASY();
                    }
                    else
                    {
                        // 정식 입력: 틀리면 틀린 횟수 증가
                        is_temp_EASY[sel_row][sel_col] = 0;

                        if (arr[sel_row][sel_col] != solution_EASY[sel_row][sel_col])
                        {
                            mistake_count_EASY++;
                        }

                        draw_cell_EASY(sel_row, sel_col, 1);
                        draw_panel_EASY();

                        if (mistake_count_EASY >= 3)
                        {
                            reveal_solution_EASY();
                            draw_panel_EASY();
                            SetMousePoint(BOARD_X, BOARD_Y + 20);
                            printf("3번 틀려서 게임 종료! 정답을 공개합니다. 아무 키나 누르면 돌아갑니다.   ");
                            _getch();
                            break;
                        }
                    }
                }
                // 0, Backspace, Delete -> 다시 빈칸으로 (임시/정식 표시도 초기화)
                else if (key.wVirtualKeyCode == '0' ||
                    key.wVirtualKeyCode == VK_BACK ||
                    key.wVirtualKeyCode == VK_DELETE)
                {
                    arr[sel_row][sel_col] = ' ';
                    is_temp_EASY[sel_row][sel_col] = 0;
                    draw_cell_EASY(sel_row, sel_col, sel_temp ? 2 : 1);
                    draw_panel_EASY();
                }
            }
        }
    }

    return 0;
}

// 각 칸(행/열)이 콘솔 좌표상 어디에 찍히는지 계산
int cell_content_x_EASY(int col) { return BOARD_X + 2 + col * 4; }
int cell_content_y_EASY(int row) { return BOARD_Y + row * 2; }

// 3x3 블록 경계는 굵은 이중선(═║╬...), 블록 안쪽 칸 경계는 얇은 단일선(─│┼...)으로 그려서
// 3x3 구역이 한눈에 구분되게 함.
// line_index: 0~9 (0=맨 위, 9=맨 아래, 3과 6은 3x3 블록 사이의 굵은 경계선)
void build_border_EASY(char* buf, int line_index)
{
    int pos = 0;
    int row_thick = (line_index % 3 == 0); // 이 가로줄이 블록 경계인지
    int is_top = (line_index == 0);
    int is_bottom = (line_index == 9);

    for (int c = 0; c <= 9; c++)
    {
        int col_thick = (c % 3 == 0); // 이 세로 경계가 블록 경계인지
        int is_left = (c == 0);
        int is_right = (c == 9);
        const char* junction;

        if (is_top && is_left)         junction = "╔";
        else if (is_top && is_right)   junction = "╗";
        else if (is_bottom && is_left) junction = "╚";
        else if (is_bottom && is_right)junction = "╝";
        else if (is_top)               junction = col_thick ? "╦" : "╤";
        else if (is_bottom)            junction = col_thick ? "╩" : "╧";
        else if (is_left)              junction = row_thick ? "╠" : "├";
        else if (is_right)             junction = row_thick ? "╣" : "┤";
        else if (row_thick && col_thick)   junction = "╬";
        else if (row_thick && !col_thick)  junction = "╪";
        else if (!row_thick && col_thick)  junction = "╫";
        else                                junction = "┼";

        pos += sprintf(buf + pos, "%s", junction);

        if (c < 9)
            pos += sprintf(buf + pos, "%s", row_thick ? "═══" : "───");
    }
}

// 보드 전체를 한 번 그림 (SetMousePoint로 각 줄 위치를 지정해서 출력)
void draw_board_EASY(void)
{
    char border_line[200];

    for (int i = 0; i <= 9; i++)
    {
        build_border_EASY(border_line, i);
        SetMousePoint(BOARD_X, BOARD_Y - 1 + i * 2);
        printf("%s", border_line);

        if (i < 9) // 마지막(맨 아래) 테두리 다음에는 칸 내용이 없음
        {
            SetMousePoint(BOARD_X, BOARD_Y + i * 2);
            printf("║"); // 왼쪽 맨 끝은 항상 굵은 테두리
            for (int c = 0; c < 9; c++)
            {
                int right_boundary_thick = ((c + 1) % 3 == 0); // 칸 c 오른쪽 경계
                printf(" %c %s", arr[i][c], right_boundary_thick ? "║" : "│");
            }
        }
    }
}

// 칸 하나만 다시 그림 (전체 다시 그리지 않아 깜빡임 없음)
// - 원래 채워진 칸: 기본색
// - 정식 입력이 정답과 다름: 빨간색
// - 임시 입력(더블클릭으로 넣은 값): 색 구분을 위해 청록색, 틀려도 틀린 횟수에 영향 없음
// highlight: 0=선택 안 됨, 1=정식 입력으로 선택됨(초록 배경), 2=임시 입력으로 선택됨(보라 배경)
void draw_cell_EASY(int row, int col, int highlight)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetMousePoint(cell_content_x_EASY(col), cell_content_y_EASY(row));

    WORD default_color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; // 기본(흰색)
    WORD wrong_color = FOREGROUND_RED | FOREGROUND_INTENSITY;                 // 오답(빨간색)
    WORD temp_color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY; // 임시 입력(청록색)
    WORD color = default_color;

    if (!is_given_EASY[row][col] && arr[row][col] != ' ' && arr[row][col] != 0)
    {
        if (is_temp_EASY[row][col])
            color = temp_color; // 임시 입력은 맞고 틀리고 상관없이 구분되는 색으로만 표시
        else if (arr[row][col] != solution_EASY[row][col])
            color = wrong_color; // 정식 입력인데 정답과 다름
    }

    if (highlight == 1)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_INTENSITY | color | FOREGROUND_INTENSITY);
        printf("%c", arr[row][col]);
        SetConsoleTextAttribute(hOut, default_color);
    }
    else if (highlight == 2)
    {
        SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY | color | FOREGROUND_INTENSITY);
        printf("%c", arr[row][col]);
        SetConsoleTextAttribute(hOut, default_color);
    }
    else
    {
        SetConsoleTextAttribute(hOut, color);
        printf("%c", arr[row][col]);
        SetConsoleTextAttribute(hOut, default_color);
    }
}

// 3번 틀려서 게임이 끝났을 때, 보드 전체를 정답으로 채워서 공개함
void reveal_solution_EASY(void)
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            arr[i][j] = solution_EASY[i][j];

    draw_board_EASY();
}

// 오른쪽에 1~9 숫자별 남은 개수와 틀린 횟수를 실시간으로 표시
void draw_panel_EASY(void)
{
    int count[10] = { 0 };
    for (int r = 0; r < 9; r++)
        for (int c = 0; c < 9; c++)
            if (arr[r][c] >= '1' && arr[r][c] <= '9')
                count[arr[r][c] - '0']++;

    SetMousePoint(PANEL_X, PANEL_Y - 1);
    printf("[남은 숫자]      ");

    for (int d = 1; d <= 9; d++)
    {
        SetMousePoint(PANEL_X, PANEL_Y + d);
        printf("%d : %d개      ", d, 9 - count[d]);
    }

    SetMousePoint(PANEL_X, PANEL_Y + 11);
    printf("틀린 횟수 : %d / 3   ", mistake_count_EASY);
}

// 여기부터 AI 다시 공부(okkyuns0329@gmail.com 기록됨)
int define_arr_EASY(int percent) {

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            arr[i][j] = 0; // 배열 초기화
            is_given_EASY[i][j] = 1; // 일단 전부 채워지는 칸으로 표시
            is_temp_EASY[i][j] = 0;  // 임시 입력 표시도 초기화
        }

    srand(time(NULL));
    fill_board_EASY(0, 0); // 원래 있던 rand() 이중 for문을 이 한 줄로 교체

    // 빈칸으로 만들기 전에, 완성된 정답을 solution 배열에 복사해둠
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            solution_EASY[i][j] = arr[i][j];

    blind_EASY(percent);
    return 0;
}

void blind_EASY(int percent)
{
    int blank_count = (int)(81 * percent / 100.0); // 40퍼센트

    int positions[81];
    for (int i = 0; i < 81; i++) positions[i] = i; // 0~80 좌표 채우기

    // Fisher-Yates 셔플 (shuffle_numbers_EASY와 완전히 같은 원리)
    for (int i = 80; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = positions[i];
        positions[i] = positions[j];
        positions[j] = tmp;
    }

    for (int k = 0; k < blank_count; k++) {
        int row = positions[k] / 9;
        int col = positions[k] % 9;
        arr[row][col] = ' ';
        is_given_EASY[row][col] = 0; // 빈칸 -> 사용자가 입력 가능
    }
}

// (row, col)에 num을 넣어도 되는지 행 / 열 / 박스 검사
int is_valid_EASY(int row, int col, int num) {
    for (int j = 0; j < 9; j++) {
        if (arr[row][j] == num + '0') return 0; // 같은 행에 이미 있음
    }
    for (int i = 0; i < 9; i++) {
        if (arr[i][col] == num + '0') return 0; // 같은 열에 이미 있음
    }
    int box_row = (row / 3) * 3;
    int box_col = (col / 3) * 3;
    for (int i = box_row; i < box_row + 3; i++) {
        for (int j = box_col; j < box_col + 3; j++) {
            if (arr[i][j] == num + '0') return 0; // 같은 3x3 박스에 이미 있음
        }
    }
    return 1;
}

// 1~9를 랜덤 순서로 섞기 (매번 다른 판이 나오게 하기 위함)
void shuffle_numbers_EASY(int nums[9]) {
    for (int i = 0; i < 9; i++) nums[i] = i + 1;
    for (int i = 8; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
}

// 원래 코드의 rand() 채우기 이중 for문을 대체하는 백트래킹 함수
int fill_board_EASY(int row, int col) {
    if (row == 9) return 1; // 9행까지 다 채웠으면 완성

    int next_row = (col == 8) ? row + 1 : row;
    int next_col = (col == 8) ? 0 : col + 1;

    int nums[9];
    shuffle_numbers_EASY(nums);

    for (int k = 0; k < 9; k++) {
        int num = nums[k];
        if (is_valid_EASY(row, col, num)) {
            arr[row][col] = '0' + num; // 이렇게 저장하면 arr에 이미 문자 코드로 들어감
            if (fill_board_EASY(next_row, next_col)) return 1;
            arr[row][col] = 0; // 실패하면 되돌리기(backtrack)
        }
    }
    return 0; // 1~9 다 시도해도 안 되면 이전 칸으로 실패 알림
}
