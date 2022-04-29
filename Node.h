
// File: Node.h
// Singly-linked list node definition/implementation (also good for circular)

#ifndef NODE_H
#define NODE_H

// Need to prototype template classes if they are to be friends
template <typename eltType> class CLinkedList;
template <typename eltType> class CListItr;

/** \brief Node class used in CLinkedList. */
template <typename eltType> class Node
{       private:
		Node(eltType info, Node* link = NULL ) :
					       data(info), next(link) 
		{};
		eltType data;
		Node *next;
        friend class CLinkedList<eltType>;
        friend class CListItr<eltType>;
};

/** \brief Circular linked list class using Node class. */
template <typename eltType> class CLinkedList{
	public:
		///last node pointer
		Node<eltType> *last; 
		
		CLinkedList() {last = NULL;}  //constructor
		CLinkedList(const CLinkedList &obj); 
		~CLinkedList(); 
		
		void insert(int); 
		void remove(int);  
		CLinkedList<eltType>* operator=(const CLinkedList &);
		
	private:
		void destroy(Node<eltType>*);
};

/** \brief CLinkedList iterator class */
template <typename eltType> class CListItr{
	public:
		/**Iterator constructor, takes a CLinkedList as its parameter.*/
		CListItr(const CLinkedList<eltType> &listItr) : 
									itr(listItr), curr(listItr.last)
		{}  //constructor
		
		void begin();
		bool isEmpty();	  	
		bool isFirstNode();	
		bool isLastNode();	
		
		eltType operator*();
		CListItr<eltType> operator++();	
		CListItr<eltType>* operator++(int);	
		
	private:
		const CLinkedList<eltType> &itr;
		Node<eltType> *curr;
		
};


/** \brief CLinkedList destructor 
  *- Mutator*/
template <typename eltType>
CLinkedList<eltType>::~CLinkedList(){
	if (last == NULL){ //is the list empty?
		return;
	}
	destroy(last); 
}


/** \brief Inserts an inputted number into the circular linked list 
  *- Mutator
  * \param int number : number to insert - input*/
template <typename eltType>
void CLinkedList<eltType>::insert(int number){
	
	Node<eltType> *newNode = new Node<eltType>(number); //new node with new data
	
	if (last == NULL){  //if list is empty, make the new node the last node
		last = newNode;
		last->next = last;
		return;
	}
	if (last->next == last){ //if list has 1 element, compare values & make node
		if (last->data < number){  //check if it's greater than previous node
			last->next = newNode;
			newNode->next = last;
			last = newNode;
			return;
		}
		newNode->next = last;
		last->next = newNode;
		return;
	}
	
	Node<eltType> *beforeCurr = last;  //node pointers to iterate list and
	Node<eltType> *Curr = last->next;  //insert new node if list size > 2
	
	//loop while list number < inserted number
	while ((Curr != last) && (Curr->data < number)){
		Curr = Curr->next;
		beforeCurr = beforeCurr->next;
	}
	//inserts new number element into list
	if (Curr == last){
		if (last->data < number){  //put in last if greater than current last
			newNode->next = last->next;
			last->next = newNode;
			last = newNode;
		}
		else{  //put before last if not greater than current last
			beforeCurr->next = newNode;
			newNode->next = Curr;
		}
	}
	else{ //Curr isn't last, so add it between two normal nodes
		beforeCurr->next = newNode;
		newNode->next = Curr;
	}
}


/** \brief Removes an inputted number from the list. 
  *- Mutator
  * \param int number : number to remove - input*/
template <typename eltType>
void CLinkedList<eltType>::remove(int number){
	
	if (last == NULL){  //is the list empty?
		return;
	}
	
	//handles situation with 1 node
	if ((last == last->next) && (last->data == number)){
		last = NULL;
		return;
	}
	
	Node<eltType> *beforeCurr = last;  //node pointers to iterate list and
	Node<eltType> *Curr = last->next;  //delete node if number = list data
	
	//loop while list number != inserted number, finding number it's equal to
	while ((Curr != last) && (Curr->data != number)){
		Curr = Curr->next;
		beforeCurr = beforeCurr->next;
	}
	
	if (Curr->data == number){ 
		Node<eltType> *doomed = Curr;
		//if doomed is last, make the node before the current last equal to last
		if (doomed == last){ 
			last = beforeCurr;
			Curr = Curr->next;
			last->next = Curr;
		}
		else{ //it isn't last, so change the pointers like normal
			Curr = Curr->next;
			beforeCurr->next = Curr;
		}
		delete doomed;
	}
}

