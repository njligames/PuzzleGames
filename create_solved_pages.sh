#!/bin/bash

set -x
shopt -s nullglob
filename=`echo $1 | awk '{printf("%09d\n", $1)}'`
arr=("book/solved/${filename}/"/*)
mkdir -p book_out
mkdir -p book_out/solved
create_4x6_519_132() {
	convert -density 300 -quality 100 -size 2626x3450 xc:none -gravity northwest \
		\( ${arr[0]} -resize 519x519 \)  -geometry +132+150 -composite \
		\( ${arr[1]} -resize 519x519 \)  -geometry +657+150 -composite \
		\( ${arr[2]} -resize 519x519 \)  -geometry +1182+150 -composite \
		\( ${arr[3]} -resize 519x519 \)  -geometry +1707+150 -composite \
		\( ${arr[4]} -resize 519x519 \)  -geometry +132+675 -composite \
		\( ${arr[5]} -resize 519x519 \)  -geometry +657+675 -composite \
		\( ${arr[6]} -resize 519x519 \)  -geometry +1182+675 -composite \
		\( ${arr[7]} -resize 519x519 \)  -geometry +1707+675 -composite \
		\( ${arr[8]} -resize 519x519 \)  -geometry +132+1200 -composite \
		\( ${arr[9]} -resize 519x519 \)  -geometry +657+1200 -composite \
		\( ${arr[10]} -resize 519x519 \)  -geometry +1182+1200 -composite \
		\( ${arr[11]} -resize 519x519 \)  -geometry +1707+1200 -composite \
		\( ${arr[12]} -resize 519x519 \)  -geometry +132+1725 -composite \
		\( ${arr[13]} -resize 519x519 \)  -geometry +657+1725 -composite \
		\( ${arr[14]} -resize 519x519 \)  -geometry +1182+1725 -composite \
		\( ${arr[15]} -resize 519x519 \)  -geometry +1707+1725 -composite \
		\( ${arr[16]} -resize 519x519 \)  -geometry +132+2250 -composite \
		\( ${arr[17]} -resize 519x519 \)  -geometry +657+2250 -composite \
		\( ${arr[18]} -resize 519x519 \)  -geometry +1182+2250 -composite \
		\( ${arr[19]} -resize 519x519 \)  -geometry +1707+2250 -composite \
		\( ${arr[20]} -resize 519x519 \)  -geometry +132+2775 -composite \
		\( ${arr[21]} -resize 519x519 \)  -geometry +657+2775 -composite \
		\( ${arr[22]} -resize 519x519 \)  -geometry +1182+2775 -composite \
		\( ${arr[23]} -resize 519x519 \)  -geometry +1707+2775 -composite \
	book_out/solved/${filename}_left.pdf
}
create_4x6_519_132
create_4x6_519_207() {
	convert -density 300 -quality 100 -size 2626x3450 xc:none -gravity northwest \
		\( ${arr[24]} -resize 519x519 \)  -geometry +207+150 -composite \
		\( ${arr[25]} -resize 519x519 \)  -geometry +732+150 -composite \
		\( ${arr[26]} -resize 519x519 \)  -geometry +1257+150 -composite \
		\( ${arr[27]} -resize 519x519 \)  -geometry +1782+150 -composite \
		\( ${arr[28]} -resize 519x519 \)  -geometry +207+675 -composite \
		\( ${arr[29]} -resize 519x519 \)  -geometry +732+675 -composite \
		\( ${arr[30]} -resize 519x519 \)  -geometry +1257+675 -composite \
		\( ${arr[31]} -resize 519x519 \)  -geometry +1782+675 -composite \
		\( ${arr[32]} -resize 519x519 \)  -geometry +207+1200 -composite \
		\( ${arr[33]} -resize 519x519 \)  -geometry +732+1200 -composite \
		\( ${arr[34]} -resize 519x519 \)  -geometry +1257+1200 -composite \
		\( ${arr[35]} -resize 519x519 \)  -geometry +1782+1200 -composite \
		\( ${arr[36]} -resize 519x519 \)  -geometry +207+1725 -composite \
		\( ${arr[37]} -resize 519x519 \)  -geometry +732+1725 -composite \
		\( ${arr[38]} -resize 519x519 \)  -geometry +1257+1725 -composite \
		\( ${arr[39]} -resize 519x519 \)  -geometry +1782+1725 -composite \
		\( ${arr[40]} -resize 519x519 \)  -geometry +207+2250 -composite \
		\( ${arr[41]} -resize 519x519 \)  -geometry +732+2250 -composite \
		\( ${arr[42]} -resize 519x519 \)  -geometry +1257+2250 -composite \
		\( ${arr[43]} -resize 519x519 \)  -geometry +1782+2250 -composite \
		\( ${arr[44]} -resize 519x519 \)  -geometry +207+2775 -composite \
		\( ${arr[45]} -resize 519x519 \)  -geometry +732+2775 -composite \
		\( ${arr[46]} -resize 519x519 \)  -geometry +1257+2775 -composite \
		\( ${arr[47]} -resize 519x519 \)  -geometry +1782+2775 -composite \
	book_out/solved/${filename}_right.pdf
}
create_4x6_519_207
