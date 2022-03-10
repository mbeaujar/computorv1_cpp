#ifndef _SOLVER_HPP_
#define _SOLVER_HPP_

#include "Parser.hpp"

class Solver {
 public:
  Solver(Member& first, Member& second, int degree);
  ~Solver();

  void reduceForm();
  void degree();
  void solve();

 private:
  Member& _first;
  Member& _second;
  int _degree;

	void firstDegreeOrLower();
	void secondDegree();
  void displayFractions(double numerator, double denumerator);
  void simplifyOperators(Member& side);
  void eraseDuplicates();
  void shiftSecondToFirst();
  void findDegreeMax();
  double findNumberWithPower(int power);
  double mysqrt(double num);
};

#endif  // _SOLVER_HPP_