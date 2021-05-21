import json

def binary_search(arr, term):
    print(f"===== 이진탐색: {term} =====")
    begin = 0      # inclusive
    end = len(arr) # exclusive

    while end - begin > 1:
        mid = begin + ((end - begin) // 2)

        print(f"data[{begin}..({mid})..{end}]")
    
        if term == arr[mid]:
            print(f">> data[{mid}]에 존재")
            return
        elif term < arr[mid]:
            # begin = begin
            end = mid # exclusive
        else:
            begin = mid # inclusive

    print("검색 결과 없음")


def main():
    metro_json = None
    with open("../data/metro.json", "r") as f:
        metro_json = json.load(f)

        # 이전에 다익스트라 하면서 추출한 서울메트로 역명 재활용
    data = sorted(metro_json["stations"])
    print(f"역: {len(data)}개")

    data = sorted(data)

    binary_search(data, "가락시장")
    binary_search(data, "가산디지털단지")
    binary_search(data, "서울역")
    binary_search(data, "홍대입구")
    binary_search(data, "수퍼빌런")


if __name__ == "__main__":
    main()
