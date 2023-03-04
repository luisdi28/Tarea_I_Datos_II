#include <iostream>
#include <vector>

class Node {
public:
    int value;
    Node* next;

    Node(int val, Node* nxt=nullptr) : value(val), next(nxt) {}

};

class List {
public:
    Node *head;

    List() : head(nullptr) {}

    void insert(int val) {
        Node *new_node = new Node(val, head);
        head = new_node;
    }
};