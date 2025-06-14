#!/bin/bash

# Create a build folder if it doesn't exist
mkdir -p build

# Compile the shell
if gcc -o build/amitx_shell window.c `pkg-config --cflags --libs gtk+-3.0`; then
    echo "Build successful. Launching AmitX Shell..."
    ./build/amitx_shell
else
    echo "Compilation failed."
    exit 1
fi
