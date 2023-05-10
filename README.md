# PuzzleGames

## Sudoku
Steps to create book. 

1. Change directories: `cd cmake-build-debug`

2. Run `./cmake-build-debug/PuzzleGames`
    PuzzleGames will output `svg` solutions and puzzles to:  
        `cmake-build-debug/out/puzzle` 
        `cmake-build-debug/out/solved`

3. Create a folder inside of the `cmake-build-debug` folder, for the book title. (ex: Mark2)

4. Run `./export_svg_to_png.sh Mark2`
    The pages will be output to `cmake-build-debug/out/Mark2/puzzle` and `cmake-build-debug/out/Mark2/solved`.

5. Create the following files:
    * A cover pdf (Cover_Mark2.pdf)
    * A back pdf (Back_Mark2.pdf)
    * A bash file that calls `create_pages.sh` (just copy `create_mark1.sh` and edit)

5. Run `./create_mark2.sh`
    Sudoku_Mark2.pdf will be created in the `book/Mark2/` folder.

TODO:
* move the doc files to the book/mark# folder.
* user the merge_files.sh in create_pages.sh

