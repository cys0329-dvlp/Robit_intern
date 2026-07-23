#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct _Node //Node 구조체 선언
{
    int data;
    struct _Node* next;
}Node;

typedef struct _Queue//Stack 구조체 선언
{
    Node* head;
    Node* tail;
    int size;
}Queue;

int Enqueue(Queue* pQu, int n);
int Dequeue(Queue* pQu);
int size(Queue* pQu);
int front(Queue* pQu);
int rear(Queue* pQu);
int isEmpty(Queue* pQu);
int printQueue(Queue* pQu);
int string_compare(char a[], char b[]);

int main()
{
    Queue qu = { NULL, NULL, 0 }; //처음은 NULL값, 크기 0으로 시작
    Queue* pQu = &qu;
    while (1)
    {
        printf("==명령어를 입력하시오==\n");
        int n = 1;
        int d;
        char oder[30];
        scanf("%s", &oder);

        //입력한 문자열이 명령어와 똑같을 때 함수 실행
        if (string_compare(oder, "Enqueue") == 0)
        {
            scanf("%d", &d); // 명령어 중에 Enqueue만 뒤에 숫자를 붙여주기 때문에 Enqueue만 따로 scanf 한번 더 해줬습니다
            Enqueue(pQu, d);
        }
        else if (string_compare(oder, "Dequeue") == 0)
        {
            Dequeue(pQu);
        }
        else if (string_compare(oder, "size") == 0)
        {
            size(pQu);
        }
        else if (string_compare(oder, "front") == 0)
        {
            front(pQu);
        }
        else if (string_compare(oder, "rear") == 0)
        {
            rear(pQu);
        }
        else if (string_compare(oder, "isEmpty") == 0)
        {
            isEmpty(pQu);
        }
        else if (string_compare(oder, "printQueue") == 0)
        {
            printQueue(pQu);
        }
        else if (string_compare(oder, "exit") == 0)
        {
            break;
        }
        else {
            printf("잘못된 명령어입니다.\n");
        }
    }
    return 0;
}
int string_compare(char a[], char b[]) //a혹은 b배열 둘 중에 하나라도 공백이 생기면 종료
{
    int i = 0;
    while (a[i] != '\0' || b[i] != '\0')
    {
        if (a[i] > b[i]) //아스키 코드 값 비교, a,b값이 다르면 다른 문자라는 의미이므로 -1 혹은 1 반환
        { 
            return -1;
        }
        else if (a[i] < b[i])
        {
            return 1;
        }
        i++;
    }
    return 0; //위 경우 모두 아니면 문자가 같다는 의미이므로 0 반환하고 main함수에서 0일 때 명령어 실행함
}

int Enqueue(Queue* pQu, int n)
{
    Node* s = (Node*)malloc(sizeof(Node));
    s->data = n;
    s->next = NULL;   // 새 노드는 큐의 맨 뒤이므로 next는 항상 NULL

    if (pQu->head == NULL)   // 큐가 비어있던 경우
    {
        pQu->head = s;
        pQu->tail = s;
    }
    else                     // 큐에 이미 노드가 있는 경우
    {
        pQu->tail->next = s;  // 기존 tail의 next가 새 노드를 가리키도록 연결
        pQu->tail = s;        // tail을 새 노드로 갱신
    }
    pQu->size++;
    return 0;
}

int Dequeue(Queue* pQu)
{
    if (pQu->size == 0)
    {
        printf("Queue가 비어있습니다.\n");
    }
    else
    {
        //ptr이라는 포인터 새로 선언해서 ptr에 top값 저장해주고 ptr 메모리 해제
        // 전 node에 top값 저장
        Node* ptr = pQu->head;
        pQu->head = pQu->head->next;
        if (pQu->head == NULL)   // 마지막 노드를 삭제한 경우 tail도 NULL로 맞춰줌
        {
            pQu->tail = NULL;
        }
        printf("삭제된 값: %d\n", ptr->data);
        free(ptr);
        pQu->size--;
    }
    return 0;
}

int size(Queue* pQu)
{
    int a = pQu->size;
    printf("Queue의 size: %d\n", a);
    return a;
}

int front(Queue* pQu)
{
    if (pQu->size == 0)
    {
        printf("Queue가 비어있습니다.\n");
        return -1;
    }
    printf("%d\n", pQu->head->data);
    return pQu->head->data;
}

int rear(Queue* pQu)
{
    if (pQu->size == 0)
    {
        printf("Queue가 비어있습니다.\n");
        return -1;
    }
    printf("%d\n", pQu->tail->data);
    return pQu->tail->data;
}

int isEmpty(Queue* pQu)
{
    if (pQu->size == 0)
    {
        printf("True\n");
        return 1;
    }
    else
    {
        printf("False\n");
        return 0;
    }
}

int printQueue(Queue* pQu)
{
    if (pQu->size == 0)
    {
        printf("Queue가 비어있습니다.\n");
    }
    else
    {
        printf("==Queue 안의 값==\n");
        for (Node* p = pQu->head; p != NULL; p = p->next)   // for문이 돌면 p = p->next로 다음 값 연속해서 출력
        {
            printf("%d ", p->data);
        }
        printf("\n");
    }
    return 0;
}
