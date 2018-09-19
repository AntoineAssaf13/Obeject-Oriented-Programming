// Lab03.cpp : Defines the entry point for the console application.
//Antoine Assaf: aca432. Lab3: Create a minesweeper game.

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

//I modified Prof. Sterling's interface in cin in order to make it intuitive and have the user able to input numbers 1 through 10 and not 0-9.

struct Tile {
	char tile;
	int adjacent;
	bool visible;
	bool bomb;
};

class Minesweeper {
public:
	int findNeighbors(int row, int col) {
		int bombCounter = 0;
		if (validRow(row+1) && board[row + 1][col].bomb == true) {
			bombCounter++;
		}
		if (validRow(row-1) && board[row - 1][col].bomb == true) {
			bombCounter++;
		}
		if (validCol(col+1) && board[row][col + 1].bomb == true) {
			bombCounter++;
		}
		if (validCol(col-1)&& board[row][col - 1].bomb == true) {
			bombCounter++;
		}
		if (validRow(row-1) && validCol(col-1) && board[row - 1][col - 1].bomb == true) {
			bombCounter++;
		}
		if (validRow(row-1) && validCol(col+1) && board[row - 1][col + 1].bomb == true) {
			bombCounter++;
		}
		if (validRow(row+1) && validCol(col+1) && board[row + 1][col + 1].bomb == true) {
			bombCounter++;
		}
		if (validRow(row+1) && validCol(col-1) && board[row + 1][col - 1].bomb == true) {
			bombCounter++;
		}
		return bombCounter;
	}
	Minesweeper(vector<vector<Tile>>& tilesVector, const int& row, const int& col) : board(tilesVector) {}
	void display(const bool& show_bomb) const {
		if (show_bomb == true) {
			for (int r = 0; r < 10; r++) {
				for (int c = 0; c < 10; c++) {
					if (board[r][c].bomb == true) {
						cout << 'X';
					}
					else {
						if (board[r][c].adjacent == 0) {
							cout << board[r][c].tile;
						}
						else if (board[r][c].adjacent > 0) {
							cout << board[r][c].adjacent;
						}
					}
				}
				cout << endl;
			}
		}
		else if (show_bomb == false) {
			for (int r = 0; r < 10; r++) {
				for (int c = 0; c < 10; c++) {
					if (board[r][c].adjacent == 0) {
						cout << board[r][c].tile;
					}
					else if (board[r][c].adjacent >0) {
						cout << board[r][c].adjacent;
					}
				}
				cout << endl;
			}
		}
	}
	bool done() const {
		for (int r = 0; r < 10; r++) {
			for (int c = 0; c < 10; c++) {
				if (board[r][c].tile == '-' && board[r][c].bomb == false) {
					return false;
				}
			}
		}

		return true;
	}
	bool validRow(const int& row) const {
		if (row >= 0 && row < 10) {
			return true;
		}
		return false;
	}
	bool validCol(const int& col) const {
		if (col >= 0 && col < 10) {
			return true;
		}
		return false;

	}
	bool isVisible(const int& row, const int& col)const {
		if (board[row][col].visible == true) {
			return true;
		}
		else {
			return false;
		}
	}
	bool play(int row, int col) {
		if (board[row][col].bomb == true && board[row][col].visible == false) {
			return false;
		}
		else if (board[row][col].bomb == false && board[row][col].visible == false) {
			int counter;
			counter = findNeighbors(row, col);
			board[row][col].adjacent = counter;
			if (counter == 0) {
				board[row][col].tile = '0';
				board[row][col].visible = true;
				if (validRow(row + 1) && board[row + 1][col].visible == false) {
					play(row + 1, col);
				}
				if (validCol(col + 1)) {
					if (board[row][col + 1].visible == false) {
						play(row, col + 1);
					}
				}
				if (validCol(col - 1)) {
					if (board[row][col - 1].visible == false) {
						play(row, col - 1);
					}
				}
				if (validRow(row - 1)) {
					if (board[row - 1][col].visible == false) {
						play(row - 1, col);
					}
				}
				if (validRow(row + 1) && validCol(col - 1)) {
					if (board[row + 1][col - 1].visible == false) {
						play(row + 1, col - 1);
					}
				}
				if (validRow(row - 1) && validCol(col - 1)) {
					if (board[row - 1][col - 1].visible == false) {
						play(row - 1, col - 1);
					}
				}
				if (validRow(row - 1) && validCol(col + 1)) {
					if (board[row - 1][col + 1].visible == false) {
						play(row - 1, col + 1);
					}
				}
				if (validRow(row + 1) && validCol(col + 1)) {
					if (board[row + 1][col + 1].visible == false) {
						play(row + 1, col + 1);
					}
				}

			}
			else if (counter > 0) {
				board[row][col].tile = '0';
				board[row][col].visible = true;
			}
		}
		return true;
	}
private:
	vector<vector<Tile>> board;

};



void createBoard(vector<vector<Tile>>& tilesVector, const int& row, const int& col) {
	srand(time(0));
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < col; c++) {
			Tile new_tile;
			new_tile.tile = '-';
			new_tile.adjacent = 0;
			new_tile.visible = false;
			if (rand() % 100 < 1) {
				new_tile.bomb = true;
			}
			else {
				new_tile.bomb = false;
			}
			tilesVector[r][c] = new_tile;
		}
	}
}

int main() {
	// creates playing board and a new sweeper class
	vector<vector<Tile>> tilesVector(10, vector<Tile>(10));
	createBoard(tilesVector, 10, 10);

	Minesweeper sweeper(tilesVector, 10, 10);
	// Continue until the only invisible cells are bombs
	while (!sweeper.done()) {
		sweeper.display(false); // display the board without bombs

		int row_sel = -1, col_sel = -1;
		while (row_sel == -1) {
			// Get a valid move
			int r, c;
			cout << "row? ";
			cin >> r;
			if (!sweeper.validRow(r - 1)) {
				cout << "Row out of bounds\n";
				continue;
			}
			cout << "col? ";
			cin >> c;
			if (!sweeper.validCol(c - 1)) {
				cout << "Column out of bounds\n";
				continue;
			}
			if (sweeper.isVisible(r - 1, c - 1)) {
				cout << "Square already visible\n";
				continue;
			}
			row_sel = r - 1;
			col_sel = c - 1;

		}
		// Set selected square to be visible. May effect other cells.
		if (!sweeper.play(row_sel, col_sel)) {
			cout << "BOOM!!!\n";
			sweeper.display(true);
			// We're done! Should consider ending more "cleanly",
			// eg. Ask user to play another game.
			exit(0);
		}
	}
	// Ah! All invisible cells are bombs, so you won!
	cout << "You won!!!!\n";
	sweeper.display(true); // Final board with bombs shown
}