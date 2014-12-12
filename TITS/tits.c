#ifndef _INCLUDES
#define _INCLUDES
#include "tits.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#endif

/**
 * Get the status of the current matrix.
 * 
 * PARAMETERS:
 * 		(Scheme) matrix		the scheme
 * 		
 * RETURNS:	
 * 		CPU_WON		if the CPU won the match
 * 		PLY_WON		if the PLAYER won the match
 * 		DRAW		if neither the CPU nor the PLY won the match
 * 		WIP			if the match is a Work In Progress 
 */
Status getstatus(Scheme matrix) {
	int i;
	
	/* Check if someone won on the vertical and orizontal lines */
	for(i = 0; i < 3; i++) {
		if (matrix[i][0] == matrix[i][1] && matrix[i][0] == matrix[i][2] && matrix[i][0]) {
			return (matrix[i][0] == CPU ? CPU_WON : PLY_WON);
		}
		if (matrix[0][i] == matrix[1][i] && matrix[0][i] == matrix[2][i] && matrix[0][i]) {
			return (matrix[0][i] == CPU ? CPU_WON : PLY_WON);
		}
	}
	
	/* Check if someone won on the main diagonal */
	if (matrix[0][0] == matrix[1][1] && matrix[0][0] == matrix[2][2] && matrix[0][0]) {
		return (matrix[0][0] == CPU ? CPU_WON : PLY_WON);
	}
	/* Check if someone won on the secondary diagonal */
	if (matrix[2][0] == matrix[1][1] && matrix[2][0] == matrix[0][2] && matrix[2][0]) {
		return (matrix[2][0] == CPU ? CPU_WON : PLY_WON);
	}
	
    return (ismatrixfull(matrix) ? DRAW : WIP);
}


/**
 * Check wheter the matrix is full or not
 * 
 * PARAMETERS:
 * 		(Scheme) matrix		the scheme
 * RETURNS:
 * 		1	if the matrix is full
 * 		0	if the matrix isn't full
 */
char ismatrixfull(Scheme matrix) {
	int i, j;
	
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			if(matrix[i][j] == 0) {
				return 0;
			}
		}
	}
	return 1;
}


/**
 * Check wheter the node is a leaf or not
 * 
 * PARAMETERS:
 * 		(Node *) node		the node
 * RETURNS:
 * 		1	if the node is a leaf
 * 		0	if the node isn't a leaf
 */
char isleaf(Node *node) {
	int i;
	
	if(node == NULL) return 0;
	for(i = 0; i < _CHILDREN_NMAX; i++) {
		if(node->children[i].next != NULL) {
			return 0;
		}
	}
	
	return 1;
}


/**
 * Add a children to the tree
 * 
 * PARAMETERS:
 * 		(Tree) father		a pointer to the father
 * 		(Scheme) mtx		the generated scheme to save in the child
 * RETURNS:
 * 		(Tree)		A pointer to the tree
 */
Tree addchild(Tree father, Scheme mtx){
    Tree newbie = calloc (1, sizeof(Node));
    int i, j;
    
    /* Look for the first free pointer */
    for(i = 0; i < _CHILDREN_NMAX && father->children[i].next != NULL ; i++);
    father->children[i].next = newbie;
    
    /* Copy generated scheme into the child memory */
    mtxcpy(newbie->matrix, mtx);
    
    /* Init stats with the default value (-1) */
    for(i = 0; i < _CHILDREN_NMAX; i++) {
    	newbie->children[i].winstat = -1.0;
    	newbie->children[i].losestat = -1.0;
    }
    
    newbie->turn = (father->turn == CPU) ? PLY : CPU;
    return newbie;
}

/**
 * Free tree's memory and delete it
 * 
 * PARAMETERS:
 * 		(Tree ) t	the tree
 * RETURNS:
 * 		nothing
 */ 
void treedel(Tree t){
    Tree ch;
    int i;
    
    if(t == NULL)
        return;
    if(isleaf(t)) {
		/* If we are in a leaf, just free it and return to the previous call */
    	free(t);
    	return;
    }
    for(i = 0; i<_CHILDREN_NMAX; i++) {
		/* Store a pointer to the i-th children in ch, set its previous pointer to NULL and recursively free it */
        ch = t->children[i].next;
        t->children[i].next = NULL;
        treedel(ch);
    }
    free(t);
    return;
}


