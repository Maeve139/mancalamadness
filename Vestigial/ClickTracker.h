/*
 * ClickTracker.h
 *
 *  Created on: May 4, 2019
 *      Author: Samma
 */
#include <stdio.h>
#include <graphics.h>
#include <winuser.h>

#ifndef CLICKTRACKER_H_
#define CLICKTRACKER_H_

using namespace std;

class ClickTracker {
public:
	ClickTracker();
	virtual ~ClickTracker();

	int getClick(){
		int x, y;
		x=0;
		y=0;
		if ((GetKeyState(VK_LBUTTON) & 0x80) != 0){
			GetCursorPos(&p);
			//gotta find how to do this with graphics, but I'm sure we'll figure it out.
			ScreenToClient(hwnd,&p);
			x=p.x;
			y=p.y;
		}

		if ((GetKeyState(114) & 0x80) != 0){
			return 7;
			//This is restart
		}

		if ((GetKeyState(113) & 0x80) != 0){
			return 8;
			//This is quit
			}

		if(x>159 && x<215 && y>127 && y<182){
			return 0;
		}
		if(x>223 && x<279 && y>127 && y<182){
			return 1;
		}
		if(x>287 && x<343 && y>127 && y<182){
			return 2;
		}
		if(x>351 && x<405 && y>127 && y<182){
			return 3;
		}
		if(x>415 && x<470 && y>127 && y<182){
			return 4;
		}
		if(x>479 && x<534 && y>127 && y<182){
			return 5;
		}
		else{
			//If no accurate hole is selected, then we will return -1.
			return -1;
		}
	}

};



#endif /* CLICKTRACKER_H_ */
