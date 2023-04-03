#include "expression.h"

Expression::Expression() {}

void Expression::getInfixed() {
  string infixedString;
  char infixedChar[500];
  cout << "\n\tIntroduce the infixed operation: ";
  cin >> infixedString;
  // Copies the string to an array of char in order to introduce one
  // \n character to be checked as the end of line char
  int i = 0, j = 0;
  while (i < infixedString.size()) {
    infixedChar[i] = infixedString[i];
    i++;
  }
  infixedChar[i] = '\n';
  j = i;
  i = 0;
  while (i <= j) {
    infixed.enqueue(infixedChar[i]);
    i++;
  }
}

void Expression::convertInfixedToPostfixed() {
  while (!(infixed.isEmpty())) {
    //  Checks if the front element of the infix queue is operator
    if (isOperator(infixed.front())) {
      createStack(infixed.front());
    } else {
      //        Adds operand to the postfixed queue
      postFixed.enqueue(infixed.front());
    }
    //  Dequeues the front element of the infix queue
    infixed.dequeue();
  }
}

bool Expression::isOperator(char element) {
  if ((element == '(') || (element == ')') || (element == '-') ||
      (element == '+') || (element == '*') || (element == '/') ||
      (element == '^') || (element == '\n'))
    return true;
  return false;
}

void Expression::createStack(char element) {
  switch (element) {
    case '(':
      myStack.push(element);
      break;
    case '\n':
      while (!(myStack.isEmpty())) {
        // Takes out every operator left in the stack
        postFixed.enqueue(myStack.top());
        myStack.pop();
      }
      break;
    case ')':
      while (!((myStack.isEmpty()) || (myStack.top() == '('))) {
        // Takes out all the operators in the stack until it finds an opening
        // parentheses
        postFixed.enqueue(myStack.top());
        myStack.pop();
      }
      // Once the opening parentheses is found it's popped out of the stack
      myStack.pop();
      break;
    default:
      if (myStack.isEmpty())
        // It introduces the first operator to the stack
        myStack.push(element);
      else {
        while (!myStack.isEmpty()) {
          if ((precedence(myStack.top()) >= precedence(element)) &&
              (myStack.top() != '(')) {
            // This compares the precedence of the introduced element with the
            // top of the stack, if it is lower, it pops out of the stack and
            // introduces it to the queue
            postFixed.enqueue(myStack.top());
            myStack.pop();
          } else
            // if it doesn't correspond just is pushed on the stack
            break;
        }
        myStack.push(element);
      }
      break;
  }
}

int Expression::precedence(char element) {
  if (element == '+' || element == '-')
    return 1;
  else if (element == '*' || element == '/')
    return 2;
  else if (element == '^')
    return 3;
  else if (element == '(' || element == ')')
    return 4;
  else
    return -1;
}

string Expression::toString() {
  string result;
  while (!postFixed.isEmpty()) {
    result += postFixed.front();
    postFixed.dequeue();
  }
  return result;
}

void Expression::print() {
  char option;
  do {
    system("cls");
    getInfixed();
    convertInfixedToPostfixed();
    cout << "\n\tThe operation in its postfixed way is: " << toString() << endl;
    cout << "\n\n\tDo you want to make another conversion?"
            "\n\t\ty -> Yes"
            "\n\t\tn -> No"
            "\n\t\t\t-> ";
    cin >> option;
  } while (option != 'n');
}
