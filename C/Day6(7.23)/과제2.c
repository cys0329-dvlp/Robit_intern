#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct _Node //Node 구조체 선언
{
    int data;
    struct _Node* next;
}Node;

typedef struct _Stack //Stack 구조체 선언
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
    Stack stack = { NULL, 0 }; //처음은 NULL값, 크기 0으로 시작
    Stack* stk = &stack;
    while (1)
    {
        printf("==명령어를 입력하시오== exit(프로그램 종료)\n");
        int n = 1;
        int d;
        char oder[30];
        scanf("%s", &oder);

        //입력한 문자열이 명령어와 똑같을 때 함수 실행
        if (string_compare(oder, "push") == 0)
        {
            scanf("%d", &d); //명령어 중에 push만 뒤에 숫자를 붙여주기 때문에 push만 따로 scanf 한번 더 해줬습니다
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
    while (a[i] != '\0' || b[i] != '\0') //a혹은 b배열 둘 중에 하나라도 공백이 생기면 종료
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
int push(Stack* stk, int n)
{
    Node* s = (Node*)malloc(sizeof(Node));
    s->next = stk->top; //현재 top의 주소를 next 포인터에 할당
    stk->top = s; //top 주소 갱신
    s->data = n; //data에 원하는 숫자 할당
    stk->size++; //사이즈 1 증가
}

int pop(Stack* stk)
{
    if (stk->size == 0)
    {
        printf("Queue가 비어있습니다.\n");
    }
    else
    {
        //ptr이라는 포인터 새로 선언해서 ptr에 top값 저장해주고 ptr 메모리 해제
        // 전 node에 top값 저장
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
        printf("--Stack 안의 값--\n"); // for문이 돌면 p = p->next로 다음 값 연속해서 출력
        for (Node* p = stk->top;p != NULL;p = (p->next)) {
            printf("%d ", p->data);
            printf("\n");
        }
    }
}
