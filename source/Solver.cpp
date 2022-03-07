#include "Solver.hpp"

Solver::Solver() : _degree(1), _first(), _second() {}

Solver::~Solver() {}

size_t Solver::skip_number(std::string& eq, size_t i) {
  while (i < eq.length() && isspace(eq[i]) == false) i++;
  return i;
}

void Solver::parseTerm(Member& l, Operators left, std::string& eq, size_t& i) {
  size_t j = skip_number(eq, i);

  double number = std::stod(eq.substr(i, j - i), &j);
  i += j;
  while (i < eq.length() && !(eq[i] >= '0' && eq[i] <= '9')) i++;
  j = skip_number(eq, i);
  int power = std::stoi(eq.substr(i, j - i), &j);
  i += j;
  // if (left == MINUS && number < 0) {
  //   left = PLUS;
  //   number *= -1;
  // }
  l.push_back(Term(left, number, power));
}

void Solver::parseEquation(std::string eq) {
  Operators left = NONE;
  bool firstSide = true;

  for (size_t i = 0; i < eq.length(); i++) {
    if (eq[i] >= '0' && eq[i] <= '9') {
      if (firstSide)
        parseTerm(_first, left, eq, i);
      else
        parseTerm(_second, left, eq, i);
    }
    if (eq[i] == '=') {
      if (firstSide == false) {
        throw std::exception();
      }
      firstSide = false;
      left = NONE;
    }
    if (eq[i] == '+') left = PLUS;
    if (eq[i] == '-') left = MINUS;
    if (eq[i] == '*') left = MUL;
    if (eq[i] == '/') left = DIV;
  }
  iterateEquation(_first, &Solver::searchDegree);
  iterateEquation(_second, &Solver::searchDegree);
}

void Solver::iterateEquation(Member& side,
                             void (Solver::*f)(Member::iterator&)) {
  Member::iterator it = side.begin(), ite = side.end();
  while (it != ite) {
    (this->*f)(it);
    ++it;
  }
}

void Solver::displayTerm(Member::iterator& it) {
  std::cout << *it;
  if (it + 1 != _second.end()) std::cout << " ";
}

void Solver::searchDegree(Member::iterator& it) {
  if (it->power > _degree) _degree = it->power;
}

void Solver::displayEquation() {
  iterateEquation(_first, &Solver::displayTerm);
  std::cout << "= ";
  iterateEquation(_second, &Solver::displayTerm);
  std::cout << std::endl;
}

double buildNumber(Operators& left, double value) {
  if (left == MINUS) return value * -1;
  return value;
}

void Solver::eraseDuplicates() {
  Member::iterator it = _first.begin(), ite = _first.end();
  int power = -1;

  while (it != ite) {
    power = it->power;
    Member::iterator tmp = it + 1;
    while (tmp != ite) {
      if (tmp->power == power && tmp->value != 0) {
        std::cout << "left is minus: " << (it->left == MINUS) << std::endl;
        std::cout << "value: " << it->value << std::endl;
        double first = buildNumber(it->left, it->value);
        if (tmp->left == MINUS) {
          it->value = first - tmp->value;
          if (it->value < 0) {
            it->value *= -1;
            it->left = PLUS;
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

void Solver::shiftToFirst() {
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

void Solver::reduceForm() {
  std::cout << "Reduced form: ";
  shiftToFirst();
  // eraseDuplicates();
  iterateEquation(_first, &Solver::displayTerm);
  if (_first.size() == 0) std::cout << "0 ";
  std::cout << "= 0" << std::endl;
  std::cout << "Polynomial Degree: " << _degree << std::endl;
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

void Solver::solveFirstDegree() {
  double a, b;
  a = findNumberWithPower(1);
  b = findNumberWithPower(0);
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
}

double calculDiscriminant(double a, double b, double c) {
  return ((b * b) - ((4 * a) * c));
}

void discriminantPositive(double a, double b, double delta) {
  std::cout << "Discriminant is strictly positive, the two solutions are:"
            << std::endl;
  std::cout << ((-b - sqrt(delta)) / (2 * a)) << std::endl;
  std::cout << ((-b + sqrt(delta)) / (2 * a)) << std::endl;
}

void discriminantNeutral(double a, double b) {
  std::cout << "Discriminant is neutral, the solution is:" << std::endl;
  std::cout << ((-b / (2 * a))) << std::endl;
}

void discriminantNegative(double a, double b, double delta) {
  double realPart, imaginaryPart;

  realPart = -b / (2 * a);
  imaginaryPart = sqrt(-delta) / (2 * a);
  std::cout
      << "Discriminant is strictly negative, the two complex solutions are:"
      << std::endl;
  std::cout << realPart << " + i * " << imaginaryPart << std::endl;
  std::cout << realPart << " - i * " << imaginaryPart << std::endl;
}

void Solver::solveSecondDegree() {
  double a, b, c;
  a = findNumberWithPower(2);
  b = findNumberWithPower(1);
  c = findNumberWithPower(0);
  double delta = calculDiscriminant(a, b, c);
  if (delta == 0) discriminantNeutral(a, b);
  if (delta > 0) discriminantPositive(a, b, delta);
  if (delta < 0) discriminantNegative(a, b, delta);
}

void Solver::solve() {
  if (_degree == 1)
    solveFirstDegree();
  else if (_degree == 2)
    solveSecondDegree();
  else
    std::cout
        << "The polynomial degree is strictly greater than 2, I can't solve."
        << std::endl;
}