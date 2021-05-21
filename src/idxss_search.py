import json

INDEX_GAP = 16


def search_index(index, name):
    for i in range(len(index) - 1):
        if index[i] <= name < index[i + 1]:
            return i

    # 마지막에서 검색
    return None


def search_index_seq(arr, index, name):
    print(f"========== 검색: {name} ==========")

    found_index = search_index(index, name)

    start = end = None
    if found_index is not None:
        # 찾은 인덱스..다음 인덱스
        start = found_index * INDEX_GAP
        end = (found_index + 1) * INDEX_GAP
    else:
        # 맨 마지막 인덱스..배열 끝까지
        start = len(index) * INDEX_GAP
        end = len(arr)

    print(f"searching for {name} in data[{start}..{end}]")
    
    for i, val in enumerate(arr[start:end]):
        if val == name:
            print(f"data[{start + i}]에서 찾음")
            return
            
    print("검색 결과 없음")


def build_index(arr):
    index_size = len(arr) // INDEX_GAP
    index = [None] * index_size

    for i in range(index_size):
        index[i] = arr[i * INDEX_GAP]

    return index


def main():
    metro_json = None
    with open("../data/metro.json", "r") as f:
        metro_json = json.load(f)

    # 이전에 다익스트라 하면서 추출한 서울메트로 역명 재활용
    data = sorted(metro_json["stations"])
    print(f"역: {len(data)}개")

    # 이거 목적이 한 번 고생해서 인덱스를 만들고 두고두고 써먹자는 이야기니까...
    index = build_index(data)
    print(f"인덱스 크기: {len(index)}")
    search_index_seq(data, index, "서울역")
    search_index_seq(data, index, "홍대입구")
    search_index_seq(data, index, "반포")
    search_index_seq(data, index, "강동")
    search_index_seq(data, index, "함정역")


if __name__ == "__main__":
    main()
