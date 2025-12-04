using BenchmarkTools
using Plots
using DataStructures
include("linked_list.jl")

# --------------------------------------------------------
# ТЕСТИРУЕМЫЕ ФУНКЦИИ
# --------------------------------------------------------

# Вставка в начало массива — O(n)
function test_insert_list(n)
    @benchmark insert!(arr, 1, 1) setup=(arr = collect(1:$n))
end


# Вставка в начало связного списка — O(1)
function test_insert_linked(n)
    @benchmark insert_at_start(ll, 1) setup=(ll = LinkedList())
end


# Очередь на list — popfirst! O(n)
function test_queue_list(n)
    @benchmark popfirst!(arr) setup=(arr = collect(1:$n)) evals=1000
end


# Очередь на deque — O(1)
function test_queue_deque(n)
    @benchmark popfirst!(dq) setup = (
        dq = begin
            dq_local = Deque{Int}()
            for i in 1:$n
                push!(dq_local, i)
            end
            dq_local
        end
    ) evals=1000
end



# --------------------------------------------------------
# СБОР ДАННЫХ
# --------------------------------------------------------

sizes = [10000000, 20000000, 40000000, 80000000, 160000000, 320000000, 640000000, 1280000000]

list_times_insert = Float64[]
linked_times_insert = Float64[]

list_times_queue = Float64[]
deque_times_queue = Float64[]

println("\n=== ОПЕРАЦИИ ОЧЕРЕДИ ===")
for n in sizes
    test_list = mean(test_queue_list(n)).time / 1e9
    test_deque = mean(test_queue_deque(n)).time / 1e9

    push!(list_times_queue, test_list)
    push!(deque_times_queue, test_deque)

    println("N=$n | list=$(round(test_list, digits=6)) | deque=$(round(test_deque, digits=6))")
end

println("=== ВСТАВКА В НАЧАЛО ===")
for n in sizes
    test_list = mean(test_insert_list(n)).time / 1e9
    test_linked = mean(test_insert_linked(n)).time / 1e9

    push!(list_times_insert, test_list)
    push!(linked_times_insert, test_linked)
    println("N=$n | list=$(round(test_list, digits=6)) | linked=$(round(test_linked, digits=6))")
end



# --------------------------------------------------------
# ГРАФИКИ
# --------------------------------------------------------

# ------ График 1 ------
p1 = plot(
    sizes, list_times_insert,
    label="list.insert в начало — O(n)",
    lw=2,
    marker=:circle,
    xlabel="Размер N",
    ylabel="Время (сек)",
    title="Вставка в начало: list vs LinkedList"
)

plot!(sizes, linked_times_insert,
      label="LinkedList.insert — O(1)",
      lw=2, marker=:star)

savefig(p1, "insert_comparison.png")
println("График insert_comparison.png сохранён.")

# ------ График 2 ------
p2 = plot(
    sizes, list_times_queue,
    label="list.popfirst! — O(n)",
    lw=2,
    marker=:circle,
    xlabel="Размер N",
    ylabel="Время (сек)",
    title="Очередь: list vs deque"
)

plot!(sizes, deque_times_queue,
      label="deque.popfirst! — O(1)",
      lw=2, marker=:star)

savefig(p2, "queue_comparison.png")
println("График queue_comparison.png сохранён.")
