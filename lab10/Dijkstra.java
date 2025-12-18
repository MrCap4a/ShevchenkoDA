import java.util.*;

public class Dijkstra {
    
    // Результат алгоритма Дейкстры
    public static class Result {
        public final int[] distances;
        public final int[] previous;
        
        public Result(int[] distances, int[] previous) {
            this.distances = distances;
            this.previous = previous;
        }
    }
    
    // Основной метод для алгоритма Дейкстры - работает с матрицей смежности
    public static Result shortestPath(AdjMatrix graph, int start) {
        int n = graph.getElementCount();
        int[] distances = new int[n];
        int[] previous = new int[n];
        boolean[] visited = new boolean[n];
        
        // Инициализация
        Arrays.fill(distances, Integer.MAX_VALUE);
        Arrays.fill(previous, -1);
        distances[start] = 0;
        
        // Используем PriorityQueue как в BFS, но с приоритетом по расстоянию
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> Integer.compare(a[1], b[1]));
        pq.add(new int[]{start, 0});
        
        while (!pq.isEmpty()) {
            int current = pq.poll()[0];
            
            if (visited[current]) continue;
            visited[current] = true;
            
            // Обрабатываем всех соседей
            for (int neighbor = 0; neighbor < n; neighbor++) {
                int weight = graph.getEdge(current, neighbor);
                if (weight > 0 && !visited[neighbor]) {
                    int newDistance = distances[current] + weight;
                    
                    if (newDistance < distances[neighbor]) {
                        distances[neighbor] = newDistance;
                        previous[neighbor] = current;
                        pq.add(new int[]{neighbor, newDistance});
                    }
                }
            }
        }
        
        return new Result(distances, previous);
    }
    
    // Основной метод для алгоритма Дейкстры - работает со списком смежности
    public static Result shortestPath(AdjList graph, int start) {
        int n = graph.getElementCount();
        int[] distances = new int[n];
        int[] previous = new int[n];
        boolean[] visited = new boolean[n];
        
        // Инициализация
        Arrays.fill(distances, Integer.MAX_VALUE);
        Arrays.fill(previous, -1);
        distances[start] = 0;
        
        // Используем PriorityQueue как в BFS, но с приоритетом по расстоянию
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> Integer.compare(a[1], b[1]));
        pq.add(new int[]{start, 0});
        
        while (!pq.isEmpty()) {
            int current = pq.poll()[0];
            
            if (visited[current]) continue;
            visited[current] = true;
            
            // Обрабатываем всех соседей
            for (int neighbor = 0; neighbor < n; neighbor++) {
                int weight = graph.getEdge(current, neighbor);
                if (weight > 0 && !visited[neighbor]) {
                    int newDistance = distances[current] + weight;
                    
                    if (newDistance < distances[neighbor]) {
                        distances[neighbor] = newDistance;
                        previous[neighbor] = current;
                        pq.add(new int[]{neighbor, newDistance});
                    }
                }
            }
        }
        
        return new Result(distances, previous);
    }
    
    // Восстановление пути от start до end
    public static List<Integer> getPath(int[] previous, int start, int end) {
        List<Integer> path = new ArrayList<>();
        for (int v = end; v != -1; v = previous[v]) {
            path.add(v);
        }
        Collections.reverse(path);
        
        // Проверяем, достижима ли цель
        if (path.get(0) != start) {
            return new ArrayList<>(); // Путь не существует
        }
        
        return path;
    }
    
    // Печать результатов
    public static void printResult(Result result, int start) {
        System.out.println("Кратчайшие расстояния от вершины " + start + ":");
        for (int i = 0; i < result.distances.length; i++) {
            if (result.distances[i] == Integer.MAX_VALUE) {
                System.out.println("Вершина " + i + ": недостижима");
            } else {
                System.out.println("Вершина " + i + ": " + result.distances[i]);
            }
        }
    }
    
    // Печать пути
    public static void printPath(List<Integer> path, int start, int end) {
        System.out.println("Путь от " + start + " до " + end + ":");
        if (path.isEmpty()) {
            System.out.println("Путь не существует");
            return;
        }
        
        for (int i = 0; i < path.size(); i++) {
            System.out.print(path.get(i));
            if (i < path.size() - 1) {
                System.out.print(" -> ");
            }
        }
        System.out.println();
    }
}