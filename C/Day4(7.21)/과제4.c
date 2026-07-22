#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 날짜(년,월,일)를 표현하는 구조체
typedef struct {
    int year; 
    int month; 
    int day;   
} Date;

// 시각(시,분,초)을 표현하는 구조체
typedef struct {
    int hour;   
    int minute;  
    int second;
} Time;

// Date와 Time을 멤버로 갖는 중첩 구조체
typedef struct {
    Date date; // 날짜 정보 
    Time time; // 시각 정보
} Timestamp;

// 윤년인지 판별하는 함수 (4의 배수이면서 100의 배수가 아니거나, 400의 배수이면 윤년)
int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 해당 연도, 월의 일수를 반환하는 함수
int daysInMonth(int year, int month) {
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // 월별 기본 일수
    if (month == 2 && isLeapYear(year)) return 29; // 2월이면서 윤년이면 29일
    return days[month - 1]; // month -1 을 해줘야 2 을 입력하면 두번째 자리 수가 나옴
}

// 1년 1월 1일부터 해당 날짜까지의 누적 총 일수를 계산하는 함수
long totalDays(Date d) {
    long days = 0; // 누적 일수를 저장할 변수 초기화

    for (int y = 1; y < d.year; y++) {           // 1년부터 (해당 연도-1)까지 반복하며
        days += isLeapYear(y) ? 366 : 366 - 1;    // 윤년이면 366일, 아니면 365일을 누적
    }

    for (int m = 1; m < d.month; m++) {           // 1월부터 (해당 월-1)까지 반복하며
        days += daysInMonth(d.year, m);           // 각 달의 일수를 누적
    }

    days += d.day; // 마지막으로 해당 월의 '일'수 만큼 더함

    return days; // 누적된 총 일수 반환
}

// "기준점부터의 총 초"로 변환하는 함수
long totalSeconds(Timestamp t) {
    long days = totalDays(t.date);                              // 날짜를 총 일수로 변환
    long seconds = days * 86400L                                // 일수를 초로 환산 (하루=86400초)
        + t.time.hour * 3600L       // 1시간은 3600초                // 시를 초로 환산
        + t.time.minute * 60L          // 1분은 60초                 // 분을 초로 환산
        + t.time.second;                                // 초는 그대로 더함
    return seconds; // 총 초 값 반환
}

int main() {
    Timestamp info[2]; // 2개의 날짜/시각을 저장할 중첩 구조체 배열 (동적 할당 대신 배열 사용)

    printf("입력 : "); // 입력 안내 문구 출력
    for (int i = 0; i < 2; i++) { // 2개의 타임스탬프를 입력받기 위한 반복문
        scanf("%d %d %d %d %d %d",           // 연 월 일 시 분 초 순서로 6개의 정수 입력
            &info[i].date.year,              // 연도 저장
            &info[i].date.month,             // 월 저장
            &info[i].date.day,               // 일 저장
            &info[i].time.hour,              // 시 저장
            &info[i].time.minute,            // 분 저장
            &info[i].time.second);           // 초 저장
    }

    long sec1 = totalSeconds(info[0]); // 첫 번째 날짜/시각을 총 초로 변환
    long sec2 = totalSeconds(info[1]); // 두 번째 날짜/시각을 총 초로 변환

    long diff = sec2 - sec1; // 두 총 초의 차이 계산 (두번째 - 첫번째)
    if (diff < 0) diff = -diff; // 만약 음수라면 절댓값으로 변환 (항상 양수 출력)

    long hour = diff / 3600;         // 전체 초를 3600으로 나눈 몫 = 시
    long minute = (diff % 3600) / 60; // 시를 제외한 나머지를 60으로 나눈 몫 = 분
    long second = diff % 60;          // 60으로 나눈 나머지 = 초

    printf("출력 : %ld시 %ld분 %ld초\n", hour, minute, second); // 최종 결과 출력

    return 0; // 프로그램 정상 종료
}
