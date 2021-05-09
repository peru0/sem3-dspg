def sort(arr):
    for i in range(len(arr)):
        min_index = i
        min_val = arr[i]

        # 다익스트라도 그렇고, 배열 내에서 for _ in arr 안에서 다시 배열의 모든 원소를
        # 최소값을 찾는 과정이 O(n ^ 2)을 만드는 일등공신이구나.
        #
        # 최소값을 찾는 부분이 나올 때마다 배열의 모든 원소를 찾아보는 게 아닌
        # priority_queue를 사용하는 것 만으로도 n -> logn 효과를 볼 수 있겠구나..
        for j in range(i, len(arr)):
            if arr[j] < min_val:
                min_val = arr[j]
                min_index = j

        # swap(arr[i], arr[min_index])
        temp = arr[i]
        arr[i] = arr[min_index]
        arr[min_index] = temp


def main():
    data = [0, 5, 3, 1, 42, 8, 3]
    sort(data)

    print(data)


if __name__ == "__main__":
    main()
