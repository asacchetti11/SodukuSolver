/*
stack.h
Alessandro Sacchetti
9/25/2018
Stack header file
*/

#include <cstdlib>
#include <iostream>

using namespace std;

typedef size_t duck;

class stack{

private:
	struct node{
		duck data;
		node *next;
	};

	size_t _size;
	node *_top;




public:
	stack();//A 0 parameter constructor that initializes all private variables appropriately,

	~stack();//A destructor


	void push(duck newdata); //- places d in a node at the top of the stack,

	void pop(); //- removes and deletes the top node of the stack. Returns nothing,

	duck top() const; //- returns the value stored in the top node. Does not change the object structure.

	size_t size() const; //- returns the size of the stack. Does not change the object structure.

	bool empty() const; //- returns a boolean value - whether the stack is empty. Does not change the object structure.

	void print(); //- prints out a representation of the stack: “[1, 2, 3, 2]”  where 1 is top. Does not change the object structure.


};