#!/bin/bash

# Define the possible file types
file_types=("png" "jpg")

# Search for a background file
for type in "${file_types[@]}"; do
    background_file="$HOME/Pictures/wallpapers/background.$type"
    
    if [ -f "$background_file" ]; then
        feh --no-fehbg --bg-scale "$background_file"
        exit 0  # Exit after setting the background
    fi
done

# If no valid background file is found
echo "No valid background file found."