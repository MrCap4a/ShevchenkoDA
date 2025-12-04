-- Реализации на Haskell с использованием рекурсии
-- 1) Факториал
-- 2) n-е число Фибоначчи (простая рекурсивная версия)
-- 3) Быстрое возведение в степень (экспоненцирование через степени двойки)

module Main where

-- Вычисление факториала числа n
factorial :: Integer -> Integer
factorial 0 = 1
factorial n
  | n > 0     = n * factorial (n - 1)
  | otherwise = error "factorial: отрицательное n"
-- Временная сложность: O(n)
-- Глубина рекурсии: n (рекурсивный стек растёт линейно по n)

-- Вычисление n-го числа Фибоначчи (простая рекурсивная версия)
fib :: Integer -> Integer
fib 0 = 0
fib 1 = 1
fib n
  | n > 1     = fib (n - 1) + fib (n - 2)
  | otherwise = error "fib: отрицательное n"
-- Временная сложность: O(2^n) (экспоненциальная)
-- Глубина рекурсии: n (максимальная глубина рекурсии равна n)

-- Быстрое возведение числа a в степень n (через степень двойки)
fastPow :: (Integral b, Num a) => a -> b -> a
fastPow _ 0 = 1
fastPow a n
  | n < 0     = error "fastPow: отрицательная степень не поддерживается"
  | even n    = let half = fastPow a (n `div` 2) in half * half
  | otherwise = a * fastPow a (n - 1)
-- Временная сложность: O(log n) (для n>0) — каждый шаг делит показатель на 2
-- Глубина рекурсии: O(log n) (стек рекурсии растёт примерно на log2(n))

-- Небольшая демонстрация в main
main :: IO ()
main = do
  putStrLn "Демонстрация рекурсивных функций"
  putStrLn $ "factorial 10 = " ++ show (factorial 10)
  putStrLn $ "fib 10 = " ++ show (fib 10)
  putStrLn $ "fastPow 2 20 = " ++ show (fastPow (2 :: Integer) (20 :: Integer))

  putStrLn "\nПримечание: для точного сравнения производительности используйте многократные запуски или Criterion."
