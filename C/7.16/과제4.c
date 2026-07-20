#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    int arr[100] = { 0, };
    int n; //배열 크기
    int b; //중앙값
    int b_index; //중앙값의 인덱스

    printf("N: ");
    scanf("%d", &n);
    printf("B: ");
    scanf("%d", &b);

    printf("수열 입력: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < n; i++)
    {
        if (arr[i] == b)
        {
            b_index = i; // 중앙값 인덱스 저장
        }
    }

    int count = 0;

    // b_index를 포함하는 모든 구간 [L, R] 확인
    for (int L = 0; L <= b_index; L++)
    {
        for (int R = b_index; R < n; R++)
        {
            int len = R - L + 1; //+1 해줘야 길이 나옴

            if (len % 2 == 0) // 짝수 길이는 건너뜀
            {
                continue;
            }

            // 구간 복사
            int temp[100] = { 0, };
            for (int i = 0; i < len; i++)
            {
                temp[i] = arr[L + i];
            }

            // temp 배열 정렬 (버블 정렬)
            for (int i = 0; i < len - 1; i++)
            {
                for (int j = 0; j < len - 1 - i; j++)
                {
                    if (temp[j] > temp[j + 1])
                    {
                        int tmp = temp[j];
                        temp[j] = temp[j + 1];
                        temp[j + 1] = tmp;
                    }
                }
            }

            // 중앙값 확인
            int median = temp[len / 2];
            if (median == b)
            {
                count++;
            }
        }
    }

    printf("\n중앙값이 %d인 부분수열의 개수 : %d\n", b, count);

    return 0;
}
