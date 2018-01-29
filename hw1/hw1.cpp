//name: Jion Fairchild
//section: C
//description: A program that takes a file called "encrypted.txt" and decrypts it using a caesar cypher
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;
//takes a character and the number of the rotation, and rotates it in reverse
char decryptChar(char character, int rotation){
  char numchars = 'z'-'a';//number of characters in alphabet
  if(character >='a' and character <='z'){//if character is lowercase
    character -= 'a';//find the number in the alphabet of the character
    character += numchars+1;//this is so we don't wrap past 0
    character -= rotation;//rotate backwards
    character = character % (numchars+1);//modulo so everything fits in the 0-25 range
    character += 'a';//translate back up to the lower case range
  }
  return character;
}

//takes a string and its rotation and decrypts it
void decryptString(string& input, int rotation){
  for(size_t i=0; i< input.size();++i){//iterate through each character
    input[i] = decryptChar(input[i],rotation);//and decrypt it
  }
}

int main(){
  ifstream file("encrypted.txt");
  if(!file){
    cerr << "couldn't read file";
    exit(1);
  }
  int rotation;
  file >> rotation;//read the rotation
  vector<string> lines;//holds lines
  string line;//holdes current line
  while(getline(file,line)){
    decryptString(line,rotation);//decrypt line
    lines.push_back(line);
  }
  
  //final loop prints backwards
  for(size_t i = lines.size();i>0;--i) cout << lines[i-1] << endl;
  return 0;
}
