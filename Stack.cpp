//
// Created by longb on 11/25/19.
//

#include "Stack.h"

Stack::Stack() {
    this->top = nullptr;
}

bool Stack::isEmpty() {
    return this->top == nullptr;
}

char* Stack::peek() {
    return this->top->data;
}

void Stack::push(char *data) {
    Node* node = new Node(data);
    node->next = this->top;
    this->top = node;
}

char* Stack::pop() {
    Node* detachedNode = this->top;
    this->top = this->top->next;
    delete detachedNode;
}
