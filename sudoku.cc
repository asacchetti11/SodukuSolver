/*
sudoku.cc
Alessandro Sacchetti
10/4/2018
"sudoku solver"
dependencies: sudokuBoard.h, sudokuBoard.cc, stack.h, stack.cc
*/
#include <cstdlib>
#include <fstream>
#include "sudokuBoard.h"
#include "stack.h"
using namespace std;

int numBacktracks=0;

bool solve(sudokuBoard & board){//returns true if able to solve and uses the board pointer inputed

	stack info = stack();//setup stack
	//-What stack looks like for each pos-
	//c
	//r
	//numPos
	//Posibilties (small on top -> biggest on bottom)

	bool backtrack=false;

	while(!board.full()){//loop until board is full

		if(!backtrack){//if no backtrack is needed

		//start of mostConstrained function
			char posibilities[9];//array that will store the chars that canPlace()
			size_t row=10;
			size_t col=10;

			size_t mostConstrained = 9;

			for(size_t i(0); i<9 && mostConstrained>=1; i++){//rows - also exit if we have already found a spot that allows less than 2 spots - if it allows 1 we r all good but if it allows 0 then the board is broken and it will go backtrack 
				for(size_t j(0); j<9; j++){//colums - empty positions
					if( (board.get(i,j)==' ') ){//has to be an empty position

						char tempPosibilty[9]={};
						size_t tempCountConstrained=0;

						for(char n('1'); n<='9'; n++){//for nums 1-9
							if(board.canPlace(i,j,n)){
								tempPosibilty[tempCountConstrained] = n;
								tempCountConstrained++;
							}
						}
						
						//saves the most constrained position along with the posibilities at that position
						if(tempCountConstrained<=mostConstrained){
							row=i;
							col=j;
							for(int t(0);t<9;t++){
								posibilities[t]=tempPosibilty[t];
							}
							mostConstrained=tempCountConstrained;
						}

					}
				}
			}
		//end of mostConstrained function

			if(mostConstrained!=0){

				//place the smallest value and setup stack for backtracking
				for(size_t i(mostConstrained-1);i>=1;i--)
					info.push(posibilities[i]);

				info.push(mostConstrained-1);
				info.push(row);
				info.push(col);
				board.place(row, col, posibilities[0]);

			}else{
				backtrack=true; //if the most constrained function finds a spot that has no posibilites
			}

		}else{//when it is currently backtracking
			numBacktracks++;

			//gets the row, col and num of posibilites  off the stack
			size_t col(info.top()); info.pop();
			size_t row(info.top()); info.pop();
			size_t numPos(info.top()); info.pop();

			board.remove(row,col);
			//cout<< "C:"<<col<< " R:"<<row<<" NUM:"<<numPos<<endl;
			if(numPos>0){
				//cout<<"Size:"<<info.size()<<endl;
				//cout<<":::";
				size_t nextNum(info.top()); info.pop();
				//put the new num on the board
				info.push(numPos-1);
				info.push(row);
				info.push(col);
				board.place(row, col, char(nextNum));
				backtrack=false;
			}

			


		}

		//board.printColor(cout);//print out each iteration of board

	}

	//cout<<"NUM OF BACKTRACKS:"<<numBacktracks<<endl;
	return board.solved();
}

int main(int argc, char const *argv[]){

	//read file to sudoku array
	if(argc!=2){
		cerr << "Expected an Argument"<<endl;
		return 1;
	}

	string filename = argv[1];
	ifstream in(filename);

	string line;
	string total="";
	for(int row = 0; getline(in,line) && row<9;row++){
		total += line;
	}
	sudokuBoard board = sudokuBoard(total);


	//fancy sudoku board
	cout<<"\033[31m"<<"~~~UNSOLVED BOARD~~~"<<"\033[0m"<<endl;
	board.printColor(cout);

	if(solve(board)){ //if solve ==true then its solved
		cout<<"\033[34m"<<"~~SOLVED WITH "<<numBacktracks<<" BACKTRACKS~~"<<"\033[0m"<<endl;
	}else{
		cout<<"\033[31m"<<"~~UNABLE TO SOLVE BOARD~~"<<"\033[0m"<<endl;
	}
	board.printColor(cout);

	//only cout that was required for program
	cout<<"Required format:"<<endl;
	board.output(cout);


}