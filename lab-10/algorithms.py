from AdjacencyListGraph import AdjacencyListGraph
from AdjacencyMatrixGraph import AdjacencyMatrixGraph

class algorithms:

    # --- для списка смежности ---
    def find_connected_components(graph: AdjacencyListGraph):  # O(n + m)
        n = graph.n
        visited = [False] * n
        components = []

        def dfs_collect(v, component):
            visited[v] = True
            component.append(v)
            for neighbor, _ in graph.adj_list[v]:
                if not visited[neighbor]:
                    dfs_collect(neighbor, component)

        for v in range(n):
            if not visited[v]:
                component = []
                dfs_collect(v, component)
                components.append(component)
        return components

    def topological_sort(graph: AdjacencyListGraph):  # O(n + m)
        visited = [False] * graph.n
        result = []

        def dfs(v):
            visited[v] = True
            for neighbor, _ in graph.adj_list[v]:
                if not visited[neighbor]:
                    dfs(neighbor)
            result.append(v)

        for v in range(graph.n):
            if not visited[v]:
                dfs(v)

        result.reverse()
        return result

    def dijkstra(graph: AdjacencyListGraph, start):  # O(n^2)
        n = graph.n
        visited = [False] * n
        dist = [float('inf')] * n
        dist[start] = 0

        for _ in range(n):
            u = -1
            min_dist = float('inf')
            for i in range(n):
                if not visited[i] and dist[i] < min_dist:
                    min_dist = dist[i]
                    u = i

            if u == -1:
                break

            visited[u] = True

            for v, w in graph.adj_list[u]:
                if dist[u] + w < dist[v]:
                    dist[v] = dist[u] + w

        return dist

    # --- для матрицы смежности ---
    def find_connected_components_matrix(graph: AdjacencyMatrixGraph):  # O(n^2)
        n = graph.n
        visited = [False] * n
        components = []

        def dfs_collect(v, component):
            visited[v] = True
            component.append(v)
            for u in range(n):
                if graph.matrix[v][u] != 0 and not visited[u]:
                    dfs_collect(u, component)

        for v in range(n):
            if not visited[v]:
                component = []
                dfs_collect(v, component)
                components.append(component)
        return components

    def topological_sort_matrix(graph: AdjacencyMatrixGraph):  # O(n^2)
        n = graph.n
        visited = [False] * n
        result = []

        def dfs(v):
            visited[v] = True
            for u in range(n):
                if graph.matrix[v][u] != 0 and not visited[u]:
                    dfs(u)
            result.append(v)

        for v in range(n):
            if not visited[v]:
                dfs(v)

        result.reverse()
        return result

    def dijkstra_matrix(graph: AdjacencyMatrixGraph, start):  # O(n^2)
        n = graph.n
        visited = [False] * n
        dist = [float('inf')] * n
        dist[start] = 0

        for _ in range(n):
            u = -1
            min_dist = float('inf')
            for i in range(n):
                if not visited[i] and dist[i] < min_dist:
                    min_dist = dist[i]
                    u = i

            if u == -1:
                break

            visited[u] = True

            for v in range(n):
                if graph.matrix[u][v] != 0:
                    if dist[u] + graph.matrix[u][v] < dist[v]:
                        dist[v] = dist[u] + graph.matrix[u][v]

        return dist
