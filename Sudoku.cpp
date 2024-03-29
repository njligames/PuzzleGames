//
//  Sudoku.cpp
//  PuzzleGames
//
//  Created by James Folk on 10/27/22.
//

#include "Sudoku.hpp"

#include <random>
#include <algorithm>

#define UNASSIGNED 0

// START: Get grid as string in row major order
string Sudoku::getGrid()
{
  string s = "";
  for(int row_num=0; row_num<9; ++row_num)
  {
    for(int col_num=0; col_num<9; ++col_num)
    {
      s = s + to_string(grid[row_num][col_num]);
    }
  }

  return s;
}
// END: Get grid as string in row major order


// START: Generate random number
int genRandNum(int maxLimit)
{
  return rand()%maxLimit;
}
// END: Generate random number


// START: Helper functions for solving grid
bool FindUnassignedLocation(int grid[9][9], int &row, int &col)
{
    for (row = 0; row < 9; row++)
    {
        for (col = 0; col < 9; col++)
        {
            if (grid[row][col] == UNASSIGNED)
                return true;
        }
    }

    return false;
}

bool UsedInRow(int grid[9][9], int row, int num)
{
    for (int col = 0; col < 9; col++)
    {
        if (grid[row][col] == num)
            return true;
    }

    return false;
}

bool UsedInCol(int grid[9][9], int col, int num)
{
    for (int row = 0; row < 9; row++)
    {
        if (grid[row][col] == num)
            return true;
    }

    return false;
}

bool UsedInBox(int grid[9][9], int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (grid[row+boxStartRow][col+boxStartCol] == num)
                return true;
        }
    }

    return false;
}

bool isSafe(int grid[9][9], int row, int col, int num)
{
    return !UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) && !UsedInBox(grid, row - row%3 , col - col%3, num);
}
// END: Helper functions for solving grid


// START: Create seed grid
void Sudoku::fillEmptyDiagonalBox(int idx)
{
  int start = idx*3;
//  random_shuffle(this->guessNum, (this->guessNum) + 9, genRandNum);
    
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(this->guessNum, (this->guessNum) + 9, g);
  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; j < 3; ++j)
    {
      this->grid[start+i][start+j] = guessNum[i*3+j];
    }
  }
}

void Sudoku::createSeed()
{
  /* Fill diagonal boxes to form:
      x | . | .
      . | x | .
      . | . | x
  */
  this->fillEmptyDiagonalBox(0);
  this->fillEmptyDiagonalBox(1);
  this->fillEmptyDiagonalBox(2);

  /* Fill the remaining blocks:
      x | x | x
      x | x | x
      x | x | x
  */
  this->solveGrid(); // TODO: not truly random, but still good enough because we generate random diagonals.

  // Saving the solution grid
  for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      this->solnGrid[i][j] = this->grid[i][j];
    }
  }
}
// END: Create seed grid


// START: Intialising
Sudoku::Sudoku() 
{

  // initialize difficulty level
  this->difficultyLevel = 0;

  // Randomly shuffling the array of removing grid positions
  for(int i=0;i<81;i++)
  {
    this->gridPos[i] = i;
  }

//  random_shuffle(this->gridPos, (this->gridPos) + 81, genRandNum);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(this->gridPos, (this->gridPos) + 81, g);

  // Randomly shuffling the guessing number array
  for(int i=0;i<9;i++)
  {
    this->guessNum[i]=i+1;
  }

//  random_shuffle(this->guessNum, (this->guessNum) + 9, genRandNum);
    std::shuffle(this->guessNum, (this->guessNum) + 9, g);

  // Initialising the grid
  for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      this->grid[i][j]=0;
    }
  }

  grid_status = true;
}
// END: Initialising
Sudoku::~Sudoku () {
}


