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
        plt.plot(x1, y1, marker="o", label=label1, linewidth=2, markersize=6)
    
    if data2:
        x2, y2 = zip(*data2)
        plt.plot(x2, y2, marker="s", label=label2, linewidth=2, markersize=6)

    plt.xlabel("Размер входных данных", fontsize=12)
    plt.ylabel("Время (нс)", fontsize=12)
    plt.title(title, fontsize=14, fontweight="bold")
    plt.legend(fontsize=11)
    plt.grid(True, alpha=0.3)
    plt.loglog()
    # plt.xscale("log", base=2)
    # plt.yscale("log")

    os.makedirs(OUTPUT_DIR, exist_ok=True)
    plt.savefig(os.path.join(OUTPUT_DIR, filename), format="svg", bbox_inches="tight", dpi=300)
    plt.close()


def plot_single(title, data, filename):
    plt.figure(figsize=(10, 6))

    if data:
        x, y = zip(*data)
        plt.plot(x, y, marker="o", linewidth=2, markersize=6)

    plt.xlabel("Размер входных данных", fontsize=12)
    plt.ylabel("Время (нс)", fontsize=12)
    plt.title(title, fontsize=14, fontweight="bold")
    plt.grid(True, alpha=0.3)
    plt.loglog()
    # plt.xscale("log", base=2)
    # plt.yscale("log")

    os.makedirs(OUTPUT_DIR, exist_ok=True)
    plt.savefig(os.path.join(OUTPUT_DIR, filename), format="svg", bbox_inches="tight", dpi=300)
    plt.close()


def main():
    data = load_iterations()

    # Объединенный график всех операций
    if "BM_InsertSequential" in data or "BM_BuildHeap" in data or "BM_Extract" in data or "BM_Heapsort" in data:
        plt.figure(figsize=(12, 8))
        
        markers = ["o", "s", "^", "D", "v", "<", ">"]
        colors = ["#1f77b4", "#ff7f0e", "#2ca02c", "#d62728", "#9467bd", "#8c564b", "#e377c2"]
        
        plot_idx = 0
        if "BM_InsertSequential" in data:
            x, y = zip(*data["BM_InsertSequential"])
            plt.plot(x, y, marker=markers[plot_idx % len(markers)], 
                    color=colors[plot_idx % len(colors)],
                    label="Вставка (O(n log n))", linewidth=2, markersize=6)
            plot_idx += 1
        
        if "BM_BuildHeap" in data:
            x, y = zip(*data["BM_BuildHeap"])
            plt.plot(x, y, marker=markers[plot_idx % len(markers)], 
                    color=colors[plot_idx % len(colors)],
                    label="Построение кучи (O(n))", linewidth=2, markersize=6)
            plot_idx += 1
        
        if "BM_Extract" in data:
            x, y = zip(*data["BM_Extract"])
            plt.plot(x, y, marker=markers[plot_idx % len(markers)], 
                    color=colors[plot_idx % len(colors)],
                    label="Извлечение (O(n log n))", linewidth=2, markersize=6)
            plot_idx += 1
        
        if "BM_Heapsort" in data:
            x, y = zip(*data["BM_Heapsort"])
            plt.plot(x, y, marker=markers[plot_idx % len(markers)], 
                    color=colors[plot_idx % len(colors)],
                    label="Heapsort (O(n log n))", linewidth=2, markersize=6)
            plot_idx += 1
        
        plt.xlabel("Размер входных данных", fontsize=12)
        plt.ylabel("Время (нс)", fontsize=12)
        plt.title("Сравнение производительности операций с кучей", fontsize=14, fontweight="bold")
        plt.legend(fontsize=11, loc="upper left")
        plt.grid(True, alpha=0.3)
        plt.loglog()
        # plt.xscale("log", base=2)
        # plt.yscale("log")
        
        os.makedirs(OUTPUT_DIR, exist_ok=True)
        plt.savefig(os.path.join(OUTPUT_DIR, "operations_comparison.svg"), format="svg", bbox_inches="tight", dpi=300)
        plt.close()

    # Сравнение методов построения кучи
    if "BM_InsertSequential" in data and "BM_BuildHeap" in data:
        plot_comparison(
            "Сравнение методов построения кучи",
            data["BM_InsertSequential"],
            data["BM_BuildHeap"],
            "Последовательная вставка (O(n log n))",
            "buildHeap (O(n))",
            "build_heap_comparison.svg"
        )

    # Heapsort на разных типах данных
    if "BM_Heapsort" in data and "BM_HeapsortSorted" in data and "BM_HeapsortReverseSorted" in data:
        plt.figure(figsize=(10, 6))
        
        x1, y1 = zip(*data["BM_Heapsort"])
        x2, y2 = zip(*data["BM_HeapsortSorted"])
        x3, y3 = zip(*data["BM_HeapsortReverseSorted"])
        
        plt.plot(x1, y1, marker="o", label="Случайные данные", linewidth=2, markersize=6)
        plt.plot(x2, y2, marker="s", label="Отсортированные данные", linewidth=2, markersize=6)
        plt.plot(x3, y3, marker="^", label="Обратно отсортированные", linewidth=2, markersize=6)
        
        plt.xlabel("Размер входных данных", fontsize=12)
        plt.ylabel("Время (нс)", fontsize=12)
        plt.title("Heapsort на разных типах данных", fontsize=14, fontweight="bold")
        plt.legend(fontsize=11)
        plt.grid(True, alpha=0.3)
        plt.loglog()
        # plt.xscale("log", base=2)
        # plt.yscale("log")
        
        os.makedirs(OUTPUT_DIR, exist_ok=True)
        plt.savefig(os.path.join(OUTPUT_DIR, "heapsort_comparison.svg"), format="svg", bbox_inches="tight", dpi=300)
        plt.close()


if __name__ == "__main__":
    main()

