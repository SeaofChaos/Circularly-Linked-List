//
//   Author:	Ryan Quinn
//   Creation 	10/10/20
//   Due Date:	10/16/20
//   Course:	CSC237 010
//   Professor Name: Dr. Spiegel
//   Assignment: #2
//   Filename:	testLL.cpp
//


#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "Node.h"

using namespace std;

void printForward(CLinkedList<int>&); //print list forwards function
void printBackward(CListItr<int>); //print list backward function

int main()
{
	char inputSelection;
	int isExit = 0;
	CLinkedList<int> circleList;
	CLinkedList<int> copyInto;
	
	//loop selection switch until exit input
	while (isExit == 0){
		cout << endl;
		cout << "LinkedList Test Driver";
		cout << "\nI)nsert Integer";
		cout << "\nR)emove Integer";
		cout << "\nF)orward Print";
		cout << "\nB)ackward Print";
		cout << "\nE)xit\n";
		cin >> inputSelection;
		
		//switch statement to run each selection, doing both input and output
		switch(inputSelection){ 
			
			case 'I':
			case 'i': //insert integer
				int numInsert;
				cout << "Number to insert: ";
				cin >> numInsert;
				cout << endl;
				circleList.insert(numInsert);  //insert inputted number
				break;
			
			case 'R':
			case 'r': //remove integer
				int numRemove;
				cout << "Number to remove: ";
				cin >> numRemove;
				cout << endl;
				circleList.remove(numRemove);  //rempve insertted number
				break;
			
			case 'F':
			case 'f': //forward print
				cout << endl << "Forward print: " << endl;
				printForward(circleList);  //call forward print function
				break;
			
			case 'B':
			case 'b':{ //backward print
				cout << endl << "Backward print: " << endl;
				if (!(circleList.last == NULL)){  //is list empty?
					//declares iterator before for recursion
					CListItr<int> itr(circleList);  
					itr.begin();
					printBackward(itr); 
					cout << *itr << " " << endl; //prints last needed number
				}
				else{ cout << "The list is empty!" << endl;}
				break; 
			}
			case 'E':
			case 'e': //exit
				isExit = 1;
				break;
			
			default:
				cout << endl << "That is not a valid choice" << endl;
		}
	}
	return 0;
}


/** \brief Prints the circular linked list forwards.
  * \param CLinkedList<int> &circleList : input, output*/
void printForward(CLinkedList<int> &circleList){
	if (circleList.last == NULL){  //is the list empty?
		cout << "The list is empty!" << endl;
		return;
	}
	
	CListItr<int> itr(circleList);
	itr.begin();
	
	do {  //iterate through list and print out data
		cout << *itr << " ";
		itr++;
	} while (!(itr.isFirstNode()));
	cout << endl;
}


/** \brief Prints the circular linked list backwards.
  * \param CListItr<int> itr : input, output*/
void printBackward(CListItr<int> itr){
	if (itr.isLastNode()){	//if reached end of list, end recursion
		itr.begin();
		return;
	}
	printBackward(++itr);  //recurisvely print out data so it's backwards
	
	cout << *itr << " ";
}


