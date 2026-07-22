#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>   //printf, scanf 쓰려고 포함
#include <stdlib.h>  //malloc, free 쓰려고 포함

//구조체 선언
//Node는 연결리스트를 이루는 하나하나의 칸이라고 생각하면 됨
typedef struct Node
{
    int data;          //실제 저장할 값 (자료형은 자유라고 해서 그냥 int로 함)
    struct Node* next; //다음 노드의 주소를 저장하는 포인터. 자기자신 구조체를 가리키는거라 struct Node로 써야함
} node;

//연결리스트 전체를 관리하는 구조체
//head, tail을 따로 들고있으면 맨앞/맨뒤 작업할 때 처음부터 안뒤져도 돼서 빠름
typedef struct LinkedList
{
    node* head; //첫번째 노드 주소
    node* tail; //마지막 노드 주소
    int size;   //지금 노드가 몇개 들어있는지
} linkedlist;

//리스트 쓰기 전에 초기화하는 함수. 안하면 head,tail이 쓰레기값이라 무조건 먼저 해줘야함
void init_list(linkedlist* list)
{
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

//새 노드 만들어서 반환해주는 함수. 밑에 함수들에서 계속 재사용할거라 따로 뺌
node* create_node(int data)
{
    node* new_node = (node*)malloc(sizeof(node)); //노드 하나 크기만큼 동적할당
    new_node->data = data; //받은 값 저장
    new_node->next = NULL; //일단 다음은 없다고 해놓고 나중에 연결부분에서 다시 이어줌
    return new_node;
}

//리스트 맨 앞에 노드 추가
void insert_first(linkedlist* list, int data)
{
    node* new_node = create_node(data);

    if (list->head == NULL) //리스트가 텅 비어있는 경우
    {
        list->head = new_node; //노드가 하나뿐이니까 head랑 tail이 같은 노드를 가리켜야함
        list->tail = new_node;
    }
    else //이미 노드가 하나라도 있는 경우
    {
        new_node->next = list->head; //새 노드가 원래 head를 가리키게 먼저 연결하고
        list->head = new_node; //그 다음에 head를 새 노드로 바꿔줘야 연결이 안끊김
    }

    list->size++; //노드 하나 늘었으니까 사이즈도 1 증가
}

//리스트 맨 뒤에 노드 추가
void insert_back(linkedlist* list, int data)
{
    node* new_node = create_node(data);

    if (list->head == NULL) //비어있으면 첫 삽입이랑 똑같은 상황
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        list->tail->next = new_node; //기존 마지막 노드가 새 노드를 가리키게 연결
        list->tail = new_node; //tail을 새 노드로 갱신해줘야 다음번에 또 뒤에 붙일 수 있음
    }

    list->size++;
}

//index 위치에 삽입하는 함수 (기존에 그 index에 있던 노드 "앞"에 새 노드가 들어가는 방식)
//index가 0이면 맨앞, size랑 같으면 맨뒤라서 그 경우는 위에 만든 함수 그대로 재사용함
void insert_by_index(linkedlist* list, int index, int data)
{
    if (index <= 0)
    {
        insert_first(list, data);
        return; //여기서 끝내야 아래 코드까지 안내려감
    }

    if (index >= list->size)
    {
        insert_back(list, data);
        return;
    }

    node* prev = list->head; //index 바로 앞 노드를 찾아야 그 사이에 새 노드를 끼울 수 있음
    for (int i = 0; i < index - 1; i++) //head에서부터 (index-1)번 이동하면 prev가 정확히 그 앞칸에 위치함
    {
        prev = prev->next;
    }

    node* new_node = create_node(data);
    new_node->next = prev->next; //새 노드가 원래 그 자리에 있던 노드를 가리키게 먼저 연결하고
    prev->next = new_node; //그 다음에 prev가 새 노드를 가리키게 바꿔야 순서가 안꼬임

    list->size++;
}

