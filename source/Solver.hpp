#ifndef _SOLVER_HPP_
#define _SOLVER_HPP_

#include <deque>
#include <iostream>
#include <string>

#include "Term.hpp"

class Solver {
 public:
  Solver();
  ~Solver();

  size_t skip_number(std::string&, size_t);
  void parseTerm(std::deque<Term>&, Operators, std::string&, size_t&);
  void parseEquation(std::string&);

  void displayEquation();

 private:
  std::deque<Term> _left;
  std::deque<Term> _right;
};

#endif  // _SOLVER_HPP_