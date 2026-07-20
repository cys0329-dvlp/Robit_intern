#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    char inputStr[100] = { 0, };
    char subStr[100] = { 0, };

    printf("최대 99개 문자 입력 <inputStr> : ");
    scanf("%s", &inputStr);

    printf("찾는 문자열 <subStr> : ");
    scanf("%s", &subStr);

    int input_len = 0;
    while (inputStr[input_len] != '\0') //문자열 끝날 때까지 inputstr 길이++
    {
        input_len++;
    }

    int sub_len = 0;
    while (subStr[sub_len] != '\0') //문자열 끝날 때까지 sub 길이++
    {
        sub_len++;
    }

    printf("%s의 위치 : ", subStr);

    int found = 0;
    for (int i = 0; i <= input_len - sub_len; i++) // input 길이에서 sub 길이를 빼야 substring이 문자열 끝을 벗어나지 않음
    {
        int match = 1; //일치하면 1, 불일치하면 0
        for (int j = 0; j < sub_len; j++)
        {
            if (inputStr[i + j] != subStr[j])
            {
                match = 0;
                break;
            }
        }
        if (match == 1)
        {
            printf("%d ", i + 1); // 1부터 시작하는 위치로 출력
            found = 1; //밑의 if문 조건 확인을 위해 found를 1로 초기화
        }
    }

    if (found == 0)
        printf("찾는 문자열이 없습니다.\n");

  

    return 0;
}
