#include <string>;
#include <iostream>;
#include <vector>;
#include <fstream>;
using namespace std;
//namespace CS2124{
  class Rational{
  public:
    Rational(): numerator(0), denominator(1){  }
    Rational(int value): numerator(value),denominator(1){}
    Rational(int num, int denom): numerator(num),denominator(denom){
      normalize();
    }
    operator bool() const{
      return numerator != 0;
    }
    
    friend ostream& operator<<(ostream& os, const Rational& R);
    friend istream& operator>>(istream& is, Rational& R);
    friend bool operator==(const Rational& lhs, const Rational& rhs);
    
    Rational& operator+=(const Rational rhs){
      int othernum = rhs.numerator * denominator;
      
      numerator = (numerator*rhs.denominator )+ othernum;
      denominator *= rhs.denominator;
      normalize();
      return *this;
    }
    
    Rational& operator++(){
      operator+=(Rational(1));
      return *this;
    }
    Rational operator++(int){
      Rational dummy(numerator, denominator);
      operator+=(Rational(1));
      return dummy;
    }
    
  private:
    void normalize(){
      if( numerator == 0 || denominator == 0){
	numerator = 0;
	denominator = 1;
	return;
      }
      
      if( (numerator < 0 && denominator < 0 ) ||
	  (numerator > 0 && denominator < 0)){
	numerator *= -1;
	denominator *= -1;
      }
      //  cout << "normalizing" << endl << endl;
      vector<int> denomFactors;
      for( int i = denominator/2;i>0;--i){
	//cout << numerat % i << endl;
	if(denominator % i == 0){
	  denomFactors.push_back(i);
	}
      }
      for(int factor: denomFactors){
	//cout << factor << endl;
      }
      for(int curr : denomFactors){
	if(numerator % curr == 0){
	  numerator /= curr;
	  denominator /= curr;
	  break;
	}
      }
    }
    int numerator, denominator;
  };
  
  ostream& operator<<(ostream& os, const Rational& R){
    os << R.numerator << "/" << R.denominator;
    return os;
  }
  istream& operator>>(istream& is, Rational& R){
    string rationalInput;
    is >> rationalInput;
    int slashLocation;
    bool found = false;
    for( slashLocation = 0; slashLocation < rationalInput.length(); ++slashLocation){
      if(rationalInput[slashLocation] == '/'){
	found = true;
	break;
      }
    }
    if(!found){
      return is;
    }
    string num = rationalInput.substr(0,slashLocation);
    string denom = rationalInput.substr(slashLocation+1,rationalInput.length()-slashLocation-1);
    int numint = stoi(num);
    int denomint = stoi(denom);
    R.numerator = numint;
    R.denominator = denomint;
    //cout <<"????";
    R.normalize();
    return is;
  }
  
  Rational operator+(Rational lhs, const Rational& rhs){
    lhs += rhs;
    return lhs;
  }
  
  bool operator==(int lhs, const Rational& rhs){
    return Rational(lhs) == rhs;
  }
  bool operator==(const Rational& lhs, const Rational& rhs){
    //if(*lhs const  == *rhs const ){ return true;}
    return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
  }
  
  bool operator!=(const Rational&lhs, const Rational& rhs){
    return !(lhs==rhs);
  }
  
  Rational& operator--(Rational& R){
    R += Rational(-1);
    return R;
  }
  
  Rational operator--(Rational& R, int){
    Rational dummy(R);
    R += Rational(-1);
    return dummy;
  }
  //}
