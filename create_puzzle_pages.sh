#!/bin/bash

set -x
shopt -s nullglob
filename=`echo $1 | awk '{printf("%09d\n", $1)}'`
arr=("book/puzzle/${filename}/"/*)
mkdir -p book_out
mkdir -p book_out/puzzle
create_3x4_782_132() {
	convert -density 300 -quality 100 -size 2626x3450 xc:none -gravity northwest \
		\( ${arr[0]} -resize 782x782 \)  -geometry +132+150 -composite \
		\( ${arr[1]} -resize 782x782 \)  -geometry +920+150 -composite \
		\( ${arr[2]} -resize 782x782 \)  -geometry +1708+150 -composite \
		\( ${arr[3]} -resize 782x782 \)  -geometry +132+938 -composite \
		\( ${arr[4]} -resize 782x782 \)  -geometry +920+938 -composite \
		\( ${arr[5]} -resize 782x782 \)  -geometry +1708+938 -composite \
		\( ${arr[6]} -resize 782x782 \)  -geometry +132+1726 -composite \
		\( ${arr[7]} -resize 782x782 \)  -geometry +920+1726 -composite \
		\( ${arr[8]} -resize 782x782 \)  -geometry +1708+1726 -composite \
		\( ${arr[9]} -resize 782x782 \)  -geometry +132+2514 -composite \
		\( ${arr[10]} -resize 782x782 \)  -geometry +920+2514 -composite \
		\( ${arr[11]} -resize 782x782 \)  -geometry +1708+2514 -composite \
	book_out/puzzle/${filename}_left.pdf
}
create_3x4_782_132
create_3x4_782_207() {
	convert -density 300 -quality 100 -size 2626x3450 xc:none -gravity northwest \
		\( ${arr[12]} -resize 782x782 \)  -geometry +207+150 -composite \
		\( ${arr[13]} -resize 782x782 \)  -geometry +995+150 -composite \
		\( ${arr[14]} -resize 782x782 \)  -geometry +1783+150 -composite \
		\( ${arr[15]} -resize 782x782 \)  -geometry +207+938 -composite \
		\( ${arr[16]} -resize 782x782 \)  -geometry +995+938 -composite \
		\( ${arr[17]} -resize 782x782 \)  -geometry +1783+938 -composite \
		\( ${arr[18]} -resize 782x782 \)  -geometry +207+1726 -composite \
		\( ${arr[19]} -resize 782x782 \)  -geometry +995+1726 -composite \
		\( ${arr[20]} -resize 782x782 \)  -geometry +1783+1726 -composite \
		\( ${arr[21]} -resize 782x782 \)  -geometry +207+2514 -composite \
		\( ${arr[22]} -resize 782x782 \)  -geometry +995+2514 -composite \
		\( ${arr[23]} -resize 782x782 \)  -geometry +1783+2514 -composite \
	book_out/puzzle/${filename}_right.pdf
}
create_3x4_782_207
