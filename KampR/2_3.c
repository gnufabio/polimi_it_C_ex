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
#include <ctype.h>
#include <math.h>
#include <string.h>

#define WRONG_STRING -1

/*
*	Write the function htoi(s) which convers a string of hexadecimal digits (including an optional 0x or 0X)
* 	into its equivalent integer  [long] value. The allowable digits are 0 -> 9, a -> f and A -> F
*/
unsigned long int htoi(const char *s) {
	/* Check if contains only allowed values */
	unsigned int len = strlen(s);
	unsigned short flag = 0;
	
	char c, next_char;

	int i = 0; /* Index for while */
	
	while(i < len) {
		c = *(s + i);
		
		/* If the first two characters of the string are "0x" or "0X", we set FLAG = 1 */
		if(i == 0) {
			next_char = *(s + ++i);
			if(c == '0' && (next_char == 'x' || next_char == 'X')) {
				flag = 1;
			}
		} else {
			if(!isxdigit(c)) {
				return WRONG_STRING;
			}
		}
		i++;
	}
	
	if(flag) {
		s += 2;  /* Ignore 0x */
	}
	
	unsigned long int result = 0;
	len = strlen(s);
	
	i = 0;
	while(i < len){
		c = *(s + i);
		
		/* Now we must assign the hex value to the char */
		if(isdigit(c)) {
			c -= '0';
		} else if (isalpha(c)) {
			c = ((isupper(c)) ? tolower(c) : c) - 'a' + 10; /* First, get the position of the chars from 'a'. Then add 10, the minimum hex value for chars */
		}
		result += c * ((long int) pow(16, i));
		i++;
	 }
	 
	 return result;
}
