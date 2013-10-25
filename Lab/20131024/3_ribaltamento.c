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

#define MAX_N 100
#define INC_SIZE 5

void print_word_reversed(char *, int, int);
void add_dot_to_array(int **, int, int *, int *);

int main(void) {
	/* Some variables necessary for indexing */
	int i = 0, min = -1, max = -1, x, aux;
	
	/* This variables stores the size of the arrays */
	int len, dot_array_size = 1, dot_array_len = 1;
	
	/* dot_positions stores the position of the dots in the string */
	int *dot_positions = malloc(sizeof(int));
	/* str is the input string */
	char *str = malloc((MAX_N + 1) * sizeof(char));
	char c;
	
	/* This allow us which is the first string! */
	dot_positions[0] = -1;
	
	printf("Enter a string with words divided by dots [.]:\n");
	fflush(stdin);
	
	/* Copy the input string to str */
	while ((c = getchar()) != '\n' && i < MAX_N) {
		str[i] = c;
		
		if(c == '.') {
			/* If it's a dot, store it in the array */
			add_dot_to_array(&dot_positions, i, &dot_array_len, &dot_array_size);
		}
		i++;
	}
	str[i] = '\0';
	add_dot_to_array(&dot_positions, i, &dot_array_len, &dot_array_size); /* Consider the terminator as a dot */
	len = strlen(str);
	
	fflush(stdin);
	printf("\n");
	
	/* Print the words reversed */
	for(i = 0; i < dot_array_len; i++) {
		if(i > 0) printf(".");
		
		min = dot_positions[i] + 1;
		max = dot_positions[i + 1] - 1;
		print_word_reversed(str, min, max);
	}
	printf("\n");

	/* Print the words in reversed order. We skip the last value dot_positions[dot_array_len - 2] since it's the terminator.
	 * For the structur of the cycle itself, it's a waste of time.
	 */
	for(i = dot_array_len - 2, x = len; (i >= 0) && (x > -1); i--) {
		for(aux = dot_positions[i] + 1; aux < x; aux++) {
			printf("%c", str[aux]);
		} 
		x = dot_positions[i];
		if(x > 1) printf("."); /* If it's not the first word */
	}
	
	free(str); 
	free(dot_positions); 
	return 0;
}

/* Print the character of a string in reverse order */
void print_word_reversed(char *str, int min, int max) {
	int x;
	for(x = max; x >= min; x--) {
		printf("%c", str[x]);
	}
}

/* Expand the array and add an integer */
void add_dot_to_array(int **array, int position, int *array_len, int *array_mem) {
	int new_size = *array_mem;
	int *tmpptr;
	
	/* If there isn't enought size, increase it! */
	if(*array_mem <= *array_len) {
		new_size = (*array_mem + (*array_len - *array_mem + INC_SIZE));
		tmpptr = realloc(*array, (new_size) * sizeof(int));
		if(tmpptr != NULL) {
			*array = tmpptr;
		}
	}
	
	(*array)[*array_len] = position;
	*(array_len) += 1;
	*array_mem = new_size;
}
