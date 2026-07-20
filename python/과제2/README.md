# Robit_intern_python_assignment2_7.14

광운대학교 로빛 수습단원 7/14(화) 과제로 진행한 과제입니다.

## 사용한 외부 라이브러리

1. requests
2. BeautifulSoup4

자세한 버전과 전체 라이브러리는 `requirements.txt` 파일을 참고해주세요.

## 실행 방법

멜론 차트 top50 웹 크롤링을 원하시는 분은 코드를 복사한 뒤 그대로 사용하시면 됩니다.

1. 프로젝트 진행을 원하는 폴더를 만든 후 Visual Studio Code에서 폴더 열기
2. 가상환경 만들기
   ```bash
   python -m venv .venv
   ```
3. 필요한 라이브러리 설치
   ```bash
   pip install requests BeautifulSoup4
   ```
4. 본인이 원하는 웹사이트의 주소를 아래 형식으로 수정
   ```python
   url = '원하는 주소를 여기에 넣으세요'
   ```
5. 본인이 선택한 웹사이트에 들어가서 `F12` 혹은 마우스 우클릭 후 **검사** 클릭
6. 뉴스의 제목을 클릭하면 html 코드로 이동하는데, 그때 `<div class="A">` 라고 써져있는 형태의 `A`를 9번 줄의 `'div.A'`로 수정
7. 같은 원리로 하나의 div에 들어있는 span에서 `<span class="B">` 라고 써져있는 형태의 `B`를 13번 줄의 `'span.B'`로 수정

주의: 웹사이트의 특성에 따라 div와 span의 구조가 다를 수 있습니다.

## 코드 설명

1. `get` 메소드를 사용하여 url에 HTTP Request 전송
2. 정상 응답 시 제대로 작동, 오류 시 error 출력
3. `'html.parser'`를 통해 응답받은 HTML 파싱
4. 파싱한 데이터에서 div, span 태그 내 클래스 데이터 저장
5. 실행

## 라이브러리에 대한 이해

### requests

Requests는 Python에서 HTTP 요청을 보내기 위한 간단하고 사용하기 쉬운 라이브러리입니다. 웹 페이지의 내용을 가져오고, API 호출을 수행하고, 웹 기반 데이터와 상호 작용하는 등의 작업을 할 수 있습니다.

### BeautifulSoup4

Beautiful Soup는 Python에서 HTML 및 XML 파일을 구문 분석하고 조작하기 위한 라이브러리입니다. 웹 스크래핑에 주로 사용되며, 웹 페이지로부터 데이터를 추출하고 분석하는 데 유용하고 사용자가 태그와 속성을 쉽게 검색하고 수정할 수 있도록 도와줍니다.# Robit_intern_python_assignment2_7.14


## 사용한 외부 라이브러리

1. requests
2. BeautifulSoup4

자세한 버전과 전체 라이브러리는 `requirements.txt` 파일을 참고해주세요.

## 실행 방법

멜론 차트 top50 웹 크롤링을 원하시는 분은 코드를 복사한 뒤 그대로 사용하시면 됩니다.

1. 프로젝트 진행을 원하는 폴더를 만든 후 Visual Studio Code에서 폴더 열기
2. 가상환경 만들기
   ```bash
   python -m venv .venv
   ```
3. 필요한 라이브러리 설치
   ```bash
   pip install requests BeautifulSoup4
   ```
4. 본인이 원하는 웹사이트의 주소를 아래 형식으로 수정
   ```python
   url = '원하는 주소를 여기에 넣으세요'
   ```
5. 본인이 선택한 웹사이트에 들어가서 `F12` 혹은 마우스 우클릭 후 **검사** 클릭
6. 뉴스의 제목을 클릭하면 html 코드로 이동하는데, 그때 `<div class="A">` 라고 써져있는 형태의 `A`를 9번 줄의 `'div.A'`로 수정
7. 같은 원리로 하나의 div에 들어있는 span에서 `<span class="B">` 라고 써져있는 형태의 `B`를 13번 줄의 `'span.B'`로 수정

주의: 웹사이트의 특성에 따라 div와 span의 구조가 다를 수 있습니다.

## 코드 설명

1. `get` 메소드를 사용하여 url에 HTTP Request 전송
2. 정상 응답 시 제대로 작동, 오류 시 error 출력
3. `'html.parser'`를 통해 응답받은 HTML 파싱
4. 파싱한 데이터에서 div, span 태그 내 클래스 데이터 저장
5. 실행

## 라이브러리에 대한 이해

### requests

Requests는 Python에서 HTTP 요청을 보내기 위한 간단하고 사용하기 쉬운 라이브러리입니다. 웹 페이지의 내용을 가져오고, API 호출을 수행하고, 웹 기반 데이터와 상호 작용하는 등의 작업을 할 수 있습니다.

### BeautifulSoup4

Beautiful Soup는 Python에서 HTML 및 XML 파일을 구문 분석하고 조작하기 위한 라이브러리입니다. 웹 스크래핑에 주로 사용되며, 웹 페이지로부터 데이터를 추출하고 분석하는 데 유용하고 사용자가 태그와 속성을 쉽게 검색하고 수정할 수 있도록 도와줍니다.
