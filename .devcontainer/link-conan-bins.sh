#!/bin/bash

if [ -d "$HOME/.conan2/p" ]; then
    find "$HOME/.conan2/p" -name "bin" -type d 2>/dev/null | while read bin_dir; do
        if [ -d "$bin_dir" ] && [ "$(ls -A "$bin_dir" 2>/dev/null)" ]; then
            for binary in "$bin_dir"/*; do
                if [ -f "$binary" ] && [ -x "$binary" ]; then
                    binary_name=$(basename "$binary")
                    sudo ln -sf "$binary" "/usr/local/bin/$binary_name" 2>/dev/null
                    echo "Linked $binary_name"
                fi
            done
        fi
    done
else
    echo "Conan cache not found, skipping binary linking"
fi >/dev/null 2>&1