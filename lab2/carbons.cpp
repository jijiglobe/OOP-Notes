#include<fstream>
#include<iostream>
#include<vector>
#include<string>
using namespace std;
//prints all the hydrocarbons such that the number of carbons is N
struct HydroCarbon{
  string numC;
  string numH;
  string names;
};
int printWithNCarbons(const vector<HydroCarbon>& carbonsList, int N){
  int count = 0;
  string stringN = to_string(N);
  for(HydroCarbon carbon : carbonsList){//iterate over list
    if(carbon.numC == stringN){//print out carbon
      count++;
      cout << "C" << carbon.numC << "H" << carbon.numH
	   << " " << carbon.names << endl;
    }
  }
  return count;//return number printed
}

//reads files into a vector of vectors <numcarbons,numhydrogens,names>
//combines carbons with the same formula into a single entry
vector<HydroCarbon > readFile(const string& filename){
  ifstream ifs(filename);
  if(!ifs) exit(1);
  
  vector<HydroCarbon> ans;
  string currentLine; //holds name of current carbon
  string holder; // holds formula
  while(ifs >> currentLine){
    HydroCarbon currentCarb;
    ifs>> holder;

    size_t hloc = holder.find('H');//find H
    currentCarb.numC = holder.substr(1,hloc-1);//store numcarbons
    currentCarb.numH = holder.substr(hloc+1,-1);//store numhydrogens

    bool formulaIsTaken = false;//is this formula in our vector already
    for(HydroCarbon& carbon : ans){
      if(carbon.numC == currentCarb.numC &&
	 carbon.numH == currentCarb.numH){//if vector is found
	
	carbon.names.append(" ");
	carbon.names.append(currentLine);//append name to vector
	formulaIsTaken = true;
	break;
      }
    }
    if(!formulaIsTaken){//formula isn't taken, so create new entry
      currentCarb.names = currentLine;
      ans.push_back(currentCarb);
    }
  }
  return ans;
}

//prints hydrocarbons in order of ascending carbon count
void printInAscendingCarbonsOrder(const string& filename){
  vector<HydroCarbon > fileVector = readFile(filename);//read file  
  int printed = 0;//count printed to make sure everything is printed
  for(int counter = 0;printed < fileVector.size();counter++){//iterate overe file
    printed += printWithNCarbons(fileVector,counter);//print n-carbons
  }
}
int main(){
  printInAscendingCarbonsOrder("carbons.txt");

}
