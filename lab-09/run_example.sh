set -euo pipefail

BUILD_DIR="build"

cmake -S . -B "$BUILD_DIR" -DBUILD_TESTING=OFF -DBUILD_BENCHMARKS=OFF
cmake --build "$BUILD_DIR" --target dp_example
"$BUILD_DIR"/dp_example
