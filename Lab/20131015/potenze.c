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
	int base, exp, i;
	short int negative_exponent = 0;
	unsigned long int result = 1;
	
	printf("Please, enter a base and an exponent in the format \"b^e\":  ");
	scanf("%d ^ %d", &base, &exp);
	
	if(exp < 0) {
		negative_exponent = 1;
		exp = -exp;
	} else if(exp == 0) {
		result = 1;
		printf("Result: %ld\n", result);
		return 0;
	}
	
	printf("\n%d^0:\t1\n", base);
	
	while(i <= exp) {
		result *= base;
		if(negative_exponent == 0) {
			printf("%d^%d:\t%ld\n", base, i, result);
		} else {
			printf("%d^%d:\t1/%ld\n", base, i, result);
		}
		i++;
	}
	
	return 0;
}
