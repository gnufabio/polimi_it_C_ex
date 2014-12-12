/***********************************************************************
 * Costants and macros definition                                      *
 ***********************************************************************/
 /* The maximum number of children of a node */
#define _CHILDREN_NMAX 7

/* The weight of win and lose in the calculation of the value of each path */
#define LOSE_WEIGHT 2.0	
#define WIN_WEIGHT 1.25





/***********************************************************************
 * Data types definition                                               *
 ***********************************************************************/
 /* ID of CPU or Player */
typedef enum {
	NONE,
	CPU,
	PLY
} ID;

/* Status of the match */
typedef enum {
	CPU_WON,
	PLY_WON,
	DRAW,
	WIP
} Status;

/* A generic position in the matrix */
typedef struct {
	char x;
	char y;
} Position;

/* Scheme is a 3x3 matrix */
typedef ID Scheme[3][3];

/* Statistics referred to the 'next' children */
typedef struct {
	float winstat;
	float losestat;
	void *next;
} ChildStat;

/* Every node of the tree is defined with a Scheme, a turn and some children. */
typedef struct _Node {
	Scheme matrix;
	ID turn;
	ChildStat children[_CHILDREN_NMAX];
} Node;

/* A tree is defined as a pointer to a Node struct. */
typedef Node * Tree;





/***********************************************************************
 * Function prototipes                                                 *
 ***********************************************************************/

/* Get the status of the current matrix. */
Status getstatus(Scheme);

/* Check wheter the matrix is full or not */
char ismatrixfull(Scheme);

/* Check wheter the node is a leaf or not */
char isleaf(Node *);

/* Add a children to the tree */
Tree addchild(Tree, Scheme);

/* Free tree's memory and delete it */
void treedel(Tree);

/* Enter a specific "path" of the tree, which represent a turn. */
Tree pathsel(Tree, unsigned char);

/* Check whether the match ended or not */
char matchend(Tree);

/* Calculate win and lose statistics of every node. */
void statcalc(ChildStat *);

/* Generate the tree containing each possible situation */
Tree treegen(Tree);

/* Artificial Intelligence selects the next movement */
char aiselect(Tree);

/* Get the path to follow to match user's movement */
char plyselect(Tree, char, char);

/* Randomly generate the first movement for the CPU */
Position randomfirstmove();

/* Read the position of the movement from 'stdin' */
Position getposfromstdin();

/* Copy a matrix into another */
void mtxcpy(Scheme, Scheme);

/* Get the symbol from the ID */
char placeholderfromid(ID);

/* Print the scheme on 'stdout' */
void printscheme(Scheme);
