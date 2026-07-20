#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n1;                 // 배열의 크기 N
    int** arr;               // 동적 할당할 2차원 배열

    printf("N: ");
    scanf("%d", &n1);       // N 값 입력

    // N개의 int* 를 담을 포인터 배열을 동적할당
    arr = (int**)malloc(sizeof(int*) * n1);

    // 각 행마다 N개의 int를 담을 공간을 동적할당
    for (int i = 0; i < n1; i++)
    {
        arr[i] = (int*)malloc(sizeof(int) * n1);
    }

    int num = 1; //1부터 시작해서 계속 증가

    // 대각선(i + j = d)을 기준으로 d를 0부터 2N-2까지 증가시키며 순회
    // 오른쪽 아래(N-1,N-1)까지 모든 대각선을 지나가는 것과 같음
    for (int d = 0; d < 2 * n1 - 1; d++)
    {
        // 현재 대각선 d 위에서 i(행 인덱스)가 가질 수 있는 최소값
        // d가 작을 때는 0부터 시작하지만, d가 N을 넘어가면
        // i는 (d - n1 + 1) 부터 시작해야 배열 범위를 벗어나지 않음
        int i_start;
        if (d - n1 + 1 > 0) 
        {
            i_start = (d - n1 + 1);
        }
        else
        {
            i_start = 0;
        }

        // 현재 대각선 d 위에서 i(행 인덱스)가 가질 수 있는 최대값
        // d가 N-1보다 작으면 d까지, 그 이상이면 N-1(마지막 행)까지
        int i_end; 
        if (d < n1 - 1)
        {
            i_end = d;
        }
        else
        {
            i_end = n1 - 1;
        }
        // 각 대각선 안에서는 i가 증가할수록 j(=d-i)는 감소하며
        // 그림처럼 위에서 아래(행 증가) 방향으로 숫자가 커짐
        for (int i = i_start; i <= i_end; i++)
        {
            int j = d - i;      // 같은 대각선 위의 열 인덱스 계산 (i + j = d)
            arr[i][j] = num;    // 계산된 위치에 현재 숫자 저장
            num++;              // 다음 칸에 넣을 숫자로 증가
        }
    }

    // 완성된 배열을 화면에 출력S
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n1; j++)
        {
            printf("%4d", arr[i][j]); // 자리수를 맞춰 보기 좋게 출력
        }
        printf("\n"); // 한 행 출력이 끝나면 줄바꿈
    }

    // 동적할당했던 메모리 해제
    for (int i = 0; i < n1; i++)
    {
        free(arr[i]); // 각 행 메모리 해제
    }
    free(arr);        // 행 포인터 배열 자체 해제

    return 0;
}