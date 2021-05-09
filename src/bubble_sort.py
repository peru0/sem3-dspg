def bubble_sort(arr):
    # 성능을 떠나서 구현 자체가 너무 간단하니 소개하는 거군.
    #
    # - 바깥 쪽 for를 돌 때마다 큰 수들이 1칸 내려올 기회가 생기는 거고 (elm이 최소값이면 n번 돌 동안 n번 내려올 수 있으니까)
    # - 이걸 len(arr)만큼 반복하니까 제일 작은 게 왼쪽으로 올 기회가 충분하다는 거겠지.
    for i in range(len(arr)):
        for left, right in zip(range(0, len(arr) - 1), range(1, len(arr))):
            if arr[right] < arr[left]:
                # swap(left, right)
                temp = arr[left]
                arr[left] = arr[right]
                arr[right] = temp


def main():
    data = [42, 4, 3, 2, 7, 6, 5, 1]
    bubble_sort(data)

    print(data)


if __name__ == "__main__":
    main()
