def partition(arr, first, last):
    # initial setup
    #  0  1  2  3  4
    # [3, 1, 5, 2, 4]
    #  ^  ^left    ^right, last
    #  pivot, first
    #
    # 주의할 사항
    # - 왼쪽에서 오른쪽으로 스캔할 때
    #   1. last 경계를 넘으면 안 된다. 이건 너무나도 자명하다.
    #      (right가 항상 last보다 작거나 같으니 이걸 이용하면 되겠지..)
    #   2. left가 right를 넘어버린 상태로 (left > right) swap을 수행하면
    #      더 이상 왼쪽 구간이 작고, 오른쪽 구간이 큰 성질을 이용할 수 없다.
    # - 오른쪽에서 왼쪽으로 스캔할 때도 마찬가지

    pivot = arr[first]
    left = first + 1
    right = last

    while left < right:
        # 오른쪽을 먼저 찾는 게 왼쪽부터 찾는 것보다 edge case를 처리하는 게 쉬워서구나..
        while left < right and pivot < arr[right]:
            right -= 1

        while left < right and arr[left] < pivot:
            left += 1

        arr[left], arr[right] = arr[right], arr[left]

    if arr[left] < pivot:
        arr[first], arr[left] = arr[left], arr[first]

    return left


def qsort(arr):
    qsort_step(arr, 0, len(arr) - 1)


def qsort_step(arr, begin, end):
    # 정렬할 것이 없거나 (len=0,1와 같은 기저 상태) 아니면 p + 2가 end를 넘어가거나..
    if end - begin <= 1:
        print(f"{end - begin}")
        return

    p = partition(arr, begin, end)
    qsort_step(arr, begin, p)
    qsort_step(arr, p + 2, end)


def main():
    data = [3, 1, 4, 2, 5]
    qsort(data)

    print(data)


if __name__ == "__main__":
    main()
