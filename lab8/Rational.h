#include <iostream>;
//namespace CS2124{

  class Rational{
  public:
    Rational();
    Rational(int value);
    Rational(int num, int denom);
    operator bool() const;
    
    Rational& operator+=(const Rational rhs);
    Rational& operator++();
    Rational operator++(int);
  };
  
  std::ostream& operator<<(std::ostream& os, const Rational& R);
  std::istream& operator>>(std::istream& is, Rational& R);
  Rational operator+(Rational lhs, const Rational& rhs);
  
  bool operator==(const Rational& lhs, const Rational& rhs);
  bool operator==(int lhs, const Rational& rhs);
  bool operator!=(const Rational&lhs, const Rational& rhs);
  
  Rational& operator--(Rational& R);
  Rational operator--(Rational& R, int);
//}
