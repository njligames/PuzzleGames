#!/bin/bash

set -x

mark=$1

shopt -s nullglob
puzzle=("book/${mark}/pages/puzzle"/*)
solved=("book/${mark}/pages/solved"/*)

/System/Library/Automator/Combine\ PDF\ Pages.action/Contents/MacOS/join --output ./book/${mark}/Sudoku_${mark}.pdf ./book/${mark}/Cover_${mark}.pdf ${puzzle[*]} ${solved[*]} ./book/${mark}/Back_${mark}.pdf --verbose

open ./book/${mark}/Sudoku_${mark}.pdf

