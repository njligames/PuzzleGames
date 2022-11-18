cmake_minimum_required(VERSION 3.17)
project(PuzzleGames)

set(CMAKE_CXX_STANDARD 14)

add_executable(PuzzleGames main.cpp MazeCreator.cpp Sudoku.cpp ThreadPool.cpp NameGenerator.cpp)
