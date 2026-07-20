import requests
from bs4 import BeautifulSoup

url = 'https://www.boannews.com/media/t_list.asp'
response = requests.get(url)  # GET 메소드를 사용하여 url에 HTTP Request 전송

if response.status_code == 200:  # 정상 응답 반환 시 아래 코드블록 실행
    soup = BeautifulSoup(response.content, 'html.parser')  # 응답 받은 HTML 파싱
    titles = soup.select('div.news_list')  # 파싱한 데이터에서 div 태그 내 news_list 클래스 내 데이터 저장
    count = 0
    for title in titles:
        count += 1
        print(f"{count}. {title.select_one('span.news_txt').get_text()}")

else:
    print('error')  # 오류 시 메시지 출력