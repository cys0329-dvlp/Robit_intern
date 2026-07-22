#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
/*
void arr_ij(int* row, int* col, int** pArr);
void print(int* sizeRow, int* sizeCol, int** pArr);
*/


//test파일이다!! 꼭 과제 2로 옮겨서 푸시해야함!!

int main()
{
    int** arr = NULL;
    int row, col, sizeRow, sizeCol;

    printf("열의 수를 입력하세요: ");
    scanf("%d", &sizeCol);
    printf("행의 수를 입력하세요: ");
    scanf("%d", &sizeRow);

    row = sizeRow;
    col = sizeCol;

    //배열 선언
    arr = (int**)malloc(sizeof(int*) * row);
    for (int i = 0; i < row; i++)
    {
        arr[i] = (int*)malloc(sizeof(int) * col);
    }

    //입력
    int count = 1;
    int stuck_i_1 = 0; //큰 for문 안에 for문이 4개 더 들어가기 때문에 i,j값을 고정시키고 ++, -- 시키는 변수 4개 선언
    int stuck_j_2 = col - 1;
    int stuck_i_3 = row - 1;
    int stuck_j_4 = 0;


    int start_1 = 0;
    int end_1 = col - 1;

    int start_2 = 1;
    int end_2 = row - 1;


    int start_3 = col - 2;
    int end_3 = 0;

    int start_4 = row - 2;
    int end_4 = 0;

    for (int i = 0; i < row; i++) {
        for (int j = start_1; j < end_1 + 1; j++) {
            arr[stuck_i_1][j] = count;
            count++;
        }
        start_1++;
        end_1--;
        stuck_i_1++;


        for (int j = start_2; j < end_2 + 1; j++) {
            arr[j][stuck_j_2] = count;
            count++;
        }
        start_2++;
        end_2--;
        stuck_j_2--;

        for (int j = start_3; j > end_3 - 1; j--) {
            arr[stuck_i_3][j] = count;
            count++;
        }
        start_3--;
        end_3++;
        stuck_i_3--;



        for (int j = start_4; j > end_4; j--) {
            arr[j][stuck_j_4] = count;
            count++;
        }
        start_4--;
        end_4++;
        stuck_j_4++;
    }
    //출력
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%4d", arr[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < row; i++)
    {
        free(arr[i]);
    }

    return 0;
}
