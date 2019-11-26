//
// Created by longb on 11/25/19.
//

#include "Queue.h"

Queue::Queue() {
    this->head = nullptr;
    this->tail = nullptr;
}

bool Queue::isEmpty() {
    return this->head == nullptr;
}

char* Queue::peek() {
    return this->head->data;
}

void Queue::enqueue(char *data) {
    Node* node = new Node(data);
    if (this->tail != nullptr) {
        this->tail->next = node;
    }
    this->tail = node;
    if (this->head == nullptr) {
        this->head = node;
    }
}

void Queue::dequeue() {
    Node* detachedNode = this->head;
    this->head = this->head->next;
    if (this->head == nullptr) {
        this->tail = nullptr;
    }
    delete detachedNode;
}
