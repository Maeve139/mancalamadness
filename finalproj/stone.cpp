#include <graphics.h>
#include <ctime>
#include <cstdlib>

using namespace std;
class Stone {
    
    //field variables. 
    //xpos is the x-coordinate of the stone's center.
    //ypos is the y-coordinate of the stone's center.
    
    public:
    int xpos, ypos;
    
    void changepos(int newx, int newy){
	xpos = newx;
	ypos = newy;
    }
    
    void draw(){	
	setcolor(WHITE);
	srand(time(0));
	int r = (rand() % 15);
	setfillstyle(SOLID_FILL, r);
	circle(xpos, ypos, 10);	
    }
}
