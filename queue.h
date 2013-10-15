#include "list.h"

class Queue {
private:

	LinkedList queueList;
 
public:
	// Constructor
	Queue(){}
 
	// Destructor
	~Queue(){}
 
	void enqueue(person e) {
		queueList.addLast(e);
	}
	
	person dequeue() {
		if (isEmpty()) {
			cout<<"Error 102 - The queue is empty!"<<endl;
			person x;
			return x;
		}
		person x = queueList.removeFirst();
		
		return x;
	}
	
	
	person front() {
		if (isEmpty()) {
			cout<<"Error 103 - The queue is empty"<<endl;
			person x;
			return x;
		}
		return queueList.getFirst();
	}
			
	int isEmpty() {
		return queueList.isEmpty();
	}
	
	void print() {
		queueList.printList();
	}
	
	int size() {
		return queueList.size();
	}
};

