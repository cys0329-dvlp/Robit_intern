#include <stdio.h>

int main()
{
    /*
    로직) 맨 아래 줄 미리 출력
          맨 위에 줄 별 하나만 출력, 그 아래부터는 2개씩 출력
          앞 공백: 처음에 n-i, 줄이 늘어날수록 1씩 작아짐
          두번째 공백: 1,3,5 순으로 늘어남
    */
    int n;
    int i, j;
    int space, inside;

    printf("값을 입력하세요.");
    scanf_s("%d", &n);

    for (i = 1; i <= n; i++) //n은 y축 방향 -> 줄 개수
    {
        // 마지막 줄
        if (i == n) 
        {
            for (j = 1; j <= 2 * n - 1; j++)//마지막 줄 별의 개수 = 2*n - 1
            {
               printf("*");
            } 
        }
        else
        {
            // 앞 공백
            space = n - i; //앞 공백은 줄이 늘어날수록 1씩 작아짐
            for (j = 1; j <= space; j++)
            {
                printf(" ");
            }
            
            // 첫 번째 별
            printf("*");
            
            // 두번째 줄부터는 다 별 2개씩만 출력
            if (i > 1)
            {
                inside = 2 * i - 3; //두번째 공백은 줄이 늘어날 수록 늘어남

                for (j = 1; j <= inside; j++)
                {
                    printf(" ");
                }
                printf("*");
            }
        }

        printf("\n");
    }

    return 0;
}
