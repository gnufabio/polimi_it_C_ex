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
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 50
#define OFFSET ('z' - 'a' + 1) + ( '9' - '0' + 1)
#define ALPHA_OFF '9' - '0' + 1

int getstr(char *, int);
int are_anagrams(char *, char *);

int main(void) {
	char str1[MAX_SIZE], str2[MAX_SIZE];
	printf("Inserisci la prima stringa: \n");
	getstr(str1, MAX_SIZE);
	printf("\nInserisci la seconda stringa: \n");
	getstr(str2, MAX_SIZE);
	
	if(are_anagrams(str1, str2)) {
		printf("\nLe due stringhe sono anagrammi!\n");
	} else {
		printf("\nLe due stringhe non sono anagrammi!\n");
	}
	
	return 0;
}

int getstr(char *str, int maxlen) {
	char c;
	int len = 0;
	
	while((c = getchar()) != '\n' && len < maxlen - 1) {
		str[len++] = c;
	}
	str[len] = '\0';
	fflush(stdin);
	return len;
}

int are_anagrams(char *str1, char *str2) {
	int *check_array;
	int i, result = 1;
	char c;
	
	check_array = calloc(OFFSET, sizeof(int));
	
	for(i = 0; i < strlen(str1); i++) {
		c = str1[i];
		if(isalpha(c)) {
			c = tolower(c);
			check_array[c - 'a' + ALPHA_OFF]++;
		} else if(isdigit(c)) {
			check_array[c - '0']++;
		}
	}
	
	for(i = 0; i < strlen(str2); i++) {
		c = str2[i];
		if(isalpha(c)) {
			c = tolower(c);
			check_array[c - 'a' + ALPHA_OFF]--;
		} else if(isdigit(c)) {
			check_array[c - '0']--;
		}
	}
	
	for(i = 0; i < OFFSET; i++) {
		if(check_array[i] != 0) {
			result = 0;
			break;
		}
	}
	
	free(check_array);
	return result;
}
