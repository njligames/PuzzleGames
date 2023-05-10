#!/bin/bash

columns=$1
rows=$2
orientation=$3
mark=$4

python3 generate_imagemagick_bash_script.py $columns $rows solved $orientation $mark > create_solved_pages.sh

