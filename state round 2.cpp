/*
 * state.cpp
 *	This is the state controller for Mancala
 *  Created on: Apr 21, 2019
 *      Author: Scott
 */


#include <iostream>
#include <array>
#include <stdio.h>
//#include <graphics.h>
//#include <winuser.h>
#include <algorithm>
#include <cstdlib>
#include <string>
//#include <drawinst.h>

using namespace std;


/*
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

*/

class AIPlayer
{
  int kalah;
public:
  std::array<int,14> board;
  std::vector<int> moves;




 /* AIPlayer(std::array<int,14> boardstate){
    //sets up board,  tells AI it's north
    kalah = 13;
    board = boardstate;
  }
*/



  void MOVE(std::array<int,14> &field, int move){
  //got tired of doing moves manually
  int counter = field[move];
  for(int drops = 0; drops <= counter; drops++){
    if(move+drops == kalah - 7){
      //this just skips the opponents kalah
      move++;
    }
    field[move+drops]++;
  }
}


void update(std::array<int,14> boardstate){
	board = boardstate;
	kalah = 13;
}

void legalmovefinder() {
  //finds legal moves
  for(int test = kalah - 6; test < kalah; test++) {
    if(board[test] > 0){
      moves.push_back(test);
    }
  }
}




  std::vector<int> legalmovefinder(std::array<int,14> hypo){
    //override for use with prediction/future moves
    std::vector<int> nextMoves;
    for(int test = kalah - 6; test < kalah; test++) {
    if(board[test] > 0){
      nextMoves.push_back(test);
    }
  }
  }





int assess(int move){
  //assesses board position, returns an int reresenting move value
  int value = 0;
  std::vector<int> nextMoves;
  std::array<int,14> testBoard = board;
  int resulthole = (board[move]+move)%14;
  if(move+board[move] > 13 || resulthole <= move){
    resulthole++;
    value++;
  }
  //still need to handle case where stones go around multiple times
  if(resulthole = kalah) {
    //assesses subsequent moves if lands in kalah
    value++;
    MOVE(testBoard, move);
    nextMoves = legalmovefinder(testBoard);
    for(int testMove = 0; testMove < nextMoves.size(); testMove++){
      nextMoves.emplace(nextMoves.begin(), assess(nextMoves.back(), testBoard));
      nextMoves.pop_back();
    }
    value += *max_element(nextMoves.begin(), nextMoves.end());
  }
  else if ((board[resulthole] == 0 && resulthole >= kalah - 7) && board[kalah-resulthole] != 0){
    //assesses captures, currently just in terms of total value
    value += 1 + board[kalah - resulthole];
    //MOVE(testBoard, move) if looking ahead makes  sense will be included
  }
  else {
    //was a thing that cleared board if would win, but now not necessary
    //here for position weighting, depending on how this runs
  }
  return value;
}



 int assess(int move, std::array<int,14> newboard ){
  //assesses board position for any given board
   //meant to be used to predict next moves
  int value = 0;
  std::vector<int> nextMoves;
  std::array<int,14> testBoard = newboard;
  int resulthole = (board[move]+move)%14;
  if(move+newboard[move] > 13 || resulthole <= move){
    resulthole++;
    value++;
  }
  //still need to handle case where stones go around multiple times
  if(resulthole = kalah) {
    //assesses subsequent moves if lands in kalah
    value++;
    MOVE(testBoard, move);
    nextMoves = legalmovefinder(testBoard);
    for(int testMove = 0; testMove < nextMoves.size(); testMove++){
      nextMoves.emplace(nextMoves.begin(), assess(nextMoves.back(), testBoard));
      nextMoves.pop_back();
    }
    value += *max_element(nextMoves.begin(), nextMoves.end());
  }
  else if ((newboard[resulthole] == 0 && resulthole >= kalah - 7) && newboard[kalah-resulthole] != 0){
    //assesses captures, currently just in terms of total value
    value += 1 + newboard[kalah - resulthole];
    //move(testBoard, move) if looking ahead makes  sense will be included
  }
  else {
    //was a thing that cleared board if would win, but now not necessary
    //here for position weighting, depending on how this runs
  }
  return value;
}






int mover(){
  //drives the other methods, what you want to call to find a move
  std::vector<int>usefulholes;
  //last variable is a relic of older version, may be removed in future
  int score = board[13];
  int playerscore = board[6];
  legalmovefinder();
  usefulholes = moves;
  for(int consider = 0; consider < usefulholes.size(); consider++) {
    //checks each possible move
    usefulholes.emplace(usefulholes.begin(), assess(usefulholes.back()));
    usefulholes.pop_back();
  }
  //this returns the int representing the chosen hole
  return *std::max_element(usefulholes.begin(), usefulholes.end());
}
};





