#include <stdio.h>

int main()
{
    int n;
    int num1 = 0, num2 = 1, next;

    printf("정수 n 입력(n>0): ");
    scanf_s("%d", &n);

    if (n == 1)
    {
        printf("%d\n", num1);
    }
    else if (n == 2)
    {
        printf("%d\n", num2);
    }
    else if(n>2)
    {
        for (int i = 3; i <= n; i++)
        {
            next = num1 + num2;
            num1 = num2;
            num2 = next;
        }

        printf("%d\n", num2);
    }
    else if(n <=0) //n 범위에 대한 예외처리
    {
        printf("ERROR. n은 1이상의 정수입니다.");
    }

    return 0;
}
