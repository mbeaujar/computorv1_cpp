#include "Solver.hpp"

Solver::Solver(Member& first, Member& second, int degree)
    : _first(first), _second(second), _degree(degree) {}

Solver::~Solver() {}

void Solver::reduceForm() {
  simplifyOperators(_first);
  simplifyOperators(_second);
  shiftSecondToFirst();
  eraseDuplicates();
  if (_first.size() > 0 && _first[0].left != MINUS) _first[0].left = NONE;
  std::cout << "Reduced form: ";
  Member::iterator it = _first.begin(), ite = _first.end();

  if (it != ite) {
    while (it != ite) {
      std::cout << *it << " ";
      ++it;
    }
  } else {
    std::cout << "0 ";
  }
  std::cout << "= 0" << std::endl;
}

void Solver::degree() {
  std::cout << "Polynomial Degree: " << _degree << std::endl;
}

void Solver::solve() {
  if (_degree == 1) {
    double a = findNumberWithPower(1);
    double b = findNumberWithPower(0);

    if (b != 0) {
      if (a != 0) {
        std::cout << "The solution is:" << std::endl;
        std::cout << ((b * -1) / a) << std::endl;
      } else {
        std::cout << "The equation has no solution" << std::endl;
      }
    } else {
      if (a != 0) {
        std::cout << "The solution is:" << std::endl;
        std::cout << "0" << std::endl;
      } else {
        std::cout << "The equation has an infinitely number of solutions"
                  << std::endl;
      }
    }
  } else if (_degree == 2) {
    double a = findNumberWithPower(2);
    double b = findNumberWithPower(1);
    double c = findNumberWithPower(0);
    double delta = ((b * b) - ((4 * a) * c));

    if (delta == 0) {
      std::cout << "Discriminant is neutral, the solution is:" << std::endl;
      std::cout << ((-b / (2 * a))) << std::endl;
    } else if (delta > 0) {
      std::cout << "Discriminant is strictly positive, the two solutions are:"
                << std::endl;
      std::cout << ((-b - mysqrt(delta)) / (2 * a)) << std::endl;
      std::cout << ((-b + mysqrt(delta)) / (2 * a)) << std::endl;
    } else if (delta < 0) {
      double realPart = -b / (2 * a);
      double imaginaryPart = mysqrt(-delta) / (2 * a);

      std::cout
          << "Discriminant is strictly negative, the two complex solutions are:"
          << std::endl;
      std::cout << realPart << " + i * " << imaginaryPart << std::endl;
      std::cout << realPart << " - i * " << imaginaryPart << std::endl;
    }
  } else if (_degree > 2) {
    std::cout
        << "The polynomial degree is strictly greater than 2, I can't solve."
        << std::endl;
  }
}

// 1 * 2 * 2 * 2

// 1 * 2 + 5

void Solver::simplifyOperators(Member& side) {
  Member::iterator it = side.begin(), ite = side.end();

  while (it != ite) {
    if (it->left == MUL) {
      Member::iterator tmp = it + 1, target = it - 1;

      target->value *= it->value;
      it->value = 0;
      if (tmp != ite && tmp->left == MUL) {
        while (tmp != ite && tmp->left == MUL) {
          target->value *= tmp->value;
          tmp->value = 0;
          ++tmp;
        }
      }
    }
    ++it;
  }
}

void Solver::eraseDuplicates() {
  Member::iterator it = _first.begin(), ite = _first.end();
  int power = -1;

  while (it != ite) {
    power = it->power;
    Member::iterator tmp = it + 1;
    while (tmp != ite) {
      if (tmp->power == power && tmp->value != 0) {
        double first = it->value;
        if (it->left == MINUS) first = it->value * -1;
        if (tmp->left == MINUS) {
          it->value = first - tmp->value;
          if (it->value < 0 && it->left == PLUS) {
            it->value *= -1;
            it->left = MINUS;
          }
        } else if (tmp->left == PLUS)
          it->value = first + tmp->value;
        tmp->value = 0;
      }
      ++tmp;
    }
    ++it;
  }
  it = _first.begin(), ite = _first.end();
  while (it != ite) {
    if (it->value == 0) {
      it = _first.erase(it);
      ite = _first.end();
    } else
      ++it;
  }
}

void Solver::shiftSecondToFirst() {
  Member::iterator it = _second.begin(), ite = _second.end();

  while (it != ite) {
    if (it->left == PLUS || it->left == NONE)
      it->left = MINUS;
    else if (it->left == MINUS)
      it->left = PLUS;
    else if (it->left == DIV)
      it->left = MUL;
    else if (it->left == MUL)
      it->left = DIV;
    _first.push_back(*it);
    ++it;
  }
  _second.clear();
}

double Solver::findNumberWithPower(int power) {
  Member::iterator it = _first.begin(), ite = _first.end();

  while (it != ite) {
    if (it->power == power) {
      if (it->left == MINUS)
        return it->value * -1;
      else
        return it->value;
    }
    ++it;
  }
  return 0;
}

double Solver::mysqrt(double num) {
  double res = num, precision = 0.0000000001;
  while (abs(num - res * res) > precision) res = (res + (num / res)) / 2;
  return res;
}