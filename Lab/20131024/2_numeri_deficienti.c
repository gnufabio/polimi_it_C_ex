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
#define EXIT_SENTINEL -1

int main() {
	int i, sigma, num;
	
	do {
		printf("Please, enter a number (-1 to exit): ");
		scanf("%d", &num);
		
		
		if(num == EXIT_SENTINEL) break;
		
		if(num < 0) num = -num; /* consider abs(num) */
		
		sigma = 0;
		
		for(i = 1; i <= (num / 2); i++) {
			if((num % i) == 0) {
				sigma += i;
			}
		}
		
		if(sigma > num) {
			printf("%d:\tDeficient number\n", num);
		} else if(sigma == num) {
			printf("%d:\tPerfect number\n", num);
		} else if(sigma < num) {
			printf("%d:\tAbundant number\n", num);
		}
		printf("\n");
	} while(1);
	
	getchar();
	return 0;
}
