import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class GraphTasks {
    private static final Random random = new Random();

    /**
     * Задание 1: Найти кратчайший путь в лабиринте
     * Лабиринт моделируется как взвешенный направленный граф
     */
    public static void shortestPathInMaze() {
        System.out.println("=== Задание 1: Кратчайший путь в лабиринте ===");
        
        // Создаем граф для лабиринта (10 вершин)
        AdjList maze = new AdjList(10);
        
        // Генерируем случайные рёбра (лабиринт)
        for (int i = 0; i < 15; i++) {
            int from = random.nextInt(10);
            int to = random.nextInt(10);
            int weight = random.nextInt(10) + 1; // вес от 1 до 10
            if (from != to) {
                maze.addEdge(from, to, weight);
            }
        }
        
        int start = 0, end = 9;
        System.out.println("Лабиринт создан: " + 10 + " комнат, " + 15 + " переходов");
        System.out.println("Ищем путь от комнаты " + start + " до комнаты " + end + ":");
        
        // Используем Дейкстру для поиска кратчайшего пути
        Dijkstra.Result result = Dijkstra.shortestPath(maze, start);
        List<Integer> path = Dijkstra.getPath(result.previous, start, end);
        
        Dijkstra.printPath(path, start, end);
        if (!path.isEmpty()) {
            System.out.println("Длина пути: " + result.distances[end]);
        }
        System.out.println();
    }
    
    /**
     * Задание 2: Определить связность сети
     * Сеть моделируется как направленный граф
     */
    public static void checkNetworkConnectivity() {
        System.out.println("=== Задание 2: Определение связности сети ===");
        
        // Создаем граф для сети (8 узлов)
        AdjMatrix network = new AdjMatrix(8);
        
        // Генерируем случайные соединения
        for (int i = 0; i < 20; i++) {
            int from = random.nextInt(8);
            int to = random.nextInt(8);
            if (from != to) {
                network.addEdge(from, to, 1);
            }
        }
        
        System.out.println("Сеть создана: " + 8 + " узлов, " + 20 + " соединений");
        
        // Проверяем связность
        List<List<Integer>> components = Connectivity.findConnectedComponentsMatrix(network);
        boolean isConnected = Connectivity.isConnectedMatrix(network);
        
        System.out.println("Сеть " + (isConnected ? "связна" : "не связна"));
        Connectivity.printComponents(components);
        System.out.println();
    }
    
    /**
     * Задание 3: Решить задачу на топологическую сортировку
     * Задачи моделируются как направленный ациклический граф
     */
    public static void solveTopologicalTask() {
        System.out.println("=== Задание 3: Топологическая сортировка ===");
        
        // Создаем граф для задач (7 задач с зависимостями)
        AdjList tasks = new AdjList(7);
        
        // Генерируем случайные зависимости (ациклические)
        // Гарантируем ацикличность, соединяя только от меньших индексов к большим
        List<int[]> edges = new ArrayList<>();
        for (int i = 0; i < 7; i++) {
            for (int j = i + 1; j < 7; j++) {
                if (random.nextDouble() < 0.3) { // 30% вероятность зависимости
                    edges.add(new int[]{i, j});
                }
            }
        }
        
        // Перемешиваем и добавляем рёбра
        for (int[] edge : edges) {
            tasks.addEdge(edge[0], edge[1], 1);
        }
        
        System.out.println("Граф задач создан: " + 7 + " задач, " + edges.size() + " зависимостей");
        System.out.println("Зависимости:");
        for (int[] edge : edges) {
            System.out.println("  Задача " + edge[0] + " -> Задача " + edge[1]);
        }
        
        // Выполняем топологическую сортировку
        List<Integer> order = TopologicalSort.topologicalSort(tasks);
        TopologicalSort.printOrder(order);
    }
    
    // Метод для запуска всех заданий
    public static void runAllTasks() {
        shortestPathInMaze();
        checkNetworkConnectivity();
        solveTopologicalTask();
    }
}