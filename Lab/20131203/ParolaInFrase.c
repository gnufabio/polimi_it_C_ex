#include <stdio.h>
#include <string.h>
#include <ctype.h>

int pif( char *, char *);

int main() {
	printf("%d\n", pif("**********", "**********"));
	return 0;
}

int pif(char *frase, char *parola) {
	int cw, i, x;
	char prev = ' ', c;
	cw = 1;
	x = 0;
	
	for(i = 0; i < strlen(frase); i++) {
		c = frase[i];
		
		if(isalnum(frase[i])) {	
			if(isspace(prev) || cw == 1) {
				if(c == parola[x]) {
					x++;
					cw = 1;
				} else {
					cw = 0;
					x = 0;
				}
			}	
		} else if(isspace(c)) {
			if(cw == 1 && x == strlen(parola)) {
				return 1;
			}
		}
		
		prev = c;
	}
	
	if(cw == 1 && x == strlen(parola)) {
		return 1;
	} else {
		return 0;
	}
}
