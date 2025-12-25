class IterativeDFS:
    def __init__(self, graph, representation): # O(n)
        self.graph = graph
        self.representation = representation
        self.n = len(graph)
        self.visited = [False] * self.n
        self.order = []

    def run(self, start): # O(n^2) для матрицы, O(n + m) для списка
        stack = [start]

        while stack:
            v = stack.pop()
            if not self.visited[v]:
                self.visited[v] = True
                self.order.append(v)

                # добавляем соседей в стек (обратный порядок, чтобы порядок совпадал с рекурсивным)
                neighbors = self._get_neighbors(v)
                neighbors.reverse()
                for u in neighbors:
                    if not self.visited[u]:
                        stack.append(u)

        return self.order

    def _get_neighbors(self, v):  # O(n) для матрицы, O(deg(v)) для списка
        neighbors = []
        if self.representation == 'matrix':
            for u in range(self.n):
                if self.graph[v][u] != 0:
                    neighbors.append(u)
        elif self.representation == 'list':
            for u, weight in self.graph[v]:
                neighbors.append(u)
        return neighbors
