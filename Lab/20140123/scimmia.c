#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MODE 	2 	/* 	0: Base
						1: Power
						2: Professional 	*/
						
typedef struct _nodo {
	int dato;				/* Numero identificativo del nodo */
	struct _nodo *dx, *sx;	/* Ramo destro e sinistro */
} Nodo;

typedef struct _banana {
	Nodo * provenienza;			/* Puntatore alla foglia da cui è stata raccolta la banana */
	struct _banana * prossima;	/* Puntatore alla banana successiva */
} Banana ;

typedef struct _mossa {
	Nodo *prec, *succ;			/* Mossa:	nodo precedente -> nodo successivo */
	struct _mossa * prossima;	/* Puntatore alla prossima mossa */
} Mossa;

typedef Nodo * Albero;
typedef Banana * Lista;
typedef Mossa * ListaMosse;

typedef enum { BANANA, CADUTO, SCESO } Evento;	

typedef struct {			/* Aggregatore di un risultato complesso: 			*/
	Evento e;				/* Evento: l'esito dei movimenti della scimmietta	*/ 
	Lista lista;			/* Lista: la lista di banane 						*/
	ListaMosse mosse;		/* ListaMosse: la lista delle mosse					*/
} EventoComplesso;			/* 													*/

/* Prototipi di funzione per l'albero */
Albero aggiungi(Albero, int);
Albero incenerisci(Albero);

/* Prototipi di funzione per la lista delle banane */
Lista aggiungibanana(Lista, Nodo *);
int contienebanana(Lista, Nodo *);
void mangiatutto(Lista);
int contabanane(Lista);

/* Prototipi di funzione per la lista delle mosse */
ListaMosse procedi(ListaMosse, Nodo *, Nodo *);
Mossa indietreggia(ListaMosse *);
void dimentica(ListaMosse);

/* Interazione con l'utente */
void stampa(EventoComplesso);
EventoComplesso muovi(Albero, int, Albero, Lista, ListaMosse);
Albero crea_albero();
int mossa_valida(Albero, char);


/*** MAIN ***/
int main() {
	Albero t = NULL;
	EventoComplesso ev;
	Lista l = NULL;
	ListaMosse lm = NULL;
	
	t = crea_albero();
	system("cls");
	
	ev = muovi(t, 0, NULL, l, lm);
	stampa(ev);
	
	l = ev.lista;
	lm = ev.mosse;
	
	t = incenerisci(t);
	mangiatutto(l);
	dimentica(lm);
	return 0;
}


/*** Funzioni di gestione dell'albero ***/

/* Aggiunge un nodo all'albero */
Albero aggiungi(Albero t, int dato) {
	Nodo * n;
	if(t == NULL) {
		n = malloc(sizeof(Nodo));
		n->dato = dato;
		n->dx = NULL;
		n->sx = NULL;
		
		return n;
	}
	
	if(dato <= t->dato) {
		t->sx = aggiungi(t->sx, dato);
	} else {
		t->dx = aggiungi(t->dx, dato);
	}
	return t;
}

/* Distrugge l'albero */
Albero incenerisci(Albero t) {
	if(t == NULL) {
		return NULL;
	}
	
	t->sx = incenerisci(t->sx);
	t->dx = incenerisci(t->dx);
	free(t);
	
	return NULL;
}


/*** Gestione lista ***/

/* Aggiunge una banane alla lista delle banane raccolte */
Lista aggiungibanana(Lista l, Nodo *n) {
	Banana * b;
	
	b = malloc(sizeof(Banana));
	b->provenienza = n;
	b->prossima = l;
	
	return b;
}

/* Cerca una banana, raccolta da una certa foglia, nell'archivio delle banane raccolte */
int contienebanana(Lista l, Nodo *n) {
	if(l == NULL) {
		return 0;
	}
	if(l->provenienza == n) {
		return 1;
	}
	
	return contienebanana(l->prossima, n);
}

/* Distrugge la lista delle banane raccolte */
void mangiatutto(Lista l) {
	Banana *succ;
	if(l == NULL) return;
	
	succ = l->prossima;
	free(l);
	mangiatutto(succ);
}

/* Conta le banane raccolte */
int contabanane(Lista l) {
	if(l == NULL) return 1;
	
	return 1 + contabanane(l->prossima);
}


/*** Prototipi di funzione per la lista delle mosse ***/

/* Aggiunge una mossa alla lista delle mosse */
ListaMosse procedi(ListaMosse l, Nodo *succ, Nodo *prec) {
	Mossa * m;
	
	m = malloc(sizeof(Mossa));
	m->prec = prec;
	m->succ = succ;
	m->prossima = l;
	
	return m;
}

/* Rimuove l'ultima mossa dalla lista delle mosse */
Mossa indietreggia(ListaMosse *l) {
	Mossa m;
	m.prec = (*l)->prec;
	m.succ = (*l)->succ;
	m.prossima = (*l)->prossima;
	
	free(*l);
	*l = m.prossima;
	m.prossima = NULL;
	return m;
}

