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
#include <math.h>

#define QUAD(X) quad##X

int is_square(unsigned long int);
double power(int, int);
void find_three_squares(unsigned long int);
void find_two_squares(unsigned long int);
int are_permutations(unsigned long int [], unsigned long int [], int);

int main() {
	unsigned long int number;
	unsigned long int QUAD(1) = 0, QUAD(2) = 0, QUAD(3) = 0;
	unsigned long int i;
	int choice;
	
	short found_flag = 0;
	
	printf("Enter the number: ");
	scanf("%lu", &number);
	
	printf("How many square numbers? [2/3/4 = all]: ");
	scanf("%d", &choice);
	
	if(choice != 2 && choice != 3) {
		choice = 4;
	}
	
	switch(choice) {
		case 2:
			find_two_squares(number);
			break;
		case 3:
			find_three_squares(number);
			break;
		case 4:
			find_two_squares(number);
			find_three_squares(number);
			break;
	}
	
	return 0;
}

void find_three_squares(unsigned long int num) {
	
	unsigned long int max, i, x, j;
	int min;
	short int flag_found = 0, permutation; /* flag_found: check if there is at least one result; 
											  permutation: check if the last numbers were a permutation. */
	
	/* Array of found values */
	int length_counter = 0; /* Counter for the array length (collections + free space) */
	unsigned long int *array = (unsigned long int *) malloc(sizeof(unsigned long int) * 3);
	unsigned long int *array_frame_ptr; /* A pointer to the current set of 3 values. This is a sort of dynamic multi-dimensional
										   array, and frame pointer points to the current row of this multi-dimensional array;  */
	unsigned long int tmparray[3];      /* A temporary array which contains the set of the three numbers */
	
	if(num < (1 + 4 + 9)) {
		printf("\n\nHow can a number be the sum of three squares if it is minor than 14?\n");
		free(array);
		return;
	}
	
	min = 9;
	max = num - (1 + 4);
	
	for(i = min; i <= max; i++) {
		if(is_square(i)) {
			for(x = 1; x <= (num - i - 4); x++) {
				if(is_square(x) && is_square( num - i - x)) {
					
					permutation = 0; /* Reset permutation flag */
					tmparray[0] = i; /* Copy the numbers to the temporary array*/
					tmparray[1] = x;
					tmparray[2] = num - i - x;
					
					if(length_counter > 0) {
						/* If there is at least one set of numbers check if the new numbers are permutations */
						for(j = 0; j < length_counter; j++) {
							array_frame_ptr = array + (j * 3);
							if(are_permutations(tmparray, array_frame_ptr, 3)) {
								goto next_square;
							}
						}
					}
					
					/* Here, we are sure that the set of numbers is not a permutation.
					   So, let's copy it in the collection of new sets, and expand the array. */
					memcpy(array + (length_counter * 3), tmparray, sizeof(unsigned long int) * 3);
					length_counter++;
					realloc(array, (length_counter) * sizeof(unsigned long int) * 3);
					
					
					flag_found = 1;
					printf("\nI found a sum of square numbers: %lu + %lu + %lu = %lu", i, x, num - x - i, num);
					next_square:;
				}
			}	
		}
	}	
	
	if(!flag_found) {
		printf("\nCouldn\'t find three square numbers that matched the requests\n");
	}
}

void find_two_squares(unsigned long int num) {
	unsigned long int i, j;
	short int found_flag = 0, permutation;
	
	int length_counter = 0;
	unsigned long int *array = (unsigned long int *) malloc(sizeof(unsigned long int) * 2);
	unsigned long int *array_frame_ptr;
	unsigned long int tmparray[2];
	
	if(num < 5) {
		printf("\n\nHow can a number be the sum of two squares if it is minor than 5?\n");
		free(array);
		return;
	}
	
	for(i = 1; i <= (num - 4); i++) {
		if(is_square(i)) {
			if(is_square(num - i)) {
				
				permutation = 0;
				
				tmparray[0] = i; 
				tmparray[1] = num - i;
					
				if(length_counter > 0) {
					for(j = 0; j < length_counter; j++) {
						array_frame_ptr = array + (j * 2);
						if(are_permutations(tmparray, array_frame_ptr, 2)) {
							goto next_square;
						}
					}
				}
				
				memcpy(array + (length_counter * 2), tmparray, sizeof(unsigned long int) * 2);
				length_counter++;
				realloc(array, (length_counter) * sizeof(unsigned long int) * 2);
				
				found_flag = 1;
				printf("\nI found a sum of square numbers: %lu + %lu = %lu", i, num - i, num);
				next_square:;
			}
		}
	}
	
	free(array);
	
	if(!found_flag) {
		printf("\nCouldn\'t find two square numbers that matched the requests\n");
	}
}

int are_permutations(unsigned long int array1[], unsigned long int array2[], int arraylen) {
	int i, x;
	short int global_result = 1, local_result;
	
	/* First of all, we must check if all the elements in array1 are in array2*/
	for(i = 0; i < arraylen; i++) {
		local_result = 0;
		for(x = 0; x < arraylen; x++) {
			if(array1[i] == array2[x]) {
				local_result = 1;
				break;
			}
		}
		global_result = global_result && local_result;
		if(!global_result) {
			return 0;
		}
	}
	
	/* Then, we must check if all the elements in array2 are in array1 too */
	for(i = 0; i < arraylen; i++) {
		local_result = 0;
		for(x = 0; x < arraylen; x++) {
			if(array2[i] == array1[x]) {
				local_result = 1;
				break;
			}
		}
		global_result = global_result && local_result;
		if(!global_result) {
			return 0;
		}
	}
	
	return global_result;
}


int is_square(unsigned long int number) {
	unsigned long int _sqrt = sqrt(number);
	return ((_sqrt * _sqrt) == number);
}

double power(int base, int exponent) {
	double result = 1;
	int i;
	
	if(exponent > 0) {
		for(i = 1; i <= exponent; i++) {
			result *= result;
		}
		return result;
	} else if(exponent == 0) {
		return 1;
	} else {
		exponent = - exponent;
		for(i = 1; i <= exponent; i++) {
			result *= result;
		}
		return (1/result);
	}
}
