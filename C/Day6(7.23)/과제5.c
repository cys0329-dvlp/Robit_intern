#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 주소 구조체 (나라, 도, 시, 구)
// 학생 한 명당 주소를 4단계(나라/도/시/구)로 나눠서 저장한다.
// 각 필드를 독립된 char 배열로 두면, 정렬/검색 시 "주소 중 어떤 단계"를
// 기준으로 삼을지(country/province/city/district) 따로따로 지정할 수 있다.
typedef struct {
	char country[30];	//나라
	char province[30];	//도
	char city[30];		//시
	char district[30];	//구
} Address;

// 학생 구조체
// num: 학번, name: 이름, addr: 주소(Address 구조체를 그대로 포함),
// score: 성적. 구조체 안에 구조체를 넣는 "중첩 구조체" 형태로 설계했다.
typedef struct {
	int num;			//번호
	char name[20];		//이름
	Address addr;		//주소
	double score;		//성적
} Student;

// ---------- 함수 선언(프로토타입) ----------
// main보다 아래쪽에 실제 구현이 있으므로, 컴파일러가 미리 함수의
// 존재와 시그니처를 알 수 있도록 위에서 먼저 선언해둔다.

int my_strcmp(const char* s1, const char* s2);
void clear_stdin(void);
int get_int(const char* msg);
double get_double(const char* msg);
void get_str(const char* msg, char* buf, int len);

int check_key(const char* key);
int cmp_key(Student a, Student b, const char* key);
void sort_arr(Student* arr, int n, const char* key);
void print_arr(Student* arr, int n);

void do_sort(Student* arr, int n);
void do_search(Student* arr, int n);
void do_add(Student** arr, int* n, int* cap);      // 배열이 커질 수 있어 이중포인터로 받음
void do_delete(Student** arr, int* n);
void do_addel(Student** arr, int* n, int* cap);
void do_save(Student* arr, int n);
void do_load(Student** arr, int* n, int* cap);      // realloc/malloc으로 배열을 통째로 교체하므로 이중포인터 필요
void do_saveload(Student** arr, int* n, int* cap);


int main(void) {
	// arr: 학생들을 담을 동적 배열의 시작 주소. 아직 학생이 없으므로 NULL.
	// size: 현재 등록된 학생 수(실제 사용 중인 원소 개수)
	// cap : malloc/realloc으로 확보해둔 "그릇의 크기"(용량). size <= cap 관계를 항상 유지.
	Student* arr = NULL;	// 학생이 처음엔 없으니까 NULL로 시작
	int size = 0;
	int cap = 0;
	int mode;

	printf("=== 출석부 프로그램 ===\n");
	printf("1 : 정렬 (기준 = number/name/country/province/city/district/grade)\n");
	printf("2 : 검색\n");
	printf("3 : add/delete - 학생 추가/삭제\n");
	printf("4 : save/load - 저장/불러오기\n");
	printf("0 : 종료\n\n");

	// 프로그램이 종료 명령(0)을 받을 때까지 계속 메뉴를 반복해서 보여준다.
	while (1) {
		mode = get_int("명령 입력 (0~4): ");

		switch (mode) {
		case 0:
			printf("프로그램을 종료합니다.\n");
			free(arr);	// malloc/realloc으로 할당했던 메모리를 반드시 해제
			return 0;
		case 1:
			// 정렬은 배열 내용을 "재배치"만 할 뿐 개수(size)가 바뀌지 않으므로
			// arr, size를 값으로만 넘겨도 충분하다(포인터 자체는 값 복사되지만
			// 그 포인터가 가리키는 배열 내용은 함수 안에서 수정 가능).
			do_sort(arr, size);
			break;
		case 2:
			// 검색도 배열을 읽기만 하고 바꾸지 않으므로 값으로 전달.
			do_search(arr, size);
			break;
		case 3:
			// add/delete는 배열의 크기(size)나 용량(cap), 혹은 arr 자체의 주소(realloc으로
			// 메모리 블록이 통째로 바뀔 수 있음)가 바뀔 수 있어서 반드시 주소(&)로 넘겨야
			// 호출한 쪽(main)의 변수도 함께 갱신된다.
			do_addel(&arr, &size, &cap);	// 배열이 커질 수 있어서 주소로 넘김
			break;
		case 4:
			// save/load도 load 시 배열을 통째로 교체하므로 마찬가지로 주소 전달.
			do_saveload(&arr, &size, &cap);
			break;
		default:
			printf("잘못된 명령입니다. 0~4 사이 숫자만 입력하세요.\n");
		}
	}

	// while(1)이 case 0에서 return으로 빠지기 때문에 이 아래 코드는 실행되지
	// 않지만, 혹시 모를 상황을 대비해 방어적으로 남겨둔 코드다.
	free(arr);
	return 0;
}

