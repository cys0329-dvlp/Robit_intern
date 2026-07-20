#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n1, n2;                          // N1: 세로, N2: 가로 개수
    printf("입력: ");
    scanf("%d %d", &n1, &n2);            // N1, N2 입력

    if (n1 % 2 == 0 || n2 % 2 == 0)      // 둘 중 하나라도 짝수면 조건 위반
    {
        printf("N1과 N2는 홀수여야합니다.\n");
        return 0;                        // 짝수면 바로 종료
    }

    //N1개의 int* 포인터 배열을 먼저 만들고
    int** arr = (int**)malloc(sizeof(int*) * n1);
    for (int i = 0; i < n1; i++)
        arr[i] = (int*)malloc(sizeof(int) * n2);   // 각 행마다 N2개의 int 공간 할당

    int ci = n1 / 2;   // 중심 행 인덱스 (N1=5 -> ci=2)
    int cj = n2 / 2;   // 중심 열 인덱스 (N2=7 -> cj=3)

    arr[ci][cj] = 1;   // 정중앙 칸은 항상 1
    int count = 2;     // 1 다음 숫자부터 채우기 시작

    // d: 중심으로부터의 |행차이|+|열차이|
    // 1을 중심으로 마름모 모양 테두리가 d=1,2,3... 순서로
    // 하나씩 커지면서(빨간→노랑→초록→하늘색→보라) 시계방향으로 번호가 매겨짐
    int maxD = n1 + n2;   // 모서리까지 충분히 도달할 수 있는 넉넉한 최대값

    for (int d = 1; d <= maxD; d++)
    {
        // ---- 마름모 테두리 d를 4개의 대각선 구간으로 나누어 순서대로 이동 ----

        // 구간1: 중심 아래쪽으로 내려가며 아래쪽 꼭짓점(di=d, dj=0)까지 우하향 이동
        for (int k = 1; k <= d; k++)
        {
            int di = k, dj = k - d;              // (di,dj)는 중심 기준 상대좌표
            int i = ci + di, j = cj + dj;         // 실제 배열 인덱스로 변환
            if (i >= 0 && i < n1 && j >= 0 && j < n2)  // 배열 범위 안일 때만
                arr[i][j] = count++;              // 번호 채우고 count 증가
        }

        // 구간2: 아래쪽 꼭짓점에서 오른쪽 꼭짓점(di=0, dj=d)까지 좌상향 이동
        for (int k = 1; k <= d; k++)
        {
            int di = d - k, dj = k;
            int i = ci + di, j = cj + dj;
            if (i >= 0 && i < n1 && j >= 0 && j < n2)
                arr[i][j] = count++;
        }

        // 구간3: 오른쪽 꼭짓점에서 위쪽 꼭짓점(di=-d, dj=0)까지 좌하향 이동
        for (int k = 1; k <= d; k++)
        {
            int di = -k, dj = d - k;
            int i = ci + di, j = cj + dj;
            if (i >= 0 && i < n1 && j >= 0 && j < n2)
                arr[i][j] = count++;
        }

        // 구간4: 위쪽 꼭짓점에서 왼쪽 꼭짓점(di=0, dj=-d)까지 우상향 이동
        for (int k = 1; k <= d; k++)
        {
            int di = -(d - k), dj = -k;
            int i = ci + di, j = cj + dj;
            if (i >= 0 && i < n1 && j >= 0 && j < n2)
                arr[i][j] = count++;
        }

        if (count > n1 * n2) break;   // 배열의 모든 칸을 다 채웠으면 조기 종료
    }

    printf("출력:\n");
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n2; j++)
            printf("%3d ", arr[i][j]);   // 3자리 폭으로 정렬 출력
        printf("\n");
    }

    // 동적할당 해제
    for (int i = 0; i < n1; i++)
        free(arr[i]);
    free(arr);

    return 0;
}