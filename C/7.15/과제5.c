#include <stdio.h>

int main()
{
    /*
    로직) 가운데 줄의 위 아래로 나눠서 위쪽 별 개수 = 줄의 개수 / 아래쪽 별 개수 = 2 * n - i
          공백 개수는 2 * n - (2 * star)로 위아래 동일 
          space, star 변수로 for문 생성
    */
    

    int n;
    int i, j;
    int star, space;

    printf("정수 값을 입력하세요.");
    scanf_s("%d", &n);
    if (n > 0)
    {
        for (i = 1; i <= 2 * n - 1; i++) //y축 방향의 크기 = 2*입력값 - 1
        {
            // 가운데 줄
            if (i == n)
            {
                for (j = 1; j <= 2 * n; j++)
                {
                    printf("*");
                }
            }
            else
            {
                // 위쪽
                if (i < n)
                {
                    star = i; //첫번째 줄이면 별 1개, 두번째 줄이면 별 2개 ....
                }
                // 아래쪽
                else
                {
                    star = 2 * n - i; //위에서부터 i번째 줄 -> 가운데 줄 아래부터 별의 개수 = 2*n - i
                }


                space = 2 * n - (2 * star); //x축 크기 2*n에서 별 개수 빼야하는데 양쪽으로 별이 2개이므로 2*star 빼야함.

                // 왼쪽 별
                for (j = 1; j <= star; j++)
                {
                    printf("*");
                }


                // 가운데 공백
                for (j = 1; j <= space; j++)
                {
                    printf(" ");
                }

                // 오른쪽 별
                for (j = 1; j <= star; j++)
                {
                    printf("*");
                }

            }

            printf("\n");
        }
    }
    else //n<1일 때 예외 처리
    {
        printf("값은 1 이상의 정수여야합니다.");
    }
    

    return 0;
}
