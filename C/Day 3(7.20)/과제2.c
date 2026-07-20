#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n1, n2;
    int** arr_A;
    int** arr_B;
    printf("N1: ");
    scanf("%d", &n1);
    printf("N2: ");
    scanf("%d", &n2);

    arr_A = (int**)malloc(sizeof(int*) * n1);
    for (int i = 0; i < n1; i++)
    {
        arr_A[i] = (int*)malloc(sizeof(int) * n2);
    }

    int count = 1;
    for (int i = 0; i < n1; i++) // i = y축 n1까지 출력
    {
        for (int j = 0; j < n2; j++) // j = x축 n2까지 출력
        {
            arr_A[i][j] = count; //count = 1부터 시작해서 1씩 증가함. 
            count++;
        }
        printf("\n");
    }
    
    
    printf("\n----배열 A--- \n");
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            printf("%2d ", arr_A[i][j]);
        }
        printf("\n");
        
    }
    //로직: 과제와 같이 출력하기 위해서는 x좌표 값과 y좌표 값을 바꾸면 됨.

    //n1과 n2를 바꿔서 가로 세로 사이즈 변경(여기서 바꿨으므로 아래 코드에서 바꿀 필요 X)
    int temp;
    temp = n1;
    n1 = n2;
    n2 = temp;

    arr_B = (int**)malloc(sizeof(int*) * n1);
    for (int i = 0; i < n1; i++)
    {
        arr_B[i] = (int*)malloc(sizeof(int) * n2);
    }

    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            arr_B[i][j] = arr_A[j][i]; // 배열 A에 있는 x좌표, y좌표 값을 바꿔서 배열 B에 대입
        }
        printf("\n");
    }

    printf("\n----배열 B----\n");
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            printf("%2d ", arr_B[i][j]);
        }
        printf("\n");

    }

    return 0;
}