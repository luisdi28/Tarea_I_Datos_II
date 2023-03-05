#include <iostream>
#include <vector>

class Collector;

class Node {
public:
    int value;
    Node* next;

    Node(int val, Node* nxt=nullptr) : value(val), next(nxt) {}

    // sobrecarga de new y delete
    void* operator new(size_t size);
    void operator delete(void* ptr);

    friend class Collector;
};

class List {
public:
    Node* head;

    List() : head(nullptr) {}

    void insert(int val) {
        Node* new_node = new Node(val, head);
        head = new_node;
    }

    void print() {
        Node* curr = head;
        while (curr != nullptr) {
            std::cout << curr->value << " ";
            curr = curr->next;
        }
        std::cout << std::endl;
    }
};