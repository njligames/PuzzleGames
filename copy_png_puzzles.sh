#!/bin/bash

set -x
columns_puzzle=$1
rows_puzzle=$2
columns_solved=$3
rows_solved=$4
num_puzzle_pages=$5
mark=$6
n=$(( $columns_puzzle * $rows_puzzle * 2 ))

shopt -s nullglob

# Get every puzzle image
inarray=("cmake-build-debug/out/${mark}/puzzle/*.png")
arr_puzzle=($(printf "%s\n" "${inarray[@]}"))

# Get every solved image
inarray=("cmake-build-debug/out/${mark}/solved/*.png")
arr_solved=($(printf "%s\n" "${inarray[@]}"))

# Create an index array the same size as the puzzle array and shuffle it.
inarray=()
i=0
for f in "${arr_puzzle[@]}"; do
    inarray[${#inarray[@]}]=$i
    ((i=i+1))
done
idx_arr=($(printf "%s\n" "${inarray[@]}" | shuf))

# Create the puzzle array that will be used in the book
i=0
page=0
inarray=()
for j in "${idx_arr[@]}"; do
    if [ "$page" -lt "$num_puzzle_pages" ]; then
        idx=${idx_arr[$j]}
        file=${arr_puzzle[$idx]}
        ((i=i+1))

        inarray[${#inarray[@]}]=$file

        if [[ "$i" -ge $n ]]; then
            i=0
            ((page=page+1))
        fi
    fi
done
arr_puzzle_sorted=($(printf "%s\n" "${inarray[@]}" | sort))
# printf "%s\n" "${arr_puzzle_sorted[@]}"


# Create the solved array that will be used in the book
i=0
page=0
inarray=()
for j in "${idx_arr[@]}"; do
    if [ "$page" -lt "$num_puzzle_pages" ]; then
        idx=${idx_arr[$j]}
        file=${arr_solved[$idx]}
        ((i=i+1))

        inarray[${#inarray[@]}]=$file

        if [[ "$i" -ge $n ]]; then
            i=0
            ((page=page+1))
        fi
    fi
done
arr_solved_sorted=($(printf "%s\n" "${inarray[@]}" | sort))
# printf "%s\n" "${arr_solved_sorted[@]}"


j=0
i=0
n=$(( $columns_puzzle * $rows_puzzle * 2 ))
page=0
page_dir=`echo $page | awk '{printf("%09d\n", $1)}'`

for f in "${arr_puzzle_sorted[@]}"; do
    ((i=i+1))
    ((j=j+1))

    mkdir -p book/${mark}/puzzle/${page_dir}/
    cp ${f} book/${mark}/puzzle/${page_dir}/

    if [[ "$i" -ge $n ]]; then
        i=0
        ((page=page+1))

        if [[ $j -lt ${#arr_puzzle_sorted[@]} ]]; then
            page_dir=`echo $page | awk '{printf("%09d\n", $1)}'`
            mkdir -p book/${mark}/puzzle/$page_dir
        fi
    fi

done


j=0
i=0
n=$(( $columns_solved * $rows_solved * 2 ))
page=0
page_dir=`echo $page | awk '{printf("%09d\n", $1)}'`

for f in "${arr_solved_sorted[@]}"; do
    ((i=i+1))
    ((j=j+1))

    mkdir -p book/${mark}/solved/${page_dir}/
    cp ${f} book/${mark}/solved/${page_dir}/

    if [[ "$i" -ge $n ]]; then
        i=0
        ((page=page+1))

        if [[ $j -lt ${#arr_solved_sorted[@]} ]]; then
            page_dir=`echo $page | awk '{printf("%09d\n", $1)}'`
            mkdir -p book/${mark}/solved/$page_dir
        fi
    fi

done

