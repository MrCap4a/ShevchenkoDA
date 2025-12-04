{-# LANGUAGE BangPatterns #-}

module Main where

import System.CPUTime (getCPUTime)
import Control.Exception (evaluate)
import Data.IORef
import Data.Array.IO
import System.Process (callCommand)
import System.IO (writeFile)

naiveFibCount :: IORef Integer -> Integer -> IO Integer
naiveFibCount counter 0 = do
  modifyIORef' counter (+1)
  return 0
naiveFibCount counter 1 = do
  modifyIORef' counter (+1)
  return 1
naiveFibCount counter n = do
  modifyIORef' counter (+1)
  a <- naiveFibCount counter (n-1)
  b <- naiveFibCount counter (n-2)
  return (a + b)

memoFibCount :: IORef Integer -> Int -> IO Integer
memoFibCount counter n = do
  arr <- newArray (0, n) (-1) :: IO (IOArray Int Integer)
  let go :: Int -> IO Integer
      go 0 = do
        modifyIORef' counter (+1)
        return 0
      go 1 = do
        modifyIORef' counter (+1)
        return 1
      go k = do
        v <- readArray arr k
        if v /= (-1)
          then return v
          else do
            modifyIORef' counter (+1)
            x <- go (k-1)
            y <- go (k-2)
            let !r = x + y
            writeArray arr k r
            return r
  go n

timeAction :: IO a -> IO (a, Double)
timeAction action = do
  start <- getCPUTime
  res <- action
  _ <- evaluate res
  end <- getCPUTime
  let diff = fromIntegral (end - start) / (1e12 :: Double)
  return (res, diff)

main :: IO ()
main = do
  let n = 35

  counter1 <- newIORef 0
  (val1, time1) <- timeAction $ do
    r <- naiveFibCount counter1 n
    evaluate r
    return r
  calls1 <- readIORef counter1

  counter2 <- newIORef 0
  (val2, time2) <- timeAction $ do
    r <- memoFibCount counter2 (fromIntegral n)
    evaluate r
    return r
  calls2 <- readIORef counter2

  putStrLn $ "n = " ++ show n
  putStrLn $ "Naive: " ++ show val1 ++ ", time = " ++ show time1 ++ " s, calls = " ++ show calls1
  putStrLn $ "Memo: " ++ show val2 ++ ", time = " ++ show time2 ++ " s, calls = " ++ show calls2

  -- Создаём Python скрипт для построения графика
  let pythonScript = "import matplotlib.pyplot as plt\n" ++
                     "import numpy as np\n" ++
                     "\n" ++
                     "methods = ['Naive', 'Memoized']\n" ++
                     "times = [" ++ show time1 ++ ", " ++ show time2 ++ "]\n" ++
                     "colors = ['#FF6B6B', '#4ECDC4']\n" ++
                     "\n" ++
                     "fig, ax = plt.subplots(figsize=(10, 6))\n" ++
                     "bars = ax.bar(methods, times, color=colors, edgecolor='black', linewidth=2, alpha=0.8)\n" ++
                     "\n" ++
                     "ax.set_ylabel('Time (seconds)', fontsize=12, fontweight='bold')\n" ++
                     "ax.set_title('Fibonacci n=35: Naive vs Memoized Recursion', fontsize=14, fontweight='bold')\n" ++
                     "ax.set_ylim(0, max(times) * 1.1)\n" ++
                     "\n" ++
                     "for bar, time in zip(bars, times):\n" ++
                     "    height = bar.get_height()\n" ++
                     "    ax.text(bar.get_x() + bar.get_width()/2., height,\n" ++
                     "            f'{time:.4f}s',\n" ++
                     "            ha='center', va='bottom', fontweight='bold', fontsize=11)\n" ++
                     "\n" ++
                     "plt.grid(axis='y', alpha=0.3, linestyle='--')\n" ++
                     "plt.tight_layout()\n" ++
                     "plt.savefig('histogram.png', dpi=150, bbox_inches='tight')\n" ++
                     "print('Histogram 1 saved to histogram.png')\n"
  writeFile "plot.py" pythonScript

  -- Вызываем Python для первого графика
  putStrLn "Generating histogram 1 with Python/Matplotlib..."
  callCommand "python plot.py"

  -- Ищем n для naive и memoized с одинаковым временем
  putStrLn "\nSearching for equal execution times..."
  let naiveN = 30
  let memoN = 95000
  
  counter3 <- newIORef 0
  (_, timeNaive) <- timeAction $ do
    r <- naiveFibCount counter3 naiveN
    evaluate r
    return r
  
  counter4 <- newIORef 0
  (_, timeMemo) <- timeAction $ do
    r <- memoFibCount counter4 memoN
    evaluate r
    return r
  
  putStrLn $ "Naive (n=" ++ show naiveN ++ "): " ++ show timeNaive ++ " s"
  putStrLn $ "Memoized (n=" ++ show memoN ++ "): " ++ show timeMemo ++ " s"

  -- Создаём второй Python скрипт с графиком сравнения
  let pythonScript2 = "import matplotlib.pyplot as plt\n" ++
                      "import numpy as np\n" ++
                      "\n" ++
                      "methods = ['Naive (n=30)', 'Memoized (n=95000)']\n" ++
                      "times = [" ++ show timeNaive ++ ", " ++ show timeMemo ++ "]\n" ++
                      "colors = ['#FF6B6B', '#4ECDC4']\n" ++
                      "\n" ++
                      "fig, ax = plt.subplots(figsize=(10, 6))\n" ++
                      "bars = ax.bar(methods, times, color=colors, edgecolor='black', linewidth=2, alpha=0.8)\n" ++
                      "\n" ++
                      "ax.set_ylabel('Time (seconds)', fontsize=12, fontweight='bold')\n" ++
                      "ax.set_title('Equal Execution Time: Naive (n=30) vs Memoized (n=95000)', fontsize=14, fontweight='bold')\n" ++
                      "ax.set_ylim(0, max(times) * 1.1)\n" ++
                      "\n" ++
                      "for bar, time in zip(bars, times):\n" ++
                      "    height = bar.get_height()\n" ++
                      "    ax.text(bar.get_x() + bar.get_width()/2., height,\n" ++
                      "            f'{time:.4f}s',\n" ++
                      "            ha='center', va='bottom', fontweight='bold', fontsize=11)\n" ++
                      "\n" ++
                      "plt.grid(axis='y', alpha=0.3, linestyle='--')\n" ++
                      "plt.tight_layout()\n" ++
                      "plt.savefig('histogram2.png', dpi=150, bbox_inches='tight')\n" ++
                      "print('Histogram 2 saved to histogram2.png')\n"
  writeFile "plot2.py" pythonScript2

  -- Вызываем Python для второго графика
  putStrLn "Generating histogram 2 with Python/Matplotlib..."
  callCommand "python plot2.py"
