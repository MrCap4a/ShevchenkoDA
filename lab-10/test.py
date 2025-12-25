import unittest
from collections import deque

from AdjacencyListGraph import AdjacencyListGraph
from BFS import BFS
from algorithms import algorithms
from RecursiveDFS import RecursiveDFS
from IterativeDFS import IterativeDFS


class TestGraphAlgorithms(unittest.TestCase):

    def setUp(self):
        # Простейший граф для тестов (ориентированный)
        # 0 -> 1 -> 2
        # 0 -> 3
        self.matrix_graph = [
            [0, 1, 0, 1],
            [0, 0, 1, 0],
            [0, 0, 0, 0],
            [0, 0, 0, 0]
        ]
        self.list_graph = [
            [(1, 1), (3, 1)],
            [(2, 1)],
            [],
            []
        ]

        # Граф для AdjacencyListGraph
        self.al_graph = AdjacencyListGraph(4)
        self.al_graph.add_edge(0, 1, 1)
        self.al_graph.add_edge(0, 3, 1)
        self.al_graph.add_edge(1, 2, 1)

        # Граф для топологической сортировки
        self.tsort_graph = AdjacencyListGraph(6)
        self.tsort_graph.add_edge(5, 2, 1)
        self.tsort_graph.add_edge(5, 0, 1)
        self.tsort_graph.add_edge(4, 0, 1)
        self.tsort_graph.add_edge(4, 1, 1)
        self.tsort_graph.add_edge(2, 3, 1)
        self.tsort_graph.add_edge(3, 1, 1)

        # Граф для алгоритма Дейкстры
        self.dijkstra_graph = AdjacencyListGraph(5)
        self.dijkstra_graph.add_edge(0, 1, 10)
        self.dijkstra_graph.add_edge(0, 2, 3)
        self.dijkstra_graph.add_edge(1, 2, 1)
        self.dijkstra_graph.add_edge(1, 3, 2)
        self.dijkstra_graph.add_edge(2, 1, 4)
        self.dijkstra_graph.add_edge(2, 3, 8)
        self.dijkstra_graph.add_edge(2, 4, 2)
        self.dijkstra_graph.add_edge(3, 4, 7)
        self.dijkstra_graph.add_edge(4, 3, 9)

    # ---------------- BFS ----------------
    def test_bfs_matrix(self):
        bfs = BFS(self.matrix_graph, 'matrix')
        distance, paths = bfs.run(0)
        self.assertEqual(distance, [0, 1, 2, 1])
        self.assertEqual(paths[2], [0, 1, 2])

    def test_bfs_list(self):
        bfs = BFS(self.list_graph, 'list')
        distance, paths = bfs.run(0)
        self.assertEqual(distance, [0, 1, 2, 1])
        self.assertEqual(paths[3], [0, 3])

    # ---------------- Iterative DFS ----------------
    def test_iterative_dfs_matrix(self):
        dfs = IterativeDFS(self.matrix_graph, 'matrix')
        order = dfs.run(0)
        self.assertEqual(order, [0, 1, 2, 3])

    def test_iterative_dfs_list(self):
        dfs = IterativeDFS(self.list_graph, 'list')
        order = dfs.run(0)
        self.assertEqual(order, [0, 1, 2, 3])

    # ---------------- Recursive DFS ----------------
    def test_recursive_dfs_matrix(self):
        dfs = RecursiveDFS(self.matrix_graph, 'matrix')
        order = dfs.run(0)
        self.assertEqual(order, [0, 1, 2, 3])

    def test_recursive_dfs_list(self):
        dfs = RecursiveDFS(self.list_graph, 'list')
        order = dfs.run(0)
        self.assertEqual(order, [0, 1, 2, 3])

    # ---------------- Connected Components ----------------
    def test_connected_components(self):
        components = algorithms.find_connected_components(self.al_graph)
        self.assertEqual(len(components), 1)
        self.assertListEqual(sorted(components[0]), [0, 1, 2, 3])

    # ---------------- Topological Sort ----------------
    def test_topological_sort(self):
        result = algorithms.topological_sort(self.tsort_graph)
        # Проверяем, что каждый предок идёт перед потомком
        self.assertTrue(result.index(5) < result.index(2))
        self.assertTrue(result.index(5) < result.index(0))
        self.assertTrue(result.index(4) < result.index(0))
        self.assertTrue(result.index(4) < result.index(1))
        self.assertTrue(result.index(2) < result.index(3))
        self.assertTrue(result.index(3) < result.index(1))

    # ---------------- Dijkstra ----------------
    def test_dijkstra(self):
        dist = algorithms.dijkstra(self.dijkstra_graph, 0)
        self.assertEqual(dist, [0, 7, 3, 9, 5])


if __name__ == '__main__':
    unittest.main()
