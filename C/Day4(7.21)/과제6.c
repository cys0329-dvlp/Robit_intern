#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    int** arr;
    arr = (int**)malloc(sizeof(int*) * 3);
    for (int i = 0; i < 3; i++)
    {
        arr[i] = (int*)malloc(sizeof(int) * 4);
    }

    int alter[100];
    int k = 0; //k는 while 문이 몇 번 돌았는지 나타내는 수

    while (1)
    {
        if (k == 0) //처음 돌 때는 input만 출력
        {
            printf("input: ");
            scanf("%d", &n);
        }
        else if (k > 0) // 두번 째 돌 때는 next input 이라고 출력
        {
            printf("next input: ");
            scanf("%d", &n);
        }

        int index = 0; // 12칸 전체를 훑는 카운터, 매 라운드 시작할 때 0으로 초기화

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (k == 0)
                {
                    arr[i][j] = n;
                    printf("%d", arr[i][j]);
                }
                else if (k > 0)
                {
                    int posit = index % (k + 1); // 지금까지 입력 개수(k+1)로 나눈 나머지
                    if (posit < k) // 처음엔 for문은 k까지 돌리며 출력하려고했으나 옆으로 계속 길어져 3X4 형태를 유지할 수 없었습니다. 
                        //그래서 for문 대신 if문을 사용해 숫자 하나 출력될 때마다 index(칸 번호)를 증가시키고 
                        // 그 칸 번호 % k+1(지금까지 입력된 개수)로 나온 나머지가 몇 번째 입력값인지를 알 수 있었습니다.
                    {
                        printf("%d", alter[posit]); // 이전에 저장된 값들
                    }
                    else
                    {
                        printf("%d", n); // 이번에 새로 입력받은 값(아직 alter에 저장 전)
                    }
                    index++;
                }
            }
            printf("\n");
        }
        k++;
        alter[k - 1] = n;
    }

    return 0;
}