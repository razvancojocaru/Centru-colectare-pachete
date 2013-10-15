//Cojocaru Mihail-Razvan, 313CA
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"

FILE *f;

//Clasa care contine informatiile utile pentru un window
//<WINDOW_ID>, <WEIGHT_MIN>, <WEIGHT_MAX>, <Q>, <K>,
//coada persoanelor din fata ghiseului si o stiva de pachete.
class ghiseu {
	public:
		int id, min, max, q, k;
		Stack<int> s;
		Queue c;
};


void open_window(ghiseu *window, int *ids) {
	int ID, nr;
	char param[20];
	
	//Citire <WINDOW_ID>, <WEIGHT_MIN>, <WEIGHT_MAX>, <Q>, <K>
	fscanf(f, "%s", param);
	ID = atoi(param);
	window[ID].id = ID;
	
	fscanf(f, "%s", param);
	nr = atoi(param);
	window[ID].min = nr;
	
	fscanf(f, "%s", param);
	nr = atoi(param);
	window[ID].max = nr;
	
	fscanf(f, "%s", param);
	nr = atoi(param);
	window[ID].q = nr;
	
	fscanf(f, "%s", param);
	nr = atoi(param);
	window[ID].k = nr;
	
	//Marcam in vectorul ids faptul ca ghiseul cu id-ul dat a fost deschis
	ids[ID] = 1;
}

void add_person(ghiseu *window) {
	person newperson;
	int nr;
	char param[20];
	
	//Citire <PERSONAL_ID>, <PACKAGE_WEIGHT>, <WINDOW_ID>
	fscanf(f, "%s", param);
	nr = atoi(param);
	newperson.id = nr;
	
	fscanf(f, "%s", param);
	nr = atoi(param);
	newperson.weight = nr;
	
	fscanf(f, "%s", param);
	nr = atoi(param);
	
	//Adaugam persoana in coada ghiseului respectiv
	window[nr].c.enqueue(newperson);
}

void process(ghiseu* window, int *ids, int n) {
	int ID, nr, i, j;
	char param[20];
	person newperson;
	
	//Citire <WINDOW_ID>, <N_PEOPLE>
	fscanf(f, "%s", param);
	ID = atoi(param);
	fscanf(f, "%s", param);
	nr = atoi(param);

	//Procesam un numar "nr" de persoane din coada ghiseului respectiv
	for (i=0; i<nr; i++) { 
		newperson = window[ID].c.dequeue(); 
		//Verificam daca pachetul persoanei se afla in limitele ghiseului
		if ( (newperson.weight <= window[ID].max) && (newperson.weight >= window[ID].min) ) { 
			//Daca greutatea pachetului este potrivita, verificam daca stiva
			//ghiseului este plina
			if ( ( window[ID].s.size() == window[ID].q ) || 
				( window[ID].s.sum() + newperson.weight > window[ID].k ) )
				window[ID].s.flush();
			//Apoi persoana este eliminata din coada si pachetul este preluat
			window[ID].s.push(newperson.weight);
		} 
		/*Daca greutatea pachetului nu este in limitele respective,
		persoana este mutata la urmatorul ghiseu.
		Aici am folosit ids - vector circular 
		(1 daca ghiseul este deschis, 0 daca e inchis)*/
		else {
			j = (ID+1) % n;
			while ( ids[j]==0 ) {
				j = (j+1) % n;
			}
			window[j].c.enqueue(newperson);
		} 
	}
	
}

//Functie similara cu PROCESS, dar realizata pentru intreaga coada de persoane
void process_all(ghiseu* window, int *ids, int n) {
	int ID, nr, i, j;
	char param[20];
	person newperson;
	
	fscanf(f, "%s", param);
	ID = atoi(param);

	//Numarul de persoane procesate este chiar dimensiunea cozii
	nr = window[ID].c.size();
	
	for (i=0; i<nr; i++) {
		newperson = window[ID].c.dequeue();
		if ( (newperson.weight <= window[ID].max) && (newperson.weight >= window[ID].min) ) {
			if ( ( window[ID].s.size() == window[ID].q ) || 
				( window[ID].s.sum() + newperson.weight > window[ID].k ) )
				window[ID].s.flush();
			window[ID].s.push(newperson.weight);
		}
		else {
			j = (ID+1) % n;
			while ( ids[j]==0 ) {
				j = (j+1) % n;
			}
			window[j].c.enqueue(newperson);
		}
		
	}	
}

void print_stacks(ghiseu* window, int *ids, int n) {
	int i;
	fprintf(stdout, "STACKS:\n");
	for (i=0; i<n; i++) {
		if (ids[i] == 1) {
			fprintf(stdout, "%d: ", window[i].id);
			//Afiseaza stiva de pachete
			window[i].s.display();
			fprintf(stdout, "\n");
		}	
	}

}

void print_queues(ghiseu* window, int *ids, int n) {
	fprintf(stdout, "QUEUES:\n");
	for (int i=0 ; i<n ; i++) {
		if (ids[i]==1) {
			fprintf(stdout, "%d: ", window[i].id);
			//Afiseaza elementele cozii, in formatul cerut
			window[i].c.print();
			fprintf(stdout, "\n");
		}
	}
}

void flush_stacks(ghiseu* window, int *ids, int n) {
	fprintf(stdout, "FLUSHING:\n");
	for (int i=0 ; i<n ; i++) {
		if (ids[i]==1) {
			fprintf(stdout, "%d: ", window[i].id);
			//Afiseaza stiva de pachete
			window[i].s.display();
			fprintf(stdout, "\n");
			//Goleste stiva
			window[i].s.flush();
		}
	}
}

int main( int argc, char *argv[] ) {
//Variabila auxiliara, in care sunt citite, pe rand, comenzile
char command[20];

//Nr maxim de ghisee ce pot fi deschise
int n;

//Vector cu n elemente, ids[i] == 0 daca nu exista ghiseu deschis cu ID==i
// ids[i] == 1 daca exista ghiseu deschis cu ID==i
int *ids;

if ( (f = fopen( argv[1], "rt")) == NULL ) {
	fprintf(stdout, "Error!");
	return -1;
}
//Citire n
fscanf(f, "%s", command);
n = atoi(command);

//Vector alocat static, care contine un nr n de ghisee,
//reprezentant nr maxim de ghisee ce pot fi deschise
ghiseu window[n];

ids = (int*)calloc(n, sizeof(int));

fscanf(f, "%s", command);
while ( !feof(f) ) {

	if ( strcmp(command, "OPEN_WINDOW") == 0 ) { 
		open_window(window, ids);
	}
	if ( strcmp(command, "ADD_PERSON") == 0 ) { 
		add_person(window);
	}
	if ( strcmp(command, "PROCESS") == 0 ) { 
		process(window, ids, n);
	}
	if ( strcmp(command, "PROCESS_ALL") == 0 ) {
		process_all(window, ids, n);
	}
	if ( strcmp(command, "PRINT_STACKS") == 0 ) {
		print_stacks(window, ids, n);
	}
	if ( strcmp(command, "FLUSH_STACKS") == 0 ) {
		flush_stacks(window, ids, n);
	}	
	if ( strcmp(command, "PRINT_QUEUES") == 0 ) {
		print_queues(window, ids, n);
	}
	fscanf(f, "%s", command);
}


free(ids);
fclose(f);
return 0;
}
