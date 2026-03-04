#!/usr/bin/env bash
set -euo pipefail

CONFIG="${1:-Debug}"
shift || true

RUN=0
TEST=0
CLEAN=0
JOBS=""

while [[ $# -gt 0 ]]; do
  case "$1" in
    --run) RUN=1; shift ;;
    --test) TEST=1; shift ;;
    --clean) CLEAN=1; shift ;;
    -j|--jobs)
      JOBS="${2:-}"
      if [[ -z "$JOBS" ]]; then
        echo "Missing value for $1" >&2
        exit 2
      fi
      shift 2
      ;;
    -h|--help)
      sed -n '1,120p' "$0"
      exit 0
      ;;
    *)
      echo "Unknown arg: $1" >&2
      exit 2
      ;;
  esac
done

if [[ "$CONFIG" != "Debug" && "$CONFIG" != "Release" && "$CONFIG" != "RelWithDebInfo" && "$CONFIG" != "MinSizeRel" ]]; then
  echo "Unknown configuration: $CONFIG" >&2
  echo "Valid: Debug, Release, RelWithDebInfo, MinSizeRel" >&2
  exit 2
fi

if ! command -v cmake >/dev/null 2>&1; then
  echo "cmake not found on PATH. Install CMake to build from source." >&2
  exit 127
fi

BUILD_DIR="build/${CONFIG}"

if [[ $CLEAN -eq 1 ]]; then
  echo "[clean] Removing ${BUILD_DIR}" 
  rm -rf "${BUILD_DIR}"
fi

echo "[configure] ${CONFIG} -> ${BUILD_DIR}"
cmake -S . -B "${BUILD_DIR}" -DCMAKE_BUILD_TYPE="${CONFIG}"

echo "[build] ${CONFIG}"
if [[ -n "$JOBS" ]]; then
  cmake --build "${BUILD_DIR}" --parallel "$JOBS"
else
  cmake --build "${BUILD_DIR}" --parallel
fi

if [[ $TEST -eq 1 ]]; then
  echo "[test]"
  ctest --test-dir "${BUILD_DIR}" --output-on-failure
fi

if [[ $RUN -eq 1 ]]; then
  EXE="${BUILD_DIR}/HexPip"
  if [[ -f "${EXE}" ]]; then
    echo "[run] ${EXE}"
    cd "${BUILD_DIR}" && ./HexPip
  elif [[ -f "${BUILD_DIR}/Debug/HexPip" ]]; then
    echo "[run] ${BUILD_DIR}/Debug/HexPip"
    cd "${BUILD_DIR}/Debug" && ./HexPip
  elif [[ -f "${BUILD_DIR}/Release/HexPip" ]]; then
    echo "[run] ${BUILD_DIR}/Release/HexPip"
    cd "${BUILD_DIR}/Release" && ./HexPip
  else
    echo "Could not find built executable. Look inside ${BUILD_DIR}." >&2
    exit 1
  fi
fi
