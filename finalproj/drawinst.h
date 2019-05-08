#include <graphics.h>
#include <cstdlib>
#include <string>
using namespace std;

void drawinstance(int stones[14], std::sting turnstate, std::string message){

//Declaring scores as their own variables for convenience
int computerscore = stones[13];
int playerscore = stones [6];

//Graphics time!
initgraph(9, 2, "");

//draw first row of circles
circle(160, 64, 27);
circle(244, 64, 27);
circle(288, 64, 27);
circle(352, 64, 27);
circle(416, 64, 27);
circle(480, 64, 27);

//draw second row of circles
circle(160, 128, 27);
circle(224, 128, 27);
circle(288, 128, 27);
circle(352, 128, 27);
circle(416, 128, 27);
circle(480, 128, 27);

//draw computer scoring rectangle
rectangle(32, 32, 128, 160);

//draw player scoring rectangle
rectangle(512, 32, 608, 160);

//draw stones
//In bottom row of circles, numbers 0-5)
for (int i = 0; i < 6; i++){
    int pocketx = 160 + 64i;
    for (int j = 0; j < stones[i]; j++){
	double angle = 137.5 * j;
	double offset = (3 * j) % 20;
	int stonex = pocketx + (int)(sin(angle) * offset);
	int stoney = 128 + (int)(cos(angle) * offset);
	circle(stonex, stoney, 5);	
    }
}

//In top row of circles, numbers 7-12
for (int j = 7; j < 13; j++){
    int pocketx = 480 - (64 * (k - 7));
    for (int k = 0; k < stones[i]; k++){
	double angle = 137.5 * k;
	double offset = (3 * k) % 20;
	int stonex = pocketx + (int)(sin( angle) * offset);
	int stoney = 128 + (int) (cos(angle) * offset);
	circle(stonex, stoney, 5);	
    }
}

//In computer store, number 13
for (int l = 0; l < stones[13]; l++){
    int stonex = (10 * (l % 9)) + 40;
    int stoney = (10 * (l / 9)) + 41;
    circle(stonex, stoney, 5); 
}

//In player store, number 6
for (int m = 0; m < stones[6]; m++){
    int stonex = (10 * (m % 9)) + 512;
    int stoney = (10 * (m / 9)) + 41;
    circle (stonex, stoney, 5);
}
//String construction for computer and player scores, turn state, and instructions
//The placeholder values are called "computerscore" and "playerscore".
//Their string versions are called "compscore" and "playscore", so if either of these names
//are already used, please replace my variable names where they occur.

std::string compscore;
std::stringstream ss;
ss<<computerscore;
compscore == ss.str();
std::string compscorestate = "COMPUTER SCORE: " + compscore;

std::string playscore;
ss<<playscore;
playscore == ss.str();
std::string playscorestate = "PLAYER SCORE: " + playscore;

std::string = turnstate + "'S TURN";

std::string instructions = "Mancala is a two-player game in which the goal is to capture more stones than your opponent. To move stones, select one pocket on your side of the board. The stones from the pocket will be distributed sequentially counterclockwise, starting at the pocket after your selection. \n To score, deposit stones in your scoring pocket ot end your turn in an empty pocket across from your opponents' stones to capture them.";

//Printing and formatting instructions for computer and player scores, turn state, and instructions
settextstyle(0, 0, 2);
outtextxy(32, 192, compscorestate);
outtextxy(178, 192, turnstate);
outtextxy(326, 192, playscorestate);

settextstyle(0, 0, 0);
outtextxy(32, 224, instructions);

//Printing the message
outtextxy(32, 240, message);
}
