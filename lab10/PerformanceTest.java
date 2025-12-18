import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class PerformanceTest {
    private static final Random random = new Random();
    
    // Тест производительности для разных операций
    public static void runPerformanceTest() {
        System.out.println("=== Тест производительности представлений графов ===");
        
        // Размеры графов для тестирования
        int[] sizes = {100, 200, 500, 1000};
        
        // Списки для хранения времени выполнения
        List<Integer> graphSizes = new ArrayList<>();
        List<Long> matrixAddTimes = new ArrayList<>();
        List<Long> listAddTimes = new ArrayList<>();
        List<Long> matrixDijkstraTimes = new ArrayList<>();
        List<Long> listDijkstraTimes = new ArrayList<>();
        List<Long> matrixBFSTimes = new ArrayList<>();
        List<Long> listBFSTimes = new ArrayList<>();
        
        for (int size : sizes) {
            System.out.println("\nТестирование графа размером " + size + " вершин...");
            
            // Создаем графы
            AdjMatrix matrixGraph = new AdjMatrix(size);
            AdjList listGraph = new AdjList(size);
            
            // Заполняем графы случайными рёбрами (плотность ~10%)
            int edgeCount = (int) (size * size * 0.1);
            
            // Тест добавления рёбер в матрицу
            long start = System.nanoTime();
            for (int i = 0; i < edgeCount; i++) {
                int from = random.nextInt(size);
                int to = random.nextInt(size);
                int weight = random.nextInt(10) + 1;
                if (from != to) {
                    matrixGraph.addEdge(from, to, weight);
                }
            }
            long matrixAddTime = (System.nanoTime() - start) / 1000000; // в миллисекундах
            
            // Тест добавления рёбер в список
            start = System.nanoTime();
            for (int i = 0; i < edgeCount; i++) {
                int from = random.nextInt(size);
                int to = random.nextInt(size);
                int weight = random.nextInt(10) + 1;
                if (from != to) {
                    listGraph.addEdge(from, to, weight);
                }
            }
            long listAddTime = (System.nanoTime() - start) / 1000000; // в миллисекундах
            
            // Тест алгоритма Дейкстры
            int startVertex = 0;
            
            start = System.nanoTime();
            Dijkstra.shortestPath(matrixGraph, startVertex);
            long matrixDijkstraTime = (System.nanoTime() - start) / 1000000;
            
            start = System.nanoTime();
            Dijkstra.shortestPath(listGraph, startVertex);
            long listDijkstraTime = (System.nanoTime() - start) / 1000000;
            
            // Тест BFS
            start = System.nanoTime();
            BFS.bfsMatrix(matrixGraph, startVertex);
            long matrixBFSTime = (System.nanoTime() - start) / 1000000;
            
            start = System.nanoTime();
            BFS.bfsList(listGraph, startVertex);
            long listBFSTime = (System.nanoTime() - start) / 1000000;
            
            // Сохраняем результаты
            graphSizes.add(size);
            matrixAddTimes.add(matrixAddTime);
            listAddTimes.add(listAddTime);
            matrixDijkstraTimes.add(matrixDijkstraTime);
            listDijkstraTimes.add(listDijkstraTime);
            matrixBFSTimes.add(matrixBFSTime);
            listBFSTimes.add(listBFSTime);
            
            // Выводим промежуточные результаты
            System.out.println("Добавление рёбер:");
            System.out.println("  Матрица: " + matrixAddTime + " ms");
            System.out.println("  Список: " + listAddTime + " ms");
            System.out.println("Алгоритм Дейкстры:");
            System.out.println("  Матрица: " + matrixDijkstraTime + " ms");
            System.out.println("  Список: " + listDijkstraTime + " ms");
            System.out.println("BFS:");
            System.out.println("  Матрица: " + matrixBFSTime + " ms");
            System.out.println("  Список: " + listBFSTime + " ms");
        }
        
        // Генерируем Python-скрипт для построения графиков
        generatePlotScript(graphSizes, matrixAddTimes, listAddTimes, 
                          matrixDijkstraTimes, listDijkstraTimes,
                          matrixBFSTimes, listBFSTimes);
        
        System.out.println("\nТест завершен. Генерируется скрипт для построения графиков...");
    }
    
    // Генерация Python-скрипта для построения графиков
    private static void generatePlotScript(List<Integer> sizes,
                                         List<Long> matrixAddTimes, List<Long> listAddTimes,
                                         List<Long> matrixDijkstraTimes, List<Long> listDijkstraTimes,
                                         List<Long> matrixBFSTimes, List<Long> listBFSTimes) {
        StringBuilder script = new StringBuilder();
        script.append("import matplotlib.pyplot as plt\n");
        script.append("import numpy as np\n");
        script.append("\n");
        script.append("# Данные из теста производительности\n");
        
        // Преобразуем списки в строковые представления массивов
        script.append("sizes = ").append(sizes.toString()).append("\n");
        script.append("matrix_add_times = ").append(matrixAddTimes.toString()).append("\n");
        script.append("list_add_times = ").append(listAddTimes.toString()).append("\n");
        script.append("matrix_dijkstra_times = ").append(matrixDijkstraTimes.toString()).append("\n");
        script.append("list_dijkstra_times = ").append(listDijkstraTimes.toString()).append("\n");
        script.append("matrix_bfs_times = ").append(matrixBFSTimes.toString()).append("\n");
        script.append("list_bfs_times = ").append(listBFSTimes.toString()).append("\n");
        script.append("\n");
        
        // Построение графика для добавления рёбер
        script.append("# График 1: Сравнение времени добавления рёбер\n");
        script.append("plt.figure(figsize=(10, 6))\n");
        script.append("plt.plot(sizes, matrix_add_times, 'o-', label='Матрица смежности', linewidth=2, markersize=8)\n");
        script.append("plt.plot(sizes, list_add_times, 's-', label='Список смежности', linewidth=2, markersize=8)\n");
        script.append("plt.xlabel('Количество вершин')\n");
        script.append("plt.ylabel('Время (мс)')\n");
        script.append("plt.title('Сравнение времени добавления рёбер')\n");
        script.append("plt.legend()\n");
        script.append("plt.grid(True, alpha=0.3)\n");
        script.append("plt.savefig('charts/edge_addition_time.png', dpi=300, bbox_inches='tight')\n");
        script.append("plt.close()\n");
        script.append("\n");
        
        // Построение графика для алгоритма Дейкстры
        script.append("# График 2: Сравнение времени выполнения алгоритма Дейкстры\n");
        script.append("plt.figure(figsize=(10, 6))\n");
        script.append("plt.plot(sizes, matrix_dijkstra_times, 'o-', label='Матрица смежности', linewidth=2, markersize=8)\n");
        script.append("plt.plot(sizes, list_dijkstra_times, 's-', label='Список смежности', linewidth=2, markersize=8)\n");
        script.append("plt.xlabel('Количество вершин')\n");
        script.append("plt.ylabel('Время (мс)')\n");
        script.append("plt.title('Сравнение времени выполнения алгоритма Дейкстры')\n");
        script.append("plt.legend()\n");
        script.append("plt.grid(True, alpha=0.3)\n");
        script.append("plt.savefig('charts/dijkstra_time.png', dpi=300, bbox_inches='tight')\n");
        script.append("plt.close()\n");
        script.append("\n");
        
        // Построение графика для BFS
        script.append("# График 3: Сравнение времени выполнения BFS\n");
        script.append("plt.figure(figsize=(10, 6))\n");
        script.append("plt.plot(sizes, matrix_bfs_times, 'o-', label='Матрица смежности', linewidth=2, markersize=8)\n");
        script.append("plt.plot(sizes, list_bfs_times, 's-', label='Список смежности', linewidth=2, markersize=8)\n");
        script.append("plt.xlabel('Количество вершин')\n");
        script.append("plt.ylabel('Время (мс)')\n");
        script.append("plt.title('Сравнение времени выполнения BFS')\n");
        script.append("plt.legend()\n");
        script.append("plt.grid(True, alpha=0.3)\n");
        script.append("plt.savefig('charts/bfs_time.png', dpi=300, bbox_inches='tight')\n");
        script.append("plt.close()\n");
        script.append("\n");
        
        // Построение сводного графика
        script.append("# График 4: Сводное сравнение всех алгоритмов для списка смежности\n");
        script.append("plt.figure(figsize=(12, 8))\n");
        script.append("plt.plot(sizes, list_add_times, 'o-', label='Добавление рёбер', linewidth=2, markersize=8)\n");
        script.append("plt.plot(sizes, list_dijkstra_times, 's-', label='Алгоритм Дейкстры', linewidth=2, markersize=8)\n");
        script.append("plt.plot(sizes, list_bfs_times, '^-', label='BFS', linewidth=2, markersize=8)\n");
        script.append("plt.xlabel('Количество вершин')\n");
        script.append("plt.ylabel('Время (мс)')\n");
        script.append("plt.title('Масштабируемость алгоритмов на списках смежности')\n");
        script.append("plt.legend()\n");
        script.append("plt.grid(True, alpha=0.3)\n");
        script.append("plt.savefig('charts/scalability_list.png', dpi=300, bbox_inches='tight')\n");
        script.append("plt.close()\n");
        script.append("\n");
        
        // Построение логарифмического графика для анализа сложности
        script.append("# График 5: Логарифмическое сравнение для анализа сложности\n");
        script.append("plt.figure(figsize=(12, 8))\n");
        script.append("\n");
        script.append("# Преобразуем в логарифмический масштаб\n");
        script.append("log_sizes = np.log10(sizes)\n");
        script.append("\n");
        script.append("# Фильтруем нулевые значения для логарифмирования\n");
        script.append("matrix_dijkstra_nonzero = [max(t, 1) for t in matrix_dijkstra_times]\n");
        script.append("list_dijkstra_nonzero = [max(t, 1) for t in list_dijkstra_times]\n");
        script.append("matrix_bfs_nonzero = [max(t, 1) for t in matrix_bfs_times]\n");
        script.append("list_bfs_nonzero = [max(t, 1) for t in list_bfs_times]\n");
        script.append("\n");
        script.append("log_matrix_dijkstra = np.log10(matrix_dijkstra_nonzero)\n");
        script.append("log_list_dijkstra = np.log10(list_dijkstra_nonzero)\n");
        script.append("log_matrix_bfs = np.log10(matrix_bfs_nonzero)\n");
        script.append("log_list_bfs = np.log10(list_bfs_nonzero)\n");
        script.append("\n");
        script.append("plt.plot(log_sizes, log_matrix_dijkstra, 'o-', label='Дейкстра (матрица)', linewidth=2, markersize=8)\n");
        script.append("plt.plot(log_sizes, log_list_dijkstra, 's-', label='Дейкстра (список)', linewidth=2, markersize=8)\n");
        script.append("plt.plot(log_sizes, log_matrix_bfs, '^-', label='BFS (матрица)', linewidth=2, markersize=8)\n");
        script.append("plt.plot(log_sizes, log_list_bfs, 'd-', label='BFS (список)', linewidth=2, markersize=8)\n");
        script.append("\n");
        script.append("plt.xlabel('log10(Количество вершин)')\n");
        script.append("plt.ylabel('log10(Время, мс)')\n");
        script.append("plt.title('Анализ сложности алгоритмов в логарифмическом масштабе')\n");
        script.append("plt.legend()\n");
        script.append("plt.grid(True, alpha=0.3)\n");
        script.append("plt.savefig('charts/complexity_analysis.png', dpi=300, bbox_inches='tight')\n");
        script.append("plt.close()\n");
        script.append("\n");
        script.append("print('Графики успешно построены и сохранены в папке charts/')\n");

        // Сохраняем скрипт
        write_to_file("/home/skmrh/IdeaProjects/ShevchenkoDA/lab10/plot_performance.py", script.toString());
    }
    
    // Метод для записи в файл (аналог Python-функции)
    private static void write_to_file(String path, String content) {
        try {
            java.nio.file.Files.write(java.nio.file.Paths.get(path), content.getBytes());
        } catch (Exception e) {
            System.err.println("Ошибка при записи файла: " + e.getMessage());
        }
    }
    
    // Метод для запуска теста и генерации графиков
    public static void main(String[] args) {
        runPerformanceTest();
        
        // Запускаем Python-скрипт для построения графиков
        try {
            Process process = Runtime.getRuntime().exec(
                "/home/skmrh/IdeaProjects/ShevchenkoDA/lab10/venv/bin/python plot_performance.py");
            
            // Ждем завершения процесса
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Графики успешно построены!");
            } else {
                System.out.println("Ошибка при построении графиков");
            }
        } catch (Exception e) {
            System.err.println("Ошибка при запуске Python-скрипта: " + e.getMessage());
            System.out.println("Вы можете вручную запустить: \nsource venv/bin/activate && python plot_performance.py");
        }
    }
}