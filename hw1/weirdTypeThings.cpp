
size_t findWord(string token, const vector<Word>& words){//return size_t for type consistancy
  for(size_t i = 0; i < words.size; i++){
    if(words[i] == token){
      return i;//might as well
    }
  }
  return words.size();//this is an invalid index. size_t can't be -1
}

class Person{
public: // everything from here down is public
  string name;

private:
  //this bit is private. By convention, put private second
  //this convention is because, when reading your code
  //people want to see what they can do, not what they can't
}

int main() {
  ifstream ifs("jabberwocky");
  if(!ifs) exit(1);
  
  int where = 0;
  vector<Word> words;
  
  string token;
  while(ifs >> token){
    size_t theIndex= findWord(token,words);
  }
}
