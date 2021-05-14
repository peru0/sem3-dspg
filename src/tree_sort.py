class Tree:
    def __init__(self):
        self.root = None

    def insert(self, value):
        if self.root is None:
            self.root = Node(value)
            return

        # 루트부터 리프까지 내려간 다음 삽입하면 되는데...
        # 이 구현으로는 skewed 되어버리면 상당히 안 좋겠구나.
        # AVL 트리 언급 부분이 그거겠지.
        node = self.root
        next_node = None
        while True:
            if value < node.value:
                next_node = node.left
            else:
                next_node = node.right

            # 리프 노드
            if next_node is None:
                if value < node.value:
                    node.left = Node(value)
                else:
                    node.right = Node(value)

                return

            node = next_node

    def sort(self):
        arr = list()
        Tree.__inorder(self.root, arr)

    @staticmethod
    def __inorder(node, arr):
        if node.left is not None:
            Tree.__inorder(node.left, arr)

        arr.append(node.value)

        if node.right is not None:
            Tree.__inorder(node.right, arr)


class Node:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right

def main():
    tree = Tree()
    tree.insert(4)
    tree.insert(2)
    tree.insert(1)
    tree.insert(5)
    tree.insert(3)

    # node.left < node < node.right 관계를 가지고 있으니 당연한 거구나...
    tsort = tree.sort()
    print(tsort)


if __name__ == "__main__":
    main()
