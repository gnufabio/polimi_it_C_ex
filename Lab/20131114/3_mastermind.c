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
#include <ctype.h>
#include <stdlib.h>

#define N 5
#define C_N 10

typedef struct { int c[N]; } Combinazione;
typedef struct s_risposta { int esatti; int spostati; } Risposta;
char colori[C_N] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'L'};

Risposta verifica(Combinazione, Combinazione);
Combinazione leggi_tentativo(void);
Combinazione genera_combinazione(void);

int main(void) {
	int f;
	Combinazione codice, tentativo;
	Risposta esito;
	
	codice = genera_combinazione();
	f = 0;
	
	while(!f) {
		tentativo = leggi_tentativo();
		esito = verifica(codice, tentativo);
		
		f = (esito.esatti == N);
		if(f) {
			printf("\nCongratulazioni, hai indovinato!\n");
		} else {
			printf("Esatti: %d, Spostati: %d", esito.esatti, esito.spostati);
		}
	}
	
	return 0;
}

Risposta verifica(Combinazione combinazione, Combinazione tentativo) {
	Risposta esito = {0, 0};
	/* Tiene traccia dei numeri esatti */
	int flag_vect_c[N] = { 0 }, flag_vect_t[N] = { 0 };
	int i, j;
	
	for(i = 0; i < N; i++) {
		if(tentativo.c[i] == combinazione.c[i]) {
			esito.esatti++;
			flag_vect_t[i] = 1;
			flag_vect_c[i] = 1;
		}
	}
	
	if(esito.esatti == N) {
		return esito;
	}
	
	for(i = 0; i < N; i++) {
		if(flag_vect_t[i] == 0) {
			
			for(j = 0; j < N; j++) {
				if(tentativo.c[i] == combinazione.c[j] && flag_vect_c[j] == 0) {
					flag_vect_c[j] = 1;
					flag_vect_t[i] = 1;
					esito.spostati++;
					break;
				}
			}
		}
	}
	
	return esito;
}

Combinazione genera_combinazione(void) {
	Combinazione comb;
	int i;
	
	srand(time(0));
	
	for(i = 0; i < N; i++) {
		comb.c[i] = colori[rand() % C_N];
	}
	
	return comb;
}

Combinazione leggi_tentativo(void) {
	int i;
	int c;
	Combinazione risposta;
	
	printf("\n\nInserisci una combinazione: ");
	for(i = 0; i < N;) {
		c = getchar();
		c = toupper(c);
		
		if(c >= 'A' && c <= 'A' + C_N - 1) {
			risposta.c[i] = c;
			i++;
		}
	}
	fflush(stdin);
	return risposta;
}
