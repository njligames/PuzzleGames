#!/bin/bash

# set -x
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

rm -rf book
mkdir -p book
mkdir -p book/puzzle
mkdir -p book/solved
bash copy_png_puzzles.sh ${columns_puzzle} ${rows_puzzle} ${columns_solved} ${rows_solved} ${num_puzzle_pages}

bash generate_puzzle_pages_script.sh ${columns_puzzle} ${rows_puzzle} ${orientation}
bash generate_solved_pages_script.sh ${columns_solved} ${rows_solved} ${orientation}

rm -rf book_out
shopt -s nullglob
arr=("book/puzzle"/*)
i=0

for f in "${arr[@]}"; do
    if [ "$i" -lt "$num_puzzle_pages" ]
    then
        bash create_puzzle_pages.sh $i
    fi

   ((i=i+1))
done

shopt -s nullglob
arr=("book/solved"/*)
i=0
((num_solved_pages=num_puzzle_pages/2))

for f in "${arr[@]}"; do
    if [ "$i" -lt "$num_solved_pages" ]
    then
        bash create_solved_pages.sh $i
    fi

   ((i=i+1))
done

shopt -s nullglob
puzzle=("book_out/puzzle"/*)
solved=("book_out/solved"/*)
/System/Library/Automator/Combine\ PDF\ Pages.action/Contents/Resources/join.py --output ./Sudoku_${mark}.pdf Cover_${mark}.pdf ${puzzle[*]} ${solved[*]} Back_${mark}.pdf --verbose

