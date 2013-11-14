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
#include <time.h>

#define N 6
#define CICLO 1000
#define N_RAND_MAX 6

typedef struct { unsigned short int r, c; } Casella;
typedef Casella TappetoElastico[N][N];

void init_matrix(TappetoElastico, int);
int ciclico(TappetoElastico);
int contasalti(TappetoElastico, int, int);
void print_matrix(TappetoElastico);

void init_matrix(TappetoElastico te, int ciclico) {
	int i, j, cic_div;
	unsigned short int r, c;
	
	srand(time(NULL));
	
	cic_div = ciclico ? N : N_RAND_MAX + 1;
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			r = (unsigned short int) (rand() % (cic_div));
			c = (unsigned short int) (rand() % (cic_div));
			
			te[i][j].r = r;
			te[i][j].c = c;
		}
	}
}

void print_matrix(TappetoElastico te) {
	int i, j;
	
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			printf(" {%d,%d}", te[i][j].r, te[i][j].c);
		}
		printf("\n");
	}
}

int ciclico(TappetoElastico te) {
	int i = 0, j = 0; /* 0,0 è la casella di partenza */
	Casella curr;
	char c_flags[N][N] = { 0 };
	
	while(i < N && j < N) {
		if(c_flags[i][j] == 0) {
			/* Se non sono ancora passato da questa casella tengo traccia del fatto che ci sono passato per la prima volta */
			c_flags[i][j] = 1;
		} else {
			/* Se sono già passato da questa casella significa che il ciclo si ripeterà infinite volte! */
			return 1; 
		}
		
		/* Preparo i e j per la prossima casella */
		curr = te[i][j];
		i = curr.r;
		j = curr.c;
	}
	/* Se esco dal while significa che i >= N || j >= N */
	return 0;
}

int contasalti(TappetoElastico te, int r, int c) {
	int salti = 1, s;
	Casella next = te[r][c];
	
	if(c == 0 && r == 0) {
		if(ciclico(te)){
			return -1;
		}
	}
	
	if(next.c >= N || next.r >= N) {
		printf("Uscita!\n");
		return 1;
	}
	
	s = contasalti(te, next.r, next.c);
	return ((s == - 1) ? -1 : (salti + s));
}

int main(void) {
	TappetoElastico te1, te2;
	
	init_matrix(te1, 0);
	init_matrix(te2, 1);
	
	print_matrix(te1);
	printf("Numero di salti: %d\n", contasalti(te1, 0, 0));
	printf("Bravaaaaaaaa! Clap clap clap!\n\n");
	
	print_matrix(te2);
	printf("Numero di salti: %d\n", contasalti(te2, 0, 0));
	printf("Bravaaaaaaaa! Clap clap clap!\n");
	return 0;
}
