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

class Collector {
public:
    std::vector<Node*> recycled;

    void* allocate(size_t size) {
        if (recycled.empty()) {
            return ::operator new(size);
        } else {
            void* ptr = recycled.back();
            recycled.pop_back();
            return ptr;
        }
    }

    void deallocate(void* ptr) {
        recycled.push_back(static_cast<Node*>(ptr));
    }
};

// instancia global del Collector
Collector collector;


// sobrecarga de new y delete
void* Node::operator new(size_t size) {
    return collector.allocate(size);
}

void Node::operator delete(void* ptr) {
    collector.deallocate(ptr);
}

// ejemplo de uso
int main() {
    List l;
    l.insert(1);
    l.insert(2);
    l.insert(3);
    std::cout << "List: ";
    l.print();
}
