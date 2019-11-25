//
// Created by longb on 11/25/19.
//

#ifndef CALCULATOR_STACK_H
#define CALCULATOR_STACK_H
#include "Node.h"

class Stack {
public:
    bool isEmpty();
    char* peek();
    void push(char* data);
    char* pop();
    Stack();
private:
    Node* top;
};


#endif //CALCULATOR_STACK_H
