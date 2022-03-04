#ifndef _TERM_HPP_
#define _TERM_HPP_

#include <iostream>

enum Operators { PLUS, MINUS, MUL, DIV, NONE };

class Term {
 public:
  Term();
  Term(Operators, double, int);
  ~Term();

  Operators left;
  double value;
  int power;
};

std::ostream& operator<<(std::ostream&, const Term&);

#endif  // _TERM_HPP_