#include "Term.hpp"

Term::Term() : left(NONE), value(0), power(0) {}

Term::Term(Operators left, double value, int power)
    : left(left), value(value), power(power) {}

Term::~Term() {}

std::ostream& operator<<(std::ostream& o, const Term& rhs) {
  if (rhs.left == PLUS) o << "+";
  if (rhs.left == MINUS) o << "-";
  if (rhs.left == MUL) o << "*";
  if (rhs.left == DIV) o << "/";
  if (rhs.left != NONE) o << " ";
  o << rhs.value << " * X^" << rhs.power;
  return o;
}