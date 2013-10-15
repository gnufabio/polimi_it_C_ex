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

int main(void) {
	int n, caso;
	int i = 1, x, remainder; /* Index for external cicle, for internal cicle and reminder. */
	
	printf("Please enter the side of the square: N = ");
	scanf("%d", &n);
	printf("\nEnter the case [1,2,3,4]: ");
	scanf("%d", &caso);
	printf("\n\n");
	
	if(caso <= 0 || caso > 4) caso = 1;
	
	switch(caso) {
		case 1:
			while(i <= n) {
				x = 1;
				
				while(x <= n) {
					printf(" *");
					x++;
				}
				printf("\n");
				i++;
			}
			break;
		case 2:
			while(i <= n) {
				x = 1;
				remainder = 0;
				while(x <= n) {
					remainder = x % n;
					
					if(remainder == 0 || remainder == 1 || i == 1 || i == n) {
						printf(" *");
					} else {
						printf("  ");
					}
					x++;
				}
				
				printf("\n");
				i++;
			}
			break;
		case 3:
			while(i <= n) {
				x = 1;
				while(x <= i) {
					printf(" *");
					x++;
				}
				
				printf("\n");
				i++;
			}
			break;
		case 4:
			while(i <= n) {
				x = 1;
				while(x <= n) {
					if(x <= i) {
						printf(" *");
					} else {
						printf(" +");
					}
					x++;
				}
				
				printf("\n");
				i++;
			}
			break;
		default:
			return 1;
	}
	return 0;
}
