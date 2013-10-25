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

#define MIN_BASE 2
#define MAX_BASE 207

/* 
 * MAX ARRAY DIGITS is the maximum length of the binary string  of 206, which is the
 * highest value of a single digit (in base 207).
 */
#define MAX_ARRAY_DIGITS 8

/* The following MACROs associate the value of the characters with numeric values */
#define DIG_UNCAP_OFFSET 	('9' - '0' + 1)
#define UNCAP_CAP_OFFSET 	(DIG_UNCAP_OFFSET + ('z' - 'a') + 1)
#define CAP_OFFSET 			(UNCAP_CAP_OFFSET +  ('Z' - 'A') + 1)

void stradd(char **, char, int *);
void strrvrt(char *);
unsigned long int to_base_10(char *, int);
int value_of(unsigned char);
unsigned char char_from_value(int);
void from_dec_to_base(unsigned long int, char *, int);


int main(void) {
	int base1, base2;
	unsigned long int number_base_10 = 0, accumulator = 1;
	unsigned char c, tmpc;
	/* Strings stuff */
	char *number_ptr = malloc(sizeof(char));
	int len = 1;
	
	strcpy(number_ptr, "\0");
	
	fflush(stdin);
	printf("Enter the base of the number you'd like to convert:  ");
	scanf("%d", &base1);
	fflush(stdin);
	printf("Enter the base to which you'd like to convert your number:  ");
	scanf("%d", &base2);
	
	if(base1 < MIN_BASE) {
		base1 = MIN_BASE;
	}
	if(base2 > MAX_BASE) {
		base2 = MAX_BASE;
	}
	
	fflush(stdin);
	printf("Enter the number:  ");
	
	while((c = getchar()) != '\n') {
		/* Get the value associated to the character */ 
		tmpc = value_of(c);
		/* Check for invalid chars */
		if(tmpc < 0 || tmpc >= base1) {
			printf("Char %c[%d] exceed the numbers for base %d!", c, value_of(c), base1);
			return 1;
		}
		
		/* Add the character to the string, and increase length if necessary */
		stradd(&number_ptr, c, &len);
	}
	
	if(strlen(number_ptr) == 0) {
		printf("You haven't entered any valid number! Exiting...");
		return 1;
	}
	
	/* Revert the string, since the characters where read in reverse order */
	strrvrt(number_ptr);
	/* Get the number in base 10 of the read number */
	number_base_10 = to_base_10(number_ptr, base1);
	/* Get the number in base base2 -> saved to number_ptr */
	from_dec_to_base(number_base_10, number_ptr, base2);
	
	printf("\nIn base %d the number is: %s", base2, number_ptr);
	
	free(number_ptr);
	return 0;
}

/* Append a character to a string, increasing its size if necessary. */
void stradd(char **str, char c, int *memlength) {
	int len = strlen(*str);
	char *tmpptr;
	
	if(len + 1 >= *memlength) {
		tmpptr = realloc(*str, *memlength + 1);
		if(tmpptr != NULL) {
			*str = tmpptr;
		}
		*memlength += 1;
	}
	(*str)[len++] = c;
	(*str)[len] = '\0';
}

/* Reverts a string */
void strrvrt(char *str) {
	char tmp;
	int len = strlen(str), i, x;
	
	/* 
	 * (len/2) is the char at the left of the middle.
	 * (len/2) - 1 represents that char in the array. 
	 * Notice that if n is uneven, there is the middle character,
	 * which remains untouched.
	 */
	for(i = 0; i <= (len / 2 - 1); i++) {
		x = (len - 1) - i;
		
		tmp = str[i];
		str[i] = str[x];
		str[x] = tmp;
	}
}

/* Convert the number - saved in a string - to a decimal unsigned long int  */
unsigned long int to_base_10(char *number, int base) {
	unsigned long int accumulator = 1, result = 0;
	int i, c;
	
	for(i = 0; i < strlen(number); i++) {
		c = value_of(number[i]);
		result += (c * accumulator);
		accumulator *= base;
	}
	
	return result;
}

/* Convert a decimal number to a number - saved in a string - in base 'base' */
void from_dec_to_base(unsigned long int number, char *to, int base) {
	int remaining, memlen;
	
	/* Reset the string */
	free(to);
	to = calloc(1, sizeof(char));
	memlen = 1;
	
	do {
		remaining = number % base;
		stradd(&to, char_from_value(remaining), &memlen);
	} while (number = (number / base));
	
	/* Revert the number, since it's saved in the wrong order */
	strrvrt(to);
}

/* 
 * Get the value associated to the character:
 * 0-9 		->	'0'...'9'	DIG_UNCAP_OFFSET = 10
 * 10-36 	-> 	'a'...'z'	UNCAP_CAP_OFFSET = 36
 * 37-62    ->	'A'...'Z'   CAP_OFFSET		 = 62
 * 63-207   ->  'z' + 1
 */
int value_of(unsigned char c) {
	if(c >= '0' && c <= '9') {
		return (c - '0');
		
	} else if(c >= 'a' && c <= 'z') {
		return ((c - 'a') + (DIG_UNCAP_OFFSET));
		
	} else if(c >= 'A' && c <= 'Z') {
		return ((c - 'A') + (UNCAP_CAP_OFFSET));
		
	} else if(c > 'z') {
		return ((c - 'z') + (CAP_OFFSET));
		
	} else {
		return -1;
	}
}

/* Get the character associated to the value (reverse of 'value_of' function) */
unsigned char char_from_value(int value) {
	if(value >= 0 && value < DIG_UNCAP_OFFSET) {
		return (value + '0');
		
	} else if(value >= DIG_UNCAP_OFFSET && value < UNCAP_CAP_OFFSET) {
		return (value - DIG_UNCAP_OFFSET + 'a');
		
	} else if(value >= UNCAP_CAP_OFFSET && value < CAP_OFFSET) {
		return (value - UNCAP_CAP_OFFSET + 'A');
		
	} else if(value >= CAP_OFFSET) {
		return (value - CAP_OFFSET + 'z');
		
	} else {
		return 0;
	}
}
