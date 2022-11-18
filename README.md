# PuzzleGames


## Sudoku
Steps to create book. 
1. Run `./cmake-build-debug/PuzzleGames`
    PuzzleGames will output `svg` solutions and puzzles to:  
        `cmake-build-debug/out/puzzle` 
        `cmake-build-debug/out/solved`
2. Run `./export_svg_to_png.sh`
    The pages will be output to `cmake-build-debug/out/puzzle` and `cmake-build-debug/out/solved`.
3. Run `./create_mark1.sh`
    Sudoku_Mark1.pdf will be created.

### New Editions
    copy `./create_mark1.sh` and edit the variables