//target_data를 가진 노드 "뒤"에 새로운 값을 삽입하는 함수
void insert_by_data(linkedlist* list, int target_data, int new_data)
{
    node* cur = list->head; //처음부터 하나씩 훑어야하니까 커서용 포인터 하나 둠

    while (cur != NULL) //끝(NULL)까지 다 돌아봄
    {
        if (cur->data == target_data) //원하는 데이터를 찾았을 때
        {
            node* new_node = create_node(new_data);
            new_node->next = cur->next; //새 노드가 cur 다음 노드를 먼저 가리키게 하고
            cur->next = new_node; //cur이 새 노드를 가리키게 이어줌

            if (cur == list->tail) //만약 찾은 노드가 원래 마지막 노드였다면
            {
                list->tail = new_node; //tail도 새 노드로 갱신해줘야 나중에 insert_back 할 때 안꼬임
            }

            list->size++;
            return; //삽입 끝났으니까 여기서 함수 종료
        }
        cur = cur->next; //못찾았으면 한칸 더 이동
    }

    printf("해당 데이터를 찾지 못했습니다\n"); //끝까지 돌았는데도 못찾은 경우
}

//맨 앞 노드 삭제
void delete_first(linkedlist* list)
{
    if (list->head == NULL) return; //비어있으면 지울게 없으니까 그냥 리턴

    node* temp = list->head; //free 하기 전에 주소를 임시로 저장해둬야함 (안하면 free할 대상을 잃어버림)
    list->head = list->head->next; //head를 그 다음 노드로 옮김

    if (list->head == NULL) //옮기고 났더니 리스트가 완전히 비어버린 경우
    {
        list->tail = NULL; //tail도 같이 NULL로 만들어줘야 나중에 삽입할 때 오류 안남
    }

    free(temp); //아까 저장해둔 노드 메모리 해제
    list->size--;
}

//맨 뒤 노드 삭제
void delete_back(linkedlist* list)
{
    if (list->head == NULL) return;

    if (list->head == list->tail) //노드가 딱 하나만 있는 경우는 따로 처리
    {
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->size--;
        return;
    }

    node* cur = list->head; //마지막 바로 전 노드를 찾아야 그 노드의 next를 NULL로 끊을 수 있음
    while (cur->next != list->tail) //cur의 다음이 tail이 되는 순간까지 이동
    {
        cur = cur->next;
    }

    free(list->tail); //진짜 마지막 노드 메모리 해제
    cur->next = NULL; //이제 cur이 새로운 마지막이니까 다음을 NULL로 끊어줘야함
    list->tail = cur; //tail 갱신
    list->size--;
}

//index번째 노드 삭제
void delete_by_index(linkedlist* list, int index)
{
    if (index < 0 || index >= list->size) //범위 벗어나면 애초에 지울 수 있는 index가 아님
    {
        printf("잘못된 index입니다\n");
        return;
    }

    if (index == 0) //맨앞을 지우는거면 위에 만든 함수 그대로 재사용
    {
        delete_first(list);
        return;
    }

    node* prev = list->head; //지울 노드의 바로 앞 노드를 찾아야함
    for (int i = 0; i < index - 1; i++) //head에서 (index-1)번 이동하면 딱 그 앞칸에 위치
    {
        prev = prev->next;
    }

    node* target = prev->next; //진짜로 지울 노드
    prev->next = target->next; //prev가 target을 건너뛰고 그 다음걸 가리키게 연결부터 바꿔놓고

    if (target == list->tail) //지운 노드가 원래 마지막이었으면
    {
        list->tail = prev; //tail을 prev로 갱신
    }

    free(target); //그 다음에 메모리 해제 (연결 먼저 안바꾸고 free부터 하면 다음 노드로 못감)
    list->size--;
}

