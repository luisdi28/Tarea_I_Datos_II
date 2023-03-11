#include <iostream>
#include <vector>

class Collector;

/**
 * Almacena un valor de tipo int y un puntero al siguiente, así como los respectivos métodos para
 * consultar o modificar estos datos.
 */
class Node {
public:
    int value;
    Node* next;

    /**
     *Crea el node
     * @param val
     * @param nxt
     */
    Node(int val, Node* nxt=nullptr) : value(val), next(nxt) {}


    /**
     * Se hace la sobre carga al new
     * @param size
     * @return
     */
    void* operator new(size_t size);
    /**
     * Se hace la sobre carga al delete
     * @param ptr
     */
    void operator delete(void* ptr);

    friend class Collector;
};

/**
 * La clase lista es una lista enlazada simple formada por objetos tipo Node.
 * Permite insertar elementos al inicio de la lista
 */
class List {
public:
    Node* head;

    List() : head(nullptr) {}

    /**
     * Se inserta un nuevo node al inicio de la lista
     * @param val
     */
    void insert(int val) {
        Node* new_node = new Node(val, head);
        head = new_node;
    }

    /**
     * Muestra la lista en consola con el nuevo Node
     */
    void print() {
        Node* curr = head;

        while (curr != nullptr) {
            std::cout << curr->value << " ";
            curr = curr->next;
        }
        std::cout << std::endl;
    }
};

/**
 * Clase encargada de reciclar la memoria liberada en List.
 */
class Collector {
public:
    std::vector<Node*> recycled;

    /**
     *Asigna memoria dinámica para el CPU
     * @param size
     * @return
     */
    void* allocate(size_t size) {
        if (recycled.empty()) {
            return ::operator new(size);
        } else {
            void* ptr = recycled.back();
            recycled.pop_back();
            return ptr;
        }
    }

    /**
     *Desasigna memoria dinámica para el CPU
     * @param ptr
     */
    void deallocate(void* ptr) {
        recycled.push_back(static_cast<Node*>(ptr));
    }
};

// instancia global del Collector
Collector collector;

/**
 * Se hace la sobre carga al new
 * @param size
 * @return
 */
void* Node::operator new(size_t size) {
    return collector.allocate(size);
}

/**
 * Se hace la sobre carga al delete
 * @param ptr
 */
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

    // liberar un Node y agregarlo al Collector
    Node* to_delete = l.head->next;
    l.head->next = to_delete->next;
    to_delete->next = nullptr;
    delete to_delete;

    std::cout << "List despues de eliminar un Node: ";
    l.print();

    // imprimir el estado actual del Collector
    std::cout << "Collector: ";
    for (Node* ptr : collector.recycled) {
        std::cout << ptr << " ";
    }
    std::cout << std::endl;

    // Crear un nuevo Node, reusando espacio del Collector
    l.insert(4);
    l.print();

    // imprimir el estado actual del Collector
    std::cout << "Collector despues de crear un nuevo Node: ";
    for (Node* ptr : collector.recycled) {
        std::cout << ptr << " ";
    }
    std::cout << std::endl;

    l.insert(7);
    l.print();
}
