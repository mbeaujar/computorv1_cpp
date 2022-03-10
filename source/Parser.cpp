#include "Parser.hpp"

bool isOperator(char c) { return c == '+' || c == '-' || c == '*'; }

bool isCharacterValid(char c) {
  return isOperator(c) || isdigit(c) || isspace(c) || c == 'X' || c == '=' ||
         c == '^' || c == 'x' || c == 0;
}

Parser::Parser(std::string eq) : _left(NONE), _first(), _second(), _degree(1) {
  bool firstMember = true;
  bool isOnOperator = false;

  for (size_t i = 0; i < eq.length(); i++) {
    if (isOperator(eq[i])) {
      if (_left == NONE && eq[i] != '-' && _first.size() == 0)
        throw InvalidFormatEntry("Invalid operator at the beginning");
      if (isOnOperator == true)
        throw InvalidFormatEntry("Invalid format (no term between operators)");
      setOperator(eq[i]);
      isOnOperator = true;
    }
    if (isdigit(eq[i])) {
      if (firstMember)
        parseTerm(_first, eq, i);
      else
        parseTerm(_second, eq, i);
      isOnOperator = false;
    }
    if (eq[i] == 'X' || eq[i] == 'x') {
      int power = parsePower(eq, ++i);
      if (firstMember)
        _first.push_back(Term(_left, 1, power));
      else
        _second.push_back(Term(_left, 1, power));
      isOnOperator = false;
    }
    if (eq[i] == '=') {
      if (_first.size() == 0)
        throw InvalidFormatEntry("Invalid format (first member empty)");
      if (isOnOperator == true)
        throw InvalidFormatEntry("Invalid format (no term between operators)");
      if (!firstMember) throw InvalidFormatEntry("Too many equal");
      firstMember = false;
      _left = NONE;
      isOnOperator = false;
    }
    if (!isCharacterValid(eq[i])) throw InvalidFormatEntry("Invalid character");
  }
  if (isOnOperator == true)
    throw InvalidFormatEntry("Invalid operator at the end");
  if (firstMember == true)
    throw InvalidFormatEntry("Invalid format (equal sign missing)");

  // Member::iterator it = _first.begin(), ite = _first.end();
  // while (it != ite) {
  //   std::cout << *it << " ";
  //   ++it;
  // }
  // std::cout << "= ";
  // it = _second.begin(), ite = _second.end();
  // while (it != ite) {
  //   std::cout << *it << " ";
  //   ++it;
  // }
  // std::cout << std::endl;
}

Parser::~Parser() {}

void Parser::setOperator(char c) {
  switch (c) {
    case '+':
      _left = PLUS;
      break;
    case '-':
      _left = MINUS;
      break;
    // case '/':
    //   _left = DIV;
    //   break;
    case '*':
      _left = MUL;
      break;
    default:
      throw InvalidFormatEntry("Invalid Character");
  }
}

size_t skip_number(std::string& eq, size_t i) {
  int point = 0;
  size_t j = 0;

  while (i + j < eq.length() && (isdigit(eq[i + j]) || eq[i + j] == '.')) {
    if (eq[i + j] == '.') {
      if (j == 0 || i + j + 1 == eq.length() ||
          isdigit(eq[i + j + 1]) == false || point > 0)
        throw Parser::InvalidFormatEntry("Invalid character in float number");
      point++;
    }
    j++;
  }
  return i + j;
}

void Parser::parseTerm(Member& side, std::string& eq, size_t& i) {
  size_t after_nb = skip_number(eq, i);
  double value = std::stod(eq.substr(i, after_nb - i), &after_nb);
  int power = 0;
  bool isOnOperator = false;

  if (i + after_nb < eq.length()) {
    for (size_t j = i + after_nb; j < eq.length(); j++) {
      if (eq[j] == '/') {
        j++;
        if (eq[j] && !isdigit(eq[j]))
          throw InvalidFormatEntry("Invalid character after '/'");
        if (!eq[j]) break;
        size_t after_deno = skip_number(eq, j);
        double denominator =
            std::stod(eq.substr(j, after_deno - j), &after_deno);
        std::cout << "value: " << value << std::endl;
        std::cout << "denorminator: " << value << std::endl;
        if (value != 0) value /= denominator;
        j += after_deno;
      }
      if (!isCharacterValid(eq[j]))
        throw InvalidFormatEntry("Invalid character in term");
      if (isOperator(eq[j]) || eq[j] == '=') {
        if (isOnOperator == true)
          throw InvalidFormatEntry(
              "Invalid format (no term between operators)");
        isOnOperator = true;
        if (eq[j] != '*') {
          i = j - 1;
          break;
        } else {
          size_t c = j + 1;
          while (c < eq.length() && isspace(eq[c])) c++;
          if (eq[c] == '*')
            throw InvalidFormatEntry(
                "Invalid format (no term between operators)");
          if (eq[c] != 'X' && eq[c] != 'x') {
            i = j - 1;
            break;
          }
        }
      }

      if (eq[j] == 'X' || eq[j] == 'x') {
        power = parsePower(eq, ++j);
        i = j;
        break;
      }
    }
  } else {
    i += after_nb;
  }
  if (power > _degree) _degree = power;
  side.push_back(Term(_left, value, power));
}

int Parser::parsePower(std::string& eq, size_t& i) {
  size_t after_nb;
  int power = 1;

  if (i < eq.length() && eq[i] == '^') {
    ++i;
    if (i == eq.length() || !isdigit(eq[i]))
      throw InvalidFormatEntry("Invalid format (expect digit after ^)");
    after_nb = skip_number(eq, i);
    power = std::stoi(eq.substr(i, after_nb - i), &after_nb);
    i += after_nb;
    return power;
  }
  return power;
}

Member& Parser::getFirst() { return _first; }

Member& Parser::getSecond() { return _second; }

int Parser::getDegree() const { return _degree; }
