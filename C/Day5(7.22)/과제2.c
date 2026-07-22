#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void arr_ij(int *row, int *col, int**pArr);
void print(int *sizeRow, int*sizeCol, int**pArr);

/*
코드 설명을 주석으로 모두 설명하기 힘들어 참고 자료 첨부했습니다. 
참고 부탁드립니다!
*/
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

	arr = (int**)malloc(sizeof(int*)*sizeRow);
	for (int i = 0; i < sizeCol; i++)
	{
		arr[i] = (int*)malloc(sizeof(int) * sizeCol);
	}

	arr_ij(&sizeRow, &sizeCol, arr);

	print(&row, &col, arr);

	for (int i = 0; i < row; i++)
	{
		free(arr[i]);
	}

	return 0;
}

void arr_ij(int* sizeRow, int* sizeCol, int** pArr) //달팽이 만드는 함수
{
    /*
    큰 for문 안에 for문이 4개 더 들어가고 i랑 j를 고정시키고 for문을 돌려야합니다 
    또한, i와 j 값을 1씩 증가시키거나 감소시키며 다시 고정시켜야합니다.
    하지만 for문 안에서 i++ 혹은 j--를 해버리면 for문을 도는 데에
    문제가 생기기 때문에 i, j값을 고정시키고++, --시키는 변수 4개 선언헀습니다.
    */
    int count = 1;
    int stuck_i_1 = 0; 
    int stuck_j_2 = *sizeCol - 1;
    int stuck_i_3 = *sizeRow - 1;
    int stuck_j_4 = 0;

    /*
    for문이 도는 횟수도 col과 row로 인해 정해지게 됩니다. 
    그러나 위의 stuck 변수들과 같은 이유로 col과 row의 수를 변경시킨다면 
    전체 구조에 문제가 생기기 때문에 start와 end 변수에 복사시켜 
    start와 end가 대신 for문이 도는 횟수를 조절하도록 하였습니다. 
    */
    int start_1 = 0;
    int end_1 = *sizeCol - 1;

    int start_2 = 1;
    int end_2 = *sizeRow - 1;


    int start_3 = *sizeCol - 2;
    int end_3 = 0;

    int start_4 = *sizeRow - 2;
    int end_4 = 0;

    /*
    큰 for문 안에서 총 4개의 for문이 반복해서 돌아야합니다.
    start, end, stuck 변수들이 왜 ++이고 왜 --인지는 추가로 첨부된 사진을
    참고해주시면 감사하겠습니다!
    */

    for (int i = 0; i < *sizeRow; i++) { 
        for (int j = start_1; j < end_1 + 1; j++) {
            pArr[stuck_i_1][j] = count;
            count++;
        }
        start_1++;
        end_1--;
        stuck_i_1++;


        for (int j = start_2; j < end_2 + 1; j++) {
            pArr[j][stuck_j_2] = count;
            count++;
        }
        start_2++;
        end_2--;
        stuck_j_2--;

        for (int j = start_3; j > end_3 - 1; j--) {
            pArr[stuck_i_3][j] = count;
            count++;
        }
        start_3--;
        end_3++;
        stuck_i_3--;



        for (int j = start_4; j > end_4; j--) {
            pArr[j][stuck_j_4] = count;
            count++;
        }
        start_4--;
        end_4++;
        stuck_j_4++;
    }
}
//결과 출력, 숫자가 커질 수 있으니 4로 
void print(int* row, int* col, int** pArr)
{
	for (int i = 0; i < *row; i++) {
		for (int j = 0; j < *col; j++) {
			printf("%4d", pArr[i][j]);
		}
		printf("\n");
	}
}