// 문자열 비교 함수 직접 구현 (s1이 크면 1, 같으면 0, 작으면 -1)
// 표준 라이브러리의 strcmp와 동일한 동작을 과제 요구사항(직접 구현)에 맞춰 작성.
// 한 글자씩(index i) 비교하다가 서로 다른 문자를 만나거나 둘 중 하나라도
// 문자열의 끝('\0')에 도달하면 비교를 멈춘다.
int my_strcmp(const char* s1, const char* s2) {
	int i = 0;
	while (s1[i] != '\0' && s2[i] != '\0') {
		if (s1[i] > s2[i]) return 1;
		if (s1[i] < s2[i]) return -1;
		i++;
	}
	// 여기까지 왔다는 건 둘 중 적어도 하나가 끝났다는 뜻.
	// 둘 다 동시에 끝났으면(길이도 같고 내용도 같음) 완전히 동일한 문자열.
	if (s1[i] == '\0' && s2[i] == '\0') return 0;
	// 한쪽만 끝났다면, 먼저 끝난(더 짧은) 쪽이 사전순으로 앞선다고 취급.
	return (s1[i] == '\0') ? -1 : 1;
}

// scanf 잘못 들어왔을 때 그 줄에 남은거 다 버리는 함수
// 예를 들어 정수를 요구했는데 "abc\n"가 들어오면 scanf("%d", ...)는 실패하고
// 입력 버퍼에는 "abc\n"이 그대로 남는다. 이걸 안 지우면 다음 입력에서도
// 계속 같은 값이 읽혀서 무한 오류 루프에 빠지므로, 줄바꿈이나 파일 끝(EOF)을
// 만날 때까지 한 글자씩 읽어서 버려준다.
void clear_stdin(void) {
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		;
}

// 정수 입력 (숫자 아니면 계속 다시 물어봄)
// "모든 항목 예외처리" 요구사항 중 숫자 입력 항목(번호, 메뉴 선택 등)을
// 담당하는 함수. scanf가 정수를 정상적으로 읽지 못하면(반환값 != 1)
// 잘못된 입력이므로 버퍼를 비우고 다시 물어보는 식으로 무한 재시도한다.
int get_int(const char* msg) {
	int val;
	while (1) {
		printf("%s", msg);
		if (scanf("%d", &val) != 1) {
			printf("잘못된 입력입니다. 숫자만 입력해주세요.\n");
			clear_stdin();
			continue;
		}
		clear_stdin();	// 정상 입력이어도 줄 끝에 남은 개행 등을 정리
		return val;
	}
}

// 실수 입력 (숫자 아니면 계속 다시 물어봄)
// 성적(score)처럼 소수점이 필요한 값을 입력받을 때 사용. 동작 방식은
// get_int와 동일하고, %d 대신 %lf(double)로 파싱한다는 점만 다르다.
double get_double(const char* msg) {
	double val;
	while (1) {
		printf("%s", msg);
		if (scanf("%lf", &val) != 1) {
			printf("잘못된 입력입니다. 숫자만 입력해주세요.\n");
			clear_stdin();
			continue;
		}
		clear_stdin();
		return val;
	}
}

// 문자열 입력 (len 크기에 맞춰서 길이제한 걸어줌)
// buf의 실제 크기(len)를 넘겨받아서, "%9s"처럼 최대로 읽을 글자 수를
// 동적으로 만들어(sprintf로 서식 문자열 fmt를 조립) scanf에 사용한다.
// 이렇게 하면 이름/나라/도/시/구 등 배열 크기가 서로 달라도 각각의
// 버퍼를 넘치게 쓰는 일(버퍼 오버플로우)을 막을 수 있다.
void get_str(const char* msg, char* buf, int len) {
	char fmt[16];
	printf("%s", msg);
	sprintf(fmt, "%%%ds", len - 1);	// 예: len=20이면 "%19s" 생성 (마지막 1자리는 '\0' 몫)
	scanf(fmt, buf);
	clear_stdin();	// scanf("%s", ...)는 공백에서 멈추므로, 남은 줄 내용은 버려준다
}

