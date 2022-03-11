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
  findDegreeMax();
  std::cout << "Polynomial Degree: " << _degree << std::endl;
}

void Solver::solve() {
  if (_degree == 1) {
    firstDegreeOrLower();
  } else if (_degree == 2) {
    secondDegree();
  } else if (_degree > 2) {
    std::cout
        << "The polynomial degree is strictly greater than 2, I can't solve."
        << std::endl;
  }
}

void Solver::firstDegreeOrLower() {
  double a = findNumberWithPower(1);
  double b = findNumberWithPower(0);

#if BONUS
  std::cout << "a	= " << a << std::endl;
  std::cout << "b	= " << b << std::endl;
#endif

  if (b != 0) {
    if (a != 0) {
      std::cout << "The solution is:" << std::endl;
#if BONUS
      std::cout << "x	= -b/a" << std::endl;
      std::cout << "x	= ";
      if (b == int(b) && a == int(a)) {
        displayFractions(-b, a);
        std::cout << std::endl;
        return;
      }
#endif
      std::cout << (-b / a) << std::endl;
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
}

void Solver::secondDegreeNeutral(double b, double denumerator) {
  double numerator = -b;

  std::cout << "Discriminant is neutral, the solution is:" << std::endl;
#if BONUS
  std::cout << "x0	= -b/2a" << std::endl;
  std::cout << "x0	= ";
  if (numerator == int(numerator) && denumerator == int(denumerator)) {
    displayFractions(numerator, denumerator);
    return;
  }
#endif
  std::cout << (numerator / denumerator);
  std::cout << std::endl;
}

void displayFormulasPositive(int nb, char sign, double b, double delta,
                             double denum) {
  std::cout << "x" << nb << "	= (-b " << sign << " √delta)/2a" << std::endl;
  std::cout << "x" << nb << "	= (" << -b << " " << sign << " " << delta
            << ")/" << denum << std::endl;
  std::cout << "x" << nb << "	= ";
}

void Solver::secondDegreePositive(double b, double delta, double denumerator) {
  double squareRootDelta = mysqrt(delta);
  double secondNumerator = -b - squareRootDelta;
  double numerator = -b + squareRootDelta;

  std::cout << "Discriminant is strictly positive, the two solutions are:"
            << std::endl;
#if BONUS
  displayFormulasPositive(1, '+', b, squareRootDelta, denumerator);
  if (numerator == int(numerator) && denumerator == int(denumerator) &&
      secondNumerator == int(secondNumerator)) {
    displayFractions(numerator, denumerator);
    std::cout << std::endl << std::endl;
    displayFormulasPositive(2, '-', b, squareRootDelta, denumerator);
    displayFractions(secondNumerator, denumerator);
    std::cout << std::endl;
    return;
  }
#endif
  std::cout << (numerator / denumerator) << std::endl;
#if BONUS
  std::cout << std::endl;
  displayFormulasPositive(2, '-', b, squareRootDelta, denumerator);
#endif
  std::cout << (secondNumerator / denumerator) << std::endl;
}

void displayFormulasNegative(int nb, char sign, double b, double delta,
                             double denum) {
  std::cout << "x" << nb << "	= (-b " << sign << " i√-delta)/2a" << std::endl;
  std::cout << "x" << nb << "	= (" << -b << " " << sign << " i√" << -delta
            << ")/" << denum << std::endl;
  std::cout << "x" << nb << "	= ";
}

void Solver::secondDegreeNegative(double b, double delta, double denumerator) {
  double numerator = -b;
  double realPart = numerator / denumerator;
  double imaginaryPart = mysqrt(-delta) / denumerator;

  std::cout
      << "Discriminant is strictly negative, the two complex solutions are:"
      << std::endl;
#if BONUS
  if (numerator == int(numerator) && denumerator == int(denumerator)) {
    displayFormulasNegative(1, '+', b, delta, denumerator);
    if (realPart != 0) {
      displayFractions(numerator, denumerator);
      std::cout << " + ";
    }
    std::cout << "i * " << imaginaryPart << std::endl;
    std::cout << std::endl;
    displayFormulasNegative(2, '-', b, delta, denumerator);
    if (realPart != 0) displayFractions(numerator, denumerator);
    std::cout << " - i * " << imaginaryPart << std::endl;
  }
#else
  if (realPart != 0) std::cout << realPart << " + ";
  std::cout << "i * " << imaginaryPart << std::endl;
  if (realPart != 0) std::cout << realPart;
  std::cout << " - i * " << imaginaryPart << std::endl;
#endif
}

void Solver::secondDegree() {
  double a = findNumberWithPower(2);
  double b = findNumberWithPower(1);
  double c = findNumberWithPower(0);
  double denumerator = (2 * a);
  double delta = ((b * b) - ((4 * a) * c));

#if BONUS
  std::cout << "a		= " << a << std::endl;
  std::cout << "b		= " << b << std::endl;
  std::cout << "c		= " << c << std::endl;
  std::cout << "Discriminant 	= b² - 4ac " << std::endl;
  std::cout << "		= " << b << "² - 4 * " << a << " * " << c
            << std::endl;
  std::cout << "		= " << (b * b) << " - " << ((4 * a) * c)
            << std::endl;
  std::cout << "		= " << ((b * b) - ((4 * a) * c)) << std::endl;
#endif

  if (delta == 0) {
    secondDegreeNeutral(b, denumerator);
  } else if (delta > 0)
    secondDegreePositive(b, delta, denumerator);
  else if (delta < 0)
    secondDegreeNegative(b, delta, denumerator);
}

void Solver::displayFractions(double numerator, double denumerator) {
  if ((numerator == 0 || denumerator == 0) || denumerator == 1) {
    std::cout << numerator / denumerator;
    return;
  }
  if (numerator < 0 && denumerator < 0) {
    numerator *= -1;
    denumerator *= -1;
  }
  double factor = denumerator / numerator;
  if (abs(numerator) < abs(denumerator)) {
    double num = numerator > 0 ? 1 : -1;
    while (num != numerator) {
      double den = num * factor;
      if (num == int(num) && den == int(den)) {
        numerator = num;
        denumerator = den;
        break;
      }
      if (numerator > 0)
        num++;
      else
        num--;
    }
  } else {
    double den = denumerator > 0 ? 1 : -1;
    while (den != denumerator) {
      double num = den / factor;
      if (num == int(num) && den == int(den)) {
        numerator = num;
        denumerator = den;
        break;
      }
      if (denumerator > 0)
        den++;
      else
        den--;
    }
  }
  if (denumerator != 1)
    std::cout << numerator << "/" << denumerator;
  else
    std::cout << numerator / denumerator;
}

void Solver::simplifyOperators(Member& side) {
  Member::iterator it = side.begin(), ite = side.end();

  while (it != ite) {
    if (it->left == MUL) {
      Member::iterator tmp = it + 1, target = it - 1;

      target->value *= it->value;
      target->power += it->power;
      it->value = 0;
      if (tmp != ite && tmp->left == MUL) {
        while (tmp != ite && tmp->left == MUL) {
          target->value *= tmp->value;
          target->power += tmp->power;
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

void Solver::findDegreeMax() {
  Member::iterator it = _first.begin(), ite = _first.end();

  while (it != ite) {
    if (it->power > _degree) _degree = it->power;
    ++it;
  }
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