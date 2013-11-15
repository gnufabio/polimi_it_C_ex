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

#define N 5

int verifica(char [], char [][N]);
int verifica_parola(char [], char [][N], int [][N], int, int);

int main(void) {
	char parola[] = { 'P', 'I', 'E', 'R', 'O', 'C', 'H', 'A', 'T', '\0'};
	char schema[N][N] = { 'Z', 'B', 'C', 'O', 'P',
						  'E', 'F', 'A', 'I', 'T',
						  'O', 'I', 'A', 'E', 'A',
						  'M', 'B', 'R', 'O', 'H',
						  'M', 'P', 'A', 'C', 'F' };
						  
	printf("\nVerifica: %d", verifica(parola, schema));
	return 0;
}

int verifica(char parola[], char schema[][N]) {
	int r, c;
	int flags[N][N] = { 0 };
	
	for(r = 0; r < N; r++) {
		for(c = 0; c < N; c++) {
			if (verifica_parola(parola, schema, flags, r, c)) {
				return 1;
			}
		}
	}
	
	return 0;
}

/* Data una parola, array di char, e uno schema, matrice bidimensionale di char, una matrice di booleani che contiene i flag di stato
 * delle varie lettere, controlliamo ricorsivamente se dalla posizione [r][c] si può trovare la parola in schema. */
int verifica_parola(char parola[], char schema[][N], int flags[][N], int r, int c) {
	int i, j;
	int continue_flag = 1;
	
	/* Controlla se la posizione indicata è libera e contiene effettivamente la prima lettera */
	if(parola[0] == schema[r][c] && flags[r][c] == 0) {
		flags[r][c] = 1;
		
		if(parola[1] == '\0') {
			/* Se era l'ultimo carattere è tutto finito, abbiamo trovato la stringa */
			return 1;
		}
		
		/* Controlla le lettere adiacenti alla prima, con opportuni controlli per evitare overflow.
		 * il flag continue_flag consente di uscire dal ciclo dopo aver trovato effettivamente la parola.
		 * Un'alternativa valida era usare un goto! */
		for(i = r - 1; (i <= r + 1) && continue_flag; i++) {
			for(j = c -1; j <= c + 1; j++) {
				
				if((i < 0 || j > N - 1) || (i == r && j == c)) {
					continue;
				}
				
				/* Se la lettera successiva alla prima è tra le lettere adiacenti, controlliamo prima di tutto il flag.
				 * POI verifichiamo ricorsivamente se da tale lettera si può trovare la coda della nostra parola */
				if((parola[1] == schema[i][j]) && (flags[i][j] == 0)) {
					continue_flag = !verifica_parola(parola + 1, schema, flags, i, j);
					if(continue_flag == 0) break;
				}
			}
		}
		
		/* Se continue_flag è 0 significa che abbiamo trovato la parola e abbiamo forzato l'uscita dal ciclo. */
		return (continue_flag == 0);
	}
	
	return 0;
}
