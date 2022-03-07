#ifndef _PARSER_HPP_
#define _PARSER_HPP_

// #include <ctype>
#include <deque>
#include <sstream>
#include <string>

#include "Term.hpp"

#define Member std::deque<Term>

// Entries:
// 5 -> 5 * X^0
// 4 * X -> 4 * X^1
// X^2 -> 1 * X^2

// 1 Example
// 5 + 4 * X + X^2= X^2

// 2 Example
// 5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0

// 3 Example
// - 3 * X^2 + 5 * X^1 = 1 * X^0

// 5 + x * 2 = 20
// 5 + x = 10

class Parser {
 public:
  Parser(std::string);
  ~Parser();

  void setOperator(char);
  void parseTerm(Member&, std::string&, size_t&);
  int parsePower(std::string&, size_t&);

  class InvalidFormatEntry : public std::exception {
   public:
    InvalidFormatEntry(const char* reason) : _reason(reason) {}
    virtual const char* what() const throw() { return _reason; }

   private:
    const char* _reason;
  };

 private:
  Operators _left;
  Member _first;
  Member _second;
  int _degree;
};

template <typename T>
std::string toString(T a) {
  std::ostringstream ss;
  ss << a;
  return ss.str();
}

#endif  // _PARSER_HPP_
