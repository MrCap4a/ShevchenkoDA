class AdjacencyMatrixGraph:
    def __init__(self, n):        # O(n^2)
        # количество вершин
        self.n = n
        # матрица смежности n x n
        self.matrix = [[0 for _ in range(n)] for _ in range(n)]

    def add_edge(self, from_v, to_v, weight):   # O(1)
        # добавление направленного ребра from_v -> to_v
        self.matrix[from_v][to_v] = weight

    def remove_edge(self, from_v, to_v):        # O(1)
        # удаление ребра from_v -> to_v
        self.matrix[from_v][to_v] = 0

    def print_matrix(self):     # O(n^2)
        # вспомогательный метод для вывода матрицы
        for row in self.matrix:
            print(row)