// START: Custom Initialising with grid passed as argument
Sudoku::Sudoku(string grid_str, bool row_major)
{
  if(grid_str.length() != 81)
  {
    grid_status=false;
    return;
  }

  // First pass: Check if all cells are valid
  for(int i=0; i<81; ++i)
  {
    int curr_num = grid_str[i]-'0';
    if(!((curr_num == UNASSIGNED) || (curr_num > 0 && curr_num < 10)))
    {
      grid_status=false;
      return;
    }

    if(row_major) grid[i/9][i%9] = curr_num;
    else          grid[i%9][i/9] = curr_num;
  }

  // Second pass: Check if all columns are valid
  for (int col_num=0; col_num<9; ++col_num)
  {
    bool nums[10]={false};
    for (int row_num=0; row_num<9; ++row_num)
    {
      int curr_num = grid[row_num][col_num];
      if(curr_num!=UNASSIGNED && nums[curr_num]==true)
      {
        grid_status=false;
        return;
      }
      nums[curr_num] = true;
    }
  }

  // Third pass: Check if all rows are valid
  for (int row_num=0; row_num<9; ++row_num)
  {
    bool nums[10]={false};
    for (int col_num=0; col_num<9; ++col_num)
    {
      int curr_num = grid[row_num][col_num];
      if(curr_num!=UNASSIGNED && nums[curr_num]==true)
      {
        grid_status=false;
        return;
      }
      nums[curr_num] = true;
    }
  }

  // Fourth pass: Check if all blocks are valid
  for (int block_num=0; block_num<9; ++block_num)
  {
    bool nums[10]={false};
    for (int cell_num=0; cell_num<9; ++cell_num)
    {
      int curr_num = grid[((int)(block_num/3))*3 + (cell_num/3)][((int)(block_num%3))*3 + (cell_num%3)];
      if(curr_num!=UNASSIGNED && nums[curr_num]==true)
      {
        grid_status=false;
        return;
      }
      nums[curr_num] = true;
    }
  }

  // Randomly shuffling the guessing number array
  for(int i=0;i<9;i++)
  {
    this->guessNum[i]=i+1;
  }

//  random_shuffle(this->guessNum, (this->guessNum) + 9, genRandNum);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(this->guessNum, (this->guessNum) + 9, g);

  grid_status = true;
}
// END: Custom Initialising


// START: Verification status of the custom grid passed
bool Sudoku::verifyGridStatus()
{
  return grid_status;
}
// END: Verification of the custom grid passed


// START: Printing the grid
void Sudoku::printGrid()
{
  for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      if(grid[i][j] == 0)
    cout<<".";
      else
    cout<<grid[i][j];
      cout<<"|";
    }
    cout<<endl;
  }

  cout<<"\nDifficulty of current sudoku(0 being easiest): "<<this->difficultyLevel;
  cout<<endl;
}
// END: Printing the grid
string Sudoku::createName()
{
    string ret;

  for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      if(grid[i][j] == 0)
          ret += "0";
      else
          ret += to_string(grid[i][j]);
    }
  }

  return ret;

}


// START: Modified Sudoku solver
bool Sudoku::solveGrid()
{
    int row, col;

    // If there is no unassigned location, we are done
    if (!FindUnassignedLocation(this->grid, row, col))
       return true; // success!

    // Consider digits 1 to 9
    for (int num = 0; num < 9; num++)
    {
        // if looks promising
        if (isSafe(this->grid, row, col, this->guessNum[num]))
        {
            // make tentative assignment
            this->grid[row][col] = this->guessNum[num];

            // return, if success, yay!
            if (solveGrid())
                return true;

            // failure, unmake & try again
            this->grid[row][col] = UNASSIGNED;
        }
    }

    return false; // this triggers backtracking

}
// END: Modified Sudoku Solver


// START: Check if the grid is uniquely solvable
void Sudoku::countSoln(int &number)
{
  int row, col;

  if(!FindUnassignedLocation(this->grid, row, col))
  {
    number++;
    return ;
  }


  for(int i=0;i<9 && number<2;i++)
  {
      if( isSafe(this->grid, row, col, this->guessNum[i]) )
      {
        this->grid[row][col] = this->guessNum[i];
        countSoln(number);
      }

      this->grid[row][col] = UNASSIGNED;
  }

}
// END: Check if the grid is uniquely solvable


// START: Gneerate puzzle
void Sudoku::genPuzzle()
{
  for(int i=0;i<81;i++)
  {
    int x = (this->gridPos[i])/9;
    int y = (this->gridPos[i])%9;
    int temp = this->grid[x][y];
    this->grid[x][y] = UNASSIGNED;

    // If now more than 1 solution , replace the removed cell back.
    int check=0;
    countSoln(check);
    if(check!=1)
    {
      this->grid[x][y] = temp;
    }
  }
}
// END: Generate puzzle


