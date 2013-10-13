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

/*
 * Write the function any(s1,s2) , which returns the first location in 
 * the string s1 where any character from the string s2 occurs, or −1 if s1 contains 
 * no characters from s2 . (The standard library function strpbrk does the same job 
 * but returns a pointer to the location.)
 */
int any(const char *s1, const char *s2) {
	int index = 0, x;
	
	char s1c, s2c;
	while((s1c = *(s1 + index)) != '\0') {
		x = 0;
		while(( s2c = *(s2 + x++)) != '\0') {
			if(s1c == s2c) return index;
		}
		index++;
	}
	
	return -1;
}
