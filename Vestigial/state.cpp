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
	  int A[14]={ 0 }; //creates array
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

	    while (A[6]<24&&A[13]<24){
	    //checks that the score trays dont have over 24 stones captured(win condition)

	    	//maeve(player_turn,ai_turn,A)
	    	//return board graphic from maeve

	        int play; //call player move from sam to get this
	        player_turn++;
	        play=0;


	        if (A[play]==0){
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

	            int counter=A[play];
	            A[play]=0;
	            for (int c=1; c<counter+1; c++){

	            	//return board graphic from maeve
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
	            	//last stone went in score tray so player gets another turn
	            	continue;
	            }
	            if ((((play+counter)%14)>-1)&&(((play+counter)%14)<6)){ //if turn ends in own side
	            	if (A[(play+counter)%14]==1&&A[(12-((play+counter)%14))]!=0){
	            	//if the bucket the last stone ends in is empty and is  across nonempty bucket
	            		//take the stones from both and add to score
	            		int add=1+A[(12-((play+counter)%14))];
	            		cout<<add<<endl;
	            		A[(12-(play+counter)%14)]=0;
	            		//return board graphic from maeve
	            		A[(play+counter)%14]=0;
	            		//return board graphic from maeve
	            		for (int k=0; k<add; k++){
	            			//return board graphic from maeve
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
	        blank=true;
	        break; //leaves loop bc we have a win
	        }

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
	        	//return board graphic from maeve

	        ai_repeat:
	        int ai; //call ai move from ben to get this
	        //this assumes ai will return an int from 7-12 that doesnt have 0  stones
	        ai_turn++;
	        ai=7;

	        int count=A[ai];
            A[ai]=0;
            for (int c=1; c<count+1; c++){
            	//return board graphic from maeve

            	if  ((ai+c)%14!=6) {
            		//adds a stone to the bucket if its not the player score tray
            		A[(ai+c)%14]++;
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
            	if (A[(ai+count)%14]==1&&A[(12-((ai+count)%14))]!=0){
            		//and last stone is in an empty bucket across from a not empty bucket
            		//take the stones from both and add to score
            		int add=1+A[(12-((ai+count)%14))];
            		A[(12-(ai+count)%14)]=0;
            		//return board graphic from maeve
            		A[(ai+count)%14]=0;
            		//return board graphic from maeve
            		for (int k=0; k<add; k++){
            			//return board graphic from maeve
            			A[13]++;
            		}
            	}
            }
            //checks if one side of board is empty
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
           	        blank=true;
           	        break; //leaves loop bc we have a win
           	        }
            		//checks if other side of board is empty
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


            //prints out current board state for testing
            for (int j=0; j<14; j++){
         	    cout<<A[j]<< ",  ";
         	  }
            cout<<endl;
	        } //end of turns while loop

//this is mostly if we  want to quit the game as soon as player/ai hits 25
	    //instead of  playing  until one  side is blank
if  (blank==false){
	//moves stones left in each side to their scoring trays
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
			//return board graphic from maeve
		}
}
cout<<A[6]<<endl;
cout<<A[13]<<endl;
if (A[6]>A[13]){
	cout<<"player has  won!"<<endl;
	//send maeve score  and winner
	//call maeve message
}

if (A[6]==A[13]){
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

