#include <vector> //like an array
#include <string> //strings!
#include <iostream> //equivalent to stdio
#include <ifstream> //for reading files
using namespace std;

int main(){
  for(int i = 0; i < 100; i+=2){//standard for loop
    if( i % 7 == 0) break;
    cout << i << ' ';
  }
  cout << endl;

  vector<int> v; // vectors are not arrays
  cout << v.size() << endl;
  v.push_back(17);
  cout << v.size() << endl;
  
  for( int i : v){//enhance!!!
    //do something
  }

  //read file "example.txt"
  ifstream ifs("example.txt");
  if(!ifs){
    //failed to open file
  }
  string s;
  while (ifs >> s){//attempt to write token to string s
    count << s << endl;//print token
    //note that tokens are whitespace delimited by default
  }

  while ( getline(ifs,s)){//delimits tokens by line
    // getline(inputstream,bufferstring)
    //do stuff
  }
  
}