// 정렬/검색 기준으로 쓸 수 있는 문자열인지 체크
// 사용자가 정렬/검색 기준으로 입력한 key가 우리가 지원하는 7가지
// (number/name/country/province/city/district/grade) 중 하나인지 검사한다.
// "모든 항목 예외처리" 요구사항 중 문자열(키) 입력에 대한 검증 담당.
int check_key(const char* key) {
	if (my_strcmp(key, "number") == 0) return 1;
	if (my_strcmp(key, "name") == 0) return 1;
	if (my_strcmp(key, "country") == 0) return 1;
	if (my_strcmp(key, "province") == 0) return 1;
	if (my_strcmp(key, "city") == 0) return 1;
	if (my_strcmp(key, "district") == 0) return 1;
	if (my_strcmp(key, "grade") == 0) return 1;
	return 0;	// 위 7가지 중 아무것도 아니면 잘못된 기준
}

// key 기준으로 학생 a, b 비교 (a가 크면 1, 같으면 0, 작으면 -1)
// 정렬(sort_arr)과, 필요하다면 다른 비교 로직에서도 재사용할 수 있도록
// "어떤 필드를 비교할지"를 key 문자열 하나로 결정하는 구조다.
// 숫자 필드(number, grade)는 부등호로, 문자열 필드는 my_strcmp로 비교한다.
int cmp_key(Student a, Student b, const char* key) {
	if (my_strcmp(key, "number") == 0) {
		if (a.num > b.num) return 1;
		if (a.num < b.num) return -1;
		return 0;
	}
	if (my_strcmp(key, "name") == 0)
		return my_strcmp(a.name, b.name);
	if (my_strcmp(key, "country") == 0)
		return my_strcmp(a.addr.country, b.addr.country);
	if (my_strcmp(key, "province") == 0)
		return my_strcmp(a.addr.province, b.addr.province);
	if (my_strcmp(key, "city") == 0)
		return my_strcmp(a.addr.city, b.addr.city);
	if (my_strcmp(key, "district") == 0)
		return my_strcmp(a.addr.district, b.addr.district);
	if (my_strcmp(key, "grade") == 0) {
		if (a.score > b.score) return 1;
		if (a.score < b.score) return -1;
		return 0;
	}
	return 0;	// check_key로 이미 걸러졌다면 여기 도달할 일은 없음(방어 코드)
}

// key 기준으로 선택정렬
// 선택 정렬(selection sort): 남은 구간 [i, n) 중 가장 작은 원소를 찾아
// 맨 앞(i번째)과 자리를 바꾸는 방식을 n-1번 반복한다. 데이터 수가 많지
// 않은 출석부 특성상 구현이 단순한 선택 정렬로도 충분하다.
void sort_arr(Student* arr, int n, const char* key) {
	int i, j, min_idx;
	Student tmp;

	for (i = 0; i < n - 1; i++) {
		min_idx = i;	// 일단 현재 위치를 "가장 작은 값의 후보"로 둔다
		for (j = i + 1; j < n; j++) {
			// arr[j]가 지금까지 찾은 최소값(arr[min_idx])보다 key 기준으로
			// 더 작다면 최소값 후보를 갱신한다.
			if (cmp_key(arr[j], arr[min_idx], key) < 0)
				min_idx = j;
		}
		if (min_idx != i) {
			// 구조체 통째로 대입(=)하면 num/name/addr/score가 한 번에 복사된다.
			tmp = arr[i];
			arr[i] = arr[min_idx];
			arr[min_idx] = tmp;
		}
	}
}

