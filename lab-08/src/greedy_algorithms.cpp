#include "greedy_algorithms.h"

#include <algorithm>
#include <queue>

namespace greedy {

// ---------------- Задача о выборе заявок ----------------

std::vector<Interval> selectIntervalsGreedy(std::vector<Interval> intervals) {
    // Сортируем интервалы по времени окончания (жадный критерий)
    std::sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) {
        if (a.end == b.end) {
            return a.start < b.start;
        }
        return a.end < b.end;
    });

    std::vector<Interval> result;
    int current_end = -1e9;

    for (const auto& interval : intervals) {
        if (interval.start >= current_end) {
            result.push_back(interval);
            current_end = interval.end;
        }
    }

    return result;
}

// ---------------- Дробный рюкзак ----------------

FractionalKnapsackResult fractionalKnapsackGreedy(const std::vector<Item>& items, double capacity) {
    struct WithIndex {
        Item item;
        std::size_t index;
    };

    std::vector<WithIndex> sorted;
    sorted.reserve(items.size());
    for (std::size_t i = 0; i < items.size(); ++i) {
        sorted.push_back({items[i], i});
    }

    // Сортируем по убыванию удельной стоимости (value / weight)
    std::sort(sorted.begin(), sorted.end(), [](const WithIndex& a, const WithIndex& b) {
        double ra = a.item.value / a.item.weight;
        double rb = b.item.value / b.item.weight;
        return ra > rb;
    });

    FractionalKnapsackResult result{};
    result.max_value = 0.0;
    result.fractions.assign(items.size(), 0.0);

    double remaining = capacity;

    for (const auto& wi : sorted) {
        if (remaining <= 0) break;
        if (wi.item.weight <= remaining) {
            // Берем предмет целиком
            result.fractions[wi.index] = 1.0;
            result.max_value += wi.item.value;
            remaining -= wi.item.weight;
        } else {
            // Берем только доступную долю
            double fraction = remaining / wi.item.weight;
            result.fractions[wi.index] = fraction;
            result.max_value += wi.item.value * fraction;
            remaining = 0;
        }
    }

    return result;
}

// ---------------- Жадная сдача монетами ----------------

std::vector<int> coinChangeGreedy(int amount, const std::vector<int>& coins) {
    // Предполагаем, что coins отсортированы по убыванию
    std::vector<int> result;
    result.reserve(coins.size());

    for (int coin : coins) {
        int cnt = amount / coin;
        result.push_back(cnt);
        amount -= cnt * coin;
    }

    return result;
}

// ---------------- Алгоритм Хаффмана ----------------

struct NodePtrWrapper {
    HuffmanNode* node;
};

struct HuffmanCompare {
    bool operator()(const NodePtrWrapper& a, const NodePtrWrapper& b) const {
        return a.node->frequency > b.node->frequency; // мин-куча по частоте
    }
};

static void buildCodesDfs(HuffmanNode* node, const std::string& prefix,
                          std::unordered_map<char, std::string>& codes) {
    if (!node) return;

    // Листовой узел: символ имеет код
    if (!node->left && !node->right) {
        // Обработка случая одного символа: присвоим код "0"
        codes[node->symbol] = prefix.empty() ? "0" : prefix;
        return;
    }

    buildCodesDfs(node->left, prefix + "0", codes);
    buildCodesDfs(node->right, prefix + "1", codes);
}

std::unordered_map<char, std::string> buildHuffmanCodes(const std::unordered_map<char, int>& frequencies) {
    if (frequencies.empty()) return {};

    std::priority_queue<NodePtrWrapper, std::vector<NodePtrWrapper>, HuffmanCompare> pq;

    // Создаем листовые узлы
    for (const auto& [ch, freq] : frequencies) {
        pq.push(NodePtrWrapper{new HuffmanNode(ch, freq)});
    }

    // Строим дерево Хаффмана, пока не останется один корень
    while (pq.size() > 1) {
        auto left = pq.top().node;
        pq.pop();
        auto right = pq.top().node;
        pq.pop();

        int sum = left->frequency + right->frequency;
        auto parent = new HuffmanNode('\0', sum, left, right);
        pq.push(NodePtrWrapper{parent});
    }

    HuffmanNode* root = pq.top().node;
    std::unordered_map<char, std::string> codes;
    buildCodesDfs(root, "", codes);

    // Освобождаем дерево
    freeHuffmanTree(root);

    return codes;
}

void freeHuffmanTree(HuffmanNode* root) {
    if (!root) return;
    freeHuffmanTree(root->left);
    freeHuffmanTree(root->right);
    delete root;
}

} // namespace greedy
