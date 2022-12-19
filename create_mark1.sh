#!/bin/bash

set -x

columns_puzzle=3
rows_puzzle=4

columns_solved=4
rows_solved=6

num_puzzle_pages=50

mark=Mark1
orientation="b"

bash create_pages.sh ${columns_puzzle} ${rows_puzzle} ${columns_solved} ${rows_solved} ${num_puzzle_pages} ${mark} ${orientation}


