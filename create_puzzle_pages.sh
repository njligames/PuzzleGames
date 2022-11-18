#!/bin/bash

set -x
shopt -s nullglob
filename=`echo $1 | awk '{printf("%09d\n", $1)}'`
arr=("book/puzzle/${filename}/"/*)
mkdir -p book_out
mkdir -p book_out/puzzle
create_1x2_373_20() {
	convert -size 612x792 xc:none -gravity northwest \
		\( ${arr[0]} -resize 373x373 \)  -geometry +139+20 -composite \
		\( ${arr[1]} -resize 373x373 \)  -geometry +139+399 -composite \
	book_out/puzzle/${filename}_left.pdf
}
create_1x2_373_20
create_1x2_373_45() {
	convert -size 612x792 xc:none -gravity northwest \
		\( ${arr[2]} -resize 373x373 \)  -geometry +164+20 -composite \
		\( ${arr[3]} -resize 373x373 \)  -geometry +164+399 -composite \
	book_out/puzzle/${filename}_right.pdf
}
create_1x2_373_45
