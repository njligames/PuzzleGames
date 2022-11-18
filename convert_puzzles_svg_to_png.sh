#!/bin/bash

set -x

shopt -s nullglob

arr=("cmake-build-debug/out/$1"/*)
columns=$2
rows=$3

i=0
n=$(( $columns * $rows * 2 ))
page=0
page_dir=`echo $page | awk '{printf("%09d\n", $1)}'`

mkdir -p book/$1/$page_dir

for f in "${arr[@]}"; do
   ((i=i+1))
    filename=`echo $i | awk '{printf("%09d\n", $1)}'`
   /Applications/Inkscape.app/Contents/MacOS/inkscape --export-filename=book/$1/$page_dir/$filename.png $f

   if [[ "$i" -ge $n ]]; then
       i=0
       ((page=page+1))
        page_dir=`echo $page | awk '{printf("%09d\n", $1)}'`
        mkdir -p book/$1/$page_dir
   fi
done

