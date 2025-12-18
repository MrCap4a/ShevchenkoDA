set -euo pipefail

BUILD_DIR="build"
RESULTS_DIR="results"

cmake -S . -B "$BUILD_DIR" -DBUILD_TESTING=OFF -DBUILD_BENCHMARKS=ON
cmake --build "$BUILD_DIR" --target run_benchmarks
"$BUILD_DIR"/benchmarks/run_benchmarks \
  --benchmark_out_format=json \
  --benchmark_out="$RESULTS_DIR"/benchmark_results.json

source ../venv/bin/activate
python3 ./scripts/plot_results.py
