#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

grub-mkrescue -o "$PROJECT_ROOT"/iso/blu_os.iso "$PROJECT_ROOT"/cmake-build-debug/kernel/blu_os.kernel 2>/dev/null