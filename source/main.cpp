#include <vector>

#include "Parser.hpp"
#include "Solver.hpp"

#define SUCCESS 0
#define FAILURE 1

int main(int argc, char **argv) {
  if (argc == 2) {
    // Solver *computor;
    Parser *parsing;

    try {
      parsing = new Parser(argv[1]);
    } catch (const std::exception &e) {
      std::cout << "Error: " << e.what() << std::endl;
      return FAILURE;
    }
    // try {
    //   computor = new Solver();
    // } catch (const std::exception &e) {
    //   std::cout << "Error: " << e.what() << std::endl;
    //   return FAILURE;
    // }
    // computor->parseEquation(argv[1]);
    // computor->reduceForm();
    // computor->solve();
    // delete computor;
    // return SUCCESS;
  } else {
    std::cout << "Error: wrong number of arguments" << std::endl;
  }
  return FAILURE;
}