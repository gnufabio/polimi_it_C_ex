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

int pre(int);
int suc(int);
int abs(int);

int sum(int, int);
int sub(int, int);
int mul(int, int);
int div(int, int);
int sigma(int);
int prod(int);

int main(void) {
	printf("%d + %d = %d\n", 10, 9, sum(10, 9));
	printf("%d + %d = %d\n", 10, -3, sum(10, -3));
	printf("%d - %d = %d\n", -10, 9, sub(-10, 9));
	printf("%d - %d = %d\n", 5, -6, sub(5, -6));
	printf("%d * %d = %d\n", 10, 5, mul(10, 5));
	printf("%d * %d = %d\n", 2, -3, mul(2, -3));
	printf("%d / %d = %d\n", 20, 3, div(20, 3));
	printf("Sigma(%d) = %d\n", -7, sigma(-7));
	printf("Prod(%d) = %d\n", 5, prod(5));
	printf("Prod(%d) = %d\n", -5, prod(-5));
	return 0;
}


int pre(int x) { 
	return (x - 1); 
}

int suc(int x) { 
	return (x + 1); 
}

int abs(int a) {
	return (a < 0 ? -a : a);
}

int sum(int a, int b) {
	if(a == 0) {
		return b;
	}
	
	if(a > 0) {
		return sum(pre(a), suc(b));
	} else {
		return sum(suc(a), pre(b));
	}
}

int sub(int a, int b) {
	if(b == 0) {
		return a;
	}
	
	if(b > 0) {
		sub(pre(a), pre(b));
	} else {
		sub(suc(a), suc(b));
	}
}

int mul(int a, int b) {
	if(b == 1) {
		return a;
	}
	
	if(b < 0) {
		return mul(-a, abs(b));
	}
	
	return sum(a, mul(a, pre(b)));
}

int div(int a, int b) {
	/* Se a == b -> Divisione senza resto.
	 * Se a < b  -> Divisione con resto. Esco dal ciclo. */
	if(a < b) {
		return 0;
	} else if(a == b){
		return 1;
	}
	
	return suc(div(sub(a,b), b));
}

int sigma(int a) {
	if(a == 0) {
		return 0;
	}
	
	if(a < 0) {
		return sum(sigma(suc(a)), a);
	} else {
		return sum(sigma(pre(a)), a);
	}
}

int prod(int a) {
	if(a == 1) {
		return 1;
	} else if(a == -1) {
		return -1;
	}
	
	if(a < 0) {
		return mul(a, prod(suc(a)));
	} else {
		return mul(a, prod(pre(a)));
	}
}
