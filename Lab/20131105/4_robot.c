#include <stdio.h>
#include <stdlib.h>

#define ROB_NORTH 'A'
#define ROB_SOUTH 'V'
#define ROB_EAST '>'
#define ROB_WEST '<'
#define SPACE ' '
#define WALL '0'

#define MOVE_FWD 1
#define MOVE_BWD -1

#define ENV 6
#define SUCCESS 1
#define FAIL 0

#define EXIT_S 'q'
#define RL_S '*'
#define RR_S '/'
#define MF_S '+'
#define MB_S '-'

char world[ENV][ENV] = {
	{ ROB_EAST, SPACE, SPACE, SPACE, SPACE, SPACE },
	{ WALL, WALL, WALL, SPACE, SPACE, SPACE },
	{ SPACE, SPACE, SPACE, SPACE, SPACE, SPACE },
	{ SPACE, SPACE, SPACE, WALL, WALL, WALL },
	{ SPACE, SPACE, SPACE, SPACE, SPACE, SPACE },
	{ SPACE, SPACE, SPACE, SPACE, SPACE, SPACE }
};

typedef struct { int x; int y; } position;
typedef enum { NORTH, SOUTH, EAST, WEST } orientation;
typedef struct { int mov; orientation or; } eq_mov;

struct s_rob {
	position pos;
	orientation or;
	char symbol;
} robot;

/* Function prototypes */
void init_robot(void);
int move_robot(int);
int rotate(orientation);
int rotate_90_right(void);
int rotate_90_left(void);
void rewrite_position(position);
int is_valid_movement(int);
eq_mov equivalent_movement(int);
void print_world(void);


int main(void) {
	char c;
	
	init_robot();
	fflush(stdin);
	
	printf("Usage: %c to exit, %c to move forward, %c to move backward, %c to rotate to left, %c to rotate to right!\n\n", EXIT_S, MF_S, MB_S, RL_S, RR_S);

    print_world();
	scanf("%c", &c);
	
	while(c != EXIT_S) {
		switch(c) {
			case MF_S:
				move_robot(MOVE_FWD);
				print_world();
				break;
			case MB_S:
				move_robot(MOVE_BWD);
				print_world();
				break;
			case RL_S:
				rotate_90_left();
				print_world();
				break;
			case RR_S:
				rotate_90_right();
				print_world();
				break;
		}
		scanf("%c", &c);
	}
	
	return 0;
} 
 
void init_robot(void) {
	robot.pos.x = 0;
	robot.pos.y = 0;
	robot.or = EAST;
	robot.symbol = ROB_EAST;
}

void print_world(void) {
	/* i=columns j=rows */
	int i, j;
	
	printf("\n");
	for(j = 0; j < ENV; j++) {
		for(i = 0; i < ENV; i++) {
			printf("%c ", world[j][i]);
		}
		printf("\n");
	}
	printf("\n");
}

int move_robot(int movement) {
	int result = FAIL;
	position newpos = robot.pos;
	
	if(!is_valid_movement(movement)) {
		return FAIL;
	}
	
	switch(robot.or) {
		case NORTH:
			newpos.y = robot.pos.y - movement;
			newpos.x = robot.pos.x;
			break;
		case SOUTH:
			newpos.y = robot.pos.y + movement;
			newpos.x = robot.pos.x;
			break;
		case EAST:
			newpos.y = robot.pos.y;
			newpos.x = robot.pos.x + movement;
			break;
		case WEST:
			newpos.y = robot.pos.y;
			newpos.x = robot.pos.x - movement;
			break;
	}
	
	rewrite_position(newpos);
	return SUCCESS;
 }
 
 int rotate(orientation new_or) {
 	char robot_or = world[robot.pos.y][robot.pos.x];
 	robot.or = new_or;
	
	switch(new_or) {
		case NORTH:
			robot_or = ROB_NORTH;
			break;
		case SOUTH:
			robot_or = ROB_SOUTH;
			break;
		case EAST:
			robot_or = ROB_EAST;
			break;
		case WEST:
			robot_or = ROB_WEST;
			break;
	}
	
	world[robot.pos.y][robot.pos.x] = robot_or;
	robot.symbol = robot_or;
	return SUCCESS;
 }
 
int rotate_90_right(void) {
	orientation new_or;
 	switch(robot.or){
 		case NORTH:
 			new_or = EAST;
 			break;
 		case SOUTH:
 			new_or = WEST;
 			break;
 		case EAST:
 			new_or = SOUTH;
 			break;
 		case WEST:
 			new_or = NORTH;
 			break;
 	}
 	return rotate(new_or);
 }
 
int rotate_90_left(void) {
	orientation new_or;
 	switch(robot.or){
 		case NORTH:
 			new_or = WEST;
 			break;
 		case SOUTH:
 			new_or = EAST;
 			break;
 		case EAST:
 			new_or = NORTH;
 			break;
 		case WEST:
 			new_or = SOUTH;
 			break;
 	}
 	return rotate(new_or);
 }
 
 void rewrite_position(position newp) {
 	world[robot.pos.y][robot.pos.x] = SPACE;
 	world[newp.y][newp.x] = robot.symbol;
 	robot.pos = newp;
 }
 
 int is_valid_movement(int mov) {
 	int valid = SUCCESS;
 	orientation eor = equivalent_movement(mov).or;
 	
 	switch(eor) {
 		case NORTH:
 			if((robot.pos.y  == 0) || world[robot.pos.y - 1][robot.pos.x] == WALL) {
 				valid = FAIL;
 			}
			break;	
 		case SOUTH:
 			if((robot.pos.y  == ENV - 1) || world[robot.pos.y + 1][robot.pos.x] == WALL) {
 				valid = FAIL;
 			}
 			break;
 		case EAST:
 			if((robot.pos.x  == ENV - 1) || world[robot.pos.y][robot.pos.x + 1] == WALL) {
 				valid = FAIL;
 			}
 			break;
 		case WEST:
 			if((robot.pos.x  == 0) || world[robot.pos.y][robot.pos.x - 1] == WALL) {
 				valid = FAIL;
 			}
 			break;
 	}
 	
 	return valid;
 }
 
eq_mov equivalent_movement(int mov) {
 	eq_mov eor;
     eor.or = robot.or;
     eor.mov = mov;
 	
 	if(mov == MOVE_BWD) {
 		eor.mov = MOVE_FWD;
 		if(eor.or % 2 == 0) {
 		    eor.or++;
 		} else {
 			eor.or--;
 		}
 	}
 	
 	return eor;
 }
