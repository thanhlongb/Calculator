//
// Created by longb on 11/25/19.
//

#include "Node.h"

Node::Node(char* data) {
    // FIXME: probably loop for 100 chars -> not optimize
    // check this
    // strcpy() equivalent:
    this->next = nullptr;
    for (int i = 0; i < sizeof(data); i++) {
        this->data[i] = *(data + i);
    }
}