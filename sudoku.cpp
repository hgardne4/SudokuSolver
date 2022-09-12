// Henry Gardner
// Sudoku Solver in C++

#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

// creating a grid object that will describe a sudoku board
// which is just a 2d array of integers, assuming 9x9
class Grid {
	public:
		// storing the board in a 2d array
		int board[9][9];
		// function to print the sudoku board
		void print_board() {
			cout << "\n          SUDOKU         \n";
			// top
			cout << "-------------------------\n";
			for(int row = 0; row < 9; row++){
				// spacing for columns
				if(row == 3 || row == 6)
					cout << "|-----------------------|\n";
				cout << "| ";
				for(int col = 0; col < 9; col++){
					// spacing for rows
					if(col == 2 || col == 5)
						cout << board[row][col] << " | ";
					else
						cout << board[row][col] << " ";
				}
				// right side
				cout << "|\n";
			}
			// bottom
			cout << "-------------------------\n\n";
		}
};

/* 
Boolean function to return whether or not a number is possible
in a location of the grid.
Inputs:
	grid    -> an instance of the sudoku board
	row     -> row location of potential placement
	col     -> col location of potential placement
	attempt -> the number we are trying to place in the board
*/
bool valid(Grid grid, int row, int col, int attempt) {
	// first make sure the spot isn't already filled
	if(grid.board[row][col] != 0)
		return false;
	// first check if that number exists in that row
	for(int i = 0; i < 9; i++) 
		if(grid.board[i][col] == attempt)
			return false;
	// then check column
	for(int j = 0; j < 9; j++)
		if(grid.board[row][j] == attempt)
			return false;
	// now check within the "box" 
	int tempRow = (row/3)*3;
	int tempCol = (col/3)*3;
	// now loop through that box and verify the number isn't in it:
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if(grid.board[tempRow+i][tempCol+j] == attempt)
				return false;
	// o/w this is a propper attempt
	return true;	
}


//SOLVE Function that completes the sudoku puzzle using recursion and backtracking
void solve(Grid grid){
	// loop through the whole board to check for empty spaces
	for(int row = 0; row < 9; row++){
		for(int col = 0; col < 9; col++){
			if(grid.board[row][col] == 0){
				// now check all possible numbers in {1, ..., 9}
				for(int temp = 1; temp < 10; temp++){
					// if valid, update it and resolve
					if(valid(grid, row, col, temp)){
						grid.board[row][col] = temp;
						solve(grid);
						// backtracking step
						grid.board[row][col] = 0;
					}
				}
				// break this iteration if it is not valid
				return;
			}
		}
	}
	// output result, will only output the first solution
	grid.print_board();
}

// "main" function, where the program begins
int main() {
	Grid grid;
	cout << "Enter the 9x9 sudoku puzzle wished to be solved with space separated values:\n";
	// read input to get the board (can copy and paste)
	for(int row = 0; row < 9; row++){
		for(int col = 0; col < 9; col++){
			cin >> grid.board[row][col];
		}
	}
	cout << "\nStarting board:\n";
	grid.print_board();
	cout << "Solved board:\n";

	// measure the time it took to solve this puzzle:
	auto start = high_resolution_clock::now();
	solve(grid);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	// output time of completion
	cout << "This puzzle took ~" << (float)duration.count()/(float)1000 << " seconds to complete.\n";
	return 0;
}