// 학생 목록 출력
// 배열 전체를 한 줄에 한 명씩, "번호 이름 나라 도 시 구 성적" 순서로 출력한다.
// score는 소수 첫째 자리까지(%.1f) 표시해서 90.500000처럼 지저분하게
// 나오지 않도록 했다.
void print_arr(Student* arr, int n) {
	int i;
	if (n == 0) {
		printf("등록된 학생이 없습니다.\n");
		return;
	}
	for (i = 0; i < n; i++) {
		printf("%d %s %s %s %s %s %.1f\n",
			arr[i].num, arr[i].name,
			arr[i].addr.country, arr[i].addr.province, arr[i].addr.city, arr[i].addr.district,
			arr[i].score);
	}
}

// 1번 메뉴 - 정렬
// 사용자에게 정렬 기준(key)을 물어보고, check_key로 검증한 뒤
// (유효할 때까지 반복 질문) sort_arr로 실제 정렬을 수행하고 결과를 출력한다.
void do_sort(Student* arr, int n) {
	char key[10];

	get_str("정렬 기준 입력 (number/name/country/province/city/district/grade): ", key, sizeof(key));
	while (!check_key(key)) {
		printf("잘못된 기준입니다. 다시 입력하세요.\n");
		get_str("정렬 기준 입력: ", key, sizeof(key));
	}

	// 학생이 한 명도 없으면 정렬할 대상이 없으므로 바로 안내만 하고 종료.
	// (키를 먼저 물어보고 나서 인원수를 확인하는 순서이므로, 학생이 0명이어도
	// 기준 입력은 한 번 받게 된다 — 사용 흐름상 큰 문제는 없지만 참고할 것.)
	if (n == 0) {
		printf("등록된 학생이 없습니다.\n");
		return;
	}

	sort_arr(arr, n, key);
	print_arr(arr, n);
}

// 2번 메뉴 - 검색 (기준+값 입력받아서 조건에 맞는 학생 이름 출력)
// key가 무엇이냐에 따라 비교해야 할 값의 타입이 달라진다.
//  - number  : 정수로 입력받아 int끼리 == 비교
//  - grade   : 실수로 입력받아 double끼리 == 비교
//  - 그 외   : 문자열로 입력받아 my_strcmp로 == 비교
// 조건에 맞는 학생이 여러 명일 수 있으므로 배열 전체를 순회하며 찾는
// 즉시 이름을 출력하고, 마지막에 found 플래그로 "결과 없음"도 안내한다.
void do_search(Student* arr, int n) {
	char key[10];
	int found = 0;
	int i;

	get_str("검색 기준 입력 (number/name/country/province/city/district/grade): ", key, sizeof(key));
	while (!check_key(key)) {
		printf("잘못된 기준입니다. 다시 입력하세요.\n");
		get_str("검색 기준 입력: ", key, sizeof(key));
	}

	if (my_strcmp(key, "number") == 0) {
		int target = get_int("찾을 번호: ");
		for (i = 0; i < n; i++) {
			if (arr[i].num == target) {
				printf("%s\n", arr[i].name);
				found = 1;
			}
		}
	}
	else if (my_strcmp(key, "grade") == 0) {
		// 주의: 실수(double)를 ==로 비교하는 것은 일반적으로 오차 문제가
		// 있을 수 있지만, 여기서는 사용자가 add할 때 입력한 값과 검색할 때
		// 입력한 값을 그대로 비교하는 것이라 실사용에서는 문제가 되지 않는다.
		double target = get_double("찾을 성적: ");
		for (i = 0; i < n; i++) {
			if (arr[i].score == target) {
				printf("%s\n", arr[i].name);
				found = 1;
			}
		}
	}
	else {
		// name/country/province/city/district 다섯 가지 문자열 기준은
		// 로직이 완전히 같고 "어떤 필드를 볼지"만 다르므로, field라는
		// char* 포인터에 해당 필드의 주소를 담아 코드 중복을 줄였다.
		char target[30];
		char* field;
		get_str("찾을 값: ", target, sizeof(target));

		for (i = 0; i < n; i++) {
			if (my_strcmp(key, "name") == 0) field = arr[i].name;
			else if (my_strcmp(key, "country") == 0) field = arr[i].addr.country;
			else if (my_strcmp(key, "province") == 0) field = arr[i].addr.province;
			else if (my_strcmp(key, "city") == 0) field = arr[i].addr.city;
			else field = arr[i].addr.district;	// check_key를 통과했으므로 여기 오면 district가 확실

			if (my_strcmp(field, target) == 0) {
				printf("%s\n", arr[i].name);
				found = 1;
			}
		}
	}

	if (!found)
		printf("해당하는 학생이 없습니다.\n");
}

