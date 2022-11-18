#!/bin/bash

set -x
shopt -s nullglob
filename=`echo $1 | awk '{printf("%09d\n", $1)}'`
arr=("book/solved/${filename}/"/*)
mkdir -p book_out
mkdir -p book_out/solved
create_3x4_183_20() {
	convert -size 612x792 xc:none -gravity northwest \
		\( ${arr[0]} -resize 183x183 \)  -geometry +45+21 -composite \
		\( ${arr[1]} -resize 183x183 \)  -geometry +234+21 -composite \
		\( ${arr[2]} -resize 183x183 \)  -geometry +423+21 -composite \
		\( ${arr[3]} -resize 183x183 \)  -geometry +45+210 -composite \
		\( ${arr[4]} -resize 183x183 \)  -geometry +234+210 -composite \
		\( ${arr[5]} -resize 183x183 \)  -geometry +423+210 -composite \
		\( ${arr[6]} -resize 183x183 \)  -geometry +45+399 -composite \
		\( ${arr[7]} -resize 183x183 \)  -geometry +234+399 -composite \
		\( ${arr[8]} -resize 183x183 \)  -geometry +423+399 -composite \
		\( ${arr[9]} -resize 183x183 \)  -geometry +45+588 -composite \
		\( ${arr[10]} -resize 183x183 \)  -geometry +234+588 -composite \
		\( ${arr[11]} -resize 183x183 \)  -geometry +423+588 -composite \
	book_out/solved/${filename}_left.pdf
}
create_3x4_183_20
create_3x4_183_45() {
	convert -size 612x792 xc:none -gravity northwest \
		\( ${arr[12]} -resize 183x183 \)  -geometry +70+21 -composite \
		\( ${arr[13]} -resize 183x183 \)  -geometry +259+21 -composite \
		\( ${arr[14]} -resize 183x183 \)  -geometry +448+21 -composite \
		\( ${arr[15]} -resize 183x183 \)  -geometry +70+210 -composite \
		\( ${arr[16]} -resize 183x183 \)  -geometry +259+210 -composite \
		\( ${arr[17]} -resize 183x183 \)  -geometry +448+210 -composite \
		\( ${arr[18]} -resize 183x183 \)  -geometry +70+399 -composite \
		\( ${arr[19]} -resize 183x183 \)  -geometry +259+399 -composite \
		\( ${arr[20]} -resize 183x183 \)  -geometry +448+399 -composite \
		\( ${arr[21]} -resize 183x183 \)  -geometry +70+588 -composite \
		\( ${arr[22]} -resize 183x183 \)  -geometry +259+588 -composite \
		\( ${arr[23]} -resize 183x183 \)  -geometry +448+588 -composite \
	book_out/solved/${filename}_right.pdf
}
create_3x4_183_45
