/*
stack.cc
Alessandro Sacchetti
9/25/2018
Stack class file
*/

#include "stack.h"
#include <cstdlib>


stack::stack(){
	_size=0;
	_top=NULL;
}

stack::~stack(){
	//uses the _top pointer as the pointer that goes through the entire linked list

	while(_top){//loops through the stack until the pointer is NULL
		node *aboutToBeDeleted;//make a temp variable so that we are able to move on in the array while also deleting the current one
		aboutToBeDeleted=_top;

		_top = _top -> next;//move to the next node in the stack
		delete aboutToBeDeleted;
	}

}

void stack::push(duck newdata){

	node *tasty;
	tasty = new node;//dynamically allocates a new node somewhere in ram 

	tasty-> data = newdata;//stores the input data into the new node
	tasty-> next = _top; //sets the next variable of this new node to the previous top variable -adding it on top

	_top = tasty; //move that new node to the top

	_size++;
}

void stack::pop(){

	if(!empty()){//if there is something to pop

		node *tasty;
		tasty = _top->next;//make a temp pointer and point to the next node in the stack

		delete _top;//delete the node at the top
		_top=tasty;//set the top node to the next node
		_size--;
	}
}

duck stack::top() const{
	return _top->data; //returns the data at the top of the stack
}

size_t stack::size() const{
	return _size; //returns the size of the linked list
}

bool stack::empty() const{
	return !_top; //returns true if the stack is empty
}

void stack::print(){
	cout<<"[";

	node *tasty=_top;
	while(tasty){//loops through the stack until the pointer is NULL

		cout << (*tasty).data;

		if( (tasty->next) ){//if it is not the last node
			cout<<", ";
		}
		tasty = tasty -> next;//move to the next node in the stack
		
	}
	cout<<"]"<<endl;
}