// 학생 추가
// *arr, *n, *cap을 이중포인터로 받는 이유: realloc이 메모리를 재할당하면
// 배열의 시작 주소 자체가 바뀔 수 있는데, 그 새 주소를 main의 arr 변수에도
// 반영하려면 arr의 "주소"(즉 Student**)를 받아야 한다. n, cap도 마찬가지로
// 함수 밖(main)의 값을 실제로 바꿔야 하므로 포인터로 받는다.
void do_add(Student** arr, int* n, int* cap) {
	Student s;
	int i;

	// 새로 추가할 학생 정보를 항목별로 입력받는다.
	s.num = get_int("번호: ");
	get_str("이름: ", s.name, sizeof(s.name));
	get_str("나라: ", s.addr.country, sizeof(s.addr.country));
	get_str("도: ", s.addr.province, sizeof(s.addr.province));
	get_str("시: ", s.addr.city, sizeof(s.addr.city));
	get_str("구: ", s.addr.district, sizeof(s.addr.district));
	s.score = get_double("성적: ");

	// 모든 항목이 완전히 같은 학생이면 중복 추가 안함
	// (번호, 이름, 주소 4단계, 성적까지 전부 일치해야 "완전히 같은 학생"으로 판단)
	for (i = 0; i < *n; i++) {
		if ((*arr)[i].num == s.num &&
			my_strcmp((*arr)[i].name, s.name) == 0 &&
			my_strcmp((*arr)[i].addr.country, s.addr.country) == 0 &&
			my_strcmp((*arr)[i].addr.province, s.addr.province) == 0 &&
			my_strcmp((*arr)[i].addr.city, s.addr.city) == 0 &&
			my_strcmp((*arr)[i].addr.district, s.addr.district) == 0 &&
			(*arr)[i].score == s.score) {
			printf("이미 존재하는 학생입니다. 추가하지 않습니다.\n");
			return;
		}
	}

	if (*n >= *cap) {	// 자리 부족하면 용량 두배로 확장
		// cap이 0(아직 한 번도 할당 안 함)이면 4칸으로 처음 시작하고,
		// 그 이후로는 현재 용량의 2배씩 늘려서 realloc 호출 횟수를 줄인다
		// (매번 1칸씩 늘리면 학생이 추가될 때마다 메모리 재할당이 일어나 비효율적).
		int new_cap = (*cap == 0) ? 4 : (*cap) * 2;
		Student* tmp = (Student*)realloc(*arr, sizeof(Student) * new_cap);
		if (tmp == NULL) {
			// realloc 실패 시 원래 *arr는 그대로 유효하므로 데이터 손실은 없다.
			// tmp에만 실패 결과(NULL)가 담기고 *arr는 건드리지 않은 것이 핵심.
			printf("메모리 할당에 실패했습니다.\n");
			return;
		}
		*arr = tmp;
		*cap = new_cap;
	}

	(*arr)[*n] = s;	// 구조체 통째로 복사해서 배열의 맨 뒤(빈 자리)에 저장
	(*n)++;
	printf("추가되었습니다. (현재 %d명)\n", *n);
}

