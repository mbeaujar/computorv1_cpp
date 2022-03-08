#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include <deque>
#include <sstream>
#include <string>

#include "Term.hpp"

#define Member std::deque<Term>

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

  Member& getFirst();
  Member& getSecond();
  int getDegree() const;

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
