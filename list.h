#include <iostream>
#include <stdlib.h>
using namespace std;

class person {
	public:
		int id, weight;
};

struct Node {
 
public:
	person info;
	Node *next;
	Node *prev;
};
 
class LinkedList{
private:
 
	Node *pfirst, *plast;
 
public:
 
	//Constructor
	LinkedList(){
      	pfirst = plast = NULL;
    }
	//Destructor
	~LinkedList(){
		Node *p;
		while ( !isEmpty() ) {
			p = pfirst->next;
			delete pfirst;
			pfirst = p;
		}
	}
 
	/*Adauga un nod cu valoarea == value la sfarsitul listei */
	void addLast(person value){
		Node *paux;
		paux = new Node;
		paux->info = value;
		paux->prev = plast;
		paux->next = NULL;

		if (plast != NULL) plast->next = paux;
		plast = paux;
		if (pfirst == NULL) pfirst = plast;
	}
 
	/*Elimina elementul de la inceputul listei si intoarce valoarea acestuia*/
	person removeFirst(){
		Node *paux; person aux;
		if (pfirst != NULL) {
			paux = pfirst->next;
			aux = pfirst->info;
			if (pfirst == plast) plast = NULL;
			delete pfirst;
			pfirst = paux;
			if (pfirst != NULL) pfirst->prev = NULL;
		}
		else cout<<"Error 101 - The list is empty"<<endl; 
		return aux;
	}

	/*Intoarce 1 daca lista este vida, 0 altfel*/
	int isEmpty() {
		return (pfirst == NULL);
	}
	
	//Intoarce primul element din lista
	person getFirst() {
		return pfirst->info;
	}

	//Intoarce numarul de elemente al listei
	int size() {
		int i=1;
		Node *p;
		p = pfirst;
		if (p == NULL) return 0;
		while ( p != plast ) {
			i++;
			p = p->next;
		}
		return i;
	}

	//Afiseaza lista
	void printList() {
		Node *p;
		if (isEmpty()) {
			return;
		}
		p = pfirst;
		if (pfirst==plast) 
			fprintf(stdout, "(%d, %d)", p->info.id, p->info.weight);
		else {
			while (p != plast) {
				fprintf(stdout, "(%d, %d), ", p->info.id, p->info.weight);
				p = p->next;		
			}
		fprintf(stdout, "(%d, %d)", p->info.id, p->info.weight);
		}
		return;
	}
};
