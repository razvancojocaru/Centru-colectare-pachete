Cojocaru Mihail-Razvan 313CA

Programul realizat reprezinta un simulator simplu al activității din centrul de colectare a pachetelor.
Comenzile sunt citite dintr-un fisier text, primit ca parametru la rulare.

Comenzile suportate de program sunt:
	OPEN_WINDOW
	ADD_PERSON
	PROCESS
	PROCESS_ALL
	PRINT_STACKS
	FLUSH_STACKS
	PRINT_QUEUES
	
Pentru implementare, am folosit o clasa "ghiseu", care contine toate informatiile relevante pentru un ghiseu, precum si o clasa "person", care contine id-ul persoanei si greutatea pachetului sau.

Fiecare ghiseu contine o stiva si o coada.
Stiva este implementata printr-un vector alocat dinamic, care isi dubleaza dimensiunea in momentul in care stiva este umpluta (realloc).
Coada este implementata printr-o lista liniara dublu inlantuita. Astfel, nici stiva si nici coada nu au limitari in ceea ce priveste numarul maxim de elemente, acesta fiind dependent numai de memoria disponibila.

Ghiseele sunt grupate intr-un vector alocat static, cu un nr n de elemente(este alocat dupa citirea numarului maxim de elemente).
In plus, am folosit un vector ids, folosit pentru a determina daca un ghiseu este deschis sau nu. Vectorul respectiv are n elemente nr intregi, si contine 0 daca ghiseul cu id ids[i] nu este deschis, respectiv 1 daca este deschis. Mentionez ca in functia process, ids este folosit ca un vector circular, pentru a permite mutarea elementelor din cozile ghiseelor, conform instructiunilor.

Pentru lizibilitate, fiecare comanda are asociata cate o functie cu acelasi nume.
Intrucat fiecare comanda are alt numar de parametrii, se realizeaza o citire pentru a recunoaste comanda de baza, apoi restul citirilor din fisier au loc in functia corespunzatoare comenzii citite.
Citirea comenzii se realizeaza intr-un buffer "comanda"(vector de 20 de caractere alocat static), iar dupa recunoasterea comenzii (cu strcmp), este apelata functia corespunzatoare comenzii citite.

Avand in vedere ca functiile open_window, add_person, print_stacks, flush_stacks si print_queues sunt destul de lizibile si comentate in codul sursa, voi explica amanuntit doar functia process (si process_all, care este asemanatoare).

Functia process scoate un element din coada ghiseului primit ca parametru (prin id), si in urma unor verificari, fie introduce pachetul in stiva ghiseului, fie muta elementul in coada urmatorului ghiseu.
Prima verificare este efectuata asupra greutatii pachetului. Daca se incadreaza in valorile min si max ale ghiseului respectiv, pachetul este acceptat, daca nu, este respins si trimis la coada urmatorului ghiseu.
Daca pachetul este asteptat, sunt realizate verificarile asupra stivei ghiseului. Daca stiva este plina ( s-a atins numarul maxim de pachete sau prin introducerea pachetului nou se depaseste greutatea maxima a stivei ), stiva este golita si abia apoi este introdus pachetul in stiva.
