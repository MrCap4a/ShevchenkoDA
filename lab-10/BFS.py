from collections import deque

class BFS:
    def __init__(self, graph, representation):
        """
        graph — матрица смежности или список смежности
        representation — 'matrix' или 'list'
        """
        self.graph = graph
        self.representation = representation
        self.n = len(graph)

    def run(self, start): # O(n + m) для списка, O(n^2) для матрицы
        visited = [False] * self.n
        distance = [-1] * self.n
        parent = [None] * self.n

        queue = deque()
        queue.append(start)
        visited[start] = True
        distance[start] = 0

        while queue:
            v = queue.popleft()

            for u in self._get_neighbors(v):
                if not visited[u]:
                    visited[u] = True
                    distance[u] = distance[v] + 1
                    parent[u] = v
                    queue.append(u)

        paths = self._build_paths(parent, start)
        return distance, paths

    def _get_neighbors(self, v): # O(n) для матрицы, O(deg(v)) для списка
        neighbors = []

        if self.representation == 'matrix':
            for u in range(self.n):
                # вес > 0 значит есть ребро
                if self.graph[v][u] != 0:
                    neighbors.append(u)

        elif self.representation == 'list':
            for u, weight in self.graph[v]:
                neighbors.append(u)

        return neighbors

    def _build_paths(self, parent, start): # O(n^2)
        paths = {}

        for v in range(self.n):
            if v == start:
                paths[v] = [start]
                continue

            path = []
            cur = v
            while cur is not None:
                path.append(cur)
                cur = parent[cur]

            if path[-1] == start:
                paths[v] = path[::-1]
            else:
                paths[v] = None  # пути нет

        return paths