/**
 * Enter a specific "path" of the tree, which represent a turn.
 * 
 * PARAMATERS:
 * 		(Tree) t				the tree
 * 		(unsigned char)	path	the path to enter
 * RETURNS:
 * 		(Tree)		the new tree
 */
Tree pathsel(Tree t, unsigned char path) {
	int i;
	Tree newpath;
	
	if(path >= _CHILDREN_NMAX || t == NULL || t->children[path].next == NULL) {
		/* This is a no-sense situation. We just don't do anything */
		return;
	}
	
	/* We select the new tree.. */
	newpath = t->children[path].next;
	for(i = 0; i < _CHILDREN_NMAX; i++) {
		if(i != path) {
			/* .. then, we free and delete the unused part of the tree .. */
			treedel(t->children[i].next);
		}
	}
	/* .. and the old parent. */
	free(t);
	return newpath;
}


/**
 * Check whether the match ended or not
 * 
 * PARAMETERS:
 * 		(Tree) t	the tree
 * RETURNS:
 * 		1	if the match ended
 * 		0	if the match hasn't ended yet
 */
char matchend(Tree t) {
        Status s = getstatus(t->matrix);
        return (s == CPU_WON || s == PLY_WON || s == DRAW);
}


/**
 * Calculate win and lose statistics of every node.
 * 
 * PARAMETERS:
 * 		(ChildStat *) stat		a pointer to the stats of a node. We need a pointer in order to update the values.
 * RETURNS:
 * 		nothing
 */
void statcalc(ChildStat *stat) {
	Status s;
	ChildStat *nextchild;
	int i, n = 0;
	float winsum = 0.0, losesum = 0.0;
	
	if(stat == NULL || stat->next == NULL) {
		return;
	}
	/* If the stats are referred to a leaf, then we generate the stats accordingly to the result */
	if(isleaf(stat->next)) {
		s = getstatus(((Tree)(stat->next))->matrix);
		switch(s) {
			case CPU_WON:
				stat->winstat = 1.0;
				stat->losestat = 0.0;
				break;
			case PLY_WON:
				stat->winstat = 0.0;
				stat->losestat = 1.0;
				break;
			case DRAW:
				stat->winstat = 0.0;
				stat->losestat = 0.0;
				break;
			default:
				stat->winstat = -1.0;
				stat->losestat = -1.0;
				break;
		}
		return;
	}
	
	/* else, we generate the stats for each child of the current node, */
	for(i = 0; i < _CHILDREN_NMAX; i++) {
		nextchild = &(((Tree)stat->next)->children[i]);
		statcalc(nextchild);
		
		/* .. we calculate the sum of each not-null child .. */
		if(nextchild->next != NULL && (nextchild->winstat != -1.0 && nextchild->losestat != -1.0)) {
			++n;
			winsum += nextchild->winstat;
			losesum += nextchild->losestat;
		}
	}
	
	if( n > 0) {
		/* and then we calculate the average. */
		stat->winstat = winsum / n;
		stat->losestat = losesum / n;
	} else {
		stat->winstat = -1.0;
		stat->losestat = -1.0;
	}
	
	return;
}


/**
 * Generate the tree containing each possible situation
 * 
 * PARAMETERS:
 * 		(Tree) node		the father of the future children
 * RETURNS:
 * 		(Tree)		the tree containg the new children
 */
Tree treegen(Tree node) {
	Scheme newmtx;
	Tree newbie;
	int i, j;
	int id;
	
	/* If the matrix is already full, or the father node represent an ended match, just return. */
	if(ismatrixfull(node->matrix) || matchend(node)) {
		return NULL;
	}
	
	/* Else, we copy the father scheme in a support matrix.. */
	mtxcpy(newmtx, node->matrix);
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			if(newmtx[i][j] == NONE) {
				/* .. in empty spaces, we put the current turn */
				newmtx[i][j] = node->turn == CPU ? PLY : CPU;
				/* .. and we recursively add new children to the newbie. */
				newbie = addchild(node, newmtx);
				newbie = treegen(newbie);
				/* Finally, we set the set that space empty again, and pass to a new one. */
				newmtx[i][j] = NONE;
			}
		}
	}
	return node;
}


