#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//구조체 선언
typedef struct Items {

    char name[10];
    int purchase;
} item;


int main() {

    int n;
    printf("입력할 과일 수: ");
    scanf("%d", &n);

    //동적 메모리 할당
    item* info = (item*)malloc(sizeof(item) * n); //입력한 n개만큼 메모리 할당

    for (int i = 0; i < n; i++)
    {
        scanf("%s %d", info[i].name, &info[i].purchase); //존재하는 과일과 가격 입력
    }

    char target[10]; //target은 찾는 과일
    scanf("%s", target);
    int sum = 0;
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        int is_match = 1; // 1이면 이번 i가 target이랑 완전히 같다고 판단

        for (int j = 0; j < 10; j++)
        {
            if (info[i].name[j] != target[j]) //info의 인덱스는 i로해서 첫번째 과일의 문자열을 j=0부터 시작으로 쭉 돌림
            {
                is_match = 0; // 한 글자라도 다르면 매칭 실패이므로 플래그 0
                break;
            }

            if (info[i].name[j] == '\0') // 널 문자까지 같았다면 완전히 같은 문자열
            {
                break;
            }
        }

        if (is_match) // target과 item이 완전이 같다면 실행, 조금이라도 다르면 실행X
        {
            sum = sum + info[i].purchase; // sum이 누적되기 때문에 count 1씩 증가시켜 나중에 출력할 때 count로 나눠줘야 제대로 된 값이 나옴
            count++;
        }
        else {
            printf("일치하는 과일이 없습니다.\n");
        }
    }

    if (count == 0) //count가 0이면 is_match가 1이였다는 적이 없다는 것이므로 일치하는 과일 없다고 판단.
    {
        printf("일치하는 과일이 없습니다.\n");
    }
    else //count가 0이 아니라면 is_match가 1이였다는 적이 있었다는 것이므로 합계 출력
    {
        printf("합계: %d", sum / count);
    }

    free(info); //메모리 누수 방지

    return 0;
}
