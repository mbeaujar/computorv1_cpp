#include "Solver.hpp"

Solver::Solver() : _left(), _right() {}

Solver::~Solver() {}

size_t Solver::skip_number(std::string& eq, size_t i) {
  while (i < eq.length() && isspace(eq[i]) == false) i++;
  return i;
}

void Solver::parseTerm(std::deque<Term>& l, Operators left, std::string& eq,
                       size_t& i) {
  size_t j = skip_number(eq, i);

  double number = std::stod(eq.substr(i, j - i), &j);
  i += j;
  while (i < eq.length() && !(eq[i] >= '0' && eq[i] <= '9')) i++;
  j = skip_number(eq, i);
  int power = std::stoi(eq.substr(i, j - i), &j);
  i += j;
  l.push_back(Term(left, number, power));
}

void Solver::parseEquation(std::string& eq) {
  Operators left = NONE;
  bool leftSide = true;
  for (size_t i = 0; i < eq.length(); i++) {
    if (eq[i] >= '0' && eq[i] <= '9') {
      if (leftSide)
        parseTerm(_left, left, eq, i);
      else
        parseTerm(_right, left, eq, i);
    }
    if (eq[i] == '=') {
      if (leftSide == false) {
        throw std::exception();
      }
      leftSide = false;
      left = NONE;
    }
    if (eq[i] == '+') left = PLUS;
    if (eq[i] == '-') left = MINUS;
    if (eq[i] == '*') left = MUL;
    if (eq[i] == '/') left = DIV;
  }
}

void Solver::displayEquation() {
  std::deque<Term>::iterator it = _left.begin(), ite = _left.end();
  while (it != ite) {
    std::cout << *it << " ";
    ++it;
  }
  std::cout << "= ";
  it = _right.begin(), ite = _right.end();
  while (it != ite) {
    std::cout << *it;
    ++it;
    if (it != ite) std::cout << " ";
  }
  std::cout << std::endl;
}