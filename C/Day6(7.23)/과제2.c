#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct _Node
{
    int data;
    struct _Node* next;
}Node;

typedef struct _Stack
{
    Node* top;
    int size;
}Stack;

int push(Stack* stk, int n);
int pop(Stack* stk);
int size(Stack* stk);
int top(Stack* stk);
int isEmpty(Stack* stk);
int printStack(Stack* stk);

int main()
{
    Stack stack = { NULL, 0 };
    Stack* stk = &stack;
    while (1)
    {
        printf("==명령어를 입력하시오== exit(프로그램 종료)\n");
        int n = 1;
        int d;
        char oder[30];
        scanf("%s", &oder);


        if (string_compare(oder, "push") == 0)
        {
            scanf("%d", &d);
            push(stk, d);
        }
        else if (string_compare(oder, "pop") == 0)
        {
            pop(stk);
        }
        else if (string_compare(oder, "size") == 0)
        {
            size(stk);
        }
        else if (string_compare(oder, "top") == 0)
        {
            top(stk);
        }
        else if (string_compare(oder, "isEmpty") == 0)
        {
            isEmpty(stk);
        }
        else if (string_compare(oder, "printStack") == 0)
        {
            printStack(stk);
        }
        else if (string_compare(oder, "exit") == 0)
        {
            break;
        }
        else {
            printf("잘못된 명령어입니다.");
        }
    }
    return 0;
}
int string_compare(char a[], char b[])
{
    int i = 0;
    while (a[i] != '\0' || b[i] != '\0')
    {
        if (a[i] > b[i])
        {
            return -1;
        }
        else if (a[i] < b[i])
        {
            return 1;
        }


        i++;
    }
    return 0;
}
int push(Stack* stk, int n)
{
    Node* s = (Node*)malloc(sizeof(Node));
    s->next = stk->top;
    stk->top = s;
    s->data = n;
    stk->size++;
}

int pop(Stack* stk)
{
    if (stk->size == 0)
    {
        printf("Queue가 비어있습니다.\n");
    }
    else
    {
        Node* ptr = stk->top;
        stk->top = stk->top->next;
        printf("삭제된 값: %d\n", ptr->data);
        free(ptr);
        stk->size--;
    }
}

int size(Stack* stk)
{
    int a = stk->size;
    printf("stack의 size: %d\n", a);
    return a;
}

int top(Stack* stk)
{
    int b = stk->top->data;
    printf("%d\n", b);
    return b;
}

int isEmpty(Stack* stk)
{
    if (stk->size == 0)
    {
        printf("True\n");
    }
    else
    {
        printf("False\n");
    }
}

int printStack(Stack* stk)
{
    if (stk->size == 0)
    {
        printf("Stack이 비어있습니다.\n");
    }
    else
    {
        printf("--Stack 안의 값--\n");
        for (Node* p = stk->top;p != NULL;p = (p->next)) {
            printf("%d ", p->data);
            printf("\n");
        }
    }
}
