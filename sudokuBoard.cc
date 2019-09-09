/*
sudokuBoard.cc
Alessandro Sacchetti
10/4/2018
sudokuBoard class file
*/
#include <iostream>
#include <string>
#include "sudokuBoard.h"

using namespace std;

sudokuBoard::sudokuBoard(string s){
	cout << "Creating board..." << endl;
	for(size_t i = 0; i<81; i++){
		if(s[i]=='_'){
			s[i]=' ';
			emptySpaces++;
		}
		sboard[i/9][i%9]=s[i];
	}
	//board = s;
}

void sudokuBoard::place(size_t r,size_t c,char num){
	if(sboard[r][c]==' '){
		emptySpaces--;
	}
	sboard[r][c]=num;
}

char sudokuBoard::get(size_t r, size_t c) const{
	return sboard[r][c];
}

void sudokuBoard::remove(size_t r, size_t c){
	if(sboard[r][c]!=' '){
		emptySpaces++;
	}
	sboard[r][c]=' ';
}

bool sudokuBoard::canPlace(size_t r, size_t c, char num) const{
	//cout<<endl<<"CANPLACE:"<<r<<", "<<c<<" :"<<num<<endl;
	size_t max = 9;
	if(sboard[r][c]!=' '){//check if the spot is ' '
		return false;
	}
	for(size_t i = 0; i < max; i++){//check if the row and col contains the num
		if(sboard[i][c]==num || sboard[r][i]==num){
			return false;
		}
	}
	
	//using int multiplication we know it will simplify to the corner
	size_t rowCorner = (r/3)*3; //ex: r = 2 so 2/3 == 0 and 0*3 == 0
	size_t colCorner = (c/3)*3;

	for(size_t i = 0; i < 3; i++){//checks the 3x3 area box
		for(size_t j = 0 ; j < 3; j++){
			if(sboard[rowCorner+i][colCorner+j]==num){
				return false;
			}
		}
	}

	return true;//it must be able to be placed
}

bool sudokuBoard::full() const{
	return emptySpaces==0;
}

bool sudokuBoard::solved() const{
	for(int r =0; r <9;r++){
		for(int c=0;c<9;c++){

			bool isThatSpotOk=true;
			char num = sboard[r][c];
			if(num> '9' || num<='0'){
				isThatSpotOk=false;
			}

			for(size_t i = 0; i < 9; i++){//check if the row and col contains the num
				if( !(r==i || c==i) && (sboard[i][c]==num || sboard[r][i]==num) ){
					isThatSpotOk = false;
		
				}
			}
	
			//using int multiplication we know it will simplify to the corner
			size_t rowCorner = (r/3)*3; //ex: r = 2 so 2/3 == 0 and 0*3 == 0
			size_t colCorner = (c/3)*3;

			for(size_t i = 0; i < 3; i++){//checks the 3x3 area box
				for(size_t j = 0 ; j < 3; j++){
					if(sboard[rowCorner+i][colCorner+j]==num && !(colCorner+j==c && rowCorner+i==r) ) {
						isThatSpotOk = false;
		
					}
				}
			}

			if(!isThatSpotOk){
				cout<<"R:"<<r<<" C:"<<c<<" NUM:"<<sboard[r][c]<<endl;
				return false;
			}


		}
	}

	return true;
}

void sudokuBoard::print(std::ostream & ostr){
	//partial source: Alistair Campbell & Ms. Wolf; program nqueens_board
	//----creates top frame of board
	ostr << "+";
	for(size_t i=0; i<9; i++)
		ostr << "---+";
	ostr<<endl;

	//----creates the rest
	for (size_t r =0; r<9; r++){
		ostr << "| "; // furthest left frame
		for(size_t c = 0; c<9; c++){
			ostr << sboard[r][c] << " | "; // right of each number frame
		} 
		ostr<< endl << "+";

		for(size_t i=0; i<9; i++)//creates each bottom of row frame
			ostr << "---+";
		ostr<<endl;
	}

}

void sudokuBoard::printColor(std::ostream & ostr){
	//Made by Alessandro Sacchetti
	//partial source: Alistair Campbell & Ms. Wolf; program nqueens_board
	//color source: https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal

	//colors: red 31, green 32, yellow 33, blue 34
	string color("\033[32m");
	string reset("\033[0m");
	//cout << "\033[1;31m"+text+"\033[0m"<<endl;

	//creates top piece of board	
	ostr << color <<"+";
	for (size_t i = 0;i<9;i++)
		ostr << "---+";
	ostr <<reset<< endl;

	for (size_t r = 0;r<9;r++) {
		ostr << color<<"| "<<reset;
		for (size_t c = 0;c<9;c++) {

			ostr << sboard[r][c];// <<" | "<<reset;
			if((c+1)%3==0){
				ostr<<color << " | "<<reset;
			}else{
				ostr<<" | ";
			}
			
		}
		ostr << endl;


		ostr <<color<< "+"<<reset;

		if((r+1)%3==0)
			ostr<<color;

		for (size_t i = 0;i<9;i++){
			ostr << "---";
			if((i+1)%3==0 && (r+1)%3!=0){
				ostr <<color<< "+"<<reset;
			}else{
				ostr << "+";	
			}
		}
		ostr <<reset<< endl;
	}

}

void sudokuBoard::output(std::ostream & ostr){
	for(int i(0);i<9;i++){
		for(int j(0);j<9;j++){
			ostr<<sboard[i][j];
		}
		ostr<<endl;
	}

}