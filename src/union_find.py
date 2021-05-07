# Kruskal MST를 구현하기 전에 union_find 구현이 먼저 되어야 한다.
#
# 사이클이 있는가 알아내는 과정을 DFS/BFS로 구현이 "아예 안 되는 건" 아니다.
#
# 하지만 edge.weight를 오름차순으로 정렬하고, MST가 될 만한 간선 후보들을 연결하는 과정에서 비연결 그래프가 생길 수 밖에 없다.
#
# (예제, 일단 weight은 여기에 쓰기 어려우니 생략)
#    A       Y - U
#   / \     /     \
#  B   D   X       V
#   \       \
#    C       Z - W
# 이제 다음으로 비용이 싼 간선인 D-X를 연결할 때 사이클이 생길 지 안 생길지 판단하자.
#
#    A       Y - U
#   / \     /     \
#  B   D - X       V
#   \       \
#    C       Z - W
#
# kruskal 함수 실행동안 visited[id]를 가지고
# 연결하기 전 edge.dest를 방문했는가 확인하는 방식으로는 이게 사이클인지 아닌지
# 판단할 수가 없다.
#   ( 0 = unvisited, 1 = visited )
#    1       1 - 1
#   / \     /     \
#  1   1   1       1
#   \    ^  \
#    1   |   1 - 1
#        |
# 이게 연결하면 사이클이 생기는가? ...어...
#
# ...따라서, 각 정점을 연결해보고 이 상태로 사이클이 생기는가 새로 테스트해야 한다.
#    A       Y - U
#   / \     /     \
#  B   D - X       V
#   \    ^  \
#    C   |   Z - W
#    (매 간선마다 연결해보고 -> DFS/BFS로 연결한 그래프에 사이클이 있는가 새로 테스트하고 -> 아니면 연결하지 않고 -> 반복)
#                                ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
#     사이클이 없을 때를 기준으로 (최악) 연결한 그래프의 정점(|V|)을 모두 방문해봐야 한다. 그리고 그걸 매 간선(|E|)마다 새로 수행해야 한다.
#
# 따라서, 이걸 개선하기 위해 Union-find를 통해 사이클을 찾는다.
#    A       Y - U
#   / \     /     \
#  B   D   X       V
#   \       \
#    C       Z - W
# (best case)
#    1       2 - 2
#   / \     /     \
#  1   1   2       2
#   \    ^  \
#    1   |   2 - 2
# 왼쪽과 오른쪽의 집합 번호만 확인하면 사이클이 생길지 바로 판단할 수 있다는 것이 골자.
# (실제로는 union() 연산도 생각해야 해서 상수는 아니지만, union()과 find() 지금은 두 개 모두 logN 시간이 걸리는 구현이 있다는 것만 알아두면 된다.)


# 그리고 union-find의 union() find()에 대해서..
# 1. find()의 최대 시간은 트리의 최대 높이만큼 차지한다.
# 2. 트리의 높이 1을 높이는 연산은 union() 뿐이다.
# 3. union()을 수행할 때 높이가 낮은 트리를 높은 트리의 루트에 매달아둔다.
#    그러면 트리 높이가 h에서 h + 1이 되려면 노드가 최소 2h개는 필요하다.
#
# (에졔1.)
# 0        0 ------+
# |        | \     | ( 높이가 그대로 )
# 1  2 ==> 1  2 ---+
#
# (에졔2.)
# 0  2     0 ------+
# |  |     | \     |
# 1  3 ==> 1  2    | ( 높이가 증가했다 )
#             |    |
#             3 ---+

class UnionFind:
    def __init__(self, size):
        self.parent = [i for i in range(size)]
        self.weight = [1] * size

    # $X \cap Y$ 연산
    def union(self, x_id, y_id):
        print(f"union({x_id}, {y_id})")

        x_root = self.find(x_id)
        y_root = self.find(y_id)

        x_weight = self.weight[x_root]
        y_weight = self.weight[y_root]

        if x_weight < y_weight:
            # y를 루트로 유지하고 x를 자식으로
            self.parent[x_root] = y_root
            self.weight[y_root] += self.weight[x_root]
        else:
            # x를 루트로 유지하고 y를 자식으로
            self.parent[y_root] = x_root
            self.weight[x_root] += self.weight[y_root]

    # 원소 x가 속한 집합의 id를 반환하는 연산
    def find(self, x_id):
        print(f"finding a root node of the given node '{x_id}'")

        id = x_id

        # path compression에 대해:
        # 0 <-+                               0 <-------+
        # |   |                             /   \       |
        # 1   |                            1     2      | (2회만 거슬러 올라가면 루트 노드)
        # |   | ( 4번 노드 find 1회 수행 후 )     /   \    |
        # 2   |            ->                 3     4 --+
        # |   |
        # 3   |  4번 노드에서 루트르 찾으려면 4번 거슬러 올라가야 하지만
        # |   |  찾을 때마다 id.parent = grant_parent_id(2회, 상수)를 저장해두는 path compression을 수행하면
        # 4 --+  나중에 같은 노드를 조회할 때는 **절반 길이**인 2회만 거슬러 올라가면 된다는 것이 기본 아이디어.
        #
        # (다른 방법도 있지만 이 방법이 구현이 제일 간단한 것도 있고. 특히 추가 힙 할당이 없다는 점이..)
        #
        # References:
        # - https://www.cs.princeton.edu/~rs/AlgsDS07/01UnionFind.pdf 29p
        # - The Algorithm Design Manual, Steven S. Skiena, Springer, 198-201p
        while id != self.parent[id]:
            print(f"-> {id} ", end="")
            # this = this.parent.parent
            self.parent[id] = self.parent[self.parent[id]]
            id = self.parent[id]

        print(f"=> {id} (root)")

        return id

    def is_in_same_set(self, x_id, y_id) -> bool:
        x_root = self.find(x_id)
        y_root = self.find(y_id)

        return x_root == y_root


def main():
    union = UnionFind(3)

    union.union(0, 1)

    print("=== before union(1, 2) ===")
    union.find(2)
    print("=== union(1, 2) ===")
    union.union(1, 2)
    print("=== after union(1, 2) ===")
    union.find(2)


if __name__ == "__main__":
    main()
