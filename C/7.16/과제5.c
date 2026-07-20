#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 제곱수 반환 함수
int square(int x)
{ 
	return x * x;
}

int main()
{
	int max, min, count = 0;
	printf("min: ");
	scanf("%d", &min);
	printf("max: ");
	scanf("%d", &max);

	if ((min > 0) && (max < 10001))
	{
	
		for (int i = min; i <= max; i++)
		{
			int flag = 1; // flag가 1이면 제곱ㄴㄴ수, 0이면 아님

			// square(j)가 i보다 커지면 더 이상 나눌 필요가 없음
			for (int j = 2; square(j) <= i; j++)
			{
				if (i % square(j) == 0)
				{
					flag = 0; // 제곱수로 나누어떨어지므로 탈락
					break;    // 더 볼 필요 없으니 안쪽 루프 탈출
				}
			}

			// 모든 제곱수를 무사히 통과했다면 출력 및 카운트
			if (flag == 1)
			{
				printf("%d ", i);
				count++;
			}
		}

		printf("\n제곱 ㄴㄴ수: %d개", count);
	}
	else //min < 1 이고 max > 10000일 때 예외 처리
	{
		printf("ERROR(지정한 정수 범위를 벗어났습니다.)");
	}

	return 0;
}
