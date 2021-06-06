#ifndef TERM
#define TERM
//CAT_STATE
static int CAR_STATE = 1;
/*
0 : STOP;
1 : GO FOWARD;
2 : GO LEFT;
3 : GO RIGHT;
*/
#define STOP 0
#define GO_FORWARD 1
#define GO_LEFT 2
#define GO_RIGHT 3

static int DELIVER_STATE = 0;
#define DELIVERABLE 0
#define DELIVERING 1
#define WAITING 2 //Waiting to remove somthing on the robot



#endif