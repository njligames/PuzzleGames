#!/bin/bash

set -x

columns_puzzle=2
rows_puzzle=3

columns_solved=4
rows_solved=6

num_puzzle_pages=85

mark=Mark4
orientation="b"

bash create_pages.sh ${columns_puzzle} ${rows_puzzle} ${columns_solved} ${rows_solved} ${num_puzzle_pages} ${mark} ${orientation}

