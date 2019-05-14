/*
*  State controller for Mancala
*  Created on: Apr 21, 2019
*      Author: Scott, Sam C. Maeve G. Ben S
*/


#include <iostream>
#include <array>
#include <stdio.h>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <ctype.h>
#include <vector>

using namespace std;

bool max_cmp(std::array<int,2> a, std::array<int,2> b){
   return a[1]<b[1];
}


class AIPlayer
{
  int kalah;
public:
  std::array<int,14> board;
  std::vector<int> moves;


  AIPlayer(std::array<int,14> boardstate){
    //sets up board,  tells AI it's north
    kalah = 13;
    board = boardstate;
  }


  void update(std::array<int,14> boardstate){
    board = boardstate;
    kalah = 13;
  }

  void MOVE(std::array<int,14> &field, int move){
    //got tired of doing moves manually
    int counter = field[move];
    field[move] = 0;
    for(int drops = 1; drops <= counter; drops++){
      if(move+drops == kalah - 7){
	//this just skips the opponents kalah
	move++;
    }
    field[(move+drops)%14]++;
  }
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
    if(hypo[test] > 0){
      nextMoves.push_back(test);
    }
  }
    return nextMoves;
  }


    
int assess(int move){
  //assesses board position, returns an int reresenting move value
  int value = 0;
  std::vector<int> nextMoves;
  std::array<int,14> testBoard = board;
  int resulthole = ((board[move]+move)%14);
  if(move+board[move] > 13 || resulthole <= move){
    resulthole++;
    value++;
  }
  //still need to handle case where stones go around multiple times
  if(resulthole == kalah) {
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
  if(resulthole == kalah) {
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
  std::vector<std::array<int, 2>>usefulholes;
  //last variable is a relic of older version, may be removed in future
  int score = board[13];
  int playerscore = board[6];
   legalmovefinder();
   std::vector<int> movecopy = moves;
  for(int a = 0; a < movecopy.size(); a++){
    std::array<int,2> a1 = {movecopy[a], 0};
    usefulholes.push_back(a1);
}
  for(int consider = 0; consider < usefulholes.size(); consider++) {
    //checks each possible move
    usefulholes.at(consider)[1] =  assess(usefulholes.at(consider)[0]);
  }
  //this returns the int representing the chosen hole
  moves.clear();
  return (*std::max_element(usefulholes.begin(), usefulholes.end(), max_cmp))[0];
}
};    


int main(){

	restart:
	cout<<endl;
	cout<<"Welcome to Mancala! Win by scoring more stones than your opponent."<<endl;
	cout<<"Play until your opponent has no moves left or you have over 24 stones in your score tray."<<endl;
	cout<<"During your turn pick a number from  1-6 to choose the corresponding bucket to move stones from."<<endl;
	cout<<"Capture opponents stones by ending your turn in an empty bucket, which capture the stones in the opposite bucket."<<endl;
	cout<<"Gain another turn by ending your turn in your scoring tray."<<endl;
	cout<<"Type 'Q' to quit and 'R' to restart. "<<endl;
	cout<<"Have fun!"<<endl;
	std::array<int,14> A={ 0 }; //creates array
	  int player_turn=0;
	  int ai_turn=0;
	  bool blank=false;

	  for (int m=0; m<13; m++){//initializes board
		  if (m!=6){
			  A[m]=4; //fills each vec with four ints of 1
	            //leaving the scoring trays empty
	        }
	    }
	int space=8; 
	cout<<"	_______________________________________"<<endl;
	cout<<"	|  AI	 		           P   |"<<endl;

	cout<<"	|	("<<A[12]<<") ("<<A[11]<<") ("<<A[10]<<") ("<<A[9]<<") ("<<A[8]<<") ("<<A[7]<<")";
	if(A[12]>9){
	    space--;    
	}
	if(A[11]>9){
	    space--;    
	}
	if(A[10]>9){
	    space--;    
	}
	if(A[9]>9){
	    space--;    
	}
	if(A[8]>9){
	    space--;    
	}
	if(A[7]>9){
	    space--;    
	}
	for (int m=0; m<space;m++){
	    cout<<" ";
	}
	cout<<"|"<<endl;
	cout<<"	| _____				 _____ |"<<endl;
	cout<<"	| |   |				 |   | |"<<endl; 
	if (A[13]>9){
	  cout<<"	| |"<<A[13]<<" |                		 |";  
	}
	else{
	 cout<<"	| | "<<A[13]<<" |                		 |"; 
	}
	if (A[6]>9){
		cout<<A[6]<<" | |"<<endl;
	}
	else{
	    cout<<" "<<A[6]<<" | |"<<endl;
	}
	cout<<"	| |   |			  	 |   | |"<<endl;
	cout<<"	| -----				 ----- |"<<endl; 
	cout<<"	|       ("<<A[0]<<") ("<<A[1]<<") ("<<A[2]<<") ("<<A[3]<<") ("<<A[4]<<") ("<<A[5]<<")";
	int sp=8;
	if(A[0]>9){
	    sp--;    
	}
	if(A[1]>9){
	    sp--;    
	}
	if(A[2]>9){
	    sp--;    
	}
	if(A[3]>9){
	    sp--;    
	}
	if(A[4]>9){
	    sp--;    
	}
	if(A[5]>9){
	    sp--;    
	}
	for (int m=0; m<sp;m++){
	    cout<<" ";
	}
	cout<<"|"<<endl;
	cout<<"	|______________________________________|"<<endl;	
	  AIPlayer *artificial = new AIPlayer(A);
 
	 while (A[6]<25&&A[13]<25){
	    //checks that the score trays dont have over 24 stones captured(win condition)
	    	cout<<"Pick a bucket to move stones from"<<endl;
	        string in;
	    	cin>>in;
		if (in.size()>1){
		    cout<<"Please only enter a single number or character  as input"<<endl;
		    continue;
		}
		char input=in[0];
	        player_turn++;

	        if (input=='R'||input=='r'){ //restarts
	        	cout<<"Restarts game"<<endl;
	        		goto restart;
	        }

	        if (input=='Q'||input=='q'){ //quits game
	        	cout<<"Quits game"<<endl;
	        	return 0;
	        }
		
	        if (!isdigit(input)){
	        	cout<<"Give a digit between 1-6 to pick the corresponding bucket"<<endl;
	        	if (player_turn>0){
	        		player_turn--;
	     		}
	        	continue;
	        }

		int play=input-49;
		if (play>5){
	       	            //error message
	        	cout<<"Please pick bucket on your side!"<<endl;
	       	            //break;
	       	            if (player_turn>0){
	       	            		player_turn--;
	       	            }
	       	            continue;
	       	        }


	        if (A[play]==0){
	            //error message
	        	cout<<"There are no stones in that bucket, please try again!"<<endl;
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
	            	if ((play+c)%14==13){
	            		//skips the ai score bucket
	            		counter++;
	            	}
	            	else{
	            		//adds a stone to the bucket
	            		A[(play+c)%14]++;
	            	}
	     }
	            if ((play+counter)%14==6){

	            	cout<<"Player gets another turn!"<<endl;
			    int space=8; 
	cout<<"	_______________________________________"<<endl;
	cout<<"	|  AI	 		           P   |"<<endl;

	cout<<"	|	("<<A[12]<<") ("<<A[11]<<") ("<<A[10]<<") ("<<A[9]<<") ("<<A[8]<<") ("<<A[7]<<")";
	if(A[12]>9){
	    space--;    
	}
	if(A[11]>9){
	    space--;    
	}
	if(A[10]>9){
	    space--;    
	}
	if(A[9]>9){
	    space--;    
	}
	if(A[8]>9){
	    space--;    
	}
	if(A[7]>9){
	    space--;    
	}
	for (int m=0; m<space;m++){
	    cout<<" ";
	}
	cout<<"|"<<endl;
	cout<<"	| _____				 _____ |"<<endl;
	cout<<"	| |   |				 |   | |"<<endl; 
	if (A[13]>9){
	  cout<<"	| |"<<A[13]<<" |                		 |";  
	}
	else{
	 cout<<"	| | "<<A[13]<<" |                		 |"; 
	}
	if (A[6]>9){
		cout<<A[6]<<" | |"<<endl;
	}
	else{
	    cout<<" "<<A[6]<<" | |"<<endl;
	}
	cout<<"	| |   |			  	 |   | |"<<endl;
	cout<<"	| -----				 ----- |"<<endl; 
	cout<<"	|       ("<<A[0]<<") ("<<A[1]<<") ("<<A[2]<<") ("<<A[3]<<") ("<<A[4]<<") ("<<A[5]<<")";
	int sp=8;
	if(A[0]>9){
	    sp--;    
	}
	if(A[1]>9){
	    sp--;    
	}
	if(A[2]>9){
	    sp--;    
	}
	if(A[3]>9){
	    sp--;    
	}
	if(A[4]>9){
	    sp--;    
	}
	if(A[5]>9){
	    sp--;    
	}
	for (int m=0; m<sp;m++){
	    cout<<" ";
	}
	cout<<"|"<<endl;
	cout<<"	|______________________________________|"<<endl;	

		            	//last stone went in score tray so player gets another turn
	            	continue;
	            }
	            if ((((play+counter)%14)>-1)&&(((play+counter)%14)<6)){ //if turn ends in own side
	            	if (A[(play+counter)%14]==1&&A[(12-((play+counter)%14))]!=0){
	            	//if the bucket the last stone ends in is empty and is  across nonempty bucket
	            		//take the stones from both and add to score
	            		int add=1+A[(12-((play+counter)%14))];
	            		A[(12-(play+counter)%14)]=0;
	            		A[(play+counter)%14]=0;
	            		for (int k=0; k<add; k++){
	            			A[6]++;;
	            		}
	            	}
	            }

			//prints out current board state for testing
		    int space=8; 
	cout<<"	_______________________________________"<<endl;
	cout<<"	|  AI	 		           P   |"<<endl;

	cout<<"	|	("<<A[12]<<") ("<<A[11]<<") ("<<A[10]<<") ("<<A[9]<<") ("<<A[8]<<") ("<<A[7]<<")";
	if(A[12]>9){
	    space--;    
	}
	if(A[11]>9){
	    space--;    
	}
	if(A[10]>9){
	    space--;    
	}
	if(A[9]>9){
	    space--;    
	}
	if(A[8]>9){
	    space--;    
	}
	if(A[7]>9){
	    space--;    
	}
	for (int m=0; m<space;m++){
	    cout<<" ";
	}
	cout<<"|"<<endl;
	cout<<"	| _____				 _____ |"<<endl;
	cout<<"	| |   |				 |   | |"<<endl; 
	if (A[13]>9){
	  cout<<"	| |"<<A[13]<<" |                		 |";  
	}
	else{
	 cout<<"	| | "<<A[13]<<" |                		 |"; 
	}
	if (A[6]>9){
		cout<<A[6]<<" | |"<<endl;
	}
	else{
	    cout<<" "<<A[6]<<" | |"<<endl;
	}
	cout<<"	| |   |			  	 |   | |"<<endl;
	cout<<"	| -----				 ----- |"<<endl; 
	cout<<"	|       ("<<A[0]<<") ("<<A[1]<<") ("<<A[2]<<") ("<<A[3]<<") ("<<A[4]<<") ("<<A[5]<<")";
	int sp=8;
	if(A[0]>9){
	    sp--;    
	}
	if(A[1]>9){
	    sp--;    
	}
	if(A[2]>9){
	    sp--;    
	}
	if(A[3]>9){
	    sp--;    
	}
	if(A[4]>9){
	    sp--;    
	}
	if(A[5]>9){
	    sp--;    
	}
	for (int m=0; m<sp;m++){
	    cout<<" ";
	}
	cout<<"|"<<endl;
	cout<<"	|______________________________________|"<<endl;	


		    }
	     
	        if ((A[7]==0&&A[8]==0&&A[9]==0&&A[10]==0&&A[11]==0&&A[12]==0)){
	        	        //if no stones on ai side, add player stones to their score and exit
	        	cout<<"No moves possible for AI"<<endl;

	        	        	int stone=A[0]+A[1]+A[2]+A[3]+A[4]+A[5];
	        	        	A[0]=0;
	        	        	A[1]=0;
	        	        	A[2]=0;
	        	        	A[3]=0;
	        	        	A[4]=0;
	        	        	A[5]=0;
	        	        	for (int l=0; l<stone; l++){
	        	        		//return board graphic from maeve
	        	        		A[6]++;
	        	        	}
	        	        blank=true;
	        	        break; //leaves loop bc we have a win
	        	        }

	        ai_repeat:
			 cout<<"AI's turn"<<endl;
		/*for (int j=0; j<14; j++){
	  	  	  cout<<A[j]<< ",  ";
  	  	  }
	   cout<<endl;
	       */ 
   		artificial->update(A);
  		int ai=artificial->mover();
 		 
		cout<<"AI has picked "<<ai<<endl;
	        //this assumes ai will return an int from 7-12 that doesnt have 0  stones
	        ai_turn++;
	        int count=A[ai];
            	A[ai]=0;
            for (int c=1; c<count+1; c++){

            	if  ((ai+c)%14!=6) {
            		//adds a stone to the bucket if its not the player score tray
			A[(ai+c)%14]++;
            	}
            	else{
            		count++;
            	}
     }
            if ((ai+count)%14==13){
int space=8; 
	cout<<"	_______________________________________"<<endl;
	cout<<"	|  AI	 		           P   |"<<endl;

	cout<<"	|	("<<A[12]<<") ("<<A[11]<<") ("<<A[10]<<") ("<<A[9]<<") ("<<A[8]<<") ("<<A[7]<<")";
	if(A[12]>9){
	    space--;    
	}
	if(A[11]>9){
	    space--;    
	}
	if(A[10]>9){
	    space--;    
	}
	if(A[9]>9){
	    space--;    
	}
	if(A[8]>9){
	    space--;    
	}
	if(A[7]>9){
	    space--;    
	}
	for (int m=0; m<space;m++){
	    cout<<" ";
	}
	cout<<"|"<<endl;
	cout<<"	| _____				 _____ |"<<endl;
	cout<<"	| |   |				 |   | |"<<endl; 
	if (A[13]>9){
	  cout<<"	| |"<<A[13]<<" |                		 |";  
	}
	else{
	 cout<<"	| | "<<A[13]<<" |                		 |"; 
	}
	if (A[6]>9){
		cout<<A[6]<<" | |"<<endl;
	}
	else{
	    cout<<" "<<A[6]<<" | |"<<endl;
	}
	cout<<"	| |   |			  	 |   | |"<<endl;
	cout<<"	| -----				 ----- |"<<endl; 
	cout<<"	|       ("<<A[0]<<") ("<<A[1]<<") ("<<A[2]<<") ("<<A[3]<<") ("<<A[4]<<") ("<<A[5]<<")";
	int sp=8;
	if(A[0]>9){
	    sp--;    
	}
	if(A[1]>9){
	    sp--;    
	}
	if(A[2]>9){
	    sp--;    
	}
	if(A[3]>9){
	    sp--;    
	}
	if(A[4]>9){
	    sp--;    
	}
	if(A[5]>9){
	    sp--;    
	}
	for (int m=0; m<sp;m++){
	    cout<<" ";
	}
	cout<<"|"<<endl;
	cout<<"	|______________________________________|"<<endl;	


            		
		//last stone went in score tray so ai gets another turn
 	cout<<"AI gets another turn!"<<endl;
           
	goto ai_repeat;
            }
            if ((((ai+count)%14)>6)&&(((ai+count)%14)<13)){ //if turn ends in own side
            	if (A[(ai+count)%14]==1&&A[(12-((ai+count)%14))]!=0){
            		//and last stone is in an empty bucket across from a not empty bucket
            		//take the stones from both and add to score
            		int add=1+A[(12-((ai+count)%14))];
            		A[(12-(ai+count)%14)]=0;
            		A[(ai+count)%14]=0;
            		for (int k=0; k<add; k++){
            			A[13]++;
            		}
            	}
            }
            //checks if one side of board is empty
            if ((A[0]==0&&A[1]==0&&A[2]==0&&A[3]==0&&A[4]==0&&A[5]==0)){
		 int space=8; 
	cout<<"	_______________________________________"<<endl;
	cout<<"	|  AI	 		           P   |"<<endl;

	cout<<"	|	("<<A[12]<<") ("<<A[11]<<") ("<<A[10]<<") ("<<A[9]<<") ("<<A[8]<<") ("<<A[7]<<")";
	if(A[12]>9){
	    space--;    
	}
	if(A[11]>9){
	    space--;    
	}
	if(A[10]>9){
	    space--;    
	}
	if(A[9]>9){
	    space--;    
	}
	if(A[8]>9){
	    space--;    
	}
	if(A[7]>9){
	    space--;    
	}
	for (int m=0; m<space;m++){
	    cout<<" ";
	}
	cout<<"|"<<endl;
	cout<<"	| _____				 _____ |"<<endl;
	cout<<"	| |   |				 |   | |"<<endl; 
	if (A[13]>9){
	  cout<<"	| |"<<A[13]<<" |                		 |";  
	}
	else{
	 cout<<"	| | "<<A[13]<<" |                		 |"; 
	}
	if (A[6]>9){
		cout<<A[6]<<" | |"<<endl;
	}
	else{
	    cout<<" "<<A[6]<<" | |"<<endl;
	}
	cout<<"	| |   |			  	 |   | |"<<endl;
	cout<<"	| -----				 ----- |"<<endl; 
	cout<<"	|       ("<<A[0]<<") ("<<A[1]<<") ("<<A[2]<<") ("<<A[3]<<") ("<<A[4]<<") ("<<A[5]<<")";
	int sp=8;
	if(A[0]>9){
	    sp--;    
	}
	if(A[1]>9){
	    sp--;    
	}
	if(A[2]>9){
	    sp--;    
	}
	if(A[3]>9){
	    sp--;    
	}
	if(A[4]>9){
	    sp--;    
	}
	if(A[5]>9){
	    sp--;    
	}
	for (int m=0; m<sp;m++){
	    cout<<" ";
	}
	cout<<"|"<<endl;
	cout<<"	|______________________________________|"<<endl;	
            	cout<<"No moves possible for Player"<<endl;
           	        //if no stones on player side,  add ai stones to their score and exit
           	        	int stone=A[7]+A[8]+A[9]+A[10]+A[11]+A[12];
           	        	A[7]=0;
           	        	A[8]=0;
           	        	A[9]=0;
           	        	A[10]=0;
           	        	A[11]=0;
           	        	A[12]=0;
           	        	for (int l=0; l<stone; l++){
           	        		A[13]++;
           	        	}
           	        blank=true;
           	        break; //leaves loop bc we have a win
           	        }
     
            //prints out current board state for testing
	    int space=8; 
	cout<<"	_______________________________________"<<endl;
	cout<<"	|  AI	 		           P   |"<<endl;

	cout<<"	|	("<<A[12]<<") ("<<A[11]<<") ("<<A[10]<<") ("<<A[9]<<") ("<<A[8]<<") ("<<A[7]<<")";
	if(A[12]>9){
	    space--;    
	}
	if(A[11]>9){
	    space--;    
	}
	if(A[10]>9){
	    space--;    
	}
	if(A[9]>9){
	    space--;    
	}
	if(A[8]>9){
	    space--;    
	}
	if(A[7]>9){
	    space--;    
	}
	for (int m=0; m<space;m++){
	    cout<<" ";
	}
	cout<<"|"<<endl;
	cout<<"	| _____				 _____ |"<<endl;
	cout<<"	| |   |				 |   | |"<<endl; 
	if (A[13]>9){
	  cout<<"	| |"<<A[13]<<" |                		 |";  
	}
	else{
	 cout<<"	| | "<<A[13]<<" |                		 |"; 
	}
	if (A[6]>9){
		cout<<A[6]<<" | |"<<endl;
	}
	else{
	    cout<<" "<<A[6]<<" | |"<<endl;
	}
	cout<<"	| |   |			  	 |   | |"<<endl;
	cout<<"	| -----				 ----- |"<<endl; 
	cout<<"	|       ("<<A[0]<<") ("<<A[1]<<") ("<<A[2]<<") ("<<A[3]<<") ("<<A[4]<<") ("<<A[5]<<")";
	int sp=8;
	if(A[0]>9){
	    sp--;    
	}
	if(A[1]>9){
	    sp--;    
	}
	if(A[2]>9){
	    sp--;    
	}
	if(A[3]>9){
	    sp--;    
	}
	if(A[4]>9){
	    sp--;    
	}
	if(A[5]>9){
	    sp--;    
	}
	for (int m=0; m<sp;m++){
	    cout<<" ";
	}
	cout<<"|"<<endl;
	cout<<"	|______________________________________|"<<endl;	


	  	    } //end of turns while loop
//Now we are at a win state
if  (blank==false){
	//moves stones left in each side to their scoring trays
	int stone=A[0]+A[1]+A[2]+A[3]+A[4]+A[5];
	A[0]=0;
	A[1]=0;
	A[2]=0;
	A[3]=0;
	A[4]=0;
	A[5]=0;
	A[6]=A[6]+stone;
	
	stone=0;
	stone=A[7]+A[8]+A[9]+A[10]+A[11]+A[12];
		A[7]=0;
		A[8]=0;
		A[9]=0;
		A[10]=0;
		A[11]=0;
		A[12]=0;;
		A[13]=A[13]+stone;		
}
cout<<"Player: "<<A[6]<<endl;
cout<<"AI: "<<A[13]<<endl;
if (A[6]>A[13]){
	cout<<"Player wins!"<<endl;
}

if (A[6]==A[13]){

cout<<"Tied game!"<<endl;
}
if(A[13]>A[6]) {
	cout<<"AI wins!"<<endl;
}
cout<<"Game Quits"<<endl;
	  return 0;
}

