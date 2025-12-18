set -euo pipefail

BUILD_DIR="build"

mkdir -p "$BUILD_DIR"
cmake -S . -B "$BUILD_DIR" -DBUILD_TESTING=ON -DBUILD_BENCHMARKS=OFF
cmake --build "$BUILD_DIR" --target run_tests
"$BUILD_DIR"/tests/run_tests
