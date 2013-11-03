/*
 *     Copyright 2013 gnufabio <bonassi.fabio.94@gmail.com>
 *
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct { int giorno, mese, anno; } Data;
typedef struct { char nome[20]; Data datanascita; float peso; int popolarita; } Maialino;
typedef struct { int numero_maialini; Maialino pigs[MAX]; } Allevamento;

/* Methods for qsort */
int confronta_data( const void *, const void *);
int confronta_nome(const void *, const void *);
int confronta_peso(const void *, const void *);
int confronta_popolarita(const void *, const void *);
/* Other methods */
void stampa_maialino(Maialino *);

int main () {
	Allevamento a = { 7, "Porky Pig", {12,7,1936}, 33.50, 85 ,
						"Miss Piggy", {17,12,1974}, 23.95, 170 ,
						"Babe", {23,1,1996}, 18.80, 250 ,
						"Pumbaa", {14,11,1994}, 79.99, 1690 ,
						"Peppa", {31,5,2004}, 12.15, 8500 ,
						"Hamm", {12,7,1968}, 19.05, 290 ,
						"Piglet", {22,4,1926}, 9.30, 1260 };
						
	Maialino *ord_alfabetico[MAX] = { NULL },
			*ord_data[MAX] = { NULL },
			*ord_peso[MAX] = { NULL },
			*ord_pop[MAX] = { NULL };
			
	
	int i;
	
	/* Inizializza gli array di puntatori */
	for(i = 0; i < a.numero_maialini; i++) {
		ord_alfabetico[i] = &(a.pigs[i]);
		ord_data[i] = &(a.pigs[i]);
		ord_peso[i] = &(a.pigs[i]);
		ord_pop[i] = &(a.pigs[i]);
	}
	
	/* Ordine alfabetico */
	qsort(ord_alfabetico, a.numero_maialini, sizeof(Maialino *), confronta_nome);
	qsort(ord_data, a.numero_maialini, sizeof(Maialino *), confronta_data);
	qsort(ord_peso, a.numero_maialini, sizeof(Maialino *), confronta_peso);
	qsort(ord_pop, a.numero_maialini, sizeof(Maialino *), confronta_popolarita);
	
	printf("Ordine alfabetico: \n");
	for(i = 0; i < a.numero_maialini; i++) {
		stampa_maialino(ord_alfabetico[i]);
	}
	printf("\n\nOrdine data:\n");
	for(i = 0; i < a.numero_maialini; i++) {
		stampa_maialino(ord_data[i]);
	}
	printf("\n\nOrdine di peso:\n");
	for(i = 0; i < a.numero_maialini; i++) {
		stampa_maialino(ord_peso[i]);
	}
	printf("\n\nOrdine di popolarita':\n");
	for(i = 0; i < a.numero_maialini; i++) {
		stampa_maialino(ord_pop[i]);
	}
	printf("\n");
	return 0;
	
}


/* Methods for qsort */
int confronta_nome(const void *m1, const void *m2) {
	Maialino * const *ptr1 = m1;
	Maialino * const *ptr2 = m2;
	
	return strcmp((*ptr1)->nome, (*ptr2)->nome);
}

int confronta_data(const void *m1, const void *m2) {
	Maialino * const *ptr1 = m1;
	Maialino * const *ptr2 = m2;
	Data *data1 = &((*ptr1)->datanascita);
	Data *data2 = &((*ptr2)->datanascita);
	
	if(data1->anno > data2->anno) {
		return 1;
	} else if(data1->anno < data2->anno) {
		return -1;
	}
	
	if(data1->mese > data2->mese) {
		return 1;
	} else if(data1->mese < data2->mese) {
		return -1;
	}
	
	if(data1->giorno > data2->giorno) {
		return 1;
	} else if(data1->giorno < data2->giorno) {
		return -1;
	}
	
	return 0;
}

int confronta_peso(const void *m1, const void *m2) {
	Maialino * const *ptr1 = m1;
	Maialino * const *ptr2 = m2;
	
	if((*ptr1)->peso > (*ptr2)->peso) {
		return 1;
	} else if((*ptr1)->peso < (*ptr2)->peso) {
		return -1;
	} else {
		return 0;
	}
}

int confronta_popolarita(const void *m1, const void *m2) {
	Maialino * const *ptr1 = m1;
	Maialino * const *ptr2 = m2;
	
	if((*ptr1)->popolarita > (*ptr2)->popolarita) {
		return 1;
	} else if((*ptr1)->popolarita < (*ptr2)->popolarita) {
		return -1;
	} else {
		return 0;
	}
}

void stampa_maialino(Maialino *m) {
	printf("Maialino %s, nato il %d/%d/%d, peso %.2f kg, popolarita' %d\n", m->nome, (m->datanascita).giorno, (m->datanascita).mese, (m->datanascita).anno, m->peso, m->popolarita);
}
