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
#include <string.h>

/* Write an alternate version of squeeze(s1,s2) that deletes 
 * each character in s1 that matches any character in the string s2 
 */
int squeeze(char *s1, const char *s2) {
	int rep_counter = 0;
	int index = 0, x;
	short int flag;
	char *charpointer;
	
	/*
	 * To check any repetition in s2 or not to check? This is the question.
	 * While avoiding repetitions in s2 would avoid lot of cicles, 
	 * checking (and removing) repetitions would waste as much cicles too.
	 */
	while(*(charpointer = s1 + index) != '\0') {
		x = 0, flag = 0; /* Reset the variables at each cicle */ 
				
		while(*(s2 + x) != '\0') {
			if(*(s2 + x) == *charpointer) {
				flag = 1;
				break;
			}
			x++;
		}
		
		if(flag == 0) {
			*(s1 + rep_counter++) = *charpointer;
		}
		index++;
	}
	
	*(s1 + rep_counter) = '\0';
	return (index - rep_counter); /* Difference of the string size */
}
