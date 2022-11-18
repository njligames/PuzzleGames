//
//  Sudoku.hpp
//  PuzzleGames
//
//  Created by James Folk on 10/27/22.
//

#ifndef Sudoku_hpp
#define Sudoku_hpp

#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Sudoku {
private:
  int grid[9][9];
  int solnGrid[9][9];
  int guessNum[9];
  int gridPos[81];
  int difficultyLevel;
  bool grid_status;

public:
  Sudoku ();
  ~Sudoku ();
  Sudoku (string, bool row_major=true);
  void fillEmptyDiagonalBox(int);
  void createSeed();
  void printGrid();
  string createName();
  bool solveGrid();
  string getGrid();
  void countSoln(int &number);
  void genPuzzle();
  bool verifyGridStatus();
  void printSVG(bool, string, string, string="");
  void calculateDifficulty();
  int  branchDifficultyScore();
  int difficulty()const;
};

#endif /* Sudoku_hpp */