//////////////////////////////////////////////////////////////////////////////
//                                                                  
//  Function name:  destroy
//  Description:  Recursively iterates through a list and destroyes all nodes
//  Member Type:  Mutator
//  Parameters:   Node<eltType> *last : input
//
//  Return Value: N/A
//
//////////////////////////////////////////////////////////////////////////////
template <typename eltType>
void CLinkedList<eltType>::destroy(Node<eltType> *last){
	static int temp = 0;	//varible used to determine if this is a new list
	static Node<eltType> *first;
	
	//if one list is destroyed, reset temp so it works with the next one
	if (temp == 0){
		first = last->next;
		temp = 1;
	}
	last = last->next;
	
	if (last->next == first){  //checks if entire list has been destroyed
		delete last;
		temp = 0;
		return; 
	}
	
	Node<eltType> *doomed = last;
	delete doomed;
	destroy(last);  //recursive call
}

/**\brief Operator= overload, allows for the deep copy of linked lists 
  *- Mutator
  *\param const CLinkedList &original : list being copied - input
  *\return CLinkedList<eltType>* : new deep copied list*/
template <typename eltType>
CLinkedList<eltType>* 
		CLinkedList<eltType>::operator=(const CLinkedList &original)
{
	if (original.last == NULL){  //return if lists are both empty
		return this;
	}
	this->last = NULL; //empties list that will get new values
	
	//iterates through original list
	Node<eltType> *origFirst = original.last->next;  
	//keeps track of original last
	Node<eltType> *constFirst = original.last->next; 
	
	do{
		insert(origFirst->data);
		origFirst = origFirst->next;
	} while(origFirst != constFirst);//copies all data while origFirst!=origLast
	
	return (this);
}

////////////////////////////////////////////////////
//
//	Iterator Member Functions
//
////////////////////////////////////////////////////

/**\brief Set's current node pointer to the first one in linked list 
  *- Mutator*/
template <typename eltType>
void CListItr<eltType>::begin(){
	if (itr.last == NULL){ //sets current node to the last node
		return;
	}
	curr = itr.last->next; //sets it to the first node
}


/**\brief Checks if the linked list is empty 
  *- Inspector
  *\return bool - true if empty, false otherwise*/
template <typename eltType>
bool CListItr<eltType>::isEmpty(){
	if (itr.last == NULL){ //is the current list empty?
		return true;
	}
	return false;
}


/**\brief Checks if current node is equal to first node in circular linked list.
  *- Inspector
  *\return bool : true if equal to first node, false otherwise */
template <typename eltType>
bool CListItr<eltType>::isFirstNode(){
	if (!(isEmpty())){
		if (curr == itr.last->next){  //is the current node the first node?
			return true;
		}
	}
	return false;
}


/**\brief Checks if current node is equal to last node in list. 
  *- Inspector
  *\return bool : true if equal to last node, false otherwise */
template <typename eltType>
bool CListItr<eltType>::isLastNode(){
	if (curr == itr.last){ //is the current node the last node?
		return true;
	}
	else {
		return false;
	}
}


/**\brief Dereference operator overload to return current node data value. 
  *- Mutator
  *\return eltType : list element data */
template <typename eltType>
eltType CListItr<eltType>::operator*(){
	return curr->data; //returns the node data
}


/**\brief Post-increment operator overload to point current node at the next 
  * node in the linked list. 
  *- Mutator
  *\return CListItr<eltType> : updated node pointer */
template <typename eltType>
CListItr<eltType> CListItr<eltType>::operator++(){
	if (isEmpty()){  //is the list empty?
		return *this;
	}
	curr = curr->next;
	return *this;  //returns the updated iterator
}


/**\brief Pre-increment operator overload to point current node at the next
  * node in the linked list. 
  *- Mutator
  *\param int dummy : dummy variable - input
  *\return CListItr<eltType>* : updated node pointer*/
template <typename eltType>
CListItr<eltType>* CListItr<eltType>::operator++(int dummy){
	if (isEmpty()){  //is the list empty?
		return this;
	}
	CListItr<eltType> *tempItr = this; //saves current this value
	curr = curr->next;
	return tempItr; //returns updated node pointer, not the this value
}					//this allows for post increment to occur


#endif
