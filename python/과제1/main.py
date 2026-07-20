import csv
import json
#students.csv에서 추출한 데이터를 clean_students에 바로 넣기 위해 한번에 두개 불러오기
with open("students.csv", "r", newline="", encoding="utf-8") as infile, \
    open("clean_students.csv", "w", newline="", encoding="utf-8") as outfile:
  reader = csv.reader(infile) #students.csv파일 읽기로 불러오기
  header = next(reader) #맨 윗 줄 생략
  writer = csv.writer(outfile) #clean_students.csv 파일 쓰기로 불러오기
  writer.writerow(["name", "score"]) #for문 전에 미리 name, score 출력해놓기

  for row in reader:
    try:  #ValueError 발생 예외처리
      name = row[0] #첫번째 열을 이름으로 설정
      score = int(row[1]) #두번째 열을 점수로 설정
      if score < 0 or score > 100:  #범위 벗어났을 때 예외처리
        print(f"{name} 범위에 맞지 않는 입력입니다.")

      else:
        print(name, score) #범위 안벗어나고 ValueError도 발생 안하는 애들만 출력
        writer.writerow([f"{name}", f"{score}"]) #정상인 애들만 clean_students.csv 파일에 작성

    except ValueError: #ValueError 예외 처리
      print(f"{name} 입력 방식에 맞지 않습니다.")

    except FileNotFoundError: #파일 이름이 잘못되거나 없을 때 예외처리
      print("파일을 찾을 수 없습니다.")

##clean_student.csv 파일의 학생들 값을 인원수, 평균, 최고점으로 기록하기
with open("clean_students.csv", "r", newline = "", encoding = "utf-8") as infile, \
  open("summary.json", "w", encoding = "utf-8") as outfile:
    reader = csv.reader(infile)
    header = next(reader)
    count = 0 #인원수
    avg = 0 # 평균
    total = 0 # 전체 점수 합
    max = score #맨 처음을 max라고 가정하고 for문에서 비교하며 최고점 선택
    for row in reader: #저장된 인원만큼 for문이 돌기 때문에 한번 돌 때마다 인원수 +1
      name = row[0]
      score = int(row[1])
      count += 1
      total += score #전체 점수 합
      if score > max:
        max = score
    avg = total/count
    data = {"인원수": count, "평균": avg, "최고점": max} #json 데이터 만들기
    json.dump(data, outfile, ensure_ascii=False, indent=4) ##json 파일에 저장