// 학생 삭제 (입력한 정보와 완전히 일치하는 학생을 찾아서 지움, 중복이면 골라서 삭제)
void do_delete(Student** arr, int* n) {
	Student s;
	int idx_list[100];	// 조건에 맞는 학생들의 인덱스를 모아두는 배열 (최대 100명까지)
	int cnt = 0;
	int i, del_idx;

	if (*n == 0) {
		printf("등록된 학생이 없습니다.\n");
		return;
	}

	// 삭제 대상을 찾기 위한 기준 정보를 add와 동일한 방식으로 입력받는다.
	s.num = get_int("번호: ");
	get_str("이름: ", s.name, sizeof(s.name));
	get_str("나라: ", s.addr.country, sizeof(s.addr.country));
	get_str("도: ", s.addr.province, sizeof(s.addr.province));
	get_str("시: ", s.addr.city, sizeof(s.addr.city));
	get_str("구: ", s.addr.district, sizeof(s.addr.district));
	s.score = get_double("성적: ");

	// 입력받은 정보와 완전히 일치하는 학생을 전부 찾아서 그 인덱스를 idx_list에 모은다.
	// (cnt < 100 조건은 idx_list 배열 범위를 벗어나지 않도록 하는 안전장치)
	for (i = 0; i < *n && cnt < 100; i++) {
		if ((*arr)[i].num == s.num &&
			my_strcmp((*arr)[i].name, s.name) == 0 &&
			my_strcmp((*arr)[i].addr.country, s.addr.country) == 0 &&
			my_strcmp((*arr)[i].addr.province, s.addr.province) == 0 &&
			my_strcmp((*arr)[i].addr.city, s.addr.city) == 0 &&
			my_strcmp((*arr)[i].addr.district, s.addr.district) == 0 &&
			(*arr)[i].score == s.score) {
			idx_list[cnt] = i;
			cnt++;
		}
	}

	if (cnt == 0) {
		printf("일치하는 학생이 없습니다.\n");
		return;
	}

	if (cnt == 1) {
		// 일치하는 학생이 딱 한 명이면 물어볼 것도 없이 바로 그 학생을 삭제 대상으로.
		del_idx = idx_list[0];
	}
	else {	// 완전히 같은 정보의 학생이 여러명이면 목록 보여주고 선택하게 함
		int pick;
		printf("동일한 정보의 학생이 %d명 있습니다.\n", cnt);
		for (i = 0; i < cnt; i++) {
			printf("[%d] %d %s %s %s %s %s %.1f\n", i + 1,
				(*arr)[idx_list[i]].num, (*arr)[idx_list[i]].name,
				(*arr)[idx_list[i]].addr.country, (*arr)[idx_list[i]].addr.province,
				(*arr)[idx_list[i]].addr.city, (*arr)[idx_list[i]].addr.district,
				(*arr)[idx_list[i]].score);
		}
		pick = get_int("삭제할 번호 선택: ");
		// 목록에 보여준 [1] ~ [cnt] 범위를 벗어나면 계속 다시 물어본다.
		while (pick < 1 || pick > cnt) {
			printf("범위를 벗어났습니다. 다시 입력하세요.\n");
			pick = get_int("삭제할 번호 선택: ");
		}
		del_idx = idx_list[pick - 1];	// 사용자는 1부터 셌으니 배열 인덱스는 -1
	}

	// 삭제할 원소(del_idx) 뒤에 있는 모든 원소를 한 칸씩 앞으로 당겨서
	// 삭제한 자리의 빈틈을 메운다. 이렇게 하면 배열이 항상 앞쪽부터
	// 빈틈없이 채워진 상태를 유지할 수 있다.
	for (i = del_idx; i < *n - 1; i++)	// 뒤에 있는 원소들 한칸씩 당김
		(*arr)[i] = (*arr)[i + 1];

	(*n)--;	// 실제 사용 중인 학생 수를 하나 줄인다 (용량 cap은 그대로 유지)
	printf("삭제되었습니다. (현재 %d명)\n", *n);
}

// 3번 메뉴 - add/delete 나눠서 처리
// "add" 또는 "delete" 문자열을 입력받아 해당하는 하위 기능으로 분기한다.
void do_addel(Student** arr, int* n, int* cap) {
	char cmd[10];
	get_str("add 또는 delete 입력: ", cmd, sizeof(cmd));

	if (my_strcmp(cmd, "add") == 0)
		do_add(arr, n, cap);
	else if (my_strcmp(cmd, "delete") == 0)
		do_delete(arr, n);
	else
		printf("잘못된 명령입니다. add 또는 delete만 입력 가능합니다.\n");
}

