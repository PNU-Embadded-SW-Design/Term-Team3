#ifndef TERM
#define TERM
/*CAT_STATE
int CAR_STATE = 0;

0 : STOP;
1 : GO FOWARD;
2 : GO LEFT;
3 : GO RIGHT;
#define STOP 0
#define GO_FORWARD 1
#define GO_LEFT 2
#define GO_RIGHT 3
*/ 

#define _DEBUG

enum CAR_STATE {STOP, GO}; 
enum CAR_DIR {FORWARD, LEFT, RIGHT}; 

static enum CAR_STATE gCarState = STOP; 
static enum CAR_DIR gCarDir = FORWARD; 

#endif