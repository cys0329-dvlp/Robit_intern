import csv
import json

# students.csv에서 추출한 데이터를 clean_students.csv에 바로 넣기 위해 한번에 두개 불러오기
with open("students.csv", "r", newline="", encoding="utf-8") as infile, \
     open("clean_students.csv", "w", newline="", encoding="utf-8") as outfile:

    reader = csv.DictReader(infile)  # 헤더를 자동으로 key로 사용해서 딕셔너리로 읽어줌
    writer = csv.DictWriter(outfile, fieldnames=["name", "score"])  # 쓸 때 사용할 컬럼명 지정
    writer.writeheader()  # header(name, score) 한 줄 출력

    for row in reader:
        try:  # ValueError 발생 예외처리
            name = row["name"]  # "name" 컬럼 값
            score = int(row["score"])  # "score" 컬럼 값을 정수로 변환

            if score < 0 or score > 100:  # 범위 벗어났을 때 예외처리
                print(f"{name} 범위에 맞지 않는 입력입니다.")
            else:
                print(name, score)  # 정상인 애들만 출력
                writer.writerow({"name": name, "score": score})  # 정상인 애들만 clean_students.csv에 작성

        except ValueError:  # ValueError 예외 처리
            print(f"{name} 입력 방식에 맞지 않습니다.")

        except FileNotFoundError:  # 파일 이름이 잘못되거나 없을 때 예외처리
            print("파일을 찾을 수 없습니다.")


## clean_students.csv 파일의 학생들 값을 인원수, 평균, 최고점으로 기록하기
with open("clean_students.csv", "r", newline="", encoding="utf-8") as infile, \
     open("summary.json", "w", encoding="utf-8") as outfile:

    reader = csv.DictReader(infile)  # 헤더를 key로 자동 인식
    count = 0  # 인원수
    total = 0  # 전체 점수 합
    max_score = None  # 최고점 (첫 데이터로 초기화 예정)

    for row in reader:
        name = row["name"]
        score = int(row["score"])
        count += 1
        total += score  # 전체 점수 합

        if max_score is None or score > max_score:  # 첫 번째 값이거나 더 큰 값이면 갱신
            max_score = score

    avg = total / count  # 평균 계산
    data = {"인원수": count, "평균": avg, "최고점": max_score}  # json 데이터 만들기
    json.dump(data, outfile, ensure_ascii=False, indent=4)  # json 파일에 저장