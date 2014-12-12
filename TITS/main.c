#ifndef _INCLUDES
#define _INCLUDES
#include "tits.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#endif

/***********************************************************************
 * TITS:	TITS Is a Tictactoe Solver                                 *
 * author:	<bonassi.fabio.94[at]gmail[dot]com>                        *
 * license:	GNU GPL v3                                                 *
 * date:	12/12/2014                                                 *
 *                                                                     *
 * Enjoy :)                                                            *
 ***********************************************************************/

int main() {
	Position pos;
	Tree t;
	int i, k;
	int uwifl = 0; /* When the flag turns to 1 means that the user entered a wrong input */
	char path;
	Scheme matrix = { NONE }; /* Create an empty scheme */
	Status s;
	
	/* We randomly generate the first move of CPU and save it to the Scheme */
	pos = randomfirstmove();
	matrix[pos.x][pos.y] = CPU;
	
	/* Then, we read player's first move */
	do {
		if (uwifl) {
			printf("** Wrong choice. Please, enter it again (x,y): ");
			pos = getposfromstdin();
		} else {
			uwifl = 1;
			printscheme(matrix);
			printf("Please, make your play (x,y): ");
			pos = getposfromstdin();
		}
	} while(matrix[pos.x][pos.y] != NONE);
	
	/* Save player's choice and reset the flag */
	matrix[pos.x][pos.y] = PLY;
	uwifl = 0;
	
	/* Create the first node of the tree containing the actual scheme */
	t = calloc(1, sizeof(Node));
	mtxcpy(t->matrix, matrix);
	t->turn = PLY;
	/* And generate the rest of the tree */
	t = treegen(t);
	
	/* Now, we must generate stats */	
	for(i = 0; i < _CHILDREN_NMAX; i++) {
		statcalc(&(t->children[i]));
	}

	while(1) {
		/* Get the actual status of the match */
		s = getstatus(t->matrix);

		if(s == WIP) {
			/* If it's a WIP either the player or the CPU must make its/his choice. */
			if(t->turn == PLY) {
				/* Player made the last move. Now it's CPU's turn! */
				path = aiselect(t);
				t = pathsel(t, path);
			} else {
				/* Player's turn! */
				do {
					if (uwifl) {
						printf("** Wrong choice. Please, enter it again (x,y): ");
						pos = getposfromstdin();
					} else {
						uwifl = 1;
						printscheme(matrix);
						printf("Please, make your play (x,y): ");
						pos = getposfromstdin();
					}
				} while(t->matrix[pos.x][pos.y] != NONE);
				uwifl = 0;
				k = plyselect(t, pos.x, pos.y);
				t = pathsel(t, k);
			}
			
		} else if (s == DRAW) {
			printf("##########\n\n\n\n");
			printscheme(t->matrix);
			printf("Draw!\n");
			exit(0);
		} else if (s == PLY_WON) {
			printf("##########\n\n\n\n");
			printscheme(t->matrix);
			printf("You won :(\n");
			exit(0);
		} else {
			printf("##########\n\n\n\n");
			printscheme(t->matrix);
			printf("I won :)\n");
			exit(0);
		}
	}
}
