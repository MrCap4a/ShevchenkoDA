class RecursiveDFS:
    def __init__(self, graph, representation): # O(n)
        """
        graph — матрица смежности или список смежности
        representation — 'matrix' или 'list'
        """
        self.graph = graph
        self.representation = representation
        self.n = len(graph)
        self.visited = [False] * self.n
        self.order = []  # порядок обхода вершин

    def run(self, start): # O(n^2) для матрицы, O(n + m) для списка
        self._dfs(start)
        return self.order

    def _dfs(self, v): # O(n^2) для матрицы, O(n + m) для списка
        self.visited[v] = True
        self.order.append(v)

        for u in self._get_neighbors(v):
            if not self.visited[u]:
                self._dfs(u)

    def _get_neighbors(self, v): # O(n) для матрицы, O(deg(v)) для списка
        neighbors = []
        if self.representation == 'matrix':
            for u in range(self.n):
                if self.graph[v][u] != 0:
                    neighbors.append(u)
        elif self.representation == 'list':
            for u, weight in self.graph[v]:
                neighbors.append(u)
        return neighbors
