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
    // FIXME: should probably delete the `this->head->next` object before detaching it
    char* data = this->top->data;
    this->top = this->top->next;
    return data;
}
