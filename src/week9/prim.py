class BinaryHeap(object):
    def __init__(self):
        self.data = list()

    def minimum(self):
        return self.data[0]

    def insert(self, value):
        index = len(self.data)
        self.data.append(value)

        while index != 0:
            parent = (index - 1) // 2
            if self.data[index] < self.data[parent]:
                # swap
                self.data[index] = self.data[parent]
                self.data[parent] = value

            index = parent

    def delete_minimum(self):
        last_idx = len(self.data) - 1

        # swap(first, last)
        temp = self.data[0]
        self.data[0] = self.data[last_idx]
        self.data[last_idx] = temp

        self.data.pop()

        index = 0
        while True:
            left_index = (index * 2) + 1
            right_index = (index * 2) + 2

            minimum = index
            if left_index < len(self.data) and self.data[left_index] < self.data[index]:
                minimum = left_index

            if right_index < len(self.data) and self.data[right_index] < self.data[minimum]:
                minimum = right_index

            if index == minimum:
                break

            # swap(index, minimum)
            temp = self.data[minimum]
            self.data[minimum] = self.data[index]
            self.data[index] = temp

            index = minimum


class Vertex(object):
    def __init__(self):
        self.adjacents = BinaryHeap()

    def connect(self):
        pass


class Graph(object):
    def __init__(self, vertices):
        self.vertices = vertices

    def prim(self):
        pass
