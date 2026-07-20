#include <stdio.h>

int main() 
{
    
    float num1, num2; 
    char op; //연산자
    float result = 1;

    printf("---calculator---\n");
    printf("ex) 3.4 + 1.4\n    5.3 - 2.3\n    5.4 * 7.1\n    3.4 ^ 4.1\n\n"); //예시 입력
    printf("input: ");
    scanf_s("%f %c %f", &num1, &op,1, &num2); 
    //microsoft visual studio에서 문자를 입력받으려면 바이트 크기 1이 반드시 들어가야합니다. 
    //혹시 컴파일 오류가 난다면 scanf_s("%f %c %f", &num1, &op, &num2); 로 다시 컴파일 부탁드립니다. 

    if (op == '+')
    {
        printf("\n%f + %f = %f",num1, num2, num1 + num2);
    }
    else if (op == '-')
    {
        printf("\n%f - %f = %f", num1, num2, num1 - num2);
    }
    else if (op == '*')
    {
        printf("\n%f * %f = %f", num1, num2, num1 * num2);
    }
    else if (op == '^')
    {   
        for (int i = 0; i < num2; i++)
        {
            result = result * num1;
        }
        printf("\n%f ^ %f = %f", num1, num2, result);
    }
    else
    {
        printf("잘못된 연산자입니다.");
    }
    
    
    
  
      return 0;
    

}
