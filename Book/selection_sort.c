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

#include <stdlib.h>
#include <stdio.h>

void selection_sort(int *, int);

int main() {
	int n, i;
	int *array;
	
	printf("Enter the number of elements: ");
	scanf("%d", &n);
	
	if(n < 0) {
		n = -n;
	} 
	
	array = (int *) malloc(sizeof(int) * n);
	printf("\n\n");
	
	for(i = 0; i < n; i++) {
		printf("[%d] = ", i);
		scanf("%d", &array[i]);
		printf("\n");
	}
	
	printf("\n\n");
	selection_sort(array, n);
	
	for(i = 0; i < n; i++) {
		printf("[%d]: %d\n", i, array[i]);
	}
	
	free(array);
	return 0;
}

void selection_sort(int *array, int max) {
	int maximum = array[0], max_position = 0; /* Store what is the maximum and its index in array */
	int i, temp;
	
	for(i = 0; i < max; i++) {
		if(array[i] > maximum) {
			maximum = array[i];
			max_position = i;
		}
	}
	
	temp = array[max - 1];
	array[max - 1] = maximum;
	array[max_position] = temp;
	
	if(max - 2 > 0) {
		selection_sort(array, max - 1); /* Be recursive ONLY if there are at least 2 elements! */
	} else {
		return;
	}
}
