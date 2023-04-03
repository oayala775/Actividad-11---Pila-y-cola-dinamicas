#ifndef STACK_H
#define STACK_H

#pragma once

template <typename T>
class Stack {
 private:
  class Node {
   private:
    T data;
    Node* next;

   public:
    Node();
    Node(T data);

    T getData();
    Node* getNext();

    void setData(T data);
    void setNext(Node*);
  };

 private:
  Node* anchor;

  void deleteAll();

  void copyAll(Stack& stackToCopy);

 public:
  Stack();
  Stack(Stack& copyStack);
  ~Stack();

  bool isEmpty();
  void push(T element);
  void pop();
  T top();

  Stack& operator=(const Stack& stackCopy);

 public:
  class Exception : public std::exception {
   private:
    std::string msg;

   public:
    explicit Exception(const char* message) : msg(message) {}
    explicit Exception(const std::string& message) : msg(message) {}

    virtual ~Exception() throw() {}

    virtual const char* what() const throw() { return msg.c_str(); }
  };
};

#endif

// CLASS Implementation
template <typename T>
Stack<T>::Node::Node() : next(nullptr) {}

template <typename T>
Stack<T>::Node::Node(T data) {
  next = nullptr;
  this->data = data;
}

template <typename T>
T Stack<T>::Node::getData() {
  return data;
}

template <typename T>
typename Stack<T>::Node* Stack<T>::Node::getNext() {
  return next;
}

template <typename T>
void Stack<T>::Node::setData(T data) {
  this->data = data;
}

template <typename T>
void Stack<T>::Node::setNext(Node* next) {
  this->next = next;
}

template <typename T>
Stack<T>::Stack() {
  anchor = nullptr;
}

template <typename T>
Stack<T>::Stack(Stack& copyStack) {
  Node* aux(copyStack->anchor);
  Node* last(nullptr);
  Node* newNode;

  while (aux != nullptr) {
    newNode = new Node(aux->getData());
    if (newNode == nullptr) throw Exception("\n\tOut of memory");

    if (last == nullptr)
      anchor = newNode;
    else
      last->setNext(newNode);

    last = newNode;

    aux = aux->getNext();
  }
}

template <typename T>
bool Stack<T>::isEmpty() {
  return anchor == nullptr;
}

template <typename T>
void Stack<T>::push(T element) {
  Node* aux(new Node(element));

  if (aux == nullptr) throw Exception("Insufficient memory, push()");

  aux->setNext(anchor);
  anchor = aux;
}

template <typename T>
void Stack<T>::pop() {
  if (anchor == nullptr) throw Exception("Insufficient data, pop()");

  Node* aux(anchor);
  anchor = anchor->getNext();

  delete aux;
}

template <typename T>
T Stack<T>::top() {
  if (anchor == nullptr) throw Exception("Insufficient data, top()");

  return anchor->getData();
}

template <typename T>
void Stack<T>::deleteAll() {
  Node* aux;
  while (!isEmpty()) {
    aux = anchor;
    anchor = anchor->getNext();
    delete aux;
  }
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& copyStack) {
  deleteAll();
  Node* aux(copyStack->anchor);
  Node* last(nullptr);
  Node* newNode;

  while (aux != nullptr) {
    newNode = new Node(aux->getData());
    if (newNode == nullptr) throw Exception("\n\tOut of memory");

    if (last == nullptr)
      anchor = newNode;
    else
      last->setNext(newNode);

    last = newNode;

    aux = aux->getNext();
  }

  return *this;
}

template <typename T>
Stack<T>::~Stack() {
  deleteAll();
}