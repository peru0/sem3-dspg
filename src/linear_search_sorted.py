def print_data_em(data, index):
    indent = 2 # 괄호 시작
    print("[ ", end="")
    for i, val in enumerate(data):
        print(f"{val} ", end="")
        val_str = str(val)

        if i < index:
            indent += len(val_str) + 1
    print("]")

    print(" " * indent, end="")
    val_str = str(data[index])
    print("^" * len(val_str), end="")
    print(" 여기에 존재")


def find_sorted(data, value):
    print(f"======== '{value}' 검색 ========")
    for i, val in enumerate(data):
        if value < val:
            print(f"{value} < data[{i}]({val}) (여기까지 확인했는데 없더라; 뒤에는 아무리 찾아봐도 없다는 이야기)")
            return
        elif value == val:
            print(f"data[{i}]에 원소가 존재")
            print_data_em(data, i)
            return

    print(f"원소 {len(data)}개를 전부 확인했는데 없더라")


def main():
    data = [1, 6, 3, 42, 3, 100]
    data = sorted(data)

    find_sorted(data, 42)
    find_sorted(data, 7)
    find_sorted(data, 9999)
    find_sorted(data, 100)
    find_sorted(data, 3)
    pass


if __name__ == "__main__":
    main()
