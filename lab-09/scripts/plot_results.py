import json
import os
import re
import matplotlib.pyplot as plt

INPUT_FILE = "./results/benchmark_results.json"
OUTPUT_DIR = "./results"

def parse_size(name):
    nums = re.findall(r"\d+", name)
    return int(nums[0]) if nums else None

def load_iterations():
    with open(INPUT_FILE, "r") as f:
        data = json.load(f)["benchmarks"]

    result = {}

    for b in data:
        if b.get("run_type") != "iteration":
            continue

        name = b["name"]
        size = parse_size(name)
        if size is None:
            continue

        family = name.split("/")[0]
        result.setdefault(family, []).append((size, b["real_time"]))

    for k in result:
        result[k].sort()

    return result

def plot_comparison(title, data1, data2, label1, label2, filename):
    plt.figure(figsize=(10, 6))
    
    if data1:
        x1, y1 = zip(*data1)
        plt.plot(x1, y1, marker="o", label=label1, linewidth=2)
    
    if data2:
        x2, y2 = zip(*data2)
        plt.plot(x2, y2, marker="s", label=label2, linewidth=2)

    plt.xlabel("Размер входных данных", fontsize=12)
    plt.ylabel("Время выполнения (нс)", fontsize=12)
    plt.title(title, fontsize=14, fontweight="bold")
    plt.legend(fontsize=10)
    plt.grid(True, alpha=0.3)
    plt.tight_layout()

    os.makedirs(OUTPUT_DIR, exist_ok=True)
    plt.savefig(os.path.join(OUTPUT_DIR, filename), format="svg", bbox_inches="tight")
    plt.close()

def plot_single(title, data, filename):
    plt.figure(figsize=(10, 6))
    
    if data:
        x, y = zip(*data)
        plt.plot(x, y, marker="o", linewidth=2)

    plt.xlabel("Размер входных данных", fontsize=12)
    plt.ylabel("Время выполнения (нс)", fontsize=12)
    plt.title(title, fontsize=14, fontweight="bold")
    plt.grid(True, alpha=0.3)
    plt.tight_layout()

    os.makedirs(OUTPUT_DIR, exist_ok=True)
    plt.savefig(os.path.join(OUTPUT_DIR, filename), format="svg", bbox_inches="tight")
    plt.close()

def main():
    data = load_iterations()

    if "BM_FibonacciMemoization" in data and "BM_FibonacciIterative" in data:
        plot_comparison(
            "Числа Фибоначчи: сравнение подходов",
            data.get("BM_FibonacciMemoization", []),
            data.get("BM_FibonacciIterative", []),
            "Мемоизация (Top-Down)",
            "Итеративный (Bottom-Up)",
            "fibonacci_comparison.svg"
        )

    if "BM_Knapsack01" in data and "BM_Knapsack01Optimized" in data:
        plot_comparison(
            "Задача о рюкзаке: сравнение версий",
            data.get("BM_Knapsack01", []),
            data.get("BM_Knapsack01Optimized", []),
            "2D массив",
            "1D массив (оптимизированная)",
            "knapsack_comparison.svg"
        )

    if "BM_LCSLength" in data and "BM_LCSLengthOptimized" in data:
        plot_comparison(
            "LCS: сравнение версий",
            data.get("BM_LCSLength", []),
            data.get("BM_LCSLengthOptimized", []),
            "2D массив",
            "1D массив (оптимизированная)",
            "lcs_comparison.svg"
        )

    if "BM_Levenshtein" in data and "BM_LevenshteinOptimized" in data:
        plot_comparison(
            "Расстояние Левенштейна: сравнение версий",
            data.get("BM_Levenshtein", []),
            data.get("BM_LevenshteinOptimized", []),
            "2D массив",
            "1D массив (оптимизированная)",
            "levenshtein_comparison.svg"
        )

    if "BM_LISLength" in data and "BM_LISLengthOptimized" in data:
        plot_comparison(
            "LIS: сравнение версий",
            data.get("BM_LISLength", []),
            data.get("BM_LISLengthOptimized", []),
            "O(n²) алгоритм",
            "O(n log n) алгоритм",
            "lis_comparison.svg"
        )

    if "BM_CoinChangeMin" in data:
        plot_single(
            "Размен монет: минимальное количество",
            data.get("BM_CoinChangeMin", []),
            "coin_change.svg"
        )

if __name__ == "__main__":
    main()
