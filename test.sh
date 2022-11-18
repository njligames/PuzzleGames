#!/bin/bash

# filename=`echo $1 | awk '{printf("%05d\n", $1)}'`
# echo $filename

# num_puzzle_pages=24
# ((num_solved_pages=num_puzzle_pages/4))
#
# echo $num_solved_pages
# i=0
# if [ "$i" -le "$num_puzzle_pages" ]
# then
#     bash create_puzzle_pages.sh $i
# fi

# set -x
# shopt -s nullglob
# arr=("book/puzzle/${1}/"/*)
# filename=`echo $1 | awk '{printf("%09d\n", $1)}'`
# echo ${arr[*]}

bash create_pages.sh
rm -rf book_out
bash create_puzzle_pages.sh 0
