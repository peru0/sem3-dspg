import json


def read_json(path):
    with open(path, "r") as f:
        return json.load(f)


class Edge(object):
    def __init__(self, source, destination, distance: float):
        self.source = source
        self.destination = destination
        self.distance = distance

class Station(object):
    def __init__(self, station_id, name):
        self.id = station_id
        self.name = name
        self.edges = list()


class Metro(object):
    stations = list()
    stations_lookup_table = dict()

    def __init__(self, json_path="metro.json"):
        data_json = read_json(json_path)

        #               (이름으로 검색하려고...)
        # stations[seq_id]   stations_look_up_table[name]
        #       \               /
        #        +-------------+
        #            station
        seq_id = 0
        for name in data_json["stations"]:
            vertex = Station(seq_id, name)
            seq_id += 1

            self.stations.append(vertex)
            self.stations_lookup_table[name] = vertex

        # 연결 정보
        for edge in data_json["edges"]:
            source_node = self.stations_lookup_table[edge["source"]]
            destination_node = self.stations_lookup_table[edge["destination"]]
            distance = edge["distance"]

            edge = Edge(source_node, destination_node, distance)
            source_node.edges.append(edge)

            edge = Edge(destination_node, source_node, distance)
            destination_node.edges.append(edge)

    def __find_by_name(self, name):
        return self.stations_lookup_table[name]

    def __find_by_id(self, station_id):
        return self.stations[station_id]

    def find_path(self, source_name, dst_name):
        source = self.__find_by_name(source_name)
        dst = self.__find_by_name(dst_name)

        # priority heap이 아닌 O(V ^ 2) 구현 먼저
        # 노드가 꽤 적은 편인데도 검색에만 *최소* 246 (데이터에 존재하는 역 갯수) * 246 * 4 => 242KB 메모리 사용(!)
        # .NET 같은 경우는 이 사이즈면 large object heap에 할당되서 GC도 잘 안 되거니와 되더라도 반드시 stop-the-world 상태가 되는데..
        # 그것보다 더 큰 데이터, 예를 들어 게임 레벨에서 경로를 찾는다고 한다면 이런 방식으로 구현하기 상당히 어렵지 않을까 싶음.
        #
        # .. 또한 stations[name]이 hashmap처럼 O(~1ish)라고 가정하자. 그렇지 않을 가능성이 더 크겠지만...
        # 정 안 되면 메모리는 싸니까 list()를 하나 더 가지고 인덱스를 따로 유지하면 될 것 같은데...

        visited = [False] * len(self.stations)
        distances = [float("inf")] * len(self.stations)
        # backtrack 경로
        back = [None] * len(self.stations)

        distances[source.id] = 0

        def find_minimum_vertex() -> Station:
            minimum = None
            min_dist = float("inf")

            for vertex in self.stations:
                # 이미 방문한 정점은 스킵
                if visited[vertex.id]:
                    continue

                if distances[vertex.id] <= min_dist:
                    minimum = vertex
                    min_dist = distances[vertex.id]

            return minimum

        while True:
            # 이게 O(V ^ 2)를 만든 일등공신이구나...
            v = find_minimum_vertex()
            visited[v.id] = True

            if v == dst:
                break

            for edge in v.edges:
                edge_src_id = v.id
                edge_dst_id = edge.destination.id

                if visited[edge_dst_id]:
                    continue

                discovered_distance = distances[edge_src_id] + edge.distance

                if discovered_distance <= distances[edge_dst_id]:
                    distances[edge_dst_id] = discovered_distance
                    back[edge_dst_id] = v

        # 경로
        path = list()
        path_vertex = dst
        while path_vertex != source:
            path.append((path_vertex, distances[path_vertex.id]))
            path_vertex = back[path_vertex.id]
        path.append((source, 0))

        return reversed(path), distances[dst.id]

def main():
    metro = Metro("../data/metro.json")
    path, distance = metro.find_path("서울역", "청량리(서울시립대입구)")

    for node, distance in path:
        print(f"↓ {node.name} (누적 {distance:.2f}km) ↓")

    print(f"총 {distance:.2f}km")


if __name__ == "__main__":
    main()
