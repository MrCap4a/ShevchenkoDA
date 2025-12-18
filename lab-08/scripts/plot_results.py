import json
import os
import re

import matplotlib.pyplot as plt

INPUT_FILE = "./results/benchmark_results.json"
OUTPUT_DIR = "./results"


def parse_size(name: str) -> int | None:
    nums = re.findall(r"\d+", name)
    return int(nums[0]) if nums else None


def load_iterations():
    with open(INPUT_FILE, "r", encoding="utf-8") as f:
        data = json.load(f)["benchmarks"]

    result: dict[str, list[tuple[int, float]]] = {}

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


def plot_single(family: str, data, title: str, filename: str):
    plt.figure()
    plt.loglog()

    x, y = zip(*data)

    plt.plot(x, y, marker="o")

    plt.xlabel("Размер входных данных")
    plt.ylabel("Время (нс)")
    plt.title(title)
    plt.grid(True)

    os.makedirs(OUTPUT_DIR, exist_ok=True)
    plt.savefig(os.path.join(OUTPUT_DIR, filename), format="svg", bbox_inches="tight")
    plt.close()


def main():
    data = load_iterations()

    if "BM_HuffmanBuild" in data:
        plot_single(
            "BM_HuffmanBuild",
            data["BM_HuffmanBuild"],
            "Построение кодов Хаффмана",
            "huffman_build.svg",
        )

    if "BM_IntervalScheduling" in data:
        plot_single(
            "BM_IntervalScheduling",
            data["BM_IntervalScheduling"],
            "Выбор заявок (жадный алгоритм)",
            "interval_scheduling.svg",
        )

    if "BM_FractionalKnapsack" in data:
        plot_single(
            "BM_FractionalKnapsack",
            data["BM_FractionalKnapsack"],
            "Дробный рюкзак (жадный алгоритм)",
            "fractional_knapsack.svg",
        )


if __name__ == "__main__":
    main()
