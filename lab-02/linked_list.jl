# -----------------------------------------------
# Реализация простого односвязного списка (LinkedList)
# -----------------------------------------------

# Узел списка — хранит значение и ссылку на следующий
struct Node
    value::Any
    next::Union{Node, Nothing}
end

# Сам список — хранит голову и хвост
mutable struct LinkedList
    head::Union{Node, Nothing}
    tail::Union{Node, Nothing}
end

# Создание пустого списка — O(1)
function LinkedList()
    return LinkedList(nothing, nothing)
end

# ---------------------------------------------------------
# ВСТАВКА В НАЧАЛО — O(1)
# ---------------------------------------------------------
# Что происходит:
#   1. Создаём новый узел
#   2. Его next указывает на бывшую голову
#   3. Переносим head на новый элемент
#   4. Если список был пуст — tail тоже обновляем
# ---------------------------------------------------------
function insert_at_start(list::LinkedList, value)
    new_node = Node(value, list.head)
    list.head = new_node

    if list.tail === nothing
        list.tail = new_node
    end
end

# ---------------------------------------------------------
# ВСТАВКА В КОНЕЦ — O(1)
# ---------------------------------------------------------
#   1. Создаём новый узел
#   2. Если список пуст — head = tail = этот узел
#   3. Иначе хвост.next = новый узел
#   4. tail = новый узел
# ---------------------------------------------------------
function insert_at_end(list::LinkedList, value)
    new_node = Node(value, nothing)

    if list.tail === nothing
        list.head = new_node
        list.tail = new_node
    else
        list.tail.next = new_node
        list.tail = new_node
    end
end

# ---------------------------------------------------------
# УДАЛЕНИЕ ИЗ НАЧАЛА — O(1)
# ---------------------------------------------------------
#   1. Сохраняем head
#   2. head = head.next
#   3. Если список стал пуст — tail = nothing
# ---------------------------------------------------------
function delete_from_start(list::LinkedList)
    if list.head === nothing
        return nothing
    end

    removed = list.head
    list.head = removed.next

    if list.head === nothing
        list.tail = nothing
    end

    return removed.value
end

# ---------------------------------------------------------
# ОБХОД СПИСКА — O(n)
# ---------------------------------------------------------
#   Просто идём по цепочке next до конца
# ---------------------------------------------------------
function traversal(list::LinkedList)
    current = list.head
    while current !== nothing
        println(current.value)
        current = current.next
    end
end
