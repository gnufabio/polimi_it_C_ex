#include <stdlib.h>
#include <stdio.h>

#define DATA_SOURCE "animali.bin"
#define OUT_FILE "out.txt"

/* Definizione dei tipi di dato */
typedef enum { CANE, GATTO, CAPIBARA } tipo_animale;
typedef struct _animale {
	char nome[20];
	tipo_animale tipo;
	struct _animale *next;
} animale;
typedef animale * lista_animali;

/* Prototipi di funzione */
lista_animali leggi_lista(FILE *);
void stampa_animali(FILE *, lista_animali, tipo_animale);
void genera_indice(FILE *, lista_animali);


int main() {
	lista_animali lista;
	FILE *f;
	FILE *out;
	
	f = fopen(DATA_SOURCE, "rb");
	out = fopen(OUT_FILE, "w+");
	if(f == NULL || out == NULL) return 1;
	
	lista = leggi_lista(f);
	genera_indice(out, lista);
	
	return 0;
}

/* Genera l'indice degli animali */
void genera_indice(FILE *f, lista_animali lista) {
	fprintf(f, "*** CANI ***\n");
	stampa_animali(f, lista, CANE);
	fprintf(f, "\n*** CAPIBARA ***\n");
	stampa_animali(f, lista, CAPIBARA);
	fprintf(f, "\n*** GATTI ***\n");
	stampa_animali(f, lista, GATTO);
}

/* Se il tipo del nodo è quello da stampare lo stampa, poi eventualmente si chiama ricorsivamente per il nodo successivo */
void stampa_animali(FILE *f, lista_animali lista, tipo_animale tipo) {
	if(lista->tipo == tipo) {
		fprintf(f, "%s\n", lista->nome);
	}
	
	if(lista->next != NULL) {
		stampa_animali(f, lista->next, tipo);
	}
}

/* Legge la lista di animali dal file DATA_SOURCE e lo carica in memoria */
lista_animali leggi_lista(FILE *f) {
	lista_animali l = NULL;
	animale *a = calloc(1, sizeof(animale));
	int i;
	char c;
	
	/* Legge i 20 byte del nome */
	for(i = 0; i < 20; i++) {
		if(fread(&c, sizeof(char), 1, f)) {
			a->nome[i] = c;
		} else {
			return NULL;
		}
	}
	
	/* Legge i 4 byte del tipo */
	if(fread(&i, sizeof(tipo_animale), 1, f)) {
		a->tipo = i;
		/* A causa di un errore nel file binario, è necessario spostare manualmente il cursore di 4 byte */
		fseek(f, 4L, SEEK_CUR);
		a->next = leggi_lista(f);
	}
	
	return a;
}
