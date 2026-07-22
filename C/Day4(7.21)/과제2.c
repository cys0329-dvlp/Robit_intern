#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Point
{
    int x;
    int y;
}point;

int main()
{
    int n; // 입력받을 좌표 수
    printf("입력: ");
    scanf("%d", &n);
    point* info = (point*)malloc(sizeof(point) * n);

    int** result_x;
    result_x = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++)
    {
        result_x[i] = (int*)malloc(sizeof(int) * (n - 1));
    }

    int** result_y;
    result_y = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++)
    {
        result_y[i] = (int*)malloc(sizeof(int) * (n - 1));
    }

    float** result;
    result = (float**)malloc(sizeof(float*) * n);
    for (int i = 0; i < n; i++)
    {
        result[i] = (float*)malloc(sizeof(float) * (n - 1));
    }

    float* sum;
    sum = (float*)malloc(sizeof(float) * n);
    for (int i = 0; i < n; i++)
    {
        sum[i] = 0; // malloc은 0으로 초기화해주지 않으므로 사용 전에 직접 초기화해야 함
    }

    //x,y값 입력받기
    for (int i = 0; i < n; i++)
    {

        scanf("%d %d", &info[i].x, &info[i].y);

    }

    int target_x;
    int compare_x;
    for (int i = 0; i < n; i++) // target의 인덱스를 바꿔주는 역할
    {
        target_x = info[i].x;
        int k = 0; //result[i][j]일 때 continue 때문에 j가 영향을 받기 때문에 j부분은 k로 대체
        for (int j = 0; j < n; j++) // target을 제외하고 j값을 바꿔주며 target과의 차를 구해야함. j는 0부터 시작하긴하지만 밑의 조건문을 통해 target과 같은 값을 가리킬 때는 continue로 스킵함
        {
            compare_x = info[j].x;
            if (i == j)
            {
                continue;
            }
            else
            {
                result_x[i][k] = (target_x - compare_x) * (target_x - compare_x);
                k++;
                //i=j일 때 continue 했기때문에 i-1부터 입력해야 인덱스 0부터 차례로 채워짐
            }
        }
    }


    int target_y;
    int compare_y;
    for (int i = 0; i < n; i++) // target의 인덱스를 바꿔주는 역할
    {
        target_y = info[i].y;
        int k = 0; //result[i][j]일 때 continue 때문에 j가 영향을 받기 때문에 j부분은 k로 대체
        for (int j = 0; j < n; j++) // target을 제외하고 j값을 바꿔주며 target과의 차를 구해야함. j는 0부터 시작하긴하지만 밑의 조건문을 통해 target과 같은 값을 가리킬 때는 continue로 스킵함
        {
            compare_y = info[j].y;
            if (i == j)
            {
                continue;
            }
            else
            {
                result_y[i][k] = (target_y - compare_y) * (target_y - compare_y);
                k++;
                //i=j일 때 continue 했기때문에 i-1부터 입력해야 인덱스 0부터 차례로 채워짐
            }
        }
    }


    for (int i = 0; i < n; i++) //본인을 제외하고 제곱값을 result에 저장했기 때문에 n-1까지 순회
    {
        for (int j = 0; j < n - 1; j++)
        {
            result[i][j] = sqrt(result_x[i][j] + result_y[i][j]);
        }
    }


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++) // result의 실제 크기(n-1)를 벗어나지 않도록 수정
        {
            sum[i] += result[i][j];
        }
    }

    float max = sum[0];
    int index = 0; // 가장 큰 값이 없을 경우를 대비해 0으로 시작
    for (int k = 0; k < n; k++)
    {
        if (sum[k] > max)
        {
            max = sum[k];
            index = k; // 조건을 만족할 때만 갱신되도록 if문 안으로 이동
        }
    }

    printf("가장 거리가 먼 좌표는 (%d, %d)이며 다른 좌표의 거리 총합은 %0.1f입니다.", info[index].x, info[index].y, max);


    return 0;
}
