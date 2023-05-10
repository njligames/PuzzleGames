 #!/bin/bash

set -x

mark=${1}
basedir=cmake-build-debug/out/${mark}

shopt -s nullglob
arr=("$basedir/puzzle"/*)

mkdir -p ${basedir}/puzzle
mkdir -p ${basedir}/solved

for f in "${arr[@]}"; do
    bname=`basename ${f} .svg`
    /Applications/Inkscape.app/Contents/MacOS/inkscape --export-dpi=900 --export-filename=${basedir}/puzzle/$bname.png $f
done

# arr=("out/solved"/*)
arr=("$basedir/solved"/*)

for f in "${arr[@]}"; do
    bname=`basename ${f} .svg`
    /Applications/Inkscape.app/Contents/MacOS/inkscape --export-dpi=900 --export-filename=${basedir}/solved/$bname.png $f
done

