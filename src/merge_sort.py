import random


def msort(arr):
    temp = [None] * len(arr)
    msort_impl(arr, 0, len(arr), temp)


def msort_impl(arr, begin, end, temp):
    # 예를 들어 [0, 1]이면
    # begin=0, end = 2 (end - begin = len이 되도록)
    arr_len = end - begin

    # 기저 상태
    if arr_len <= 1:
        return

    mid = begin + (arr_len // 2)
    msort_impl(arr, begin, mid, temp)
    msort_impl(arr, mid, end, temp)
    # print(f"msort: {begin}..{mid}..{end} ({arr_len})")

    # 결국 mergesort가 selection sort보다 효율적인 이유에는 **이미 정렬된 두 배열이 존재한다**는 조건이 붙으면
    # 병합한 배열도 정렬되게 만들 수 있는 효율적인 방법이 존재한다는 거겠지.
    offset = begin
    left_offset = begin
    right_offset = mid
    while left_offset < mid and right_offset < end:
        if arr[left_offset] < arr[right_offset]:
            temp[offset] = arr[left_offset]
            left_offset += 1
        else:
            temp[offset] = arr[right_offset]
            right_offset += 1

        offset += 1

    # 과연, if문이 4개 들어가서 복사하는 것보다 (left가 mid를 넘어갔는가, right가 end를 넘어갔는가, left <=> right 비교)
    # left, right 조건은 나중에 비교하고 한번에 memcpy()로 복사하는 게 더 빠르겠지. 이쪽은 많은 언어에서 simd 지원도 받고..
    if left_offset == mid:
        temp[offset:end] = arr[right_offset:end]
    else:
        temp[offset:end] = arr[left_offset:mid]

    # 복사
    arr[begin:end] = temp[begin:end]


def main():
    data = [4, 3, 42, 1, 2, 5, 6, 7]
    msort(data)
    print(data)

    # 홀수
    data = [4, 3, 42, 1, 2, 5, 7]
    msort(data)
    print(data)

    print("====100====")
    data = [random.randint(0, 10000) for _ in range(100)]
    msort(data)
    print(data)

    print("====sorting 1m elements====")
    data = [random.randint(0, 1000000) for _ in range(1_000_000)]
    msort(data)
    print("testing..")
    # 이쯤되면 눈으로 판단하는 게 어려우니
    m = -1
    for val in data:
        m = max(m, val)
        if m != val:
            print(f"something is wrong ({m} > {val})")
    print("done!")


if __name__ == "__main__":
    main()
