#include <stdio.h>

int main()
{
	int n, r;
	int total_top = 1, total_bot = 1, total_bot2 = 1;

	printf("n을 입력하시오>");
	scanf_s("%d", &n);
	
	printf("r을 입력하시오>");
	scanf_s("%d", &r);
	
	//순열
	for (int i = 1; i <= n; i++) //n! 구하기
	{
		total_top = total_top * i; 
	}
	for (int i = 1; i <= n-r; i++) //(n-r)! 구하기
	{
		total_bot = total_bot * i;
	}
	printf("순열 %dP%d = %d\n", n, r, total_top / total_bot);
	//total 값 초기화
	total_top = 1;
	total_bot = 1;


	//중복 순열
	for (int i = 0; i < r; i++) //r! 구하기
	{
		total_top = total_top * n; // r번 n곱하기 -> n^r
	}
	printf("중복순열 %dPI%d = %d\n", n, r, total_top);
	//total 값 초기화
	total_top = 1;
	total_bot = 1;

	//조합
	for (int i = 1; i <= n; i++) //n! 구하기
	{
		total_top = total_top * i;
	}
	for (int i = 1; i <= r; i++) //r! 구하기
	{
		total_bot2 = total_bot2 * i;
	}
	for (int i = 1; i <= n-r; i++) //(n-r)! 구하기
	{
		total_bot = total_bot * i;
	}
	printf("조합 %dC%d = %d\n", n, r, total_top / (total_bot*total_bot2));

	//total 값 초기화
	total_top = 1;
	total_bot = 1;
	total_bot2 = 1;

	//중복조합
	for (int i = 1; i <= n+r-1; i++) //(n+r-1)! 구하기
	{
		total_top = total_top * i;
	}

	for (int i = 1; i <= r; i++) //r! 구하기
	{
		total_bot2 = total_bot2 * i;
	}
	 
	for (int i = 1; i <= n-1; i++) //(n-1)! 구하기
	{
		total_bot = total_bot * i;
	}

	printf("중복조합 %dH%d = %d\n", n, r, total_top / (total_bot * total_bot2));

	return 0;
}
