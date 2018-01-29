//Author: Jion Fairchild

#include <vector>
#include<string>
#include<iostream>
#include<fstream>
using namespace std;

//This function reads the life.txt file and converts it to a 2-d array that is padded with extra dead cells around the perimiter
vector<string> readLifeToArray(){
  ifstream inputFile("life.txt");
  if(!inputFile){
    cout <<"ERROR, File could not be opened successfully";
    exit(0);
  }
  vector<string> ans;
  string currentLine;
  string blankline;
  bool first = true;
  //ans.push_back(blankline);
  while( getline(inputFile,currentLine) ){
    if(first){
      for(int i = 0; i< currentLine.size()+2; i+=1){
	blankline.append("-");
      }
      ans.push_back(blankline);
      first = false;
    }
    
    string copy;
    copy.append("-");
    copy.append(currentLine);
    copy.append("-");
    ans.push_back(copy);
  }
  ans.push_back(blankline);
  inputFile.close();
  return ans;
}

//Takes the location xcor and ycor and decides whether it should be killed or brought to life
//A return of 0 means to do nothing
//A return of 1 means to kill the cell
//A return of 2 means to bring the cell to life
int decideToKill(vector<string> lifearray,int xcor,int ycor){
  //cout << "choosing" << xcor <<","<< ycor <<endl;
  if(lifearray[xcor][ycor] == '-'){//test if the cell should be brough to life
    int livingNeighbors = 0;
    for(int x=-1; x<2;x+=1){//counts neighbors
      for( int y=-1; y<2; y+=1){
	if( lifearray[xcor+x][ycor+y] == '*'){
	  livingNeighbors +=1;
	}
      }
    }
    if(livingNeighbors == 3){
      return 2;//bring to life
    }
    return 0;//do nothing
  }else{//test if a cell should be killed
    int livingNeighbors = -1;//-1 to account for it counting itself
    for(int x=-1; x<2;x+=1){
      for( int y=-1; y<2; y+=1){
	if( lifearray[xcor+x][ycor+y] == '*'){
	  livingNeighbors +=1;
	}
      }
    }
    if(livingNeighbors <2 || livingNeighbors > 3){
      return 1;//kill the cell
    }
    return 0;//do nothing
  }
}

//This function creates a vector of coordinates to be killed or revived
//Associated with each array is the integers for kill or revive
vector< vector< int > > findCellsToKill(vector<string> lifearray){
  vector< vector<int> > killLocations;
  for( int x = 1; x< lifearray.size()-1; x+=1){
    for( int y = 1; y< lifearray[x].size()-1; y+=1){
      int killAnswer = decideToKill(lifearray,x,y);//check kill or revive
      if(killAnswer != 0){//anything except do nothing
	//cout << "killnow";
	vector<int> coordinates;
	coordinates.push_back(x);
	coordinates.push_back(y);
	coordinates.push_back(killAnswer);
	killLocations.push_back(coordinates);
      }
    }
  }
  return killLocations;
}

//find all of the kill and revive locations, then execute them simultaneously
vector<string> generation(vector<string> lifearray){
  vector< vector<int> > killLocations = findCellsToKill(lifearray);
  //cout << killLocations.size();
  for( int location = 0; location< killLocations.size(); location+=1){
    //cout << "killing: " << killLocations[location][0] <<","<<killLocations[location][1] << endl;
    if(killLocations[location][2] == 1){//kill the cell at this location
      lifearray[killLocations[location][0]][killLocations[location][1]] = '-';
    }else{//everything is either kill or revive, so this revives
      lifearray[killLocations[location][0]][killLocations[location][1]] = '*';
    }
  }
  return lifearray;
}
  
int main(){
  vector<string> life = readLifeToArray();//read in starting condition
  for(int generationNum = 0; generationNum < 11; generationNum+=1){//loop over generations
    for(int i=1; i < life.size()-1; i+=1){//output the life array
      cout << life[i].substr(1,-1) << endl;
    }
    life = generation(life);//iterate to the next generation
    cout << endl;//line break
  }
  return 0;
}
    
    
