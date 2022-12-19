#!/usr/bin/python

import sys

# columns=4
# rows=6
columns=int(sys.argv[1])
rows=int(sys.argv[2])
subdir=sys.argv[3]
orientation=sys.argv[4]
idx = 0
gutter = 6

# margin_outer = 75
# margin_inner = 188
# margin_top = 75
# margin_bottom = 75
# page_width = 2550
# page_height = 3300
# gutter = 50

margin_outer = 132
margin_inner = 207
margin_top = 150
margin_bottom = 151
page_width = 2626
page_height = 3450
density=300

print("#!/bin/bash\n")
print("set -x")
print("shopt -s nullglob")
print("filename=`echo $1 | awk '{printf(\"%09d\\n\", $1)}'`")
print("arr=(\"book/" + subdir + "/${filename}/\"/*)")
# print("filename=$1")
print("mkdir -p book_out")
print("mkdir -p book_out/" + subdir)

def gen(num_columns, num_rows, puzzle_dimension, offset, side):
    global idx

    # total_width = (puzzle_dimension * num_columns) + (margin_outer + margin_inner) + (gutter * (num_columns - 1))
    total_width = (puzzle_dimension * num_columns) + (gutter * (num_columns - 1))
    total_height = (puzzle_dimension * num_rows) + (margin_top + margin_bottom) + (gutter * (num_rows - 1))

    x_offset = 0 #int((page_width - total_width) / 2)
    y_offset = 0 #int((page_height - total_height) / 2)

    print("create_" + str(num_columns) + "x" + str(num_rows) + "_" + str(puzzle_dimension) + "_" + str(offset) + "() {")
    print("\tconvert -density " + str(density) + " -quality 100 -size " + str(page_width) + "x" + str(page_height) + " xc:none -gravity northwest \\")

    for row in range(num_rows):
        for column in range(num_columns):
            x = x_offset + (offset) + (column * puzzle_dimension) + (column * gutter)
            y = y_offset + (margin_top) + (row * puzzle_dimension) + (row * gutter)
            print("\t\t\\( ${arr[" + str(idx) + "]} -resize " + str(puzzle_dimension) + "x" + str(puzzle_dimension) + " \\)  -geometry +" + str(x) + "+" + str(y) + " -composite \\")
            idx = idx + 1

    print("\tbook_out/"+ subdir + "/${filename}_" + side + ".pdf")
    print("}")
    print("create_" + str(num_columns) + "x" + str(num_rows) + "_" + str(puzzle_dimension) + "_" + str(offset) + "")


def gen_left(num_columns, num_rows, puzzle_dimension):
    gen(num_columns, num_rows, puzzle_dimension, margin_outer, "left")


def gen_right(num_columns, num_rows, puzzle_dimension):
    gen(num_columns, num_rows, puzzle_dimension, margin_inner, "right")


def genA_left(num_columns, num_rows):

    numerator = page_width - (margin_outer + margin_inner) - (gutter * (num_columns - 1))
    puzzle_dimension = int(numerator / num_columns)

    gen_left(num_columns, num_rows, puzzle_dimension)


def genB_left(num_columns, num_rows):

    numerator = page_height - (margin_top + margin_bottom) - (gutter * (num_rows - 1))
    puzzle_dimension = int(numerator / num_rows)

    gen_left(num_columns, num_rows, puzzle_dimension)


def genA_right(num_columns, num_rows):

    numerator = page_width - (margin_outer + margin_inner) - (gutter * (num_columns - 1))
    puzzle_dimension = int(numerator / num_columns)

    gen_right(num_columns, num_rows, puzzle_dimension)

def genB_right(num_columns, num_rows):

    numerator = page_height - (margin_top + margin_bottom) - (gutter * (num_rows - 1))
    puzzle_dimension = int(numerator / num_rows)

    gen_right(num_columns, num_rows, puzzle_dimension)

if orientation=="a":
    genA_left(columns, rows)
    genA_right(columns, rows)
else:
    genB_left(columns, rows)
    genB_right(columns, rows)


