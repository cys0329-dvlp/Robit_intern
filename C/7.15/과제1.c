#include <stdio.h>

int main()
{
    float a, b, c, d, e;
    float avg, max, min, total;

    printf("첫번째 실수를 입력하세요> ");
    scanf_s("%f", &a);

    printf("두번째 실수를 입력하세요> ");
    scanf_s("%f", &b);

    printf("세번째 실수를 입력하세요> ");
    scanf_s("%f", &c);

    printf("네번째 실수를 입력하세요> ");
    scanf_s("%f", &d);

    printf("다섯번째 실수를 입력하세요> ");
    scanf_s("%f", &e);

    total = a + b + c + d + e;
    avg = total / 5;

    // 최대값
    max = a;
    if (b > max)
    {
        max = b;
    }
    if (c > max)
    {
        max = c;
    }
    if (d > max)
    {
        max = d;
    }
    if (e > max)
    {
        max = e;
    }

    // 최소값
    min = a;
    if (b < min)
    {
        min = b;
    }
    if (c < min)
    {
        min = c;
    }
    if (d < min)
    {
        min = d;
    }
    if (e < min)
    {
        min = e;
    }

    printf("평균: %f\n", avg);
    printf("최고점: %f\n", max);
    printf("최저점: %f\n", min);

    return 0;
}
