class AdjacencyListGraph:
    def __init__(self, n):        # O(n)
        # количество вершин
        self.n = n
        # список смежности
        self.adj_list = [[] for _ in range(n)]

    def add_edge(self, from_v, to_v, weight):   # O(1)
        # добавление направленного ребра from_v -> to_v
        self.adj_list[from_v].append((to_v, weight))

    def remove_edge(self, from_v, to_v):        # O(k)
        # удаление ребра from_v -> to_v
        # k — количество рёбер из from_v
        new_edges = []
        for (v, w) in self.adj_list[from_v]:
            if v != to_v:
                new_edges.append((v, w))
        self.adj_list[from_v] = new_edges

    def print_list(self):     # O(n + m)
        # вывод списка смежности
        # n — количество вершин, m — общее количество рёбер
        for i in range(self.n):
            print(f"{i} -> {self.adj_list[i]}")
