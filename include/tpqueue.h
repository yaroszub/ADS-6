// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

template<typename T>
class TPQueue {
 private:
  struct Node {
    T data;
    Node* next;

    explicit Node(const T& value) : data(value), next(nullptr) {}
  };

  Node* head;

 public:
  TPQueue() : head(nullptr) {}

  ~TPQueue() {
    clear();
  }

  TPQueue(const TPQueue&) = delete;
  TPQueue& operator=(const TPQueue&) = delete;

  bool empty() const {
    return head == nullptr;
  }

  void clear() {
    while (head != nullptr) {
      Node* tmp = head;
      head = head->next;
      delete tmp;
    }
  }

  void push(const T& value) {
    Node* node = new Node(value);

    if (head == nullptr || value.prior > head->data.prior) {
      node->next = head;
      head = node;
      return;
    }

    Node* cur = head;
    while (cur->next != nullptr && cur->next->data.prior >= value.prior) {
      cur = cur->next;
    }

    node->next = cur->next;
    cur->next = node;
  }

  T pop() {
    if (head == nullptr) {
      throw std::out_of_range("TPQueue is empty");
    }

    Node* tmp = head;
    T result = head->data;
    head = head->next;
    delete tmp;
    return result;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
