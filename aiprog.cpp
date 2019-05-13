/*
 * aiprog.cpp
 * This is the decision-making code for the ai player
 *
 *Status:Still needs to account for defence, plays too aggressively
 * Also need to rewrite assess for two AIs, or flip the board around
 * latter seems easierbut may need change in others code
 *Not Yet Tested
 * Author: Ben Smullyan
 */

#include <array>
#include <vector>
#include <algorithm>



  


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
  std::array<int, 14> mytestboard;
  mytestboard.fill(4);
  AIPlayer *ai = new AIPlayer(mytestboard);
  ai->update(mytestboard);
  ai->mover();
}
