#!/bin/bash

set -x

columns_puzzle=1
rows_puzzle=2

columns_solved=3
rows_solved=4

num_puzzle_pages=3

mark=Mark2
orientation="b"

bash create_pages.sh ${columns_puzzle} ${rows_puzzle} ${columns_solved} ${rows_solved} ${num_puzzle_pages} ${mark} ${orientation}

