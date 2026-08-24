#!/bin/bash

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

qemu-system-i386 -cdrom "$PROJECT_ROOT"/iso/boot/grub/blu_os.iso -d int,cpu_reset,guest_errors,invalid_mem -no-shutdown -no-reboot
