#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n1, n2;              // n1: 행(row) 개수, n2: 열(column) 개수
    int** arr;                // 동적 할당할 2차원 배열의 포인터

    printf("N1: ");
    scanf("%d", &n1);         // 행의 개수 입력받기

    printf("N2: ");
    scanf("%d", &n2);         // 열의 개수 입력받기

    //행 개수(n1)만큼 포인터 배열 생성
    arr = (int**)malloc(sizeof(int*) * n1);

    //각 행마다 열 개수(n2)만큼 int 배열 생성
    for (int i = 0; i < n1; i++)
    {
        arr[i] = (int*)malloc(sizeof(int) * n2);
    }

    //채울 때 경계값 설정
    int top = 0;              // 위쪽 경계(행 인덱스)
    int bottom = n1 - 1;      // 아래쪽 경계(행 인덱스)
    int left = 0;             // 왼쪽 경계(열 인덱스)
    int right = n2 - 1;       // 오른쪽 경계(열 인덱스)

    int count = 1;            // 배열에 채워 넣을 값(1부터 시작)

    // top이 bottom보다 작거나 같고, left가 right보다 작거나 같은 동안 반복
    // (아직 채울 테두리가 남아있는 동안 반복)
    while (top <= bottom && left <= right)
    {
        // 1) 왼쪽(left) -> 오른쪽(right) : 맨 윗줄(top)을 좌에서 우로 채움
        for (int j = left; j <= right; j++)
        {
            arr[top][j] = count++;   // 현재 위치에 count 값을 넣고 1 증가
        }
        top++;                        // 윗줄을 다 채웠으므로 위쪽 경계를 한 칸 아래로

        // 2) 위(top) -> 아래(bottom) : 맨 오른쪽 줄(right)을 위에서 아래로 채움
        for (int i = top; i <= bottom; i++)
        {
            arr[i][right] = count++; // 현재 위치에 count 값을 넣고 1 증가
        }
        right--;                      // 오른쪽 줄을 다 채웠으므로 오른쪽 경계를 한 칸 왼쪽으로

        // 남은 영역이 있는지 다시 확인 (한 줄/한 칸만 남은 경우 중복 방지)
        if (top <= bottom)
        {
            // 3) 오른쪽(right) -> 왼쪽(left) : 맨 아랫줄(bottom)을 우에서 좌로 채움
            for (int j = right; j >= left; j--)
            {
                arr[bottom][j] = count++; // 현재 위치에 count 값을 넣고 1 증가
            }
            bottom--;                      // 아랫줄을 다 채웠으므로 아래쪽 경계를 한 칸 위로
        }

        if (left <= right)
        {
            // 4) 아래(bottom) -> 위(top) : 맨 왼쪽 줄(left)을 아래에서 위로 채움
            for (int i = bottom; i >= top; i--)
            {
                arr[i][left] = count++; // 현재 위치에 count 값을 넣고 1 증가
            }
            left++;                      // 왼쪽 줄을 다 채웠으므로 왼쪽 경계를 한 칸 오른쪽으로
        }
    }

    // 완성된 배열을 화면에 행렬 형태로 출력
    for (int i = 0; i < n1; i++)         // 행을 순서대로 순회
    {
        for (int j = 0; j < n2; j++)     // 열을 순서대로 순회
        {
            printf("%2d ", arr[i][j]);   // 각 원소를 폭 2칸으로 정렬하여 출력
        }
        printf("\n");                     // 한 행 출력이 끝나면 줄바꿈
    }

    // 동적 할당했던 메모리 해제
    for (int i = 0; i < n1; i++)
    {
        free(arr[i]);                     // 각 행에 할당했던 메모리 해제
    }
    free(arr);                             // 포인터 배열 자체의 메모리 해제

    return 0;
}
