import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class TopologicalSort {
    
    // Основной метод для топологической сортировки
    // Использует DFS для построения порядка
    public static List<Integer> topologicalSort(AdjList graph) {
        int n = graph.getElementCount();
        boolean[] visited = new boolean[n];
        Stack<Integer> stack = new Stack<>();
        
        // Проходим по всем вершинам
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(graph, i, visited, stack);
            }
        }
        
        // Переносим элементы из стека в список для возврата
        List<Integer> result = new ArrayList<>();
        while (!stack.isEmpty()) {
            result.add(stack.pop());
        }
        
        return result;
    }
    
    // Вспомогательный метод DFS для топологической сортировки
    private static void dfs(AdjList graph, int vertex, boolean[] visited, Stack<Integer> stack) {
        visited[vertex] = true;
        
        // Обрабатываем всех соседей текущей вершины
        for (int neighbor = 0; neighbor < graph.getElementCount(); neighbor++) {
            // Если есть ребро из vertex в neighbor и сосед еще не посещен
            if (graph.getEdge(vertex, neighbor) > 0 && !visited[neighbor]) {
                dfs(graph, neighbor, visited, stack);
            }
        }
        
        // Добавляем вершину в стек после обработки всех её потомков
        stack.push(vertex);
    }
    
    // Метод для печати результата
    public static void printOrder(List<Integer> order) {
        System.out.println("Топологический порядок:");
        for (int i = 0; i < order.size(); i++) {
            System.out.print(order.get(i));
            if (i < order.size() - 1) {
                System.out.print(" -> ");
            }
        }
        System.out.println();
    }
}