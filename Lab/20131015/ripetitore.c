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

#define MODE_1 1
#define MODE_2 2
#define MODE_3 3
#define MODE_4 4
#define MODE_ALL 5

char *farfallino(char, int);
char vamavvo(char, int);
char urlata(char, int);
char fiorentina(char, char, int);
void all(char, char, int);

int main(void) {
	int mode = 0;
	char c = '0', prev = ' ';
	
	printf
		("Modalita' disponibili:\n1=Alfabeto Farfallino, \n2=Variante del vamavvo, \n3=Variante urlata, \n4=Variante fiorentina, \n5=Tutto!\n\nInserisci la modalita': ");

	scanf("%d", &mode);
	if (mode < 1 || mode > 5)
		mode = 5;

	printf("\nInserisci la stringa:\n");
	fflush(stdin);
	scanf("%c", &c);

	while (c != '\n') {
		switch (mode) {
		case MODE_1:
			farfallino(c, 1);
			break;
		case MODE_2:
			vamavvo(c, 1);
			break;
		case MODE_3:
			urlata(c, 1);
			break;
		case MODE_4:
			fiorentina(c, prev, 1);
			break;
		case MODE_ALL:
			all(c, prev, 1);
			break;
		}
		prev = c;
		scanf("%c", &c);
	}

	return 0;
}

char *farfallino(char c, int print) {
	char *ret;
	
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
		if (print)
			printf("%cf%c", c, c);
		ret = (char *)malloc(sizeof(char) * 3);
		*ret = c;
		*(ret + 1) = 'f';
		*(ret + 2) = c;
		return ret;
	} else if (c == 'A' || c == 'E' || c == 'E' || c == 'O' || c == 'U') {
		if (print)
			printf("%cF%c", c, c);
		ret = (char *)malloc(sizeof(char) * 3);
		*ret = c;
		*(ret + 1) = 'F';
		*(ret + 2) = c;
		return ret;
	} else {
		if (print)
			printf("%c", c);
		return &c;
	}
}

char vamavvo(char c, int print) {
	if (c == 'r') {
		if (print)
			printf("v");
		return 'v';
	} else if (c == 'R') {
		if (print)
			printf("V");
		return 'V';
	} else {
		if (print)
			printf("%c", c);
		return c;
	}
}

char urlata(char c, int print) {
	char newchar = c;
	if (islower(c))
		newchar = toupper(c);
	if (print)
		printf("%c", newchar);
	return newchar;
}

char fiorentina(char c, char prev_char, int print) {
	if (c == 'c' && prev_char == ' ') {
		if (print)
			printf("h");
		return 'h';
	} else if (c == 'C' && prev_char == ' ') {
		if (print)
			printf("H");
		return 'H';
	} else {
		if (print)
			printf("%c", c);
		return c;
	}
}

void all(char in, char prev, int print) {
	char c = toupper(in);
	if (c == 'A' || c == 'E' || c == 'E' || c == 'O' || c == 'U') {
		farfallino(c, print);
	} else if (c == 'R') {
		vamavvo(c, print);
	} else if (c == 'C') {
		fiorentina(c, prev, print);
	} else {
		printf("%c", c);
	}
}
