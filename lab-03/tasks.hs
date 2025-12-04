{-# LANGUAGE ScopedTypeVariables #-}

module Main where

import System.Directory (listDirectory, doesDirectoryExist, getDirectoryContents)
import System.FilePath ((</>))
import Control.Exception (catch, SomeException)
import Data.List (sort)
import Data.IORef

-- ============================================================================
-- Задача 1: Рекурсивный бинарный поиск
-- ============================================================================

-- Бинарный поиск в отсортированном массиве (список)
-- Временная сложность: O(log n)
-- Глубина рекурсии: O(log n)
binarySearch :: (Ord a) => a -> [a] -> Bool
binarySearch x xs = go 0 (length xs - 1)
  where
    arr = xs
    go low high
      | low > high = False
      | otherwise =
          let mid = (low + high) `div` 2
              midVal = arr !! mid
          in if midVal == x
             then True
             else if x < midVal
                  then go low (mid - 1)
                  else go (mid + 1) high

-- Бинарный поиск с возвращением индекса (если найдено) или -1
binarySearchIdx :: (Ord a) => a -> [a] -> Int
binarySearchIdx x xs = go 0 (length xs - 1)
  where
    arr = xs
    go low high
      | low > high = -1
      | otherwise =
          let mid = (low + high) `div` 2
              midVal = arr !! mid
          in if midVal == x
             then mid
             else if x < midVal
                  then go low (mid - 1)
                  else go (mid + 1) high

-- ============================================================================
-- Задача 2: Рекурсивный обход файловой системы
-- ============================================================================

-- Обход файловой системы с отслеживанием глубины рекурсии
traverseDir :: FilePath -> Int -> IORef Int -> IO ()
traverseDir path depth maxDepthRef = do
  -- Обновить максимальную глубину
  modifyIORef' maxDepthRef (max depth)
  
  -- Получить содержимое директории
  contents <- catch (listDirectory path) handleError
  
  -- Сортировать для более читаемого вывода
  let sortedContents = sort contents
  
  -- Вывести каждый файл/директорию
  mapM_ (processEntry path depth) sortedContents
  
  where
    processEntry :: FilePath -> Int -> String -> IO ()
    processEntry dir d name = do
      let fullPath = dir </> name
      isDir <- doesDirectoryExist fullPath
      let indent = replicate (d * 2) ' '
      
      if isDir
        then do
          putStrLn $ indent ++ "[DIR] " ++ name ++ "/"
          -- Рекурсивный вызов для поддиректории
          catch (traverseDir fullPath (d + 1) maxDepthRef) handleDirError
        else do
          putStrLn $ indent ++ "[FILE] " ++ name
    
    handleError :: SomeException -> IO [String]
    handleError _ = return []
    
    handleDirError :: SomeException -> IO ()
    handleDirError _ = return ()

-- ============================================================================
-- Задача 3: Ханойские башни
-- ============================================================================

-- Решение задачи "Ханойские башни"
-- Временная сложность: O(2^n)
-- Глубина рекурсии: O(n)
hanoi :: Int -> String -> String -> String -> IO Int
hanoi 0 _ _ _ = return 0
hanoi n source target aux = do
  -- Переместить n-1 дисков со стержня source на aux, используя target
  moves1 <- hanoi (n - 1) source aux target
  
  -- Переместить самый большой диск со стержня source на target
  putStrLn $ "Диск " ++ show n ++ ": " ++ source ++ " -> " ++ target
  
  -- Переместить n-1 дисков со стержня aux на target, используя source
  moves2 <- hanoi (n - 1) aux target source
  
  return (moves1 + 1 + moves2)

-- Подсчёт количества перемещений без вывода
hanoiCount :: Int -> Integer
hanoiCount 0 = 0
hanoiCount n = 2 * hanoiCount (n - 1) + 1

-- ============================================================================
-- Главная программа
-- ============================================================================

main :: IO ()
main = do
  putStrLn "=== Решение трёх рекурсивных задач ==="
  
  -- Задача 1: Бинарный поиск
  putStrLn "\n--- Задача 1: Бинарный поиск ---"
  let sortedList = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19] :: [Int]
  putStrLn $ "Массив: " ++ show sortedList
  
  let testValues = [5, 10, 19, 20]
  putStrLn "\nРезультаты поиска:"
  mapM_ (\x -> do
    let found = binarySearch x sortedList
    let idx = binarySearchIdx x sortedList
    putStrLn $ "  Значение " ++ show x ++ ": " ++ 
      (if found then "найдено (индекс " ++ show idx ++ ")" else "не найдено")) 
    testValues
  
  -- Задача 2: Обход файловой системы
  putStrLn "\n--- Задача 2: Обход файловой системы ---"
  let startPath = "."
  putStrLn $ "Начало обхода с: " ++ startPath
  
  maxDepthRef <- newIORef 0
  traverseDir startPath 0 maxDepthRef
  maxDepth <- readIORef maxDepthRef
  putStrLn $ "\nМаксимальная глубина рекурсии: " ++ show maxDepth
  
  -- Задача 3: Ханойские башни
  putStrLn "\n--- Задача 3: Ханойские башни (n=4) ---"
  let n = 4
  putStrLn $ "Перемещение " ++ show n ++ " дисков:"
  putStrLn "Стержни: A (источник), B (вспомогательный), C (целевой)\n"
  
  moveCount <- hanoi n "A" "C" "B"
  putStrLn $ "\nВсего перемещений: " ++ show moveCount
  putStrLn $ "Теоретическое количество: " ++ show (hanoiCount n)
  
  putStrLn "\n=== Все задачи выполнены ==="
