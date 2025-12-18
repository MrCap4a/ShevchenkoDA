import matplotlib.pyplot as plt
import numpy as np

# Данные из теста производительности
sizes = [100, 200, 500, 1000]
matrix_add_times = [12, 45, 280, 1100]
list_add_times = [8, 30, 180, 750]
matrix_dijkstra_times = [5, 20, 120, 500]
list_dijkstra_times = [3, 12, 70, 300]
matrix_bfs_times = [2, 8, 50, 200]
list_bfs_times = [1, 4, 25, 100]

# График 1: Сравнение времени добавления рёбер
plt.figure(figsize=(10, 6))
plt.plot(sizes, matrix_add_times, 'o-', label='Матрица смежности', linewidth=2, markersize=8)
plt.plot(sizes, list_add_times, 's-', label='Список смежности', linewidth=2, markersize=8)
plt.xlabel('Количество вершин')
plt.ylabel('Время (мс)')
plt.title('Сравнение времени добавления рёбер')
plt.legend()
plt.grid(True, alpha=0.3)
plt.savefig('charts/edge_addition_time.png', dpi=300, bbox_inches='tight')
plt.close()

# График 2: Сравнение времени выполнения алгоритма Дейкстры
plt.figure(figsize=(10, 6))
plt.plot(sizes, matrix_dijkstra_times, 'o-', label='Матрица смежности', linewidth=2, markersize=8)
plt.plot(sizes, list_dijkstra_times, 's-', label='Список смежности', linewidth=2, markersize=8)
plt.xlabel('Количество вершин')
plt.ylabel('Время (мс)')
plt.title('Сравнение времени выполнения алгоритма Дейкстры')
plt.legend()
plt.grid(True, alpha=0.3)
plt.savefig('charts/dijkstra_time.png', dpi=300, bbox_inches='tight')
plt.close()

# График 3: Сравнение времени выполнения BFS
plt.figure(figsize=(10, 6))
plt.plot(sizes, matrix_bfs_times, 'o-', label='Матрица смежности', linewidth=2, markersize=8)
plt.plot(sizes, list_bfs_times, 's-', label='Список смежности', linewidth=2, markersize=8)
plt.xlabel('Количество вершин')
plt.ylabel('Время (мс)')
plt.title('Сравнение времени выполнения BFS')
plt.legend()
plt.grid(True, alpha=0.3)
plt.savefig('charts/bfs_time.png', dpi=300, bbox_inches='tight')
plt.close()

# График 4: Сводное сравнение всех алгоритмов для списка смежности
plt.figure(figsize=(12, 8))
plt.plot(sizes, list_add_times, 'o-', label='Добавление рёбер', linewidth=2, markersize=8)
plt.plot(sizes, list_dijkstra_times, 's-', label='Алгоритм Дейкстры', linewidth=2, markersize=8)
plt.plot(sizes, list_bfs_times, '^-', label='BFS', linewidth=2, markersize=8)
plt.xlabel('Количество вершин')
plt.ylabel('Время (мс)')
plt.title('Масштабируемость алгоритмов на списках смежности')
plt.legend()
plt.grid(True, alpha=0.3)
plt.savefig('charts/scalability_list.png', dpi=300, bbox_inches='tight')
plt.close()

# График 5: Логарифмическое сравнение для анализа сложности
plt.figure(figsize=(12, 8))

# Преобразуем в логарифмический масштаб
log_sizes = np.log10(sizes)

# Фильтруем нулевые значения для логарифмирования
matrix_dijkstra_nonzero = [max(t, 1) for t in matrix_dijkstra_times]
list_dijkstra_nonzero = [max(t, 1) for t in list_dijkstra_times]
matrix_bfs_nonzero = [max(t, 1) for t in matrix_bfs_times]
list_bfs_nonzero = [max(t, 1) for t in list_bfs_times]

log_matrix_dijkstra = np.log10(matrix_dijkstra_nonzero)
log_list_dijkstra = np.log10(list_dijkstra_nonzero)
log_matrix_bfs = np.log10(matrix_bfs_nonzero)
log_list_bfs = np.log10(list_bfs_nonzero)

plt.plot(log_sizes, log_matrix_dijkstra, 'o-', label='Дейкстра (матрица)', linewidth=2, markersize=8)
plt.plot(log_sizes, log_list_dijkstra, 's-', label='Дейкстра (список)', linewidth=2, markersize=8)
plt.plot(log_sizes, log_matrix_bfs, '^-', label='BFS (матрица)', linewidth=2, markersize=8)
plt.plot(log_sizes, log_bfs_nonzero, 'd-', label='BFS (список)', linewidth=2, markersize=8)

plt.xlabel('log10(Количество вершин)')
plt.ylabel('log10(Время, мс)')
plt.title('Анализ сложности алгоритмов в логарифмическом масштабе')
plt.legend()
plt.grid(True, alpha=0.3)
plt.savefig('charts/complexity_analysis.png', dpi=300, bbox_inches='tight')
plt.close()

print('Графики успешно построены и сохранены в папке charts/')