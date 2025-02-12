//
// Created by longb on 11/25/19.
//

#ifndef CALCULATOR_QUEUE_H
#define CALCULATOR_QUEUE_H
#include "Node.h"

class Queue {
public:
    bool isEmpty();
    char* peek();
    void enqueue(char* data);
    void dequeue();
    Queue();
private:
    Node *head;
    Node *tail;
};


#endif //CALCULATOR_QUEUE_H