// START: Printing into SVG file
void Sudoku::printSVG(bool solved, string name, string puzzle_name, string path)
{
    string svgheadText = R"(
 <?xml version="1.0" encoding="UTF-8" standalone="no"?>
 <svg version="1.1"
      baseProfile="full"
      width="450" height="490"
      xmlns="http://www.w3.org/2000/svg" style="padding:10px;margin:10px">
  
   <polyline points="0,0 450,0 450,450 0,450 0,0"
   style="fill:none;stroke:black;stroke-width:5" />
   <polyline points="0,50 450,50" style="fill:none; stroke:black ; stroke-width:1" />
   <polyline points="0,100 450,100" style="fill:none; stroke:black ; stroke-width:1" />
   <polyline points="0,150 450,150" style="fill:none; stroke:black ; stroke-width:5" />
   <polyline points="0,200 450,200" style="fill:none; stroke:black ; stroke-width:1" />
   <polyline points="0,250 450,250" style="fill:none; stroke:black ; stroke-width:1" />
   <polyline points="0,300 450,300" style="fill:none; stroke:black ; stroke-width:5" />
   <polyline points="0,350 450,350" style="fill:none; stroke:black ; stroke-width:1" />
   <polyline points="0,400 450,400" style="fill:none; stroke:black ; stroke-width:1" />
   <polyline points="50,0 50,450" style="fill:none; stroke:black ; stroke-width:1" />
   <polyline points="100,0 100,450" style="fill:none; stroke:black ; stroke-width:1" />
   <polyline points="150,0 150,450" style="fill:none; stroke:black ; stroke-width:5" />
   <polyline points="200,0 200,450" style="fill:none; stroke:black ; stroke-width:1" />
   <polyline points="250,0 250,450" style="fill:none; stroke:black ; stroke-width:1" />
   <polyline points="300,0 300,450" style="fill:none; stroke:black ; stroke-width:5" />
   <polyline points="350,0 350,450" style="fill:none; stroke:black ; stroke-width:1" />
   <polyline points="400,0 400,450" style="fill:none; stroke:black ; stroke-width:1" />
                       )";

  string temp_path("out/puzzle/puzzle.sudoku." + name + ".svg");
  if(solved)
  {
      temp_path = "out/solved/solved.sudoku." + name + ".svg";
  }

  string cmd;

    
  system("mkdir -p out/puzzle");
  system("mkdir -p out/solved");

    // cmd = "mkdir -p out/puzzle/" + to_string(this->difficultyLevel) + "/";
    // system(cmd.c_str());
    // cmd = "mkdir -p out/solved/" + to_string(this->difficultyLevel) + "/";
    // system(cmd.c_str());
  

  ofstream outFile(temp_path, std::ofstream::out);
  outFile << svgheadText;

  for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      if(this->grid[i][j]!=0)
      {
        int x = (50*j + 16);
        int y = (50*i + 35);

        stringstream text;
        text<<"<text x=\""<<x<<"\" y=\""<<y<<"\" style=\"font-weight:bold\" font-size=\"30px\">"<<this->grid[i][j]<<"</text>\n";

        outFile << text.rdbuf();
      }
    }
  }


    outFile << "<text x=\"10\" y=\"480\" style=\"font-weight:bold\" font-size=\"28px\">" << puzzle_name <<"</text>\n";
//    outFile << "<image width=\"30\" height=\"30\" preserveAspectRatio=\"none\" xlink:href=\"/Users/jamesfolk/Work/Sudoku-Generator/level.png\" id=\"image728\" x=\"10\" y=\"455\" />\n";
    outFile << "</svg>";

    outFile.close();
}
// END: Printing into SVG file


// START: Calculate branch difficulty score
int Sudoku::branchDifficultyScore()
{
   int emptyPositions = -1;
   int tempGrid[9][9];
   int sum=0;

   for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      tempGrid[i][j] = this->grid[i][j];
    }
  }

   while(emptyPositions!=0)
   {
     vector<vector<int> > empty;

     for(int i=0;i<81;i++)
     {
        if(tempGrid[(int)(i/9)][(int)(i%9)] == 0)
        {
             vector<int> temp;
      temp.push_back(i);
    
      for(int num=1;num<=9;num++)
      {
        if(isSafe(tempGrid,i/9,i%9,num))
        {
          temp.push_back(num);
        }
      }

      empty.push_back(temp);
        }
      
     }

     if(empty.size() == 0)
     {
       cout<<"Hello: "<<sum<<endl;
       return sum;
     }

     int minIndex = 0;

     int check = empty.size();
     for(int i=0;i<check;i++)
     {
       if(empty[i].size() < empty[minIndex].size())
      minIndex = i;
     }

     int branchFactor=empty[minIndex].size();
     int rowIndex = empty[minIndex][0]/9;
     int colIndex = empty[minIndex][0]%9;

     tempGrid[rowIndex][colIndex] = this->solnGrid[rowIndex][colIndex];
     sum = sum + ((branchFactor-2) * (branchFactor-2)) ;

     emptyPositions = empty.size() - 1;
   }

   return sum;

}
// END: Finish branch difficulty score

int Sudoku::difficulty()const {
    int l(difficultyLevel);
    if(l > 2500)l = 2500;
    float t = l / 2500.0;
    return (int)(t * 100.0);
}

// START: Calculate difficulty level of current grid
void Sudoku::calculateDifficulty()
{
  int B = branchDifficultyScore();
  int emptyCells = 0;

  for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
    if(this->grid[i][j] == 0)
       emptyCells++;
    }
  }

  this->difficultyLevel = B*100 + emptyCells;
}
// END: calculating difficulty level
