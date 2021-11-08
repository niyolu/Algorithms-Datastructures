#include <utility>
#include <vector>
#include <iostream>
#include <set>

#define DEBUG 1

#define UNASSIGNED 0
class SudokuSolver {
public:
    using Board = std::vector<std::vector<int>>;
    Board board;
private:

    int dim = 9;

public:
    SudokuSolver() = default;

    void init_board(Board in_board) {
        this->board = std::move(in_board);
    }

    void print_board() {

        std::cout << std::endl;
        for (const auto& row: this->board) {
            std::cout << "|";
            for (auto col: row)
                std::cout << col << "|";
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    bool solve(int row, int col) {
        if (col == this->dim) {
            col = 0;
            ++row;
        }

        if (row == this->dim) {
            return true;
        }

        if (this->board[row][col] != 0)
            return solve(row, col + 1);

        for (int candidate = 1; candidate <= dim; candidate++) {
            if (!valid_move(row, col, candidate)) continue;
            this->board[row][col] = candidate;
#if DEBUG
            print_board();
#endif
            if (solve(row, col + 1))
                return true;
            this->board[row][col] = 0;
        }
        return false;
    }

    bool valid_row(int row, int value) {
        for (int col = 0; col < this->dim; col++)
            if (this->board[row][col] == value)
                return false;
        return true;
    }

    bool valid_col(int col, int value) {
        for (int row = 0; row < this->dim; row++)
            if (this->board[row][col] == value)
                return false;
        return true;
    }

    bool valid_box(int irow, int icol, int value) {
        int box_col = icol - icol % 3;
        int box_row = irow - irow % 3;

        for (int row = 0; row < 3; row++)
            for (int col = 0; col < 3; col++)
                if (this->board[row + box_row][col + box_col] == value)
                    return false;
        return true;
    }

    bool valid_move(int row, int col, int value) {
        return valid_row(row, value) &&
               valid_col(col, value) &&
               valid_box(row, col, value);
    }

    bool board_equals(const Board& other_board) const {
        return this->board == other_board;
    }

};
#if 1
using namespace std;
class checker {

public:
static int valid_row(int row, SudokuSolver::Board grid){
  set<int> s;
  for(int i = 0; i < 9; i++){
    // Checking for values outside 0 and 9;
    // 0 is considered valid because it
    // denotes an empty cell.
    // Removing zeros and the checking for values and
    // outside 1 and 9 is another way of doing
    // the same thing.
    if(grid[row][i] < 0 || grid[row][i] > 9){
      cout<<"Invalid value"<<endl;
      return -1;
    }
    else
    { //Checking for repeated values.
      if(grid[row][i] != 0){
        if(!s.insert(grid[row][i]).second){
          return 0;
        }
      }
    }
  }
  return 1;
}
// Function to check if a given column is valid. It will return:
// -1 if the column contains an invalid value
// 0 if the column contains repeated values
// 1 is the column is valid.
static int valid_col(int col, SudokuSolver::Board grid){
  set<int> s;
  for(int i = 0; i < 9; i++){
    // Checking for values outside 0 and 9;
    // 0 is considered valid because it
    // denotes an empty cell.
    // Removing zeros and the checking for values and
    // outside 1 and 9 is another way of doing
    // the same thing.
    if(grid[i][col] < 0 || grid[i][col] > 9){
      cout<<"Invalid value"<<endl;
      return -1;
    }
    else
    { // Checking for repeated values.
      if(grid[i][col] != 0){
        if(s.insert(grid[i][col]).second == false){
          return 0;
        }
      }
    }
  }
  return 1;
}
// Function to check if all the subsquares are valid. It will return:
// -1 if a subsquare contains an invalid value
// 0 if a subsquare contains repeated values
// 1 if the subsquares are valid.
static int valid_subsquares(SudokuSolver::Board grid){
  for(int row = 0; row < 9; row = row + 3){
    for(int col = 0; col < 9; col = col + 3){
        set<int> s;
        for(int r = row; r < row + 3; r++){
          for(int c = col; c < col + 3; c++){
            // Checking for values outside 0 and 9;
            // 0 is considered valid because it
            // denotes an empty cell.
            // Removing zeros and the checking for values and
            // outside 1 and 9 is another way of doing
            // the same thing.
            if(grid[r][c] < 0 || grid[r][c] > 9){
              cout<<"Invalid value"<<endl;
              return -1;
            }
            else{
              // Checking for repeated values
              if(grid[r][c] != 0){
                if(s.insert(grid[r][c]).second == false){
                  return 0;
                }
              }
            }
          }
        }
    }
  }
  return 1;
}
//Function to check if the board invalid.
static void valid_board(SudokuSolver::Board grid) {
        for (int i = 0; i < 9; i++) {
            int res1 = valid_row(i, grid);
            int res2 = valid_col(i, grid);
            // If a row or a column is invalid, then the board is invalid.
            if (res1 < 1 || res2 < 1) {
                cout << "The board rowcol is invalid" << endl;
                return;
            }
        }
        // if any one the subsquares is invalid, then the board is invalid.
        int res3 = valid_subsquares(grid);
        if (res3 < 1) {
            cout << "The board is box invalid" << endl;
        } else {
            cout << "The board is valid" << endl;
        }
    }
};
#endif