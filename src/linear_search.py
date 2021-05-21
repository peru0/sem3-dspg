def search(data, value):
    for i, v in enumerate(data):
        if value == v:
            print(f"{i}번 원소가 값을 가지고 있음 ({i + 1}회)")
            return v

    print(f"{value} => {len(data)}개를 다 찾아봐도 결과가 없음")
    return None


def main():
    data = ["AAA", "asdf", "qwerty", "zxcvb", "42", "hi"]
    search(data, "AAA")
    search(data, "42")
    search(data, "nope")

    pass


if __name__ == "__main__":
    main()
