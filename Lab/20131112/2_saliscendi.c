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
