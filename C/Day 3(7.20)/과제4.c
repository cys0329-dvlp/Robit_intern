#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n1;
    int* arr;
    printf("몇 개의 원소를 할당하겠습니까? : ");
    scanf("%d", &n1);
    
    
    arr = (int*)malloc(sizeof(int) * n1);

    for (int i = 0; i < n1; i++)
    {
        printf("정수형 데이터 입력: ");
        scanf("%d", &arr[i]);
    }
    //인덱스 0번은 max, min으로 가정하고 뒤의 값들을 하나씩 비교하며 뒤의 값이 더 크면 그것을 max로 더 작으면 그것을 min으로 수정
    int max = arr[0]; 
    int min = arr[0];

    for (int j = 1; j < n1; j++)
    {
        if (arr[j] > max)
        {
            max = arr[j];
        }
        else if (arr[j] < min)
        {
            min = arr[j];
        }
 
    }
    int sum = 0;
    for (int i = 0; i < n1; i++)
    {
        sum = sum + arr[i];
    }

    float avg = sum / n1; //평균만 실수형으로 정의

    printf("최대: %d\n", max);
    printf("최소: %d\n", min);
    printf("전체 합: %d\n", sum);
    printf("평균: %f\n", avg); 
    return 0;
}
