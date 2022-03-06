#ifndef _SOLVER_HPP_
#define _SOLVER_HPP_

#include <cmath>
#include <deque>
#include <iostream>
#include <string>

#include "Term.hpp"

#define Member std::deque<Term>

class Solver {
 public:
  Solver();
  ~Solver();

  size_t skip_number(std::string&, size_t);
  void parseTerm(Member&, Operators, std::string&, size_t&);
  void parseEquation(std::string);
  void iterateEquation(Member&, void (Solver::*f)(Member::iterator&));
  void displayTerm(Member::iterator&);
  void searchDegree(Member::iterator&);
  void displayEquation();

  double findNumberWithPower(int);
  void eraseDuplicates();
  void shiftToFirst();
  void reduceForm();
  void solveFirstDegree();
  void solveSecondDegree();
  void solve();

 private:
  int _degree;
  Member _first;
  Member _second;
};

#endif  // _SOLVER_HPP_