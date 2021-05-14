import random


class BinaryHeap(object):
    def __init__(self, capacity=0):
        self.data = [None] * capacity

    def __up_heapifty(self, idx):
        while idx != 0:
            parent = idx // 2
            if self.data[idx] < self.data[parent]:
                self.data[idx], self.data[parent] = self.data[parent], self.data[idx]

            idx = parent

    def __down_heapify(self, idx):
        while idx < len(self.data):
            left = (idx * 2) + 1
            right = (idx * 2) + 2

            moff = idx
            if left < len(self.data) and self.data[left] < self.data[moff]:
                moff = left

            if right < len(self.data) and self.data[right] < self.data[moff]:
                moff = right

            if moff == idx:
                break

            self.data[idx], self.data[moff] = self.data[moff], self.data[idx]
            idx = moff

    def push(self, value):
        self.data.append(value)
        self.__up_heapifty(len(self.data) - 1)

    def pop(self):
        top = self.data[0]

        last_idx = len(self.data) - 1
        self.data[0], self.data[last_idx] = self.data[last_idx], self.data[0]
        self.data.pop()

        self.__down_heapify(0)

        return top

    def empty(self):
        return len(self.data) == 0


def main():
    data = [3, 42, 1, 2, 8, 7, 5]

    heap = BinaryHeap()
    for val in data:
        heap.push(val)

    print(f"[", end="")
    while not heap.empty():
        val = heap.pop()
        print(f"{val}, ", end="")
    print(f"]")

    print("=> sorting 1m random elements")
    data = [random.randint(0, 1000000) for _ in range(1_000_000)]
    heap = BinaryHeap()
    for val in data:
        heap.push(val)


    # C++로 구현한 건 size=5m이라도 1~2초면 되는데
    # 파이썬으로 구현했더니 size=1m인데도 꽤 걸리네...
    m = -1
    while not heap.empty():
        val = heap.pop()
        if m > val:
            print(f"❌ something is wrong: val={val}, m={m}")
            return

    print("✅ done!")


if __name__ == "__main__":
    main()
