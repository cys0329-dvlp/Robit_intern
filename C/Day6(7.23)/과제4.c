#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node //Node 구조체 선언
{
    char data;
    struct _Node* next;
} Node;

typedef struct _Queue //Queue 구조체 선언
{
    Node* head;
    Node* tail;
    int size;
} Queue;

typedef struct _Stack //Stack 구조체 선언
{
    Node* top;
    int size;
} Stack;

void Enqueue(Queue* pQu, char c);
int Dequeue(Queue* pQu, char* out);
void push(Stack* stk, char c);
int pop(Stack* stk, char* out);

int main()
{
    char c;
    Queue qu = { NULL, NULL, 0 };
    Queue* pQu = &qu;

    Stack stack = { NULL, 0 };
    Stack* stk = &stack;

    printf("문자열 입력: ");

    // 큐에 문자를 순서대로, 스택에도 동시에 넣음
    while (1)
    {
        scanf("%c", &c);
        if (c == '\n')   //엔터 치면 while문 종료 
        {
            break;
        }
        if (c == ' ')    // 공백은 카운트 X (양쪽에서 세면 어긋나기 때문에)
        {
            continue;
        }
        Enqueue(pQu, c);
        push(stk, c);
    }

    int count = pQu->size;   // 큐 크기 = 공백을 제외한 문자 개수
    int is_same = 1;         // 1이면 회문, 0이면 회문 아님

    for (int i = 0; i < count; i++)
    {
        char front, top;
        Dequeue(pQu, &front);   // 큐에서 앞에서부터 순서대로 꺼냄
        pop(stk, &top);         // 스택에서 뒤에서부터(역순) 꺼냄

        if (front != top) //문자가 하나라도 다르면 0출력하고 바로 for문 끝냄
        {
            is_same = 0;
            break;
        }
    }

    if (is_same == 1)
    {
        printf("회문입니다\n");
    }
    else
    {
        printf("회문이 아닙니다\n");
    }

    return 0;
}

void Enqueue(Queue* pQu, char c)
{
    Node* s = (Node*)malloc(sizeof(Node));
    s->data = c;
    s->next = NULL;

    if (pQu->head == NULL) //NULL이라는 것은 Node가 하나 밖에 안들어 온 것이기 때문에 head와 tail이 모두 같아야함.
    {
        pQu->head = s;
        pQu->tail = s;
    }
    else  //아니라면 새로 추가 된 값을 tail로 할당
    {
        pQu->tail->next = s;
        pQu->tail = s;
    }
    pQu->size++;
}

int Dequeue(Queue* pQu, char* out)
{
    if (pQu->head == NULL) //head가 NULL이면 하나 밖에 없는 것이므로 굳이 없애지 않아도 됨.
    {
        return 0;
    }
    Node* ptr = pQu->head;
    *out = ptr->data;
    pQu->head = pQu->head->next; //여기서 head 변경
    if (pQu->head == NULL) //head 변경 후 한번 더 확인
    {
        pQu->tail = NULL;
    }
    free(ptr);
    pQu->size--;
    return 1;
}

void push(Stack* stk, char c)
{
    Node* s = (Node*)malloc(sizeof(Node));
    s->data = c;
    s->next = stk->top;   // 새 노드가 항상 맨 위(top)가 됨
    stk->top = s;
    stk->size++;
}

int pop(Stack* stk, char* out)
{
    if (stk->top == NULL)
    {
        return 0;
    }
    Node* ptr = stk->top;
    *out = ptr->data;
    stk->top = stk->top->next;
    free(ptr);
    stk->size--;
    return 1;
}
