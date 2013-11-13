#include <stdio.h>
#include <math.h>

void effezero(int);
void effetre(int);
void effetre_ric(int, int);

void effezero(int n) {
	int i;
	
	if(n == 0) {
		printf(".");
		return;
	}
	
	for(i = 0; i < n; i++) {
		printf("%d", n);
	}
	
	effezero(n - 1);
	
	for(i = 0; i < n; i++) {
		printf("%d", n);
	}
	
	return;
}

void effetre_ric(int n, int k) {
	int i;
	
	if( n - k == 0 ) {
		effetre(n + 1, k);
		return;
	}
	
	if(n < k) {
		for(i = 0; i < (k - n); i++) {
			printf("%d", n + 1);
		}
		effetre( n + 1, k);
	} else if(n > k && abs(n - k) < k) {
		for(i = 0; i <= (n - k); i++) {
			printf("%d", 2 * k - n);
		}
		effetre( n + 1, k);
	}
	return;
}

void effetre(int n) {
	effetre_ric(0, n);
}

int main(void) {
	int n0 = 5;
	
	effezero(n0);
	printf("\n");
	effetre(0, n0);
	return 0;
}
