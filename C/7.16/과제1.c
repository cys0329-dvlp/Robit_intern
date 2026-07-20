#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//전역변수로 선언하여 메인과 함수에서 모두 사용 가능하도록함
int len;
int type;

void type1(int len, int tpye)
{
	for (int i = 1; i <= len; i++) //중앙선 출력
	{
		if (i == (len / 2) + 1)
		{
			for (int j = 1; j <= i; j++)
			{
				printf("*");
			}
			printf("\n");
		}
		else if (i < (len / 2) + 1) //중앙선 위
		{
			for (int j = 1; j <= i; j++)
			{
				printf("*");
			}
			printf("\n");
		}
		else if (i > (len / 2) + 1) // 중앙선 아래
		{
			for (int j = 1; j <= len - i + 1; j++) //별 출력 규칙성: len - i + 1
			{
				printf("*");
			}

			printf("\n");
		}
	}
}

void type2(int len, int tpye)
{
	int type2_count = 0;
	for (int i = 1; i <= len; i++) //중앙선 출력
	{
		if (i == (len / 2) + 1)
		{
			for (int j = 1; j <= (len / 2) + 1; j++)
			{
				printf("*");
			}
			printf("\n");
		}
		else if (i < (len / 2) + 1) //중앙선 위
		{
			for (int j = 1; j <= len / 2 + 1 - i; j++) //공백 출력 규칙성: len/2 + 1 -i(중앙선 값에서 라인 인덱스(i) 빼기)
			{
				printf(" ");
			}
			for (int k = 1; k <= i; k++) //별 출력 규칙성: 중앙선 위에는 i만큼 별 출력
			{
				printf("*");
			}
			printf("\n");
		}
		else if (i > (len / 2) + 1) // 중앙선 아래
		{
			for (int j = 1; j <= i - len / 2 - 1; j++) // 공백 출력 규칙성: i - len/2 - 1
			{
				printf(" ");
			}
			for (int k = 1; k <= len - i + 1; k++) // 별 출력 규칙성: len - i + 1
			{
				printf("*");
			}
			printf("\n");
		}
	}
}

void type3(int len, int tpye)
{
	int type3_count = 0;
	for (int i = 1; i <= len; i++)
	{
		if (i == len / 2 + 1) // 중앙선 출력
		{
			for (int k = 1; k <= len / 2; k++)
			{
				printf(" ");
			}
			printf("*\n");
		}

		else if (i < len / 2 + 1) // 중앙선 위
		{
			for (int k = 1; k <= i - 1; k++)
			{
				printf(" ");
			}
			for (int j = 1; j <= len - 2 * (i - 1); j++) // 별 출력 규칙성: len -2*(i-1)
			{
				printf("*");
			}
			printf("\n");
		}

		else if (i > len / 2 + 1) // 중앙선 아래
		{
			int type3_count = 0;
			for (int k = 1; k <= len - i; k++) // 공백 출력 규칙성: len - i
			{
				printf(" ");
				type3_count++;
			}
			for (int j = 1; j <= i - type3_count;j++) //별 출력 규칙성: 라인 인덱스(i)에서 공백 개수만큼 빼면 되므로 공백 출력마다 count 증가시켜 i에서 빼주기
			{
				printf("*");
			}
			printf("\n");
		}
	}
}

void type4(int len, int tpye)
{
	for (int i = 1; i <= len; i++)
	{
		int type4_count = 0;
		if (i < len / 2 + 1) //중앙선 위까지
		{
			for (int j = 1; j <= i - 1; j++) //공백 출력
			{
				printf(" ");
				type4_count++;
			}
			for (int k = 1; k <= len / 2 + 1 - type4_count; k++) // 별 출력 규칙성: len/2 + 1에서 -1씩 줄어들며 별 출력, -1은 count에 따라 조절
			{
				printf("*");
			}
			printf("\n");
		}
		else if (i >= len / 2 + 1) // 중앙선부터 중앙선 아래까지 한번에 출력
		{
			int type4_under_count = 0;
			for (int j = 1; j <= len / 2; j++)
			{
				printf(" ");
				type4_under_count++;
			}
			for (int k = 1; k <= i - type4_under_count; k++)
			{
				printf("*");
			}
			printf("\n");
		}
	}
}


int main()
{
	printf("사이즈와 종류를 입력하시오.");
	scanf("%d %d", &len, &type);

	if (type == 1)
	{
		type1(len, type);
	}
	else if (type == 2)
	{
		type2(len, type);
	}
	else if (type == 3)
	{
		type3(len, type);
	}
	else if (type == 4)
	{
		type4(len, type);
	}


	return 0;
}
