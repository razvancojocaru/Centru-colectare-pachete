#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

//Stiva este alocata dinamic, memoria alocata se dubleaza in momentul 
//in care stiva se umple
template<typename T>
class Stack {
	private:
		// vectorul de stocare
		T* stackArray;

		// pozitia in vector a varfului stivei, numarul maxim de elemente
		int topLevel, max;
	public:
		// constructor
		Stack() {
			stackArray = (T*)malloc(sizeof(T));
			topLevel = -1;
			max=1;
		}

		// destructor
		~Stack() {
			free(stackArray);
		}

		// operator de adaugare
		void push(T x) {
			if (topLevel >= max-1) {
				stackArray = (T*)realloc(stackArray, 2*max*sizeof(T));
				max *= 2;
			}
			topLevel++;
			stackArray[topLevel] = x;
		}

		// operatorul de stergere
		T pop() {
			if ( isEmpty() ) {
				cout<<"Error - The stack is empty"<<endl;
				T x;
				return x;
			}
			T x = stackArray[topLevel];
			topLevel--;
			return x;
		}

		// operatorul de consultare
		T peek() {
			if ( isEmpty() ){
				cout<<"Error - The stack is empty"<<endl;
				T x;
				return x;
			}
			return stackArray[topLevel];
		}

		// operatorul de verificare dimensiune
		int isEmpty() {
			return (topLevel<0);
		}

		//Intoarce nr de elemente al stivei
		int size() {
			return topLevel + 1;
		}

		//Intoarce suma elementelor stivei
		int sum() {
			int suma=0;
			for(int i=(this->size())-1 ; i>=0 ; i--) {
				suma += stackArray[i];	
			}
			return suma;
		}
		
		//Goleste stiva
		void flush() {
			topLevel=-1;	
		}
		
		//Afiseaza elementele stivei
		void display() {
			int i;
			if ( (this->size()) == 0 ) return;
			for(i=(this->size())-1 ; i>0 ; i--) {
				fprintf(stdout, "%d, ",stackArray[i]);	
			}
			fprintf(stdout, "%d",stackArray[i]);
		}
};
