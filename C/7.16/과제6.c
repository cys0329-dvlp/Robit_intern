#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int SIZE = 0;
int set[20] = { 0, };
int x;

void printSet()
{
	printf("집합: {");

	for (int i = 0; i < SIZE; i++)
	{
		printf("%d", set[i]);

		if (i != SIZE - 1) // 마지막 원소가 아니면 콤마로 구분
			printf(", ");
	}

	printf("}\n");
}

int find_index(int x) // x가 set 안에 있으면 인덱스, 없으면 -1 반환 (공통으로 쓰기 위해 추가)
{
	for (int i = 0; i < SIZE; i++)
	{
		if (set[i] == x)
			return i;
	}
	return -1;
}

void add(int x)
{
	if ((x >= 1) && (x <= 20)) // 유효 범위 확인
	{
		if (find_index(x) == -1) // 이미 있으면 무시
		{
			set[SIZE++] = x; // 배열 맨 뒤에 추가하고 SIZE 1 증가
		}
		printSet();
	}
	else
	{
		printf("ERROR. x값이 범위를 초과했습니다.\n");
	}
}

void is_remove(int x) //stdio.h에 remove 함수가 있어서 다른 이름으로 바꿨습니다.
{
	if ((x >= 1) && (x <= 20))
	{
		int idx = find_index(x);

		if (idx != -1) // 있을 때만 제거
		{
			for (int i = idx; i < SIZE - 1; i++)
			{
				set[i] = set[i + 1]; // 뒤의 원소들을 한 칸씩 앞으로 당김
			}
			SIZE--; //원소 하나 줄었으므로 1 감소
		}
		printSet();
	}
	else
	{
		printf("ERROR. x값이 범위를 초과했습니다.\n");
	}
}

void check(int x)
{
	if (find_index(x) != -1)
		printf("1 "); // 존재하면 1 출력
	else
		printf("0 "); // 없으면 0 출력

	printSet();
}

void toggle(int x)
{
	if ((x >= 1) && (x <= 20))
	{
		int idx = find_index(x);

		if (idx != -1) // 있으면 제거
		{
			for (int i = idx; i < SIZE - 1; i++)
			{
				set[i] = set[i + 1];
			}
			SIZE--;
		}
		else // 없으면 추가
		{
			set[SIZE++] = x;
		}

		printSet();
	}
	else
	{
		printf("ERROR. x값이 범위를 초과했습니다.\n");
	}
}

void empty(int x)
{
	SIZE = 0;
	printSet();
}

void all(int x)
{
	if (x == 0) // all은 0만 허용
	{
		for (int i = 0; i < 20; i++)
		{
			set[i] = i + 1;
		}
		SIZE = 20;
	}
	printSet();
}

int main()
{
	char string[20];
	printf("연산을 선택하세요.(1 <= x <= 20)\n");
	printf("add x\n");
	printf("remove x\n");
	printf("check x\n");
	printf("toggle x\n");
	printf("all 0\n");
	printf("empty 0\n");

	while (1)
	{
		printf("\ninput: ");
		scanf("%s %d", string, &x);

		if (string[0] == 'a' && string[1] == 'd' && string[2] == 'd' && string[3] == '\0')
		{
			add(x);
			continue;
		}
		else if (string[0] == 'r' && string[1] == 'e' && string[2] == 'm' && string[3] == 'o' && string[4] == 'v' && string[5] == 'e' && string[6] == '\0')
		{
			is_remove(x);
			continue;
		}
		else if (string[0] == 'c' && string[1] == 'h' && string[2] == 'e' && string[3] == 'c' && string[4] == 'k' && string[5] == '\0')
		{
			check(x);
			continue;
		}
		else if (string[0] == 't' && string[1] == 'o' && string[2] == 'g' && string[3] == 'g' && string[4] == 'l' && string[5] == 'e' && string[6] == '\0')
		{
			toggle(x);
			continue;
		}
		else if (string[0] == 'a' && string[1] == 'l' && string[2] == 'l' && string[3] == '\0')
		{
			if (x == 0)
			{
				all(x);
				continue;
			}
			else
			{
				printf("ERROR. all 명령어는 정수 0만 사용 가능합니다.\n");
			}
		}
		else if (string[0] == 'e' && string[1] == 'm' && string[2] == 'p' && string[3] == 't' && string[4] == 'y' && string[5] == '\0')
		{
			if (x == 0)
			{
				empty(x);
				continue;
			}
			else
			{
				printf("ERROR. empty 명령어는 정수 0만 사용 가능합니다.\n");
			}
		}
		// 종료 명령 추가했습니다. 
		else if (string[0] == 'e' && string[1] == 'x' && string[2] == 'i' && string[3] == 't' && string[4] == '\0')
		{
			break;
		}
		else
		{
			printf("ERROR. 잘못된 명령어입니다.\n"); // 등록되지않은 명령어 예외처리
		}
	}
	return 0;
}
