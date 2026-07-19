#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
KERNEL_BIN="$PROJECT_ROOT/build/i386-release/kernel/blu_os.kernel32"
ISO_DIR="$PROJECT_ROOT/iso_root"
OUTPUT_ISO="$PROJECT_ROOT/iso/boot/grub/blu_os.iso"

if [ ! -f "$KERNEL_BIN" ]; then
    echo "Kernel binary not found at $KERNEL_BIN"
    exit 1
fi

rm -rf "$ISO_DIR"
rm -f "$OUTPUT_ISO"

mkdir -p "$ISO_DIR/boot/grub"

cp "$KERNEL_BIN" "$ISO_DIR/boot/blu_os.kernel32"

cat << 'EOF' > "$ISO_DIR/boot/grub/grub.cfg"
set timeout=0
set default=0

menuentry "blu-OS" {
    multiboot /boot/blu_os.kernel32
    boot
}
EOF

MKRESCUE_CMD="grub-mkrescue"
if ! command -v grub-mkrescue &> /dev/null; then
    if command -v grub2-mkrescue &> /dev/null; then
        MKRESCUE_CMD="grub2-mkrescue"
    else
        echo "Please ensure grub utilities and xorriso are installed."
        exit 1
    fi
fi

$MKRESCUE_CMD -o "$OUTPUT_ISO" "$ISO_DIR"

rm -rf "$ISO_DIR"