//data값을 가진 첫번째 노드 삭제
void delete_by_data(linkedlist* list, int data)
{
    node* prev = NULL;      //지울 노드의 앞 노드. 맨앞이 지워질수도 있어서 처음엔 NULL로 둠
    node* cur = list->head;

    while (cur != NULL)
    {
        if (cur->data == data) //찾았을 때
        {
            if (prev == NULL) //prev가 NULL이라는건 cur이 head라는 뜻
            {
                delete_first(list); //그러면 delete_first 함수 그대로 씀
            }
            else
            {
                prev->next = cur->next; //prev가 cur을 건너뛰게 연결
                if (cur == list->tail) //cur이 마지막 노드였으면
                {
                    list->tail = prev; //tail 갱신
                }
                free(cur);
                list->size--;
            }
            return; //하나 지웠으면 바로 종료 (중복 데이터가 있어도 첫번째껏만 지움)
        }
        prev = cur; //못찾았으면 prev, cur 둘다 한칸씩 이동
        cur = cur->next;
    }

    printf("해당 데이터를 찾지 못했습니다\n");
}

//index로 찾을 시 data 반환
int get_entry_by_index(linkedlist* list, int index)
{
    if (index < 0 || index >= list->size)
    {
        printf("잘못된 index입니다\n");
        return -1; //잘못됐다는 표시로 -1 반환 (정상적인 데이터랑 헷갈리지 않게 에러표시용)
    }

    node* cur = list->head;
    for (int i = 0; i < index; i++) //head에서 index번 이동하면 그 자리에 도착함
    {
        cur = cur->next;
    }

    return cur->data;
}

//data로 찾을 시 index 반환
int get_entry_by_data(linkedlist* list, int data)
{
    node* cur = list->head;
    int index = 0; //몇번째 칸인지 세는 카운터

    while (cur != NULL)
    {
        if (cur->data == data)
        {
            return index; //찾은 순간의 index 값이 바로 정답
        }
        cur = cur->next;
        index++; //못찾았으면 한칸 이동했으니까 index도 같이 1 증가시켜야 정확함
    }

    return -1; //끝까지 못찾은 경우
}

//리스트 전체 길이 반환
int get_length(linkedlist* list)
{
    return list->size; //따로 세지 않고 미리 저장해둔 size 값을 바로 반환하면 됨
}

