sudoku: sudoku.o stack.o sudokuBoard.o
	g++ -o sudoku stack.o sudokuBoard.o sudoku.o

stack.o: stack.cc stack.h
	g++ -c stack.cc

sudokuBoard.o: sudokuBoard.cc sudokuBoard.h
	g++ -c sudokuBoard.cc

sudoku.o: sudoku.cc stack.h sudokuBoard.h
	g++ -c sudoku.cc

clean:
	rm -rf stack.o sudokuBoard.o sudoku.o sudoku
