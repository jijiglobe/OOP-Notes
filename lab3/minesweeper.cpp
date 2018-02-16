//Name: Jion Fairchild
//Description: This assignment is a minesweeper game that runs in terminal using ASCII characters to indicate various board states.
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;

//struct for a coordinate pair
struct Coordinates{
  int xcor;
  int ycor;
};

//struct for a board tile
struct Tile{
  int ycor;
  int xcor;
  int numBombNeighbors;//number of bomb neighbors.
  bool isVisible;//whether the tile is visible
  bool isBomb;
};

//main assignment
class Minesweeper{
public:
  //instantiates minesweeper with a random 10x10 board
  Minesweeper(): numrows(10),numcols(10), isdone(false){
    srand(time(NULL));
    for( int y = 0; y < numrows; y++){
      vector< Tile > current;
      for(int x = 0; x < numcols; x++){
	//create tile
	Tile thisTile;
	thisTile.isVisible = false;
	thisTile.xcor = x;
	thisTile.ycor = y;
	if(rand() % 100 <= 10){//tile has a 10% chance to be a bomb
	  thisTile.isBomb = true;
	  current.push_back(thisTile);
	}else{
	  thisTile.isBomb = false;
	  current.push_back(thisTile);
	}
      }
      board.push_back(current);
    }
    countBombs();
  }
  
  //displays board with coordinate labels
  void display(bool displayBombs){
    cout << endl<<endl<<endl;
    for( int y=numrows-1; y>=0;y--){//iterates over board and prints all
      cout << y << "|   ";//prints y axis
      for( int x=0; x<numcols;x++){
	if(displayBombs and board[x][y].isBomb){
	  cout<< "@  ";
	}else if(board[x][y].isVisible){
	  cout<< board[x][y].numBombNeighbors << "  ";
	}else{
	  cout<< "#  ";
	}
	   }
      cout << endl<<" |" << endl;
    }
    cout << "    ";
    for(int x = 0; x < numcols ;x++){//prints x axis
      cout << "___";
    }cout << endl;
    cout << "    ";
    for(int x = 0; x < numcols ;x++){//prints x axis
      cout << x << "  ";
    }cout << endl;

  }
  
  //checks if all non-bomb locations are visible. if so, the game is won
  //returns true if game is won
  bool done(){
    for( int x = 0; x < numrows; x++){
      for( int y = 0; y < numcols; y++){
	if(!board[x][y].isVisible && !board[x][y].isBomb){
	  return false;
	}
      }
    } 
    return true;
  }
  
  //returns if the row is valid
  bool validRow(int y){
    return y >= 0 && y < numrows;
  }
  
  //returns if the column is valid
  bool validCol(int x){
    return x >=0 && x<numcols;
  }
  
  //returns if the indicated coordinate is visible
  bool isVisible(int xcor, int ycor){
    return board[ycor][xcor].isVisible;
  }

  //plays a certain location
  //returns false if the location is a bomb, true otherwise
  bool play(int ycor, int xcor){
    if(board[xcor][ycor].isBomb){//check if bomb is triggered
      isdone = true;
      return false;
    }
    
    //creates coordinate pair for depth first search
    vector<Coordinates> stack;
    Coordinates here;
    here.xcor = xcor;
    here.ycor = ycor;
    
    stack.push_back(here);//push pair to stack
    while(stack.size() >0){
      Coordinates current = stack.back();
      stack.pop_back();//retrieve pair of stack

      board[current.xcor][current.ycor].isVisible = true;
      if(board[current.xcor][current.ycor].numBombNeighbors == 0){
	//if this location is a 0 continue searching
	//iterates over neighbor coordinates
	for( int x = current.xcor-1; x<=current.xcor+1 ; x++){
	  for( int y = current.ycor-1; y <= current.ycor+1; y++){
	    if(validRow(y) && validCol(x) && !board[x][y].isVisible){
	      //if location is valid and invisible, we add it to the stack
	      Coordinates here;
	      here.xcor = x;
	      here.ycor = y;
	      stack.push_back(here);
	    }
	  }
	}
      }
    }
    return true;
  }
private:
  vector< vector< Tile > > board;
  int numrows;
  int numcols;
  bool isdone;

  //counts the bombs around a given location and returns that number
  int countBombsAroundLocation(int xcor, int ycor){
    int numBombs = 0;
    for( int x = xcor-1; x<=xcor+1 ; x++){
      for( int y = ycor-1; y <= ycor+1; y++){
	if(validRow(y) && validCol(x) && board[x][y].isBomb){
	  numBombs++;
	}
      }
    }
    return numBombs;
  }

  //counts bombs around every tile and sets their numBombNeighbor to that
  void countBombs(){
    for( int x = 0; x < numrows; x++){
      for( int y = 0; y < numcols; y++){
	board[x][y].numBombNeighbors = countBombsAroundLocation(x,y);
      }
    }
  }
};

int main() {
  Minesweeper sweeper;
  sweeper.display(true);
  // Continue until only invisible cells are bombs
  while (!sweeper.done()) {
    sweeper.display(false); // display board without bombs

    int row_sel = -1, col_sel = -1;
    while (row_sel == -1) {
      // Get a valid move
      int r, c;
      cout << "row? ";
      cin >> r;
      if (!sweeper.validRow(r)) {
	cout << "Row out of bounds\n";
	continue;
      }
      cout << "col? ";
      cin >> c;
      if (!sweeper.validRow(c)) {
	cout << "Column out of bounds\n";
	continue;
      }
      if (sweeper.isVisible(r,c)) {
	cout << "Square already visible\n";
	continue;
      }
      row_sel = r;
      col_sel = c;
    }
    // Set selected square to be visible. May effect other cells.
    if (!sweeper.play(row_sel,col_sel)) {
      cout << "Sorry, you died..\n";
      sweeper.display(true); // Final board with bombs shown
      exit(0);
    }
  }
  // Ah! All invisible cells are bombs, so you won!
  cout << "You won!!!!\n";
  sweeper.display(true); // Final board with bombs shown
}

