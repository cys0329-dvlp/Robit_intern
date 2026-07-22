#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n = 2;
    //동적 메모리 할당
    char* sentence = (char*)malloc(sizeof(char));
    int asci[128]; //아스키코드는 총 127개이고 입력된 문자의 개수를 세는 방법은 해당하는 아스키코드의 값의 -1한 값의 인덱스에 +1해주는 것


    for(int i = 1; i < n; i++) //realloc으로 문자를 입력할 때마다 메모리 공간을 1씩 추가시킴 -> 메모리 최대한 절약
    {
        scanf("%c", &sentence[i - 1]);
        sentence = (char*)realloc(sentence, sizeof(char) * (i+1));
        n++;
        if (sentence[i - 1] == '\n')
        {
            break;
        }
    }
    printf("\n--출력--\n");

    for (int j = n-3; j >= 0; j--)
    {
        printf("%c", sentence[j]);
    }

    printf("\n");
    //문자 개수 세는 것
    
    for (int i = 0; i < n; i++) 
    {
        char ch = sentence[i]; //문자 ch를 int형 정수에 저장하면 아스키코드 값으로 저장이 됨
        int index = ch; //index는 현재 ch 문자의 아스키코스 값을 나타내는 정수
        asci[index]++; //해당하는 아스키코드값의 배열의 값을 +1해줌 -> 계속 반복 -> 결국 숫자가 가장 큰 부분의 인덱스와 동일한 아스키 코드를 가진 문자가 가장 많이 출력된 것.
    }

    int max = asci[0];
    int index_1;
    for (int i = 33; i < 128;i++) //띄어쓰기 아스키코드 값이 32이므로 33부터 for문 돌려서 띄어쓰기는 개수 세는 데에 포함되지 않도록함
    {
        if (asci[i] > max)
        {
            max = asci[i];
            index_1 = i; //가장 많이 출력된 문자의 인덱스 값 따로 저장
        }
    }

    printf("가장 많이 입력된 문자는 %c입니다.", index_1); //정수형 인덱스를 %c로 출력하므로써 아스키코드 값에 해당하는 문자가 출력됨. 
    return 0;
}