//리스트 안에 있는 값 순서대로 출력
void print_list(linkedlist* list)
{
    node* cur = list->head;

    printf("리스트: ");
    while (cur != NULL)
    {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

//리스트 순서를 거꾸로 뒤집는 함수
//포인터 3개(prev, cur, next)를 같이 옮겨가면서 화살표 방향을 하나씩 반대로 바꿔주는 방식
void reverse(linkedlist* list)
{
    node* prev = NULL;
    node* cur = list->head;
    node* next = NULL; //cur->next를 먼저 저장 안해두면 방향 바꾸는 순간 다음 노드로 못넘어감

    list->tail = list->head; //다 뒤집고나면 원래 head였던게 새로운 tail이 됨

    while (cur != NULL)
    {
        next = cur->next;  //방향 바꾸기 전에 다음 노드 주소부터 미리 챙겨놓음
        cur->next = prev;  //화살표를 반대로 돌림 (원래 앞을 가리키게)
        prev = cur;         //prev를 한칸 전진
        cur = next;         //cur도 한칸 전진 (아까 저장해둔 next 사용)
    }

    list->head = prev; //반복 끝나면 prev가 마지막으로 가리키고 있는 노드가 새로운 head
}

//메뉴를 출력해주는 함수. 매번 반복문 돌 때마다 이걸 보여줘야 뭘 눌러야할지 알 수 있음
void print_menu()
{
    printf("\n----------메뉴----------\n");
    printf("1. 맨앞에 삽입 (insert_first)\n");
    printf("2. 맨뒤에 삽입 (insert_back)\n");
    printf("3. index 위치에 삽입 (insert_by_index)\n");
    printf("4. 특정 data 뒤에 삽입 (insert_by_data)\n");
    printf("5. 맨앞 삭제 (delete_first)\n");
    printf("6. 맨뒤 삭제 (delete_back)\n");
    printf("7. index로 삭제 (delete_by_index)\n");
    printf("8. data로 삭제 (delete_by_data)\n");
    printf("9. index로 값 찾기 (get_entry_by_index)\n");
    printf("10. data로 index 찾기 (get_entry_by_data)\n");
    printf("11. 리스트 길이 확인 (get_length)\n");
    printf("12. 리스트 전체 출력 (print_list)\n");
    printf("13. 리스트 뒤집기 (reverse)\n");
    printf("0. 종료\n");
    printf("------------------------\n");
    printf("명령어 입력 : ");
}

int main()
{
    linkedlist mylist;   //연결리스트 변수 선언
    init_list(&mylist);  //쓰기 전에 무조건 초기화부터

    int cmd;             //사용자가 고를 메뉴 번호
    int input1, input2;  //명령어에 따라 추가로 필요한 값들 (index나 data)

    while (1) //0을 입력할때까지 계속 메뉴가 반복되도록 무한루프로 돌림
    {
        print_menu();
        scanf("%d", &cmd); //메뉴 번호부터 입력받음

        if (cmd == 0) //0이면 반복문 탈출해서 프로그램 종료
        {
            break;
        }
        else if (cmd == 1) //맨앞에 삽입
        {
            printf("삽입할 데이터 입력 : ");
            scanf("%d", &input1);
            insert_first(&mylist, input1);
        }
        else if (cmd == 2) //맨뒤에 삽입
        {
            printf("삽입할 데이터 입력 : ");
            scanf("%d", &input1);
            insert_back(&mylist, input1);
        }
        else if (cmd == 3) //index 위치에 삽입 (index랑 data 둘다 입력받아야함)
        {
            printf("삽입할 index 입력 : ");
            scanf("%d", &input1);
            printf("삽입할 데이터 입력 : ");
            scanf("%d", &input2);
            insert_by_index(&mylist, input1, input2);
        }
        else if (cmd == 4) //특정 data 뒤에 삽입 (기준 data랑 새로 넣을 data 둘다 필요)
        {
            printf("기준이 될 data 입력 : ");
            scanf("%d", &input1);
            printf("새로 삽입할 데이터 입력 : ");
            scanf("%d", &input2);
            insert_by_data(&mylist, input1, input2);
        }
        else if (cmd == 5) //맨앞 삭제. 값을 새로 입력받을 필요없이 바로 함수 실행하면 됨
        {
            delete_first(&mylist);
        }
        else if (cmd == 6) //맨뒤 삭제
        {
            delete_back(&mylist);
        }
        else if (cmd == 7) //index로 삭제
        {
            printf("삭제할 index 입력 : ");
            scanf("%d", &input1);
            delete_by_index(&mylist, input1);
        }
        else if (cmd == 8) //data로 삭제
        {
            printf("삭제할 data 입력 : ");
            scanf("%d", &input1);
            delete_by_data(&mylist, input1);
        }
        else if (cmd == 9) //index로 값 찾기
        {
            printf("찾을 index 입력 : ");
            scanf("%d", &input1);
            printf("결과 : %d\n", get_entry_by_index(&mylist, input1));
        }
        else if (cmd == 10) //data로 index 찾기
        {
            printf("찾을 data 입력 : ");
            scanf("%d", &input1);
            printf("결과 : %d\n", get_entry_by_data(&mylist, input1));
        }
        else if (cmd == 11) //길이 확인
        {
            printf("리스트 길이 : %d\n", get_length(&mylist));
        }
        else if (cmd == 12) //전체 출력
        {
            print_list(&mylist);
        }
        else if (cmd == 13) //뒤집기
        {
            reverse(&mylist);
            printf("리스트를 뒤집었습니다.\n");
        }
        else //0~13 사이가 아닌 이상한 값을 입력한 경우
        {
            printf("잘못된 명령어입니다. 다시 입력해주세요.\n");
        }
    }

    //프로그램 끝내기 전에 아직 리스트에 남아있는 노드들을 다 지워줘야함
    //안그러면 마지막에 malloc으로 잡아둔 메모리가 free 안된 채로 프로그램이 끝나버림
    while (mylist.head != NULL)
    {
        delete_first(&mylist);
    }

    return 0;
}
