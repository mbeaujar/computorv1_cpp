#include <limits.h>
#include <stdio.h>

#include <iostream>

double mysqrt(double num) {
  double res = num, precision = 0.0000000001;
  while (abs(num - res * res) > precision) res = (res + (num / res)) / 2;
  return res;
}

int main() {
  std::cout << mysqrt(2) << std::endl;
  return 0;
}