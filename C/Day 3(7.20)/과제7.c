#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char input[1000]; // 입력받을 문자열
    char** stack;      // 태그 이름을 저장할 스택 (동적할당)
    int top = -1;       // 스택 맨 위 위치 (비어있으면 -1)
    int depth = 0;       // 들여쓰기 깊이
    int len = 0;
    int i;

    printf("HTML 태그 입력: ");
    scanf("%s", input); // 공백 없이 문자열 하나로 입력받기

    while (input[len] != '\0') len++; // 문자열 길이 구하기

    // 태그는 최대 len개까지 열릴 수 있으므로 그만큼 스택 공간을 동적할당
    stack = (char**)malloc(sizeof(char*) * len);
    for (i = 0; i < len; i++)
    {
        stack[i] = (char*)malloc(sizeof(char) * 30); // 태그 이름은 30글자로 제한
    }

    i = 0;
    while (i < len)
    {
        if (input[i] == '<') // 태그 시작
        {
            int j = i + 1;
            while (input[j] != '>') j++; // '>' 나올 때까지 이동

            int isClose = 0;       // 닫는 태그인지 표시
            int start = i + 1;
            if (input[start] == '/') // '/' 로 시작하면 닫는 태그
            {
                isClose = 1;
                start++;
            }

            // '<' 와 '>' 사이에서 태그 이름만 뽑기
            char tagName[30];
            int k = 0;
            int p;
            for (p = start; p < j; p++)
            {
                tagName[k] = input[p];
                k++;
            }
            tagName[k] = '\0';

            if (isClose == 0) // ---- 여는 태그 ----
            {
                int t;
                for (t = 0; t < depth; t++) printf("  "); // 들여쓰기
                printf("<%s>\n", tagName);

                top++; // push
                int c;
                for (c = 0; c <= k; c++)
                    stack[top][c] = tagName[c];

                depth++;
            }
            else // ---- 닫는 태그 ----
            {
                if (top < 0) // 여는 태그 없이 닫는 태그가 나온 경우
                {
                    printf("오류: 태그 구조가 잘못되었습니다.\n");
                    return 0;
                }

                // 스택 맨 위 태그 이름과 지금 태그 이름이 같은지 비교
                int same = 1;
                int c = 0;
                while (stack[top][c] != '\0' || tagName[c] != '\0')
                {
                    if (stack[top][c] != tagName[c])
                    {
                        same = 0;
                        break;
                    }
                    c++;
                }

                if (same == 0) // 짝이 안 맞는 경우
                {
                    printf("오류: 태그 구조가 잘못되었습니다.\n");
                    return 0;
                }

                top--;   // pop
                depth--;
                int t;
                for (t = 0; t < depth; t++) printf("  ");
                printf("</%s>\n", tagName);
            }

            i = j + 1; // '>' 다음으로 이동
        }
        else // 태그가 아니면 그냥 내용(텍스트)
        {
            int start = i;
            while (i < len && input[i] != '<') i++;

            int t;
            for (t = 0; t < depth; t++) printf("  ");
            for (t = start; t < i; t++) printf("%c", input[t]);
            printf("\n");
        }
    }

    if (top != -1) // 다 읽었는데 아직 안 닫힌 태그가 남아있으면
    {
        printf("오류: 태그 구조가 잘못되었습니다.\n");
    }

    for (i = 0; i < len; i++) // 동적할당 해제
        free(stack[i]);
    free(stack);

    return 0;
}
