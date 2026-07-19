#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

cmake -DCMAKE_BUILD_TYPE=Release --preset release-x86_64 -S "$PROJECT_ROOT"
cmake --build --preset release-x86_64