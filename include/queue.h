#ifndef QUEUE_H
#define QUEUE_H

#pragma once

template <typename T>
class Queue {
 private:
  class Node {
   private:
    T* data;
    Node* next;
    Node* prev;

   public:
    Node();
    Node(T element);

    T getData();
    T* getDataPtr();
    Node* getNext();
    Node* getPrev();

    void setData(const T& data);
    void setDataPtr(T* data);
    void setNext(Node* next);
    void setPrev(Node* prev);

    ~Node();

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

 public:
  Queue();
  Queue(Queue& copyQueue);
  ~Queue();

  bool isEmpty();
  void enqueue(T element);
  void dequeue();
  T front();

  Queue& operator=(const Queue& queueCopy);

 private:
  Node* header;
  void deleteAll();
};

#endif

template <typename T>
Queue<T>::Node::Node() : next(nullptr), prev(nullptr), data(nullptr) {}

template <typename T>
Queue<T>::Node::Node(T element) {
  next = nullptr;
  prev = nullptr;
  data = new T(element);
  if (data == nullptr) throw Exception("Not enought memory");
}

template <typename T>
T Queue<T>::Node::getData() {
  if (data == nullptr) throw Exception("Non existent data, getData");
  return *data;
}

template <typename T>
T* Queue<T>::Node::getDataPtr() {
  return data;
}

template <typename T>
typename Queue<T>::Node* Queue<T>::Node::getNext() {
  return next;
}

template <typename T>
typename Queue<T>::Node* Queue<T>::Node::getPrev() {
  return prev;
}

template <typename T>
void Queue<T>::Node::setData(const T& data) {
  if (data == nullptr) {
    // Tries to create a new data, if it isn't capable of creating it
    // then rises an exception
    if ((data = new T(data)) == nullptr)
      throw Exception("Non available memory, setData");
  } else
    *data = data;
}

template <typename T>
void Queue<T>::Node::setDataPtr(T* data) {
  this->data = data;
}

template <typename T>
void Queue<T>::Node::setNext(Node* next) {
  this->next = next;
}

template <typename T>
void Queue<T>::Node::setPrev(Node* prev) {
  this->prev = prev;
}

template <typename T>
Queue<T>::Node::~Node() {
  delete data;
}

template <typename T>
Queue<T>::Queue() {
  header = new Node();
  header->setPrev(header);
  header->setNext(header);
}

template <typename T>
bool Queue<T>::isEmpty() {
  return header->getNext() == header;
}

template <typename T>
void Queue<T>::enqueue(T element) {
  Node* aux;
  try {
    if ((aux = new Node(element)) == nullptr) {
      throw Exception("Unavailable memory, enqueue()");
    }
  } catch (typename Node::Exception ex) {
    throw Exception(ex.what());
  }

  aux->setPrev(header->getPrev());
  aux->setNext(header);

  header->getPrev()->setNext(aux);
  header->setPrev(aux);
}

template <typename T>
void Queue<T>::dequeue() {
  if (isEmpty()) throw Exception("Queue is empty, dequeue()");

  Node* aux(header->getNext());

  aux->getPrev()->setNext(aux->getNext());

  aux->getNext()->setPrev(aux->getPrev());

  delete aux;
}

template <typename T>
T Queue<T>::front() {
  if (isEmpty()) throw Exception("Queue is empty, dequeue()");

  return header->getNext()->getData();
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& copyQueue) {
  deleteAll();
  Node* aux(copyQueue.header->getNext());
  Node* newNode;

  while (aux != copyQueue.header) {
    try {
      if ((newNode = new Node(aux->getData())) == nullptr) {
        throw Exception("Non available memory, operator = ");
      }
    } catch (typename Node::Exception ex) {
      throw Exception(ex.what());
    }

    newNode->setPrev(header->getPrev());
    newNode->setNext(header);

    header->getPrev()->setNext(newNode);
    header->setPrev(newNode);
    aux = aux->getNext();
  }

  return *this;
}

template <typename T>
Queue<T>::~Queue() {
  deleteAll();
}

template <typename T>
void Queue<T>::deleteAll() {
  Node* aux;
  while (!isEmpty()) {
    aux = header->getNext();
    header->setNext(aux->getNext());
    delete aux;
  }
  header->setPrev(header);
}
