#include <vector>

#include "Parser.hpp"
#include "Solver.hpp"

#define SUCCESS 0
#define FAILURE 1

int main(int argc, char **argv) {
  if (argc == 2) {
    Solver *computor;
    Parser *parsing;

    try {
      parsing = new Parser(argv[1]);
    } catch (const std::exception &e) {
      std::cout << "Error: " << e.what() << std::endl;
      return FAILURE;
    }
    try {
      computor = new Solver(parsing->getFirst(), parsing->getSecond(),
                            parsing->getDegree());
    } catch (const std::exception &e) {
      std::cout << "Error: " << e.what() << std::endl;
      delete parsing;
      return FAILURE;
    }
    computor->reduceForm();
    computor->degree();
    computor->solve();
    delete computor;
    delete parsing;
    return SUCCESS;
  } else {
    std::cout << "Error: wrong number of arguments" << std::endl;
  }
  return FAILURE;
}