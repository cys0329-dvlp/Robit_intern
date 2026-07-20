#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int judge(char set[8])
{
    if (set[0] == 'c' && set[1] == 'd' && set[2] == 'e' && set[3] == 'f' &&
        set[4] == 'g' && set[5] == 'a' && set[6] == 'b' && set[7] == 'C')
    {
        return 0; // ascending
    }
    else if (set[0] == 'C' && set[1] == 'b' && set[2] == 'a' && set[3] == 'g' &&
        set[4] == 'f' && set[5] == 'e' && set[6] == 'd' && set[7] == 'c')
    {
        return 1; // descending
    }
    else
    {
        return 2; // mixed
    }
}

int main()
{
    char set[8];
    int result;

    printf("음 입력\n");

    for (int i = 0; i < 8; i++)
    {
        scanf(" %c", &set[i]); // 공백 문자 무시하도록 %c 앞에 공백 추가
    }

    result = judge(set); //반환함수 가져오기

    printf("\n결과 : ");
    switch (result)
    {
    case 0:
        printf("ascending\n");
        break;
    case 1:
        printf("descending\n");
        break;
    case 2:
        printf("mixed\n");
        break;
    }

    return 0;
}
