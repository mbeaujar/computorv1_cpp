#include "Parser.hpp"

bool isOperator(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }

bool isCharacterValid(char c) {
  return isOperator(c) || isdigit(c) || isspace(c) || c == 'X' || c == '=' ||
         c == '^';
}

Parser::Parser(std::string eq) : _first(), _second() {
  _left = NONE;
  bool firstMember = true;

  for (size_t i = 0; i < eq.length(); i++) {
    if (isOperator(eq[i])) setOperator(eq[i]);
    if (isdigit(eq[i])) {
      if (firstMember)
        parseTerm(_first, eq, i);
      else
        parseTerm(_second, eq, i);
    }
    if (eq[i] == '=') {
      if (!firstMember)
        throw std::invalid_argument('format of the equation invalid');
      firstMember = false;
      _left = NONE;
    }
    if (!isCharacterValid(eq[i]))
      throw std::invalid_argument('invalid character');
  }
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
    case '/':
      _left = DIV;
      break;
    case '*':
      _left = MUL;
      break;
    default:
      throw std::invalid_argument('character not valid');
  }
}

size_t skip_number(std::string& eq, size_t i) {
  while (i < eq.length() && isspace(eq[i]) == false) i++;
  return i;
}

void Parser::parseTerm(Member& side, std::string& eq, size_t& i) {
  size_t after_nb = skip_number(eq, i);
  double value = std::stod(eq.substr(i, after_nb - i), &after_nb);

  for (size_t j = i; j < eq.length(); j++) {
  }
}

void Parser::createTerm() {}