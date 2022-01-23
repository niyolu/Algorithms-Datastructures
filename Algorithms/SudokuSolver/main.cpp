#include <iostream>
#include "SudokuSolver.h"

int main() {
    SudokuSolver solver = SudokuSolver();
    /* // wikipedia
    SudokuSolver::Board board = {
            { 5,3,0,0,7,0,0,0,0 },
            { 6,0,0,1,9,5,0,0,0 },
            { 0,9,8,0,0,0,0,6,0 },
            { 8,0,0,0,6,0,0,0,3 },
            { 4,0,0,8,0,3,0,0,1 },
            { 7,0,0,0,2,0,0,0,6 },
            { 0,6,0,0,0,0,2,8,0 },
            { 0,0,0,4,1,9,0,0,5 },
            { 0,0,0,0,8,0,0,7,9 }
    };
     */
    SudokuSolver::Board board = {
            { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
            { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
            { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
            { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
            { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
            { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
            { 0, 0, 5, 2, 0, 6, 3, 0, 0 }
    };
    solver.init_board(board);
    solver.print_board();
    // std::cout << solver.valid_move(0,2,4) << std::endl;
    std::cout << solver.solve(0, 0) << std::endl;
    solver.print_board();
    checker::valid_board(solver.board);


    SudokuSolver::Board expected = {
            { 3,1,6,5,7,8,4,9,2 },
            { 5,2,9,1,3,4,7,6,8 },
            { 4,8,7,6,2,9,5,3,1 },
            { 2,6,3,4,1,5,9,8,7 },
            { 9,7,4,8,6,3,1,2,5 },
            { 8,5,1,7,9,2,6,4,3 },
            { 1,3,8,9,4,7,2,5,6 },
            { 6,9,2,3,5,1,8,7,4 },
            { 7,4,5,2,8,6,3,1,9 }
    };

    checker::valid_board(expected);

    std::cout << "TC success? " << solver.board_equals(expected) << std::endl;

    return 0;
}
