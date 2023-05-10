#!/bin/bash

set -x
# columns_puzzle=$1
# rows_puzzle=$2
# columns_solved=$3
# rows_solved=$4
# num_puzzle_pages=$5
# n=$(( $columns_puzzle * $rows_puzzle * 2 ))

shopt -s nullglob

# # Get every puzzle image
# inarray=("cmake-build-debug/out/mark2/puzzle/*.png")
# arr_puzzle=($(printf "%s\n" "${inarray[@]}"))
# for fullfile in "${arr_puzzle[@]}"; do
#     filename=$(basename -- "$fullfile" .png)
#     # mv cmake-build-debug/out/puzzle/${filename}.png /Volumes/GoogleDrive/My\ Drive/SudokuPuzzlesVault/Puzzle/puzzle.${filename}.png
#     mv cmake-build-debug/out/mark2/puzzle/${filename}.png cmake-build-debug/out/mark2/puzzle/puzzle.${filename}.png
# done

# Get every solved image
inarray=("cmake-build-debug/out/mark2/solved/*.png")
arr_solved=($(printf "%s\n" "${inarray[@]}"))
for fullfile in "${arr_solved[@]}"; do
    filename=$(basename -- "$fullfile" .png)
    # mv cmake-build-debug/out/solved/${filename}.png /Volumes/GoogleDrive/My\ Drive/SudokuPuzzlesVault/Solution/solved.${filename}.png

    mv cmake-build-debug/out/mark2/solved/${filename}.png cmake-build-debug/out/mark2/solved/solved.${filename}.png
done
