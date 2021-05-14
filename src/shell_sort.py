import random
from datetime import datetime

def shellsort(arr):
    # https://en.wikipedia.org/wiki/Shellsort#Gap_sequences
    gap = len(arr) // 2

    while gap >= 1:
        for i in range(gap, len(arr)):
            j = i
            while gap <= j:
                if arr[j - gap] < arr[j]:
                    break

                arr[j - gap], arr[j] = arr[j], arr[j - gap]
                j -= gap

        gap //= 2


def main():
    data = [3, 2, 8, 5, 4, 1]
    shellsort(data)
    print(data)

    # 100만 건 여기서도
    print("sorting 1m elements..")

    before = datetime.now()

    data = [random.randint(0, 1000000) for _ in range(1_000_000)]
    shellsort(data)

    after = datetime.now()

    print(f"took {after - before}")

    # 정렬이 오름차순으로 되었나 체크
    m = -1
    for val in data:
        if val < m:
            print(f"❌ something is wrong: val={val}, m={m}")
            return

    print("✅ OK!")


if __name__ == "__main__":
    main()
