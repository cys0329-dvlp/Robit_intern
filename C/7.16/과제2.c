#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{

	int arr[8] = { 0, };

	//입력
	printf("입력\n");

	for (int i = 0; i < 8; i++)
	{
		printf("%d: ", i);
		scanf("%d", &arr[i]);
	}

	printf("\n");

	
	for (int i = 0; i < 8; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	for (int k = 0; k<8; k++)
	{
		int max = arr[0];
		int index = 0;
		for (int i = 0; i < 8-k; i++)
		{
			if (max < arr[i])
			{
				max = arr[i];
				index = i; // 최대값 인덱스 저장 
			}
		}
		// 마지막 인덱스랑 최대값 변환(max가 temp역할을 함)
		arr[index] = arr[7 - k];
		arr[7 - k] = max;

		for (int j = 0; j < 8; j++)
		{
			printf("%d ", arr[j]);
		}
		printf("\n");
	}

	//출력
	for (int i = 0;i < 8; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n\n출력 \n");
	
	for (int i = 0; i < 8; i++)
	{
		printf("%d: ", i);
		printf("%d\n", arr[i]);
	}
	
	return 0;
}
