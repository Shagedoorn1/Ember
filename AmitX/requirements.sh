#!/bin/bash
# requirements.sh — install everything needed to build & run AmitX

set -e

echo "🛠  Installing AmitX build requirements..."

REQUIRED_PACKAGES=(
  build-essential
  gcc
  make
  nasm
  qemu-system-x86
  grub-pc-bin
  grub-common
  xorriso
  mtools
)

# Check if apt exists
if ! command -v apt &> /dev/null; then
  echo "❌ This script currently supports apt-based systems (Debian, Ubuntu)."
  echo "    Please install the following packages manually:"
  printf '    %s\n' "${REQUIRED_PACKAGES[@]}"
  exit 1
fi

# Update and install packages
sudo apt update
sudo apt install -y "${REQUIRED_PACKAGES[@]}"

echo "All required packages installed!"
echo "You can now run: make run"
echo -e "\n Verifying tools:"
for tool in gcc make nasm qemu-system-x86 xorriso grub-mkrescue; do
    if ! command -v $tool &> /dev/null; then
        echo "$tool not found!"
    else
        echo "$tool is available"
    fi
done
