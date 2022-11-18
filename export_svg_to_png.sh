 #!/bin/bash

set -x

shopt -s nullglob
arr=("cmake-build-debug/out/puzzle"/*)

for f in "${arr[@]}"; do
    bname=`basename ${f} .svg`
    /Applications/Inkscape.app/Contents/MacOS/inkscape --export-dpi=900 --export-filename=cmake-build-debug/out/puzzle/$bname.png $f
done

arr=("cmake-build-debug/out/solved"/*)

for f in "${arr[@]}"; do
    bname=`basename ${f} .svg`
    /Applications/Inkscape.app/Contents/MacOS/inkscape --export-dpi=900 --export-filename=cmake-build-debug/out/solved/$bname.png $f
done