/* Distrugge la lista delle mosse */
void dimentica(ListaMosse l) {
	Mossa *succ;
	if(l == NULL) return;
	
	succ = l->prossima;
	free(l);
	dimentica(succ);	
}

/*** Interazione con l'utente ***/

/* Crea un albero leggendo i dati dalla shell */
Albero crea_albero() {
	Albero t = NULL;
	int letto;
	
	printf("Benvenuto al gioco delle scymmie!!1!\n");
	
	do {
		printf("Aggiungi un nodo all'albero: ");
		scanf("%d", &letto);
		
		if (letto >= 0) {
			t = aggiungi(t, letto);
		}
	} while (letto >= 0);
	
	return t;
}


/* Muove la scimmia. It's magic! */
EventoComplesso muovi(Albero t, int prf, Albero p, Lista l, ListaMosse lm) {
	EventoComplesso ev;
	Mossa m;
	char s;
	int val;
	
	if(lm == NULL) {
		/* Se è nullo significa che non abbiamo ancora aggiunto la prima mossa (salire sull'albero) */
		lm = procedi(lm, t, p);
	}
	
	if(t == NULL && p != NULL && prf == -1) {
		/* Se siamo scesi dall'albero è tempo di ridare il controllo al main */
		ev.e = SCESO;
		ev.lista = l;
		ev.mosse = lm;
		return ev;
	}
	
	if(t == NULL) {
		/* Se siamo caduti, ridiamo il controllo al main */
		ev.e = CADUTO;
		ev.lista = l;
		ev.mosse = lm;
		return ev;
	}
	
	if(t->sx == NULL && t->dx == NULL) {
		/* Se invece siamo su una foglia... */
		
		if(MODE == 2) {
			/* Se è la modalità pro, verifico se la banana è già stata raccolta, altrimenti la aggiungo alla collezione! */
			if(!contienebanana(l, t)) {
				l = aggiungibanana(l, t);
				printf("\nHo trovato una banana [%d]\n", t->dato);
			}
		
		} else {
			/* Se siamo in modalità POW o STD, raccogliamo semplicemente la banana e ce ne andiamo.. */
			printf("\nHo trovato la banana [%d]!!!1!\n", t->dato);
			ev.e = BANANA;
			ev.lista = l;
			return ev;
		}
	}
	
	do {
		printf("\nSei a profondita' %d [%d]\n", prf, t->dato);
		
		if(MODE == 2) {
			/* Se siamo in modalità PRO, verifichiamo la validità delle mosse */
			printf("Inserisci la direzione ( ");
			if(mossa_valida(t, 's')) printf("'s' = sinistra, ");
			if(mossa_valida(t, 'd')) printf("'d' = destra, ");
			printf("'i' = indietro ):  ");
		} else  {
			/* Altrimenti stampiamo tutto e l'utente si arrangia :) */
			printf("Inserisci la direzione ('s' = sx, 'd' = dx");
			if(MODE > 0) printf(", 'i' = indietro");
			printf("):  ");
		}
		
		/* Pulisco il buffer (non si sa mai..) e leggo la mossa*/
		fflush(stdin);
		scanf("%c", &s);
		fflush(stdin);
		
		val = mossa_valida(t, s);
		if(!val) printf("Mossa non valida!!1!\n");
	} while(!val);
	
	/* E ora è tempo di muoverci. Se procediamo verso l'alto, aggiungiamo una nuova mossa
	   altrimenti se scendiamo cancelliamo l'ultima mossa! */
	switch(s) {
		case 's':
			lm = procedi(lm, t->sx, t);
			return muovi(t->sx, prf + 1, t, l, lm);
		case 'd':
			lm = procedi(lm, t->dx, t);
			return muovi(t->dx, prf + 1, t, l, lm);
		case 'i':
			if(MODE) {
				m = indietreggia(&lm);
				return muovi(m.prec, prf - 1, m.succ, l, lm);	
			} 
		default:
			/* Non dovremmo trovarci qui...ma meglio prevenire che curare! */
			return muovi(t, prf, p, l, lm);
	}
}

/* Verifica che la mossa sia valida */
int mossa_valida(Albero t, char d) {
	if(t == NULL) return 0;
	
	if(MODE == 2) {
		if(		(t->sx == NULL && d == 's') ||
				(t->dx == NULL && d == 'd'))
				return 0;
	}
	
	return (d == 's' || d == 'd' || d == 'i');
}

/* Stampa l'esito del movimento della scimmietta */
void stampa(EventoComplesso ev) {
	switch(ev.e) {
		case BANANA:
			printf("\nCongratulazioni! La scimmia si e' magnata la banana...contento ora?\n");
			break;
		case CADUTO:
			printf("\nL'immortacci tua! Mi hai fatto cadere!\n");
			break;
		case SCESO:
			if(MODE == 2 && contabanane(ev.lista) > 0)	printf("\nCongratulazioni! La scimmia si e' magnata %d banana/e...contento ora?\n", contabanane(ev.lista));
			else printf("Sono a terra...quante banane si vedono da qui', oihbo'\n");
			break;
	}
}
