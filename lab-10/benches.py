import time
import random
import matplotlib.pyplot as plt
from AdjacencyListGraph import AdjacencyListGraph
from BFS import BFS
from RecursiveDFS import RecursiveDFS
from IterativeDFS import IterativeDFS
from AdjacencyMatrixGraph import AdjacencyMatrixGraph
from algorithms import algorithms

# ---------------------- Генерация случайного графа ----------------------
def generate_graph(n, edge_prob=0.2, max_weight=10):
    matrix_graph = AdjacencyMatrixGraph(n)
    list_graph = AdjacencyListGraph(n)

    for i in range(n):
        for j in range(n):
            if i != j and random.random() < edge_prob:
                w = random.randint(1, max_weight)
                matrix_graph.add_edge(i, j, w)
                list_graph.add_edge(i, j, w)

    return matrix_graph, list_graph

# ---------------------- Измерение времени ----------------------
def measure_time(func, *args):
    start = time.time()
    func(*args)
    return time.time() - start

# ---------------------- Основной эксперимент ----------------------
graph_sizes = [10, 50, 100, 200, 300]

# Для BFS/DFS
bfs_times_matrix, bfs_times_list = [], []
dfs_rec_times_matrix, dfs_rec_times_list = [], []
dfs_iter_times_matrix, dfs_iter_times_list = [], []

# Для добавления и удаления ребер
add_edge_times_matrix, add_edge_times_list = [], []
remove_edge_times_matrix, remove_edge_times_list = [], []

# Для алгоритмов из класса algorithms
cc_times_matrix, cc_times_list = [], []
topo_times_matrix, topo_times_list = [], []
dijkstra_times_matrix, dijkstra_times_list = [], []

for n in graph_sizes:
    matrix, adj_list = generate_graph(n, edge_prob=0.1)

    # ---------- BFS/DFS ----------
    bfs = BFS(matrix.matrix, 'matrix')
    dfs_rec = RecursiveDFS(matrix.matrix, 'matrix')
    dfs_iter = IterativeDFS(matrix.matrix, 'matrix')

    bfs_times_matrix.append(measure_time(bfs.run, 0))
    dfs_rec_times_matrix.append(measure_time(dfs_rec.run, 0))
    dfs_iter_times_matrix.append(measure_time(dfs_iter.run, 0))

    bfs = BFS(adj_list.adj_list, 'list')
    dfs_rec = RecursiveDFS(adj_list.adj_list, 'list')
    dfs_iter = IterativeDFS(adj_list.adj_list, 'list')

    bfs_times_list.append(measure_time(bfs.run, 0))
    dfs_rec_times_list.append(measure_time(dfs_rec.run, 0))
    dfs_iter_times_list.append(measure_time(dfs_iter.run, 0))

    # ---------- Добавление и удаление ребер ----------
    # Матрица
    add_edge_times_matrix.append(measure_time(matrix.add_edge, 0, 1, 5))
    remove_edge_times_matrix.append(measure_time(matrix.remove_edge, 0, 1))
    # Список
    add_edge_times_list.append(measure_time(adj_list.add_edge, 0, 1, 5))
    remove_edge_times_list.append(measure_time(adj_list.remove_edge, 0, 1))

    # ---------- Алгоритмы из класса algorithms ----------
    # --- для списка смежности ---
    cc_times_list.append(measure_time(algorithms.find_connected_components, adj_list))
    topo_times_list.append(measure_time(algorithms.topological_sort, adj_list))
    dijkstra_times_list.append(measure_time(algorithms.dijkstra, adj_list, 0))
    # --- для матрицы смежности ---
    cc_times_matrix.append(measure_time(algorithms.find_connected_components_matrix, matrix))
    topo_times_matrix.append(measure_time(algorithms.topological_sort_matrix, matrix))
    dijkstra_times_matrix.append(measure_time(algorithms.dijkstra_matrix, matrix, 0))

# ---------------------- Визуализация ----------------------
# BFS/DFS
plt.figure(figsize=(12, 6))
plt.plot(graph_sizes, bfs_times_matrix, label='BFS Matrix', marker='o')
plt.plot(graph_sizes, bfs_times_list, label='BFS List', marker='o')
plt.plot(graph_sizes, dfs_rec_times_matrix, label='DFS Recursive Matrix', marker='x')
plt.plot(graph_sizes, dfs_rec_times_list, label='DFS Recursive List', marker='x')
plt.plot(graph_sizes, dfs_iter_times_matrix, label='DFS Iterative Matrix', marker='s')
plt.plot(graph_sizes, dfs_iter_times_list, label='DFS Iterative List', marker='s')
plt.xlabel("Размер графа (число вершин)")
plt.ylabel("Время выполнения (сек)")
plt.title("BFS и DFS: матрица vs список")
plt.legend()
plt.grid(True)
plt.show()

# Добавление/удаление ребра
plt.figure(figsize=(12, 6))
plt.plot(graph_sizes, add_edge_times_matrix, label='Add Edge Matrix', marker='o')
plt.plot(graph_sizes, add_edge_times_list, label='Add Edge List', marker='o')
plt.plot(graph_sizes, remove_edge_times_matrix, label='Remove Edge Matrix', marker='x')
plt.plot(graph_sizes, remove_edge_times_list, label='Remove Edge List', marker='x')
plt.xlabel("Размер графа (число вершин)")
plt.ylabel("Время выполнения (сек)")
plt.title("Добавление и удаление ребра")
plt.legend()
plt.grid(True)
plt.show()

# Алгоритмы из класса algorithms
plt.figure(figsize=(12, 6))
plt.plot(graph_sizes, cc_times_matrix, label='Connected Components Matrix', marker='o')
plt.plot(graph_sizes, cc_times_list, label='Connected Components List', marker='o')
plt.plot(graph_sizes, topo_times_matrix, label='Topological Sort Matrix', marker='x')
plt.plot(graph_sizes, topo_times_list, label='Topological Sort List', marker='x')
plt.plot(graph_sizes, dijkstra_times_matrix, label='Dijkstra Matrix', marker='s')
plt.plot(graph_sizes, dijkstra_times_list, label='Dijkstra List', marker='s')
plt.xlabel("Размер графа (число вершин)")
plt.ylabel("Время выполнения (сек)")
plt.title("Алгоритмы из класса algorithms: матрица vs список")
plt.legend()
plt.grid(True)
plt.show()
