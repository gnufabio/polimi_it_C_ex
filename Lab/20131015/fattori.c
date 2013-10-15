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

unsigned long int factorize(unsigned long int, unsigned long int);
int is_prime(unsigned long int);
void print_repetition(unsigned long int, unsigned long int, unsigned long int *);

int main(void) {
	unsigned long int number, index, rep;
	short int two_flag = 0;
	
	printf("Please, enter a positive number to factorize:  ");
	scanf("%lu", &number);
	printf("\n\n%lu: ", number);
	
	index = 2;
	do {
		if(index == 3) two_flag = 1;
		
		if(is_prime(index)) {
			print_repetition(number, index, &rep);
		}
		
		if(two_flag == 0) {
			index++;
		} else {
			index += 2;
		}
	} while((index <= (number / 2)) || !two_flag);
	
	if(is_prime(number)) {
		print_repetition(number, number, &rep);
	}
	
	printf("\n");
	return 0;
}

void print_repetition(unsigned long int number, unsigned long int factor, unsigned long int *rep_counter) {
	*rep_counter = factorize(number, factor);
	if(*rep_counter > 0) {
		printf("%lu^%lu ", factor, *rep_counter);
	}
}

unsigned long int factorize(unsigned long int number, unsigned long int factor) {
	unsigned long int rep = 0;
	unsigned long int number_local = number;
	
	while(number_local % factor == 0) {
		number_local /= factor;
		rep++;
	}
	return rep;
}

int is_prime(unsigned long int num) {
	unsigned long int i = 3;
	long double square;
	
	if( num <= 1) {
		return 0;
	} else if(num == 2 || num == 3) {
		return 1;
	}
	
	if(num % 2 == 0) {
		return 0;
	}
		
	while(i <= sqrt(num)) {
		if(num % i == 0) {
			return 0;
		}
		i += 2;
	}
	return 1;
}
