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


def plot_comparison(title, balanced, degenerate, filename):
    plt.figure()

    bx, by = zip(*balanced)
    dx, dy = zip(*degenerate)

    plt.plot(bx, by, marker="o", label="Balanced")
    plt.plot(dx, dy, marker="o", label="Degenerate")

    plt.xlabel("Input size")
    plt.ylabel("Time (ns)")
    plt.title(title)
    plt.legend()
    plt.grid(True)

    os.makedirs(OUTPUT_DIR, exist_ok=True)
    plt.savefig(os.path.join(OUTPUT_DIR, filename), format="svg", bbox_inches="tight")
    plt.close()


def main():
    data = load_iterations()

    plot_comparison(
        "Insert",
        data["BM_InsertBalanced"],
        data["BM_InsertDegenerate"],
        "insert.svg"
    )

    plot_comparison(
        "Search",
        data["BM_SearchBalanced"],
        data["BM_SearchDegenerate"],
        "search.svg"
    )

    plot_comparison(
        "Height",
        data["BM_HeightBalanced"],
        data["BM_HeightDegenerate"],
        "height.svg"
    )


if __name__ == "__main__":
    main()

