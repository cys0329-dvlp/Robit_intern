#include <stdio.h>

int main()
{
    int year;
    printf("년도를 입력하세요>");
    scanf_s("%d", &year);
    if (((year % 4 == 0) && (year % 100 != 0)) || ((year % 4 == 0) && (year % 400 == 0))) //윤년 조건
    {
        printf("%d년은 윤년입니다.", year);
    }
    else if (year < 0)
    {
        printf("ERROR. 년도는 0이상의 정수입니다.");
    }
    else 
    {
        printf("%d년은 윤년이 아닙니다.", year);
    }
    return 0;
}


