#!/bin/bash

set -x
mark=$2
shopt -s nullglob
filename=`echo $1 | awk '{printf("%09d\n", $1)}'`
arr=("book/Mark2/puzzle/${filename}/"/*)
mkdir -p book/Mark2/pages/puzzle
create_3x4_754_75() {
	convert -density 300 -quality 100 -size 2550x3300 xc:none -gravity northwest \
		\( ${arr[0]} -resize 754x754 \)  -geometry +75+150 -composite \
		\( ${arr[1]} -resize 754x754 \)  -geometry +835+150 -composite \
		\( ${arr[2]} -resize 754x754 \)  -geometry +1595+150 -composite \
		\( ${arr[3]} -resize 754x754 \)  -geometry +75+910 -composite \
		\( ${arr[4]} -resize 754x754 \)  -geometry +835+910 -composite \
		\( ${arr[5]} -resize 754x754 \)  -geometry +1595+910 -composite \
		\( ${arr[6]} -resize 754x754 \)  -geometry +75+1670 -composite \
		\( ${arr[7]} -resize 754x754 \)  -geometry +835+1670 -composite \
		\( ${arr[8]} -resize 754x754 \)  -geometry +1595+1670 -composite \
		\( ${arr[9]} -resize 754x754 \)  -geometry +75+2430 -composite \
		\( ${arr[10]} -resize 754x754 \)  -geometry +835+2430 -composite \
		\( ${arr[11]} -resize 754x754 \)  -geometry +1595+2430 -composite \
	book/Mark2/pages/puzzle/${filename}_left.pdf
}
create_3x4_754_75
create_3x4_754_188() {
	convert -density 300 -quality 100 -size 2550x3300 xc:none -gravity northwest \
		\( ${arr[12]} -resize 754x754 \)  -geometry +188+150 -composite \
		\( ${arr[13]} -resize 754x754 \)  -geometry +948+150 -composite \
		\( ${arr[14]} -resize 754x754 \)  -geometry +1708+150 -composite \
		\( ${arr[15]} -resize 754x754 \)  -geometry +188+910 -composite \
		\( ${arr[16]} -resize 754x754 \)  -geometry +948+910 -composite \
		\( ${arr[17]} -resize 754x754 \)  -geometry +1708+910 -composite \
		\( ${arr[18]} -resize 754x754 \)  -geometry +188+1670 -composite \
		\( ${arr[19]} -resize 754x754 \)  -geometry +948+1670 -composite \
		\( ${arr[20]} -resize 754x754 \)  -geometry +1708+1670 -composite \
		\( ${arr[21]} -resize 754x754 \)  -geometry +188+2430 -composite \
		\( ${arr[22]} -resize 754x754 \)  -geometry +948+2430 -composite \
		\( ${arr[23]} -resize 754x754 \)  -geometry +1708+2430 -composite \
	book/Mark2/pages/puzzle/${filename}_right.pdf
}
create_3x4_754_188