// 출석부를 파일에 저장
// 텍스트 파일(attendance.txt)에 "전체 학생 수" 한 줄, 그 뒤로 학생 한 명당
// 한 줄씩(공백으로 구분된 7개 값) 저장한다. 이렇게 첫 줄에 인원수를
// 적어두면 불러올 때(do_load) 몇 명을 읽어야 할지 미리 알 수 있다.
void do_save(Student* arr, int n) {
	FILE* fp = fopen("attendance.txt", "w");
	int i;

	if (fp == NULL) {
		printf("파일을 열 수 없습니다.\n");
		return;
	}

	fprintf(fp, "%d\n", n);
	for (i = 0; i < n; i++) {
		// score는 %lf(double)로 저장 — fprintf에서는 %f와 %lf가 동일하게
		// double을 받아들이지만, do_load에서 fscanf로 읽을 때는 %lf가
		// 반드시 필요하다는 것과 짝을 맞추기 위해 명시적으로 %lf를 사용.
		fprintf(fp, "%d %s %s %s %s %s %lf\n",
			arr[i].num, arr[i].name,
			arr[i].addr.country, arr[i].addr.province, arr[i].addr.city, arr[i].addr.district,
			arr[i].score);
	}

	fclose(fp);
	printf("저장되었습니다.\n");
}

// 출석부를 파일에서 불러옴
// do_save가 만든 형식(첫 줄=인원수, 이후 한 줄당 학생 1명)을 그대로 읽어서
// 새로운 배열(new_arr)에 담고, 성공하면 기존 배열(*arr)을 통째로 교체한다.
void do_load(Student** arr, int* n, int* cap) {
	FILE* fp = fopen("attendance.txt", "r");
	int cnt, i;
	Student* new_arr;

	if (fp == NULL) {
		printf("파일을 열 수 없습니다. 먼저 저장을 해보세요.\n");
		return;
	}

	// 첫 줄에서 저장돼 있던 학생 수를 읽는다. 형식이 깨졌거나(정수가 아님)
	// 음수라면 잘못된 파일이므로 바로 중단.
	if (fscanf(fp, "%d", &cnt) != 1 || cnt < 0) {
		printf("파일 형식이 잘못되었습니다.\n");
		fclose(fp);
		return;
	}

	// cnt명이 들어갈 배열을 새로 확보. cnt가 0이어도 malloc(0)은 동작이
	// 애매할 수 있어서 최소 1칸은 확보하도록 방어적으로 처리했다.
	new_arr = (Student*)malloc(sizeof(Student) * (cnt == 0 ? 1 : cnt));
	if (new_arr == NULL) {
		printf("메모리 할당에 실패했습니다.\n");
		fclose(fp);
		return;
	}

	for (i = 0; i < cnt; i++) {
		// %19s, %29s처럼 필드 크기에 맞춰 최대 길이를 제한해서 읽어야
		// name(20), addr 각 필드(30) 배열의 경계를 넘지 않는다. get_str에서
		// 쓰는 길이 제한과 정확히 짝이 맞도록(len-1) 맞춰둔 값이다.
		if (fscanf(fp, "%d %19s %29s %29s %29s %29s %lf",
			&new_arr[i].num, new_arr[i].name,
			new_arr[i].addr.country, new_arr[i].addr.province,
			new_arr[i].addr.city, new_arr[i].addr.district,
			&new_arr[i].score) != 7) {
			// 한 줄이라도 형식이 안 맞으면(반환값이 7개 필드가 아니면)
			// 거기서 읽기를 중단하고, 그 앞까지 읽은 데이터만 살려서 사용한다.
			printf("%d번째 줄을 읽는 중 오류가 발생했습니다. 여기까지만 불러옵니다.\n", i + 1);
			cnt = i;
			break;
		}
	}

	fclose(fp);
	free(*arr);		// 기존에 쓰던 배열은 더 이상 필요 없으므로 메모리 해제 (메모리 누수 방지)
	*arr = new_arr;	// main의 arr가 새로 불러온 배열을 가리키도록 교체
	*n = cnt;
	*cap = (cnt == 0 ? 1 : cnt);	// 용량도 방금 malloc한 크기와 맞춰준다
	printf("%d명의 학생을 불러왔습니다.\n", cnt);
	print_arr(*arr, *n);
}

// 4번 메뉴 - save/load 나눠서 처리
// "save" 또는 "load" 문자열을 입력받아 해당하는 하위 기능으로 분기한다.
void do_saveload(Student** arr, int* n, int* cap) {
	char cmd[10];
	get_str("save 또는 load 입력: ", cmd, sizeof(cmd));

	if (my_strcmp(cmd, "save") == 0)
		do_save(*arr, *n);
	else if (my_strcmp(cmd, "load") == 0)
		do_load(arr, n, cap);
	else
		printf("잘못된 명령입니다. save 또는 load만 입력 가능합니다.\n");
}
