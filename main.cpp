#include <iostream>
#include "MazeCreator.hpp"
#include "Sudoku.hpp"
#include "ThreadPool.hpp"
#include "NameGenerator.hpp"

static NameGenerator n;

void sudokuGen(size_t i) {
    // Creating an instance of Sudoku
    Sudoku *puzzle = new Sudoku();

    // Creating a seed for puzzle generation
    puzzle->createSeed();

    // Generating the puzzle
    puzzle->genPuzzle();

    // Calculating difficulty of puzzle
    puzzle->calculateDifficulty();


    n.randomize();
    auto puzzle_name = n.next();
    string name = puzzle_name;

    // std::string old_str = to_string(i); 
    // size_t n_zero = 20;
    // auto puzzle_name = std::string(n_zero - std::min(n_zero, old_str.length()), '0') + old_str;
    puzzle_name = puzzle_name + " (" + to_string(puzzle->difficulty()) + "/100)";

    // testing by printing the grid
    // puzzle->printGrid();

    // Printing the grid into SVG file
    puzzle->printSVG(false, name, puzzle_name);

    puzzle->solveGrid();
    // Printing the grid into SVG file
    puzzle->printSVG(true, name, puzzle_name);

    // freeing the memory
    delete puzzle;
}

void mazeGen() {
    auto maze = MazeCreator::GetInstance()->CreateNew(9*12, 9*8);
    maze->Save();
    maze->SolveMaze();
    maze->Save();
}

int main() {
    ThreadPool thread_pool;

    thread_pool.Start();


    auto amt(std::numeric_limits<size_t>::max());
    for(auto i = 0; i < amt; i++)
        thread_pool.QueueJob([&i] { sudokuGen(i+1); });
    // thread_pool.QueueJob([] { mazeGen(); });
    thread_pool.Stop();

    return 0;
}
