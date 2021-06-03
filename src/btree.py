class Btree:
    def __init__(self, m=8):
        self.__root = Node(m)

    def find(self, key):
        return self.__root.find(key)

    def insert(self, key, value):
        if key is None:
            raise KeyError("key must not be None")

        self.__root = self.__root.insert(key, value)


class Node:
    def __init__(self, m):
        self.__kvs = [(None, None)] * (m - 1)
        self.__children = [None] * m

    def find(self, key):
        subtree = self
        while subtree is not None:
            index = 0
            while self.__kvs[index][0] is not None:
                if self.__kvs[index][0] == key:
                    # found the key
                    return self.__kvs[index][1]
                elif key < self.__kvs[index][0]:
                    break
                index += 1

            if self.__children[index] is None:
                raise KeyError("could not find the key", key)

            subtree = self.__children[index]

    def insert(self, key, value):
        index = 0
        while self.__kvs[index][0] is not None:
            if self.__kvs[index][0] == key:
                # replace it
                self.__kvs[index][1] = value
                return self
            elif key < self.__kvs[index][0]:
                break

            index += 1

        # TODO


def main():
    pass


if __name__ == "__main__":
    main()
