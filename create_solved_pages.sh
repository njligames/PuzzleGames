#!/bin/bash

set -x
mark=$2
shopt -s nullglob
filename=`echo $1 | awk '{printf("%09d\n", $1)}'`
arr=("book/Mark3/solved/${filename}/"/*)
mkdir -p book/Mark3/pages/solved
create_4x6_505_75() {
	convert -density 300 -quality 100 -size 2550x3300 xc:none -gravity northwest \
		\( ${arr[0]} -resize 505x505 \)  -geometry +75+150 -composite \
		\( ${arr[1]} -resize 505x505 \)  -geometry +586+150 -composite \
		\( ${arr[2]} -resize 505x505 \)  -geometry +1097+150 -composite \
		\( ${arr[3]} -resize 505x505 \)  -geometry +1608+150 -composite \
		\( ${arr[4]} -resize 505x505 \)  -geometry +75+661 -composite \
		\( ${arr[5]} -resize 505x505 \)  -geometry +586+661 -composite \
		\( ${arr[6]} -resize 505x505 \)  -geometry +1097+661 -composite \
		\( ${arr[7]} -resize 505x505 \)  -geometry +1608+661 -composite \
		\( ${arr[8]} -resize 505x505 \)  -geometry +75+1172 -composite \
		\( ${arr[9]} -resize 505x505 \)  -geometry +586+1172 -composite \
		\( ${arr[10]} -resize 505x505 \)  -geometry +1097+1172 -composite \
		\( ${arr[11]} -resize 505x505 \)  -geometry +1608+1172 -composite \
		\( ${arr[12]} -resize 505x505 \)  -geometry +75+1683 -composite \
		\( ${arr[13]} -resize 505x505 \)  -geometry +586+1683 -composite \
		\( ${arr[14]} -resize 505x505 \)  -geometry +1097+1683 -composite \
		\( ${arr[15]} -resize 505x505 \)  -geometry +1608+1683 -composite \
		\( ${arr[16]} -resize 505x505 \)  -geometry +75+2194 -composite \
		\( ${arr[17]} -resize 505x505 \)  -geometry +586+2194 -composite \
		\( ${arr[18]} -resize 505x505 \)  -geometry +1097+2194 -composite \
		\( ${arr[19]} -resize 505x505 \)  -geometry +1608+2194 -composite \
		\( ${arr[20]} -resize 505x505 \)  -geometry +75+2705 -composite \
		\( ${arr[21]} -resize 505x505 \)  -geometry +586+2705 -composite \
		\( ${arr[22]} -resize 505x505 \)  -geometry +1097+2705 -composite \
		\( ${arr[23]} -resize 505x505 \)  -geometry +1608+2705 -composite \
	book/Mark3/pages/solved/${filename}_left.pdf
}
create_4x6_505_75
create_4x6_505_188() {
	convert -density 300 -quality 100 -size 2550x3300 xc:none -gravity northwest \
		\( ${arr[24]} -resize 505x505 \)  -geometry +188+150 -composite \
		\( ${arr[25]} -resize 505x505 \)  -geometry +699+150 -composite \
		\( ${arr[26]} -resize 505x505 \)  -geometry +1210+150 -composite \
		\( ${arr[27]} -resize 505x505 \)  -geometry +1721+150 -composite \
		\( ${arr[28]} -resize 505x505 \)  -geometry +188+661 -composite \
		\( ${arr[29]} -resize 505x505 \)  -geometry +699+661 -composite \
		\( ${arr[30]} -resize 505x505 \)  -geometry +1210+661 -composite \
		\( ${arr[31]} -resize 505x505 \)  -geometry +1721+661 -composite \
		\( ${arr[32]} -resize 505x505 \)  -geometry +188+1172 -composite \
		\( ${arr[33]} -resize 505x505 \)  -geometry +699+1172 -composite \
		\( ${arr[34]} -resize 505x505 \)  -geometry +1210+1172 -composite \
		\( ${arr[35]} -resize 505x505 \)  -geometry +1721+1172 -composite \
		\( ${arr[36]} -resize 505x505 \)  -geometry +188+1683 -composite \
		\( ${arr[37]} -resize 505x505 \)  -geometry +699+1683 -composite \
		\( ${arr[38]} -resize 505x505 \)  -geometry +1210+1683 -composite \
		\( ${arr[39]} -resize 505x505 \)  -geometry +1721+1683 -composite \
		\( ${arr[40]} -resize 505x505 \)  -geometry +188+2194 -composite \
		\( ${arr[41]} -resize 505x505 \)  -geometry +699+2194 -composite \
		\( ${arr[42]} -resize 505x505 \)  -geometry +1210+2194 -composite \
		\( ${arr[43]} -resize 505x505 \)  -geometry +1721+2194 -composite \
		\( ${arr[44]} -resize 505x505 \)  -geometry +188+2705 -composite \
		\( ${arr[45]} -resize 505x505 \)  -geometry +699+2705 -composite \
		\( ${arr[46]} -resize 505x505 \)  -geometry +1210+2705 -composite \
		\( ${arr[47]} -resize 505x505 \)  -geometry +1721+2705 -composite \
	book/Mark3/pages/solved/${filename}_right.pdf
}
create_4x6_505_188
