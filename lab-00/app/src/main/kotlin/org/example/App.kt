package org.example

import kotlin.random.Random
import kotlin.system.measureTimeMillis
import org.knowm.xchart.XYChartBuilder
import org.knowm.xchart.SwingWrapper

fun main() {
    val times = mutableListOf<Float>()
    val arraySizes = arrayOf(10000, 100000, 500000, 1000000, 2000000)

    for (size in arraySizes) {
        val list = mutableListOf<Int>()
        // Заполняем список — O(n)
        for (index in 0..size - 1) {
            list.add(Random.nextInt(100)) // добавление в конец — O(1)
        }

        var timeSum: Long = 0
        var sum = 0

        // Запускаем 1000 итераций измерения — O(1000 * n)
        for (i in 1..1000) {
            val time = measureTimeMillis {
                // Основная операция суммирования по массиву — O(n)
                for (index in 1..size - 1) {
                    sum = list[index - 1] + list[index] // доступ по индексу — O(1)
                }
            }
            if (i > 10) {
                timeSum += time // O(1)
            }
        }

        // Подсчёт среднего времени — O(1)
        val averageTime: Float = timeSum.toFloat() / 1000f
        println("Summation ${size / 2} takes ${averageTime} milliseconds")

        times.add(averageTime) // добавление в конец списка — O(1)
    }

    // Создание графика — O(1)
    val chart = XYChartBuilder()
        .width(800)
        .height(600)
        .title("Time vs Array Size")
        .xAxisTitle("Array Size")
        .yAxisTitle("Time (ms)")
        .build()

    // Добавляем серию данных — O(n)
    chart.addSeries(
        "Summation",
        arraySizes.map { it.toDouble() }.toDoubleArray(),  // O(n)
        times.map { it.toDouble() }.toDoubleArray()        // O(n)
    )

    // Отображение графика — O(1)
    SwingWrapper(chart).displayChart()
}
