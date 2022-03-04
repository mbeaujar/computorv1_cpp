#include <vector>

#include "Solver.hpp"

int main() {
  Solver *a = new Solver();
  std::string eq = "5.6 * X^1 + 0 * X^0 = 0 * X^0";
  a->parseEquation(eq);
  a->displayEquation();
  delete a;
  return 0;
}