#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//완료
#define SIZE 5
typedef struct Student
{
	int grade;
	float score;
	char name[10];
}student;

int main()
{
	student s[SIZE];

	student temp;

	for (int i = 0; i < SIZE; i++)
	{
		scanf("%d %f %s", &s[i].grade, &s[i].score, &s[i].name);
	}
	//[1순위: 학년 순, 2순위: 점수 순, 3순위: 이름 순]

	//1순위: 학년이 낮은 순으로 정렬했습니다.
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 1; j < SIZE; j++)
		{
			if (s[j - 1].grade > s[j].grade) //i를 1로 설정하고 i-1부터 돌리면 인덱스가 0부터 4까지 모두 돌 수 있음
			{
				temp = s[j - 1]; //temp를 구조체로 선언했기 때문에 이렇게 바꿔도 학년, 점수, 이름이 모두 같이 바뀜
				s[j - 1] = s[j];
				s[j] = temp;

				
			}
			else if (s[j - 1].grade == s[j].grade) //학년이 똑같을 떼
			{
				if (s[j - 1].score > s[j].score)
				{
					temp = s[j - 1]; //temp를 구조체로 선언했기 때문에 이렇게 바꿔도 학년, 점수, 이름이 모두 같이 바뀜
					s[j - 1] = s[j];
					s[j] = temp;
				}
				else if (s[j - 1].score == s[j].score) //학년이 똑같으면서 점수도 같을 때
				{
					for(int k = 0; k < 10; k++)
					{
						if (s[j - 1].name[k] > s[j].name[k]) //문자 하나하나 받으며 아스키코드 값 비교: 아스키 코드가 작으면 더 먼저 배치
						{
							temp = s[j - 1]; //temp를 구조체로 선언했기 때문에 이렇게 바꿔도 학년, 점수, 이름이 모두 같이 바뀜
							s[j - 1] = s[j];
							s[j] = temp;
							break;
							
						}
						else if (s[j - 1].name[k] < s[j].name[k])
						{
							break;
						}
					}
					
				}
			}
		}
	}

	for (int i = 0; i < SIZE; i++)
	{
		printf("학년: %d, 점수: %f, 이름: %s\n", s[i].grade, s[i].score, s[i].name);
	}

	return 0;
}