package org.example

import kotlin.math.log2
import kotlin.random.Random
import kotlin.system.measureNanoTime
import org.knowm.xchart.SwingWrapper
import org.knowm.xchart.XYChartBuilder
import org.knowm.xchart.style.markers.None

// ---------- АЛГОРИТМЫ ПОИСКА ----------

/**
 * Линейный поиск — O(n)
 * Последовательно проверяет каждый элемент до нахождения цели.
 */
fun linearSearch(list: List<Int>, target: Int): Long {
    val time = measureNanoTime {
        // Перебор всех элементов: O(n)
        for (index in 0 until list.size) {
            if (list[index] == target) break // В среднем O(n/2), в худшем O(n)
        }
    }
    return time
}

/**
 * Бинарный поиск — O(log n)
 * Работает только на отсортированных списках; на каждом шаге делит диапазон поиска пополам.
 */
fun binarySearch(list: List<Int>, target: Int): Long {
    val time = measureNanoTime {
        var low = 0
        var high = list.size - 1
        // Цикл выполняется максимум log2(n) раз: O(log n)
        while (low <= high) {
            val mid = (low + high) / 2
            when {
                list[mid] == target -> return@measureNanoTime // Найдено, выход
                list[mid] > target -> high = mid - 1 // Сужаем верхнюю границу
                else -> low = mid + 1 // Сужаем нижнюю границу
            }
        }
    }
    return time
}

// ---------- ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ДЛЯ АППРОКСИМАЦИИ ----------

// Линейная регрессия (y = a*x + b) — O(n)
fun linearRegression(x: List<Double>, y: List<Double>): Pair<Double, Double> {
    val meanX = x.average() // O(n)
    val meanY = y.average() // O(n)
    val a = (x.zip(y).sumOf { (xi, yi) -> (xi - meanX) * (yi - meanY) }) / // O(n)
            (x.sumOf { (it - meanX) * (it - meanX) }) // O(n)
    val b = meanY - a * meanX
    return Pair(a, b)
}

// Регрессия для функции вида y = a*log2(x) + b — O(n)
fun logRegression(x: List<Double>, y: List<Double>): Pair<Double, Double> {
    val logX = x.map { log2(it) } // O(n)
    return linearRegression(logX, y)
}

fun main() {
    // ---------- PART 1: Linear vs Binary Comparison ----------
    val arraySizes = listOf(100_000, 200_000, 300_000, 400_000, 500_000)
    val results = mutableListOf<Pair<Long, Long>>()

    println("=== Comparing Linear and Binary Search ===")

    for (size in arraySizes) {
        var linearTime = 0L
        var binaryTime = 0L

        repeat(80) { iteration ->
            val list = MutableList(size) { Random.nextInt(-100_000_000, 100_000_000) } // O(n)
            val sortedList = list.sorted() // O(n log n)
            val target = list.random() // O(1)

            val linearResult = linearSearch(list, target)
            val binaryResult = binarySearch(sortedList, target)

            if (iteration >= 40) { // skip warm-up
                linearTime += linearResult
                binaryTime += binaryResult
            }
        }

        linearTime /= 40
        binaryTime /= 40
        println("Array size $size: Linear avg = $linearTime ns, Binary avg = $binaryTime ns")
        results.add(Pair(linearTime, binaryTime))
    }

    val sizes = arraySizes.map { it.toDouble() }
    val linearTimes = results.map { it.first.toDouble() }
    val binaryTimes = results.map { it.second.toDouble() }

    // ---------- Plot 1: Raw comparison ----------
    val chartCompare = XYChartBuilder()
        .width(800)
        .height(600)
        .title("Linear vs Binary Search (raw data)")
        .xAxisTitle("Array Size")
        .yAxisTitle("Time (ns)")
        .build()

    chartCompare.addSeries("Linear Search", sizes, linearTimes).apply { marker = None() }
    chartCompare.addSeries("Binary Search", sizes, binaryTimes).apply { marker = None() }

    SwingWrapper(chartCompare).displayChart()

    // ---------- Plot 2: Comparison + approximations ----------
    val (aLin, bLin) = linearRegression(sizes, linearTimes)
    val linearApprox = sizes.map { aLin * it + bLin }

    val (aBin, bBin) = logRegression(sizes, binaryTimes)
    val binaryApprox = sizes.map { aBin * log2(it) + bBin }

    val chartCompareApprox = XYChartBuilder()
        .width(800)
        .height(600)
        .title("Linear vs Binary Search with Approximation")
        .xAxisTitle("Array Size")
        .yAxisTitle("Time (ns)")
        .build()

    chartCompareApprox.addSeries("Linear Search (data)", sizes, linearTimes).apply { marker = None() }
    chartCompareApprox.addSeries("Binary Search (data)", sizes, binaryTimes).apply { marker = None() }
    chartCompareApprox.addSeries("Linear Approx", sizes, linearApprox).apply { marker = None() }
    chartCompareApprox.addSeries("Binary Approx", sizes, binaryApprox).apply { marker = None() }

    SwingWrapper(chartCompareApprox).displayChart()

    // ---------- PART 2: Binary Search Detailed ----------
    val bigSizes = listOf(
        50_000, 100_000, 200_000, 300_000, 400_000, 500_000,
        700_000, 900_000, 1_200_000, 1_500_000,
        1_800_000, 2_100_000, 2_400_000, 2_700_000, 3_000_000,
        3_400_000, 3_800_000, 4_300_000, 5_000_000
    )

    val binaryResultsLarge = mutableListOf<Long>()

    println("\n=== Measuring Binary Search (Detailed) ===")

    for (size in bigSizes) {
        var totalTime = 0L
        repeat(30) { iteration ->
            val list = MutableList(size) { Random.nextInt(-1_000_000_000, 1_000_000_000) }.sorted() // O(n log n)
            val target = list.random() // O(1)
            val time = binarySearch(list, target)
            if (iteration >= 15) totalTime += time // skip warm-up
        }
        val avgTime = totalTime / 15
        binaryResultsLarge.add(avgTime)
        println("Array size $size: Binary avg = $avgTime ns")
    }

    val bigSizesDouble = bigSizes.map { it.toDouble() }
    val binaryTimesLarge = binaryResultsLarge.map { it.toDouble() }

    // ---------- Plot 3: Binary search only ----------
    val chartBinary = XYChartBuilder()
        .width(800)
        .height(600)
        .title("Binary Search on Large Arrays")
        .xAxisTitle("Array Size")
        .yAxisTitle("Time (ns)")
        .build()

    chartBinary.addSeries("Binary Search", bigSizesDouble, binaryTimesLarge).apply { marker = None() }
    SwingWrapper(chartBinary).displayChart()

    // ---------- Plot 4: Binary search + approximation ----------
    val (aLarge, bLarge) = logRegression(bigSizesDouble, binaryTimesLarge)
    val binaryApproxLarge = bigSizesDouble.map { aLarge * log2(it) + bLarge }

    val chartBinaryApprox = XYChartBuilder()
        .width(800)
        .height(600)
        .title("Binary Search (with log2 approximation)")
        .xAxisTitle("Array Size")
        .yAxisTitle("Time (ns)")
        .build()

    chartBinaryApprox.addSeries("Binary Search (data)", bigSizesDouble, binaryTimesLarge).apply { marker = None() }
    chartBinaryApprox.addSeries("Approximation (log2)", bigSizesDouble, binaryApproxLarge).apply { marker = None() }

    SwingWrapper(chartBinaryApprox).displayChart()
}
