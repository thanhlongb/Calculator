//
// Created by longb on 11/25/19.
//

#ifndef CALCULATOR_NODE_H
#define CALCULATOR_NODE_H

#define MAX_DATA_SIZE   100

class Node {
public:
    char data[MAX_DATA_SIZE];
    Node(char* data);
    Node* next;
private:
};

#endif //CALCULATOR_NODE_H