int main(){


	restart:
	cout<<"new game"<<endl;
	std::array<int,14> A={ 0 }; //creates array
	  int player_turn=0;
	  int ai_turn=0;
	  bool blank=false;
	  //int A[14]={ 0 }; //creates array

	  for (int m=0; m<13; m++){//initializes board
		  if (m!=6){
			  A[m]=4; //fills each vec with four ints of 1
	            //leaving the scoring trays empty
	        }
	    }
	    for (int j=0; j<14; j++){
	  	  	  cout<<A[j]<< ",  ";
  	  	  }
	    cout<<endl;
	   AIPlayer artificial;
	    while (A[6]<24&&A[13]<24){
	    //checks that the score trays dont have over 24 stones captured(win condition)
	    	cout<<"Pick a bucket to move stones from!"<<endl;
	    	//drawinst(A,"Player","Pick a bucket to move stones from!"); //returns board graphic
	        //int play=getClick(); //calls player move
	        char play;
	    	cin>>play;

//cin doesnt work rn
	        cout<<"Player picks:"<<play<<endl;
	        player_turn++;
	       // play=0;

	        if (play=='R'){ //restarts
	        	cout<<"Restarts game"<<endl;
	        		goto restart;
	        }

	        if (play=='Q'){ //quits game
	        	cout<<"Quits game"<<endl;
	        	return 0;
	        }


	        if (play<-1&&play>13){
	        	cout<<"Give a digit between 0-5 to pick the corresponding bucket"<<endl;
	        		            if (player_turn>0){
	        		            		player_turn--;
	        		            }
	        		            continue;
	        		        }


	        if (play>5){
	       	            //error message
	        	cout<<"Please pick bucket on your side!"<<endl;
	       	        	//drawinst(A,"Player","Please click in a bucket on your side!");
	       	            //break;
	       	            if (player_turn>0){
	       	            		player_turn--;
	       	            }
	       	            continue;
	       	        }


	        if (A[play]==0){
	            //error message
	        	cout<<"There are no stones in that bucket, please try again!"<<endl;
	        	//drawinst(A,"Player","There are no stones in that bucket, please try again!");
	            //break;
	            if (player_turn>0){
	            		player_turn--;
	            }
	            continue;
	        }
	        else{

	            int counter=A[play];
	            A[play]=0;
	            for (int c=1; c<counter+1; c++){
	            	//drawinst(A,"Player",""); //returns board graphic
	            	if ((play+c)%14==13){
	            		//skips the ai score bucket
	            		counter++;
	            	}
	            	else{
	            		//adds a stone to the bucket
	            		//drawinst(A,"Player",""); //returns board graphic
	            		A[(play+c)%14]++;
	            	}
	     }
	            if ((play+counter)%14==6){

	            cout<<"player goes again"<<endl;
	            	//drawinst(A,"Player","Player gets another turn!"); //returns board graphic
	            	//last stone went in score tray so player gets another turn
	            	continue;
	            }
	            if ((((play+counter)%14)>-1)&&(((play+counter)%14)<6)){ //if turn ends in own side
	            	if (A[(play+counter)%14]==1&&A[(12-((play+counter)%14))]!=0){
	            	//if the bucket the last stone ends in is empty and is  across nonempty bucket
	            		//take the stones from both and add to score
	            		int add=1+A[(12-((play+counter)%14))];
	            		A[(12-(play+counter)%14)]=0;
	            		//drawinst(A,"Player",""); //returns board graphic
	            		A[(play+counter)%14]=0;
	            		//drawinst(A,"Player",""); //returns board graphic
	            		for (int k=0; k<add; k++){
	            			//drawinst(A,"Player",""); //returns board graphic
	            			A[6]++;;
	            		}


	            	}
	            }

			//prints out current board state for testing
	            for (int j=0; j<14; j++){
	         	    cout<<A[j]<< ",  ";
	         	  }
	            cout<<endl;

	    }
	     /* drawinst(A,"Player","No moves possible for player"); //returns board graphic
	        if ((A[0]==0&&A[1]==0&&A[2]==0&&A[3]==0&&A[4]==0&&A[5]==0)){
	        //if no stones on player side,  add ai stones to their score and exit
	        	int stone=A[7]+A[8]+A[9]+A[10]+A[11]+A[12];
	        	A[7]=0;
	        	A[8]=0;
	        	A[9]=0;
	        	A[10]=0;
	        	A[11]=0;
	        	A[12]=0;
	        	for (int l=0; l<stone; l++){
	        		//return board graphic from maeve
	        		A[13]++;
	        	}
	        	drawinst(A,"Player","No moves possible for player"); //returns board graphic
	        blank=true;
	        break; //leaves loop bc we have a win
	        }
*/
	        if ((A[7]==0&&A[8]==0&&A[9]==0&&A[10]==0&&A[11]==0&&A[12]==0)){
	        	        //if no stones on ai side, add player stones to their score and exit
	        	//drawinst(A,"AI","No moves possible for AI"); //returns board graphic

	        	        	int stone=A[0]+A[1]+A[2]+A[3]+A[4]+A[5];
	        	        	A[0]=0;
	        	        	A[1]=0;
	        	        	A[2]=0;
	        	        	A[3]=0;
	        	        	A[4]=0;
	        	        	A[5]=0;
	        	        	for (int l=0; l<stone; l++){
	        	        		//return board graphic from maeve
	        	        		A[13]++;
	        	        	}
	        	        	//drawinst(A,"AI","No moves possible for AI"); //returns board graphic
	        	        blank=true;
	        	        break; //leaves loop bc we have a win
	        	        }

	    	//drawinst(A,"AI","AI's turn"); //returns board graphic
	        ai_repeat:
			 cout<<"AI's turn"<<endl;
			 artificial.update(A);
	        int ai=artificial.mover(); //call ai move from ben to get this
	        cout<<"ai has picked "<<ai<<endl;
	        //this assumes ai will return an int from 7-12 that doesnt have 0  stones
	        ai_turn++;
	        ai=7;

	        int count=A[ai];
            A[ai]=0;
            for (int c=1; c<count+1; c++){
            	//drawinst(A,"AI",""); //returns board graphic

            	if  ((ai+c)%14!=6) {
            		//drawinst(A,"AI",""); //returns board graphic
            		//adds a stone to the bucket if its not the player score tray
            		A[(ai+c)%14]++;
            	}
            	else{
            		count++;
            	}
     }
           // drawinst(A,"AI",""); //returns board graphic
            if ((ai+count)%14==13){
            	//last stone went in score tray so ai gets another turn
            	//drawinst(A,"AI","AI gets another turn!"); //returns board graphic
            	goto ai_repeat;
            }
            if ((((ai+count)%14)>6)&&(((ai+count)%14)<13)){ //if turn ends in own side
            	if (A[(ai+count)%14]==1&&A[(12-((ai+count)%14))]!=0){
            		//and last stone is in an empty bucket across from a not empty bucket
            		//take the stones from both and add to score
            		int add=1+A[(12-((ai+count)%14))];
            		A[(12-(ai+count)%14)]=0;
            		//drawinst(A,"AI",""); //returns board graphic
            		A[(ai+count)%14]=0;
            		//drawinst(A,"AI",""); //returns board graphic
            		for (int k=0; k<add; k++){
            			//drawinst(A,"AI",""); //returns board graphic
            			A[13]++;
            		}
            	}
            }
            //drawinst(A,"AI",""); //returns board graphic
            //checks if one side of board is empty
            if ((A[0]==0&&A[1]==0&&A[2]==0&&A[3]==0&&A[4]==0&&A[5]==0)){
            	cout<<"no moves for player, ends game"<<endl;
            	//drawinst(A,"Player","No moves possible for player");
           	        //if no stones on player side,  add ai stones to their score and exit
           	        	int stone=A[7]+A[8]+A[9]+A[10]+A[11]+A[12];
           	        	A[7]=0;
           	        	A[8]=0;
           	        	A[9]=0;
           	        	A[10]=0;
           	        	A[11]=0;
           	        	A[12]=0;
           	        	for (int l=0; l<stone; l++){
           	        		//return board graphic from maeve
           	        		A[13]++;
           	        	}
           	      //  	drawinst(A,"Player","No moves possible for player");
           	        blank=true;
           	        break; //leaves loop bc we have a win
           	        }
         /*   		//checks if other side of board is empty
            if ((A[7]==0&&A[8]==0&&A[9]==0&&A[10]==0&&A[11]==0&&A[12]==0)){
            	//if no stones on ai side, add player stones to their score and exit
           	    int stone=A[0]+A[1]+A[2]+A[3]+A[4]+A[5];
           	    A[0]=0;
           	    A[1]=0;
           	    A[2]=0;
           	    A[3]=0;
           	    A[4]=0;
           	    A[5]=0;
           	    for (int l=0; l<stone; l++){
           	    	//return board graphic from maeve
           	    	A[13]++;
           	   }
           	   blank=true;
           	   break; //leaves loop bc we have a win
           	   }
*/

            //prints out current board state for testing
            for (int j=0; j<14; j++){
         	    cout<<A[j]<< ",  ";
         	  }
            cout<<endl;





	    } //end of turns while loop
//Now we are at a win state
if  (blank==false){
	//drawinst(A,"","Win condition achieved: One player has over half of the stones!");
	//moves stones left in each side to their scoring trays
	int stone=A[0]+A[1]+A[2]+A[3]+A[4]+A[5];
	A[0]=0;
	A[1]=0;
	A[2]=0;
	A[3]=0;
	A[4]=0;
	A[5]=0;
	for (int l=0; l<stone; l++){
		A[6]++;
	}
	//drawinst(A,"","Win condition achieved: One player has over half of the stones!");
	stone=0;
	stone=A[7]+A[8]+A[9]+A[10]+A[11]+A[12];
		A[7]=0;
		A[8]=0;
		A[9]=0;
		A[10]=0;
		A[11]=0;
		A[12]=0;;
		for (int l=0; l<stone; l++){
			A[13]++;
		}
		//drawinst(A,"","Win condition achieved: One player has over half of the stones!");
}
cout<<"Player: "<<A[6]<<endl;
cout<<"AI: "<<A[13]<<endl;
if (A[6]>A[13]){

	cout<<"player wins"<<endl;
	//drawinst(A,"","Player has won!");
}

if (A[6]==A[13]){

cout<<"tied game"<<endl;
	//drawinst(A,"","The game is tied! Player: 24 AI: 24");
}
else{
	//drawinst(A,"","AI has won!");
	cout<<"ai wins"<<endl;
}
cout<<"ends program"<<endl;
	  return 0;
}

