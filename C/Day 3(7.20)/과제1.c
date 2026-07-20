#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main()
{
	int arr[5][5]; // 5x5 배열 선언

	int count = 1; //count가 1부터 시작해서 for문 돌 때마다 1씩 증가
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (((1 <= i && i <= 3) && (j == 0 || j == 4)) //5x5 배열로 정해져있으므로 제외할 인덱스만 추출
				|| (i == 2 && (j == 1 || j == 3)))
			{
				arr[i][j] = 0;
			}
			else 
			{
				arr[i][j] = count; //count를 1부터 1씩 증가시켜 차례대로 저장
				count++;
			}
		}
	}
	//배열 출력
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			printf("%2d ", arr[i][j]); 
		}
		printf("\n");
	}
	return 0;
}