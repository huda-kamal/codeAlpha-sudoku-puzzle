#include <iostream>   // For cout
#include <vector>     // For vector

using namespace std;

// Function to print the Sudoku gridnnnnnnn
void printSudoku(const vector<vector<int>>& board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool isSafe(const vector<vector<int>>& board, int row, int col, int num) {
    // Check the row
    for (int x = 0; x < 9; x++) {
        if (board[row][x] == num) {
            return false;
        }
    }

    // Check the column
    for (int x = 0; x < 9; x++) {
        if (board[x][col] == num) {
            return false;
        }
    }

    // Check the 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku using backtracking
bool solveSudoku(vector<vector<int>>& board) {
    int row = -1;
    int col = -1;
    bool empty = true;

    // Find an empty cell (denoted by 0)
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == 0) {
                row = i;
                col = j;
                empty = false;
                break;
            }
        }
        if (!empty) {
            break;
        }
    }

    // No empty cell left, the Sudoku is solved
    if (empty) {
        return true;
    }

    // Try digits 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;

            // Recursively try to solve the rest of the board
            if (solveSudoku(board)) {
                return true;
            }

            // Backtrack if no solution is found
            board[row][col] = 0;
        }
    }

    // No solution found, return false
    return false;
}

int main() {
    // Example Sudoku puzzle (0 denotes empty cells)
    vector<vector<int>> board = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(board)) {
        cout << "Sudoku solved:" << endl;
        printSudoku(board);
    } else {
        cout << "No solution exists!" << endl;
    }

    return 0;
}

