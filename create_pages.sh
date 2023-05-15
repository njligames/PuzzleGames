#!/bin/bash

set -x
#
# rm -rf cmake-build-debug/out
#
# cd cmake-build-debug
# ./PuzzleGames
#

columns_puzzle=$1
rows_puzzle=$2

columns_solved=$3
rows_solved=$4

num_puzzle_pages=$5

mark=$6

orientation=$7

bash copy_png_puzzles.sh ${columns_puzzle} ${rows_puzzle} ${columns_solved} ${rows_solved} ${num_puzzle_pages} ${mark}

bash generate_puzzle_pages_script.sh ${columns_puzzle} ${rows_puzzle} ${orientation} ${mark}
bash generate_solved_pages_script.sh ${columns_solved} ${rows_solved} ${orientation} ${mark}

shopt -s nullglob
arr=("book/$mark/puzzle"/*)
i=0

for f in "${arr[@]}"; do
    if [ "$i" -lt "$num_puzzle_pages" ]
    then
        bash create_puzzle_pages.sh $i $mark
    fi

   ((i=i+1))
done

shopt -s nullglob
arr=("book/$mark/solved"/*)
i=0
((num_solved_pages=num_puzzle_pages/2))

echo "a"
echo $arr

for f in "${arr[@]}"; do
    if [ "$i" -lt "$num_solved_pages" ]
    then
        bash create_solved_pages.sh $i $mark
    fi

   ((i=i+1))
done

bash merge_pages.sh ${mark}

# shopt -s nullglob
# puzzle=("book/${mark}/pages/puzzle"/*)
# solved=("book/${mark}/pages/solved"/*)
#
# /System/Library/Automator/Combine\ PDF\ Pages.action/Contents/MacOS/join --output ./book/${mark}/Sudoku_${mark}.pdf ./book/${mark}/Cover_${mark}.pdf ${puzzle[*]} ${solved[*]} ./book/${mark}/Back_${mark}.pdf --verbose
#
# open ./book/${mark}/Sudoku_${mark}.pdf

