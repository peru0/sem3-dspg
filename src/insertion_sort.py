def main():
    data = [42, 5, 4, 2, 3, 1]
    print(sort(data))


def sort(arr):
    # 데이터를 삽입해도 되지만 0개부터 삽입했다고 치고 늘여가면서 정렬해도 마찬가지.
    #
    # insertion sort가 많은 경우에는 O(n ^ 2)임에도 불구하고
    # 원소가 삽입될 때 정렬된다는 건
    # ..insert(arr, 10) # (1)
    # 정렬된 arr을 쓰고 있다가
    # 나중에 무언가가 일어날 때 까지 대기
    # insert(arr, 5) # (2)
    # ..나중에 무언가가 일어날 때 있다가
    # insert(arr, 1) # (3)
    # 이런 식으로 나누어서 해도 (1) (2) (3)을 수행한 결과가 모두 정렬되어 있는 상태인 건 분명히 큰 장점이군...
    sorted_arr = []

    for i in range(len(arr)):
        sorted_arr.append(arr[i])

        # 정렬할 것이 없음
        if len(sorted_arr) <= 1:
            continue

        # 맨 마지막 원소가 insert 되었다고 하자
        for j in range(len(sorted_arr) - 1, 0, -1):
            left = j - 1
            right = j

            if sorted_arr[left] < sorted_arr[right]:
                break

            # swap(left, right)
            temp = sorted_arr[left]
            sorted_arr[left] = sorted_arr[right]
            sorted_arr[right] = temp

        print(f"step {i + 1}: {sorted_arr}")

    return sorted_arr


if __name__ == "__main__":
    main()
