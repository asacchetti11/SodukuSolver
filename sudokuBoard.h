/*
sudokuBoard.h
Alessandro Sacchetti
10/4/2018
sudokuBoard header file
*/
#include <iostream>
#include <string>
class sudokuBoard{
private:
	std::string sboard[9];
	int emptySpaces;

public:
	//takes in raw string of sudoku board with no spaces or returns
	sudokuBoard(std::string s);

	// place a number at (r,c).
	void place(size_t r,size_t c,char num);

	// return the numeral at position (r,c)
	char get(size_t r,size_t c) const;

	// remove a number from (r,c).
	void remove(size_t r,size_t c); 

	// true if able to place a num at (r,c) within the rules of sudoku
	bool canPlace(size_t r,size_t c, char num) const;  

 	// true iff there are no blank spots on the board
	bool full() const;

	bool solved() const;


	// print the board without color
	void print(std::ostream & ostr);

	// print the board in color
	void printColor(std::ostream & ostr); 

	//print in the format that is required
	void output(std::ostream & ostr);

};