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

#define DATA_MAX_LEN 8

typedef struct { 
	int giorno;
	int mese;
	int anno; 
} Data;

int confronta(Data, Data);
void stampa(Data);

int main(void) {
	Data d1, d2;
	
	printf("Inserisci la prima data, formato dd/mm/YYYY: ");
	scanf("%d / %d / %d", &(d1.giorno), &(d1.mese), &(d1.anno));
	fflush(stdin);
	
	printf("\nInserisci la seconda data, formato dd/mm/YYYY: ");
	scanf("%d / %d / %d", &(d2.giorno), &(d2.mese), &(d2.anno));
	
	switch(confronta(d1, d2)) {
		case 0:
			printf("La data ");
			stampa(d1);
			printf(" e' uguale alla data ");
			stampa(d2);
			printf("!\n");
			break;
		case 1:
			printf("La data ");
			stampa(d1);
			printf(" e' antecedente alla data ");
			stampa(d2);
			printf("!\n");
			break;
		case -1:
			printf("La data ");
			stampa(d1);
			printf(" e' successiva alla data ");
			stampa(d2);
			printf("!\n");
			break;
	} 
	
	free(test);
	return 0;
}

int confronta(Data d1, Data d2) {
	char *date_1 = calloc((DATA_MAX_LEN + 1), sizeof(char));
	char *date_2 = calloc((DATA_MAX_LEN + 1), sizeof(char));
	int i, result = 0;
	
	sprintf(date_1, "%.4d%.2d%.2d\0", d1.anno, d1.mese, d1.giorno);
	sprintf(date_2, "%.4d%.2d%.2d\0", d2.anno, d2.mese, d2.giorno);
	
	for(i = 0; i < DATA_MAX_LEN; i++) {
		if(date_1[i] > date_2[i]) {
			result = -1;
			break;
		} else if(date_1[i] < date_2[i]) {
			result = 1;
			break;
		}	
	}
	
	free(date_1);
	free(date_2);
	return result;
}

void stampa(Data d1) {
	printf("%d/%d/%d", d1.giorno, d1.mese, d1.anno);
}
