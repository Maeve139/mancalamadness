/*
 * state.cpp
 *	This is the state controller for Mancala
 *  Created on: Apr 21, 2019
 *      Author: Scott
 */

//#include "state.h"
#include <iostream>
#include <array>
#include <vector>

using namespace std;

int main(){

	  int player_turn=0;
	  int ai_turn=0;
	  bool blank=false;
	  vector <int> A[14]; //creates array of vectors
	  for (int m=0; m<13; m++){//initializes board
		  if (m!=6
				  ){
			  A[m].assign(4,1); //fills each vec with four ints of 1
	            //leaving the scoring trays empty
	        }
	    }
	    for (int j=0; j<14; j++){
	  	  	  cout<<A[j].size()<< ",  ";
  	  	  }
	    cout<<endl;

	    while (A[6].size()<24&&A[13].size()<24){

	    //checks that the score trays dont have over 24 stones captured(win condition)

	    	//maeve(player_turn,ai_turn,A)
	    	//return board graphic from maeve

	        int play; //call player move from sam to get this
	        player_turn++;
	        play=0;
	        if (A[play].size()==0){
	            //error message
	        	//call maeve message
	            cout<< "There are no stones in that bucket, please try again!"<< endl;
	            break;
	            if (player_turn>0){
	            		player_turn--;
	            }
	            continue;
	        }
	        else{

	            int counter=A[play].size();
	            A[play].clear();
	            for (int c=1; c<counter+1; c++){
	            	//return board graphic from maeve
	            	if ((play+c)%14==13){
	            		//skips the ai score bucket
	            		counter++;
	            	}
	            	else{
	            		//adds a stone to the bucket
	            		A[(play+c)%14].push_back(1);
	            	}
	     }
	            if ((play+counter)%14==6){
	            	//last stone went in score tray so player gets another turn
	            	continue;
	            }
	            if ((((play+counter)%14)>-1)&&(((play+counter)%14)<6)){ //if turn ends in own side
	            	if (A[(play+counter)%14].size()==1&&!A[(12-((play+counter)%14))].empty()){
	            	//if the bucket the last stone ends in is empty and is  across nonempty bucket
	            		//take the stones from both and add to score
	            		int add=1+A[(12-((play+counter)%14))].size();
	            		A[(12-(play+counter)%14)].clear();
	            		//return board graphic from maeve
	            		A[(play+counter)%14].clear();
	            		//return board graphic from maeve
	            		for (int k=0; k<add; k++){
	            			//return board graphic from maeve
	            			A[6].push_back(1);
	            		}
	            	}
	            }

	            //prints out current board state for testing
	            for (int j=0; j<14; j++){
	         	    cout<<A[j].size()<< ",  ";
	         	  }
	            cout<<endl;
	    }
	        if ((A[0].empty()&&A[1].empty()&&A[2].empty()&&A[3].empty()&&A[4].empty()&&A[5].empty())){
	        //if no stones on player side,  add ai stones to their score and exit
	        	int stone=A[7].size()+A[8].size()+A[9].size()+A[10].size()+A[11].size()+A[12].size();
	        	A[7].clear();
	        	A[8].clear();
	        	A[9].clear();
	        	A[10].clear();
	        	A[11].clear();
	        	A[12].clear();
	        	for (int l=0; l<stone; l++){
	        		//return board graphic from maeve
	        		A[13].push_back(1);
	        	}
	        blank=true;
	        break; //leaves loop bc we have a win
	        }

	        if ((A[7].empty()&&A[8].empty()&&A[9].empty()&&A[10].empty()&&A[11].empty()&&A[12].empty())){
	        	        //if no stones on ai side, add player stones to their score and exit
	        	        	int stone=A[0].size()+A[1].size()+A[2].size()+A[3].size()+A[4].size()+A[5].size();
	        	        	A[0].clear();
	        	        	A[1].clear();
	        	        	A[2].clear();
	        	        	A[3].clear();
	        	        	A[4].clear();
	        	        	A[5].clear();
	        	        	for (int l=0; l<stone; l++){
	        	        		//return board graphic from maeve
	        	        		A[13].push_back(1);
	        	        	}
	        	        blank=true;
	        	        break; //leaves loop bc we have a win
	        	        }
	        	//return board graphic from maeve

	        ai_repeat:
	        int ai; //call ai move from ben to get this
	        //this assumes ai will return an int from 7-12 that doesnt have 0  stones
	        ai_turn++;
	        ai=7;

	        int count=A[ai].size();
            A[ai].clear();
            for (int c=1; c<count+1; c++){
            	//return board graphic from maeve

            	if  ((ai+c)%14!=6) {
            		//adds a stone to the bucket if its not the player score tray
            		A[(ai+c)%14].push_back(1);
            	}
            	else{
            		count++;
            	}
     }
            if ((ai+count)%14==13){
            	//last stone went in score tray so ai gets another turn
            	goto ai_repeat;
            }
            if ((((ai+count)%14)>6)&&(((ai+count)%14)<13)){ //if turn ends in own side
            	if (A[(ai+count)%14].size()==1&&!A[(12-((ai+count)%14))].empty()){
            		//and last stone is in an empty bucket across from a not empty bucket
            		//take the stones from both and add to score
            		int add=1+A[(12-((ai+count)%14))].size();
            		A[(12-(ai+count)%14)].clear();
            		//return board graphic from maeve
            		A[(ai+count)%14].clear();
            		//return board graphic from maeve
            		for (int k=0; k<add; k++){
            			//return board graphic from maeve
            			A[13].push_back(1);
            		}
            	}
            }
            //checks if one side of board is empty
            if ((A[0].empty()&&A[1].empty()&&A[2].empty()&&A[3].empty()&&A[4].empty()&&A[5].empty())){
           	        //if no stones on player side,  add ai stones to their score and exit
           	        	int stone=A[7].size()+A[8].size()+A[9].size()+A[10].size()+A[11].size()+A[12].size();
           	        	A[7].clear();
           	        	A[8].clear();
           	        	A[9].clear();
           	        	A[10].clear();
           	        	A[11].clear();
           	        	A[12].clear();
           	        	for (int l=0; l<stone; l++){
           	        		//return board graphic from maeve
           	        		A[13].push_back(1);
           	        	}
           	        blank=true;
           	        break; //leaves loop bc we have a win
           	        }
            		//checks if other side of board is empty
           	        if ((A[7].empty()&&A[8].empty()&&A[9].empty()&&A[10].empty()&&A[11].empty()&&A[12].empty())){
           	        	        //if no stones on ai side, add player stones to their score and exit
           	        	        	int stone=A[0].size()+A[1].size()+A[2].size()+A[3].size()+A[4].size()+A[5].size();
           	        	        	A[0].clear();
           	        	        	A[1].clear();
           	        	        	A[2].clear();
           	        	        	A[3].clear();
           	        	        	A[4].clear();
           	        	        	A[5].clear();
           	        	        	for (int l=0; l<stone; l++){
           	        	        		//return board graphic from maeve
           	        	        		A[13].push_back(1);
           	        	        	}
           	        	        blank=true;
           	        	        break; //leaves loop bc we have a win
           	        	        }


            //prints out current board state for testing
            for (int j=0; j<14; j++){
         	    cout<<A[j].size()<< ",  ";
         	  }
            cout<<endl;
	        } //end of turns while loop

//this is mostly if we  want to quit the game as soon as player/ai hits 25
	    //instead of  playing  until one  side is blank
if  (blank==false){
	//moves stones left in each side to their scoring trays
	int stone=A[0].size()+A[1].size()+A[2].size()+A[3].size()+A[4].size()+A[5].size();
	A[0].clear();
	A[1].clear();
	A[2].clear();
	A[3].clear();
	A[4].clear();
	A[5].clear();
	for (int l=0; l<stone; l++){
		//return board graphic from maeve
		A[6].push_back(1);
	}
	stone=0;
	stone=A[7].size()+A[8].size()+A[9].size()+A[10].size()+A[11].size()+A[12].size();
		A[7].clear();
		A[8].clear();
		A[9].clear();
		A[10].clear();
		A[11].clear();
		A[12].clear();
		for (int l=0; l<stone; l++){
			A[13].push_back(1);
			//return board graphic from maeve
		}
}
cout<<A[6].size()<<endl;
cout<<A[13].size()<<endl;
if (A[6].size()>A[13].size()){
	cout<<"player has  won!"<<endl;
	//send maeve score  and winner
	//call maeve message
}

if (A[6].size()==A[13].size()){
	//can you tie mancala?
	cout<<"the game is tied!"<<endl;
	//send maeve score  and winner
	//call maeve message
}
else{
	cout<<"ai has  won!"<<endl;
		//send maeve score  and winner
		//call maeve message
}
	  return 0;
}

