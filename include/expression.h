#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <string>

#include "queue.h"
#include "stack.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

class Expression {
 private:
  Queue<char> infixed;
  Queue<char> postFixed;
  Stack<char> myStack;

 public:
  Expression();
  void getInfixed();
  void convertInfixedToPostfixed();
  // This function checks if the char is an operator
  bool isOperator(char element);
  // This function creates and operates the stack of operators
  void createStack(char element);
  // This function checks and evaluates the precedence of the operators
  // as they don't correspond with the ASCII given
  int precedence(char element);
  void print();
  //  This function fills a string with all the postfixed data while erases
  //  all the data from the postfixed queue
  string toString();
};

#endif  // EXPRESSION_H