/**
 * Artificial Intelligence selects the next movement
 * 
 * PARAMETERS:
 * 		(Tree) t	the current tree
 * RETURNS:
 * 		(char)		the best path to be followed
 */
char aiselect(Tree t) {
	float max = -1.0;	/* this is the maximum cval found */
	float cval;			/* this represent a weighted value for a pat */
	char path = 0;		/* this is the path for the maximum cval */
	char i;
	
	if(t == NULL || isleaf(t)) return -1;
	
	for(i = 0; i < _CHILDREN_NMAX; i++) {
		if(t->children[i].winstat > -1.0 && t->children[i].losestat > -1.0) {
			cval = (WIN_WEIGHT * t->children[i].winstat) + (LOSE_WEIGHT *  ( 1 - t->children[i].losestat));
			if(cval >= max) {
				max = cval;
				path = i;
			}
		}
	}
	return path;
}


/**
 * Get the path to follow to match user's movement
 * 
 * PARAMETERS:
 * 		(Tree) t	the current tree
 * 		(char) x	the x coordinate of user's choice
 * 		(char) y	the y coordinate of user's choice
 * RETURNS:
 * 		(char)		the path
 */
char plyselect(Tree t, char x, char y) {
	Tree tr;
	char i;
	
	if(t == NULL) {
		return -1;
	}
	
	for (i = 0; i < _CHILDREN_NMAX; i++) {
		/* We just find the path to reach the Scheme which realizes user's choice. */
		tr = (Tree)t->children[i].next;
		if(tr != NULL && tr->matrix[x][y] == PLY) {
			return i;
		}
	}
	
	return -1;
}


/**
 * Randomly generate the first movement for the CPU
 * 
 * PARAMETERS:
 * 		none
 * RETURNS:
 * 		(Position)	the position
 */
Position randomfirstmove() {
	Position pos;
	srand(time(NULL));
	pos.x = rand() % 3;
	pos.y = rand() % 3;
	return pos;
}


/**
 * Read the position of the movement from 'stdin'
 * 
 * PARAMETERS:
 * 		none
 * RETURNS:
 * 		(Position)	the position
 */
Position getposfromstdin() {
	Position pos;
	int x, y;
	
	do {
		fflush(stdin);
		scanf("%d,%d", &x, &y);
                fflush(stdin);
	} while((x < 0 || x > 2) || (y < 0 || y > 2));
	
	pos.x = (char) x;
	pos.y = (char) y;
	return pos;
}


/**
 * Copy a matrix into another
 * 
 * PARAMETERS:
 * 	(Scheme) dest		the destination
 *  (Scheme) origin		the origin
 * RETURNS:
 * 		nothing
 */
void mtxcpy (Scheme dest, Scheme origin) {
	int i, j;
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			dest[i][j] = origin[i][j];
		}
	}
}


/**
 * Get the symbol from the ID
 * 
 * PARAMETERS:
 * 		(ID) id		the ID
 * RETURNS;
 * 		(char)		the symbol
 */
char placeholderfromid(ID id) {
	switch(id) {
		case CPU:
			return 'O';
		case PLY:
			return 'X';
		default:
			return ' ';
    }
}


/**
 * Print the scheme on 'stdout'
 * 
 * PARAMETERS:
 * 		(Scheme) matrix		the scheme to be printed
 * RETURNS:
 * 		nothing
 */
void printscheme(Scheme matrix) {
	printf(" %c | %c | %c \n", placeholderfromid(matrix[0][0]), placeholderfromid(matrix[0][1]), placeholderfromid(matrix[0][2]));
	printf("____________\n");
	printf(" %c | %c | %c \n", placeholderfromid(matrix[1][0]), placeholderfromid(matrix[1][1]), placeholderfromid(matrix[1][2]));
	printf("____________\n");
	printf(" %c | %c | %c \n", placeholderfromid(matrix[2][0]), placeholderfromid(matrix[2][1]), placeholderfromid(matrix[2][2]));
	printf("\n");
}
