from tracemalloc import start
from AdjacencyListGraph import AdjacencyListGraph
from BFS import BFS


class tasks:
    def shortest_path_in_maze(maze, start, end):
        rows = len(maze)
        cols = len(maze[0])

        def cell_to_vertex(r, c):
            return r * cols + c
        def vertex_to_cell(v):
            return v // cols, v % cols

        # создаём граф
        graph = AdjacencyListGraph(rows * cols)
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

        for r in range(rows):
            for c in range(cols):
                if maze[r][c] == 0:
                    v = cell_to_vertex(r, c)

                    for dr, dc in directions:
                        nr, nc = r + dr, c + dc
                        if 0 <= nr < rows and 0 <= nc < cols:
                            if maze[nr][nc] == 0:
                                u = cell_to_vertex(nr, nc)
                                graph.add_edge(v, u, 1)

        start_v = cell_to_vertex(*start)
        end_v = cell_to_vertex(*end)

        bfs = BFS(graph.adj_list, 'list')
        distances, paths = bfs.run(start_v)
        if paths[end_v] is None:
            return None, -1

        path_cells = [vertex_to_cell(v) for v in paths[end_v]]
        return path_cells, distances[end_v]

maze = [
    [0, 1, 0, 0],
    [0, 1, 0, 1],
    [0, 0, 0, 0],
    [1, 1, 1, 0]
]

start = (0, 0)
end = (2, 3)

path, length = tasks.shortest_path_in_maze(maze, start, end)

print("Путь:", path)
print("Длина:", length)
